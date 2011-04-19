#include "qemu-timer.h"

#include "gnat-bus.h"
#include "trace.h"

static inline int gnatbus_process_setIRQ(GnatBus_Device       *qbdev,
                                         GnatBusPacket_SetIRQ *setIRQ)
{
    trace_gnatbus_setirq(setIRQ->line, setIRQ->level);

    if (setIRQ->line > qbdev->master->nr_irq) {
        fprintf(stderr, "%s: Invalid IRQ line: %d\n", __func__, setIRQ->line);
        return -1;
    }

    switch (setIRQ->level) {
    case 0:
        qemu_irq_lower(qbdev->master->cpu_irqs[setIRQ->line]);
        break;
    case 1:
        qemu_irq_raise(qbdev->master->cpu_irqs[setIRQ->line]);
        break;
    case 2:
        qemu_irq_pulse(qbdev->master->cpu_irqs[setIRQ->line]);
        break;
    default:
        fprintf(stderr, "%s: Unknown IRQ level (%d)\n",
                __func__, setIRQ->level);
        return -1;
        break;
    }
    return 0;
}

static inline int gnatbus_process_registerevent(GnatBus_Device              *qbdev,
                                                GnatBusPacket_RegisterEvent *event)
{
    trace_gnatbus_registerevent(event->expire_time, event->event);

    gnatbus_add_event(qbdev, event->expire_time, event->event_id, event->event);
    return 0;
}


static inline int gnatbus_process_event(GnatBus_Device      *qbdev,
                                        GnatBusPacket_Event *event)
{
    switch (event->type) {
    case GnatBusEvent_SetIRQ:
        return gnatbus_process_setIRQ(qbdev, (GnatBusPacket_SetIRQ *)event);
        break;

    case GnatBusEvent_RegisterEvent:
        return gnatbus_process_registerevent(qbdev, (GnatBusPacket_RegisterEvent *)event);
        break;

    default:
        fprintf(stderr, "%s: Unknown event type (%d)\n",
                __func__, event->type);
        return -1;
        break;
    }
}

/* Response */

static void gnatbus_resp_error(GnatBus_Device *qbdev,
                               uint32_t        request_id,
                               uint32_t        error_code)
{
    GnatBusPacket_Error err;

    trace_gnatbus_resp_error(request_id, error_code);

    GnatBusPacket_Error_Init(&err);

    err.parent.id  = request_id;
    err.error_code = error_code;

    gnatbus_send(qbdev, (uint8_t *)&err, sizeof(err));
}

/* Request */

static inline int gnatbus_process_read(GnatBus_Device     *qbdev,
                                       GnatBusPacket_Read *read)
{
    GnatBusPacket_Data *resp;

    trace_gnatbus_process_read(read->address, read->length);

    /* Allocate packet + data */
    resp = qemu_malloc(sizeof(GnatBusPacket_Data) + read->length);

    GnatBusPacket_Data_Init(resp);
    resp->parent.parent.size = sizeof(GnatBusPacket_Data) + read->length;
    resp->parent.id          = read->parent.id;
    resp->length             = read->length;

    cpu_physical_memory_read(read->address, resp->data, read->length);

    gnatbus_send(qbdev, (uint8_t *)resp, sizeof(GnatBusPacket_Data) + read->length);
    qemu_free(resp);
    return 0;
}

static inline int gnatbus_process_write(GnatBus_Device      *qbdev,
                                        GnatBusPacket_Write *write)
{
    trace_gnatbus_process_write(write->address, write->length);

    cpu_physical_memory_write(write->address, write->data, write->length);

    gnatbus_resp_error(qbdev, write->parent.id, 0);
    return 0;
}

extern CPUReadMemoryFunc * const  gnatbus_read_fn[];
extern CPUWriteMemoryFunc * const gnatbus_write_fn[];

static int gnatbus_init_device(SysBusDevice *dev)
{
    GnatBus_SysBusDevice *pdev  = FROM_SYSBUS(typeof(*pdev), dev);
    GnatBus_Device       *qbdev = pdev->qbdev;
    int                   ioindex;
    int                   i;



    for (i = 0; i < pdev->qbdev->info.nr_iomem; i++) {
        qbdev->io_base[i].qbdev = qbdev;
        qbdev->io_base[i].base  = qbdev->info.iomem[i].base & TARGET_PAGE_MASK;

        ioindex = cpu_register_io_memory(gnatbus_read_fn,
                                         gnatbus_write_fn,
                                         &qbdev->io_base[i],
                                         DEVICE_NATIVE_ENDIAN);

        if (ioindex <= 0) {
            return -1;
        }

        sysbus_init_mmio(dev, qbdev->info.iomem[i].size, ioindex);
        sysbus_mmio_map(dev, i, qbdev->info.iomem[i].base);
    }

    return 0;
}

static inline int gnatbus_process_register(GnatBus_Device         *qbdev,
                                           GnatBusPacket_Register *reg)
{
    /* printf("GnatBus: Received Register request from: '%s'\n", reg->name); */

    DeviceState          *qdev;
    GnatBus_SysBusDevice *pdev;

    trace_gnatbus_process_register(reg->name);

    if (reg->bus_version != GNATBUS_VERSION) {
        fprintf(stderr, "%s: GNATBUS_VERSION mismatch qemu:%d device:%d\n",
                __func__, GNATBUS_VERSION, reg->bus_version);
        return -1;
    }

    sysbus_register_dev(reg->name, sizeof(*pdev), gnatbus_init_device);

    qdev = qdev_create(NULL, reg->name);
    pdev = (typeof(pdev))qdev;

    pdev->qbdev = qbdev;
    memcpy (&qbdev->info, reg, sizeof(*reg));

    if (qdev_init(qdev)) {
        gnatbus_resp_error(qbdev, reg->parent.id, 1);
        return -1;
    }

    qbdev->start_ok = 1;
    QLIST_INSERT_HEAD(&qbdev->master->devices_list, qbdev, list);
    gnatbus_resp_error(qbdev, reg->parent.id, 0);
    return 0;
}

static inline int gnatbus_process_gettime(GnatBus_Device        *qbdev,
                                          GnatBusPacket_GetTime *gettime)
{
    GnatBusPacket_Time time;

    GnatBusPacket_Time_Init(&time);

    time.parent.id = gettime->parent.id;
    time.time      = qemu_get_clock_ns(vm_clock);

    trace_gnatbus_process_gettime(time.time);

    gnatbus_send(qbdev, (uint8_t *)&time, sizeof(time));
    return 0;
}

static inline int gnatbus_process_request(GnatBus_Device        *qbdev,
                                          GnatBusPacket_Request *request)
{
    switch (request->type) {
    case GnatBusRequest_Register:
        return gnatbus_process_register(qbdev, (GnatBusPacket_Register *)request);
        break;

    case GnatBusRequest_Read:
        return gnatbus_process_read(qbdev, (GnatBusPacket_Read *)request);
        break;

    case GnatBusRequest_Write:
        return gnatbus_process_write(qbdev, (GnatBusPacket_Write *)request);
        break;

    case GnatBusRequest_GetTime:
        return gnatbus_process_gettime(qbdev, (GnatBusPacket_GetTime *)request);
        break;

    default:
        fprintf(stderr, "%s: Unknown request type (%d)\n",
                __func__, request->type);
        gnatbus_resp_error(qbdev, request->id, 1);
        return -1;
        break;
    }
}

int gnatbus_process_packet(GnatBus_Device *qbdev,
                           GnatBusPacket  *packet)
{
    switch (packet->type) {
    case GnatBus_Event:
        return gnatbus_process_event(qbdev, (GnatBusPacket_Event *)packet);
        break;
    case GnatBus_Request:
        return gnatbus_process_request(qbdev, (GnatBusPacket_Request *)packet);
        break;
    default:
        fprintf(stderr, "%s: Unknown packet type (%d)\n",
                __func__, packet->type);
        return -1;
        break;
    }
}
