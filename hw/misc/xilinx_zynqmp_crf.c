/*
 * QEMU model of the CRF_APB APB control registers for clock controller. The
 * RST_ctrl_fpd will be added to this as well
 *
 * Copyright (c) 2014 Xilinx Inc.
 *
 * Autogenerated by xregqemu.py 2014-01-22.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "qemu/osdep.h"
#include "hw/sysbus.h"
#include "hw/register.h"
#include "qemu/bitops.h"
#include "qemu/log.h"
#include "qemu/qemu-clock.h"
#include "hw/irq.h"
#include "migration/vmstate.h"

#ifndef XILINX_CRF_APB_ERR_DEBUG
#define XILINX_CRF_APB_ERR_DEBUG 0
#endif

#define TYPE_XILINX_CRF_APB "xlnx.zynqmp_crf"

#define XILINX_CRF_APB(obj) \
     OBJECT_CHECK(CRF_APB, (obj), TYPE_XILINX_CRF_APB)

REG32(ERR_CTRL, 0x0)
    FIELD(ERR_CTRL, SLVERR_ENABLE, 0, 1)
REG32(IR_STATUS, 0x4)
    FIELD(IR_STATUS, ADDR_DECODE_ERR, 0, 1)
REG32(IR_MASK, 0x8)
    FIELD(IR_MASK, ADDR_DECODE_ERR, 0, 1)
REG32(IR_ENABLE, 0xc)
    FIELD(IR_ENABLE, ADDR_DECODE_ERR, 0, 1)
REG32(IR_DISABLE, 0x10)
    FIELD(IR_DISABLE, ADDR_DECODE_ERR, 0, 1)
REG32(CRF_ECO, 0x18)
REG32(APLL_CTRL, 0x20)
    FIELD(APLL_CTRL, POST_SRC, 24, 3)
    FIELD(APLL_CTRL, PRE_SRC, 20, 3)
    FIELD(APLL_CTRL, CLKOUTDIV, 17, 1)
    FIELD(APLL_CTRL, DIV2, 16, 1)
    FIELD(APLL_CTRL, FBDIV, 8, 7)
    FIELD(APLL_CTRL, BYPASS, 3, 1)
    FIELD(APLL_CTRL, RESET, 0, 1)
REG32(APLL_CFG, 0x24)
    FIELD(APLL_CFG, LOCK_DLY, 25, 7)
    FIELD(APLL_CFG, LOCK_CNT, 13, 10)
    FIELD(APLL_CFG, LFHF, 10, 2)
    FIELD(APLL_CFG, CP, 5, 4)
    FIELD(APLL_CFG, RES, 0, 4)
REG32(APLL_FRAC_CFG, 0x28)
    FIELD(APLL_FRAC_CFG, ENABLED, 31, 1)
    FIELD(APLL_FRAC_CFG, SEED, 22, 3)
    FIELD(APLL_FRAC_CFG, ALGRTHM, 19, 1)
    FIELD(APLL_FRAC_CFG, ORDER, 18, 1)
    FIELD(APLL_FRAC_CFG, DATA, 0, 16)
REG32(DPLL_CTRL, 0x2c)
    FIELD(DPLL_CTRL, POST_SRC, 24, 3)
    FIELD(DPLL_CTRL, PRE_SRC, 20, 3)
    FIELD(DPLL_CTRL, CLKOUTDIV, 17, 1)
    FIELD(DPLL_CTRL, DIV2, 16, 1)
    FIELD(DPLL_CTRL, FBDIV, 8, 7)
    FIELD(DPLL_CTRL, BYPASS, 3, 1)
    FIELD(DPLL_CTRL, RESET, 0, 1)
REG32(DPLL_CFG, 0x30)
    FIELD(DPLL_CFG, LOCK_DLY, 25, 7)
    FIELD(DPLL_CFG, LOCK_CNT, 13, 10)
    FIELD(DPLL_CFG, LFHF, 10, 2)
    FIELD(DPLL_CFG, CP, 5, 4)
    FIELD(DPLL_CFG, RES, 0, 4)
REG32(DPLL_FRAC_CFG, 0x34)
    FIELD(DPLL_FRAC_CFG, ENABLED, 31, 1)
    FIELD(DPLL_FRAC_CFG, SEED, 22, 3)
    FIELD(DPLL_FRAC_CFG, ALGRTHM, 19, 1)
    FIELD(DPLL_FRAC_CFG, ORDER, 18, 1)
    FIELD(DPLL_FRAC_CFG, DATA, 0, 16)
REG32(VPLL_CTRL, 0x38)
    FIELD(VPLL_CTRL, POST_SRC, 24, 3)
    FIELD(VPLL_CTRL, PRE_SRC, 20, 3)
    FIELD(VPLL_CTRL, CLKOUTDIV, 17, 1)
    FIELD(VPLL_CTRL, DIV2, 16, 1)
    FIELD(VPLL_CTRL, FBDIV, 8, 7)
    FIELD(VPLL_CTRL, BYPASS, 3, 1)
    FIELD(VPLL_CTRL, RESET, 0, 1)
REG32(VPLL_CFG, 0x3c)
    FIELD(VPLL_CFG, LOCK_DLY, 25, 7)
    FIELD(VPLL_CFG, LOCK_CNT, 13, 10)
    FIELD(VPLL_CFG, LFHF, 10, 2)
    FIELD(VPLL_CFG, CP, 5, 4)
    FIELD(VPLL_CFG, RES, 0, 4)
REG32(VPLL_FRAC_CFG, 0x40)
    FIELD(VPLL_FRAC_CFG, ENABLED, 31, 1)
    FIELD(VPLL_FRAC_CFG, SEED, 22, 3)
    FIELD(VPLL_FRAC_CFG, ALGRTHM, 19, 1)
    FIELD(VPLL_FRAC_CFG, ORDER, 18, 1)
    FIELD(VPLL_FRAC_CFG, DATA, 0, 16)
REG32(PLL_STATUS, 0x44)
    FIELD(PLL_STATUS, VPLL_STABLE, 5, 1)
    FIELD(PLL_STATUS, DPLL_STABLE, 4, 1)
    FIELD(PLL_STATUS, APLL_STABLE, 3, 1)
    FIELD(PLL_STATUS, VPLL_LOCK, 2, 1)
    FIELD(PLL_STATUS, DPLL_LOCK, 1, 1)
    FIELD(PLL_STATUS, APLL_LOCK, 0, 1)
REG32(APLL_TO_LPD_CTRL, 0x48)
    FIELD(APLL_TO_LPD_CTRL, DIVISOR0, 8, 6)
REG32(DPLL_TO_LPD_CTRL, 0x4c)
    FIELD(DPLL_TO_LPD_CTRL, DIVISOR0, 8, 6)
REG32(VPLL_TO_LPD_CTRL, 0x50)
    FIELD(VPLL_TO_LPD_CTRL, DIVISOR0, 8, 6)
REG32(CPU_A9_CTRL, 0x60)
    FIELD(CPU_A9_CTRL, A9CLKSTOP, 26, 2)
    FIELD(CPU_A9_CTRL, CLKACT_HALF, 25, 1)
    FIELD(CPU_A9_CTRL, CLKACT_FULL, 24, 1)
    FIELD(CPU_A9_CTRL, DIVISOR0, 8, 6)
    FIELD(CPU_A9_CTRL, SRCSEL, 0, 3)
REG32(DBG_TRACE_CTRL, 0x64)
    FIELD(DBG_TRACE_CTRL, CLKACT, 24, 1)
    FIELD(DBG_TRACE_CTRL, DIVISOR0, 8, 6)
    FIELD(DBG_TRACE_CTRL, SRCSEL, 0, 3)
REG32(DBG_FPD_CTRL, 0x68)
    FIELD(DBG_FPD_CTRL, CLKACT, 24, 1)
    FIELD(DBG_FPD_CTRL, DIVISOR0, 8, 6)
    FIELD(DBG_FPD_CTRL, SRCSEL, 0, 3)
REG32(DP_VIDEO_REF_CTRL, 0x70)
    FIELD(DP_VIDEO_REF_CTRL, CLKACT, 24, 1)
    FIELD(DP_VIDEO_REF_CTRL, DIVISOR0, 8, 6)
    FIELD(DP_VIDEO_REF_CTRL, SRCSEL, 0, 3)
REG32(DP_AUDIO_REF_CTRL, 0x74)
    FIELD(DP_AUDIO_REF_CTRL, CLKACT, 24, 1)
    FIELD(DP_AUDIO_REF_CTRL, DIVISOR0, 8, 6)
    FIELD(DP_AUDIO_REF_CTRL, SRCSEL, 0, 3)
REG32(DP_LINK_REF_CTRL, 0x78)
    FIELD(DP_LINK_REF_CTRL, CLKACT, 24, 1)
    FIELD(DP_LINK_REF_CTRL, DIVISOR1, 16, 6)
    FIELD(DP_LINK_REF_CTRL, DIVISOR0, 8, 6)
    FIELD(DP_LINK_REF_CTRL, SRCSEL, 0, 3)
REG32(DP_STC_REF_CTRL, 0x7c)
    FIELD(DP_STC_REF_CTRL, CLKACT, 24, 1)
    FIELD(DP_STC_REF_CTRL, DIVISOR1, 16, 6)
    FIELD(DP_STC_REF_CTRL, DIVISOR0, 8, 6)
    FIELD(DP_STC_REF_CTRL, SRCSEL, 0, 3)
REG32(DDR_CTRL, 0x80)
    FIELD(DDR_CTRL, CLKACT, 24, 1)
    FIELD(DDR_CTRL, DIVISOR0, 8, 6)
    FIELD(DDR_CTRL, SRCSEL, 0, 3)
REG32(GPU_REF_CTRL, 0x84)
    FIELD(GPU_REF_CTRL, PP1_CLKACT, 26, 1)
    FIELD(GPU_REF_CTRL, PP0_CLKACT, 25, 1)
    FIELD(GPU_REF_CTRL, CLKACT, 24, 1)
    FIELD(GPU_REF_CTRL, DIVISOR0, 8, 6)
    FIELD(GPU_REF_CTRL, SRCSEL, 0, 3)
REG32(AFI0_REF_CTRL, 0x88)
    FIELD(AFI0_REF_CTRL, CLKACT, 24, 1)
    FIELD(AFI0_REF_CTRL, DIVISOR0, 8, 6)
    FIELD(AFI0_REF_CTRL, SRCSEL, 0, 3)
REG32(AFI1_REF_CTRL, 0x8c)
    FIELD(AFI1_REF_CTRL, CLKACT, 24, 1)
    FIELD(AFI1_REF_CTRL, DIVISOR0, 8, 6)
    FIELD(AFI1_REF_CTRL, SRCSEL, 0, 3)
REG32(AFI2_REF_CTRL, 0x90)
    FIELD(AFI2_REF_CTRL, CLKACT, 24, 1)
    FIELD(AFI2_REF_CTRL, DIVISOR0, 8, 6)
    FIELD(AFI2_REF_CTRL, SRCSEL, 0, 3)
REG32(AFI3_REF_CTRL, 0x94)
    FIELD(AFI3_REF_CTRL, CLKACT, 24, 1)
    FIELD(AFI3_REF_CTRL, DIVISOR0, 8, 6)
    FIELD(AFI3_REF_CTRL, SRCSEL, 0, 3)
REG32(AFI4_REF_CTRL, 0x98)
    FIELD(AFI4_REF_CTRL, CLKACT, 24, 1)
    FIELD(AFI4_REF_CTRL, DIVISOR0, 8, 6)
    FIELD(AFI4_REF_CTRL, SRCSEL, 0, 3)
REG32(AFI5_REF_CTRL, 0x9c)
    FIELD(AFI5_REF_CTRL, CLKACT, 24, 1)
    FIELD(AFI5_REF_CTRL, DIVISOR0, 8, 6)
    FIELD(AFI5_REF_CTRL, SRCSEL, 0, 3)
REG32(SATA_REF_CTRL, 0xa0)
    FIELD(SATA_REF_CTRL, CLKACT, 24, 1)
    FIELD(SATA_REF_CTRL, DIVISOR0, 8, 6)
    FIELD(SATA_REF_CTRL, SRCSEL, 0, 3)
REG32(PCIE_REF_CTRL, 0xb4)
    FIELD(PCIE_REF_CTRL, CLKACT, 24, 1)
    FIELD(PCIE_REF_CTRL, DIVISOR0, 8, 6)
    FIELD(PCIE_REF_CTRL, SRCSEL, 0, 3)
REG32(GDMA_REF_CTRL, 0xb8)
    FIELD(GDMA_REF_CTRL, CLKACT, 24, 1)
    FIELD(GDMA_REF_CTRL, DIVISOR0, 8, 6)
    FIELD(GDMA_REF_CTRL, SRCSEL, 0, 3)
REG32(DPDMA_REF_CTRL, 0xbc)
    FIELD(DPDMA_REF_CTRL, CLKACT, 24, 1)
    FIELD(DPDMA_REF_CTRL, DIVISOR0, 8, 6)
    FIELD(DPDMA_REF_CTRL, SRCSEL, 0, 3)
REG32(TOPSW_MAIN_CTRL, 0xc0)
    FIELD(TOPSW_MAIN_CTRL, CLKACT, 24, 1)
    FIELD(TOPSW_MAIN_CTRL, DIVISOR0, 8, 6)
    FIELD(TOPSW_MAIN_CTRL, SRCSEL, 0, 3)
REG32(TOPSW_LSBUS_CTRL, 0xc4)
    FIELD(TOPSW_LSBUS_CTRL, CLKACT, 24, 1)
    FIELD(TOPSW_LSBUS_CTRL, DIVISOR0, 8, 6)
    FIELD(TOPSW_LSBUS_CTRL, SRCSEL, 0, 3)
REG32(GTGREF0_REF_CTRL, 0xc8)
    FIELD(GTGREF0_REF_CTRL, CLKACT, 24, 1)
    FIELD(GTGREF0_REF_CTRL, DIVISOR0, 8, 6)
    FIELD(GTGREF0_REF_CTRL, SRCSEL, 0, 3)
REG32(GTGREF1_REF_CTRL, 0xcc)
    FIELD(GTGREF1_REF_CTRL, CLKACT, 24, 1)
    FIELD(GTGREF1_REF_CTRL, DIVISOR0, 8, 6)
    FIELD(GTGREF1_REF_CTRL, SRCSEL, 0, 3)
REG32(DFT300_REF_CTRL, 0xd0)
    FIELD(DFT300_REF_CTRL, CLKACT, 24, 1)
    FIELD(DFT300_REF_CTRL, DIVISOR0, 8, 6)
    FIELD(DFT300_REF_CTRL, SRCSEL, 0, 3)
REG32(DFT270_REF_CTRL, 0xd4)
    FIELD(DFT270_REF_CTRL, CLKACT, 24, 1)
    FIELD(DFT270_REF_CTRL, DIVISOR0, 8, 6)
    FIELD(DFT270_REF_CTRL, SRCSEL, 0, 3)
REG32(DFT250_REF_CTRL, 0xd8)
    FIELD(DFT250_REF_CTRL, CLKACT, 24, 1)
    FIELD(DFT250_REF_CTRL, DIVISOR0, 8, 6)
    FIELD(DFT250_REF_CTRL, SRCSEL, 0, 3)
REG32(DFT125_REF_CTRL, 0xdc)
    FIELD(DFT125_REF_CTRL, CLKACT, 24, 1)
    FIELD(DFT125_REF_CTRL, DIVISOR0, 8, 6)
    FIELD(DFT125_REF_CTRL, SRCSEL, 0, 3)

REG32(RST_FPD_TOP, 0x100)
    FIELD(RST_FPD_TOP, PCIE_BRDG_RESET, 18, 1)
    FIELD(RST_FPD_TOP, PCIE_CTRL_RESET, 17, 1)
    FIELD(RST_FPD_TOP, DP_RESET, 16, 1)
    FIELD(RST_FPD_TOP, AFI_FM5_RESET, 12, 1)
    FIELD(RST_FPD_TOP, AFI_FM4_RESET, 11, 1)
    FIELD(RST_FPD_TOP, AFI_FM3_RESET, 10, 1)
    FIELD(RST_FPD_TOP, AFI_FM2_RESET, 9, 1)
    FIELD(RST_FPD_TOP, AFI_FM1_RESET, 8, 1)
    FIELD(RST_FPD_TOP, AFI_FM0_RESET, 7, 1)
    FIELD(RST_FPD_TOP, GDMA_RESET, 6, 1)
    FIELD(RST_FPD_TOP, GPU_PP1_RESET, 5, 1)
    FIELD(RST_FPD_TOP, GPU_PP0_RESET, 4, 1)
    FIELD(RST_FPD_TOP, GPU_RESET, 3, 1)
    FIELD(RST_FPD_TOP, GT_RESET, 2, 1)
    FIELD(RST_FPD_TOP, SATA_RESET, 1, 1)
REG32(RST_FPD_APU, 0x104)
    FIELD(RST_FPD_APU, PERI_RESET, 13, 1)
    FIELD(RST_FPD_APU, SCU_RESET, 12, 1)
    FIELD(RST_FPD_APU, CPU1_AWDT_RESET, 9, 1)
    FIELD(RST_FPD_APU, CPU0_AWDT_RESET, 8, 1)
    FIELD(RST_FPD_APU, CPU1_CP14_RESET, 5, 1)
    FIELD(RST_FPD_APU, CPU0_CP14_RESET, 4, 1)
    FIELD(RST_FPD_APU, CPU3_A9_RESET, 3, 1)
    FIELD(RST_FPD_APU, CPU2_A9_RESET, 2, 1)
    FIELD(RST_FPD_APU, CPU1_A9_RESET, 1, 1)
    FIELD(RST_FPD_APU, CPU0_A9_RESET, 0, 1)
REG32(RST_DDR_SS, 0x108)
    FIELD(RST_DDR_SS, DDR_RESET, 3, 1)
    FIELD(RST_DDR_SS, APM_RESET, 2, 1)
    FIELD(RST_DDR_SS, QOS_RESET, 1, 1)
    FIELD(RST_DDR_SS, XMPU_RESET, 0, 1)

#define R_MAX (R_RST_DDR_SS + 1)

typedef struct CRF_APB {
    SysBusDevice parent_obj;
    MemoryRegion iomem;
    qemu_irq irq_ir;

    uint32_t regs[R_MAX];
    RegisterInfo regs_info[R_MAX];

    /* input clocks */
    QEMUClock *pss_ref_clk;
    QEMUClock *video_clk;
    QEMUClock *pss_alt_ref_clk;
    QEMUClock *aux_refclk;
    QEMUClock *gt_crx_ref_clk;

    /* internal clocks */
    QEMUClock *apll_clk;
    QEMUClock *dpll_clk;
    QEMUClock *vpll_clk;

    /* output clocks */
    QEMUClock *acpu_clk;
    QEMUClock *dbg_trace;
    QEMUClock *dbg_fdp;
    QEMUClock *dp_video_ref;
    QEMUClock *dp_audio_ref;
    QEMUClock *dp_stc_ref;
    QEMUClock *ddr;
    QEMUClock *gpu_ref;
    QEMUClock *sata_ref;
    QEMUClock *pcie_ref;
    QEMUClock *gdma_ref;
    QEMUClock *dpdma_ref;
    QEMUClock *topsw_main;
    QEMUClock *topsw_lsbus;
    QEMUClock *dbg_tstmp;
    QEMUClock *apll_to_lpd;
    QEMUClock *dpll_to_lpd;
    QEMUClock *vpll_to_lpd;
} CRF_APB;

static uint64_t apll_to_lpd_update_rate(void *opaque, uint64_t input_rate);
static uint64_t dpll_to_lpd_update_rate(void *opaque, uint64_t input_rate);
static uint64_t vpll_to_lpd_update_rate(void *opaque, uint64_t input_rate);
static uint64_t apll_update_rate(void *opaque, uint64_t input_rate);
static uint64_t dpll_update_rate(void *opaque, uint64_t input_rate);
static uint64_t vpll_update_rate(void *opaque, uint64_t input_rate);
static uint64_t dp_video_update_rate(void *opaque, uint64_t input_rate);

/* Clock array */
ClockInitElement crf_clock[] = {
    /* input clocks */
    DEVICE_CLOCK(CRF_APB, pss_ref_clk, NULL),
    DEVICE_CLOCK(CRF_APB, video_clk, NULL),
    DEVICE_CLOCK(CRF_APB, pss_alt_ref_clk, NULL),
    DEVICE_CLOCK(CRF_APB, aux_refclk, NULL),
    DEVICE_CLOCK(CRF_APB, gt_crx_ref_clk, NULL),
    /* internal clocks */
    DEVICE_CLOCK(CRF_APB, apll_clk, apll_update_rate),
    DEVICE_CLOCK(CRF_APB, dpll_clk, dpll_update_rate),
    DEVICE_CLOCK(CRF_APB, vpll_clk, vpll_update_rate),
    /* output clocks */
    DEVICE_CLOCK(CRF_APB, acpu_clk, NULL),
    DEVICE_CLOCK(CRF_APB, dbg_trace,  NULL),
    DEVICE_CLOCK(CRF_APB, dbg_fdp, NULL),
    DEVICE_CLOCK(CRF_APB, dp_video_ref, dp_video_update_rate),
    DEVICE_CLOCK(CRF_APB, dp_audio_ref, NULL),
    DEVICE_CLOCK(CRF_APB, dp_stc_ref, NULL),
    DEVICE_CLOCK(CRF_APB, ddr, NULL),
    DEVICE_CLOCK(CRF_APB, gpu_ref, NULL),
    DEVICE_CLOCK(CRF_APB, sata_ref, NULL),
    DEVICE_CLOCK(CRF_APB, pcie_ref, NULL),
    DEVICE_CLOCK(CRF_APB, gdma_ref, NULL),
    DEVICE_CLOCK(CRF_APB, dpdma_ref, NULL),
    DEVICE_CLOCK(CRF_APB, topsw_main, NULL),
    DEVICE_CLOCK(CRF_APB, topsw_lsbus, NULL),
    DEVICE_CLOCK(CRF_APB, dbg_tstmp, NULL),
    DEVICE_CLOCK(CRF_APB, apll_to_lpd, apll_to_lpd_update_rate),
    DEVICE_CLOCK(CRF_APB, dpll_to_lpd, dpll_to_lpd_update_rate),
    DEVICE_CLOCK(CRF_APB, vpll_to_lpd, vpll_to_lpd_update_rate),
    DEVICE_CLOCK_END()
};

static const MemoryRegionOps crf_apb_ops = {
    .read = register_read_memory,
    .write = register_write_memory,
    .endianness = DEVICE_LITTLE_ENDIAN,
    .valid = {
        .min_access_size = 4,
        .max_access_size = 4,
    },
};

static void ir_update_irq(CRF_APB *s)
{
    bool pending = s->regs[R_IR_STATUS] & ~s->regs[R_IR_MASK];
    qemu_set_irq(s->irq_ir, pending);
}

static void ir_status_postw(RegisterInfo *reg, uint64_t val64)
{
    CRF_APB *s = XILINX_CRF_APB(reg->opaque);
    ir_update_irq(s);
}

static uint64_t ir_enable_prew(RegisterInfo *reg, uint64_t val64)
{
    CRF_APB *s = XILINX_CRF_APB(reg->opaque);
    uint32_t val = val64;

    s->regs[R_IR_MASK] &= ~val;
    ir_update_irq(s);
    return 0;
}

static uint64_t ir_disable_prew(RegisterInfo *reg, uint64_t val64)
{
    CRF_APB *s = XILINX_CRF_APB(reg->opaque);
    uint32_t val = val64;

    s->regs[R_IR_MASK] |= val;
    ir_update_irq(s);
    return 0;
}

enum clk_src {
    VIDEO_CLK = 4,
    PSS_ALT_REF_CLK = 5,
    AUX_REF_CLK = 6,
    GT_CRX_REF_CLK = 7,
    PSS_REF_CLK = 0
};

static void apll_to_lpd_postw(RegisterInfo *reg, uint64_t val64)
{
    CRF_APB *s = XILINX_CRF_APB(reg->opaque);

    qemu_clk_refresh(s->apll_to_lpd);
}

static uint64_t apll_to_lpd_update_rate(void *opaque, uint64_t input_rate)
{
    CRF_APB *s = XILINX_CRF_APB(opaque);
    uint32_t divisor = FIELD_EX32(s->regs[R_APLL_TO_LPD_CTRL],
                                  APLL_TO_LPD_CTRL,
                                  DIVISOR0);

    if (!divisor) {
        return 0.0f;
    } else {
        return input_rate / (float)divisor;
    }
}

static void dpll_to_lpd_postw(RegisterInfo *reg, uint64_t val64)
{
    CRF_APB *s = XILINX_CRF_APB(reg->opaque);

    qemu_clk_refresh(s->dpll_to_lpd);
}

static uint64_t dpll_to_lpd_update_rate(void *opaque, uint64_t input_rate)
{
    CRF_APB *s = XILINX_CRF_APB(opaque);
    uint32_t divisor = FIELD_EX32(s->regs[R_DPLL_TO_LPD_CTRL],
                                  DPLL_TO_LPD_CTRL,
                                  DIVISOR0);

    if (!divisor) {
        return 0.0f;
    } else {
        return input_rate / (float)divisor;
    }
}

static void vpll_to_lpd_postw(RegisterInfo *reg, uint64_t val64)
{
    CRF_APB *s = XILINX_CRF_APB(reg->opaque);

    qemu_clk_refresh(s->vpll_to_lpd);
}

static uint64_t vpll_to_lpd_update_rate(void *opaque, uint64_t input_rate)
{
    CRF_APB *s = XILINX_CRF_APB(opaque);
    uint32_t divisor = FIELD_EX32(s->regs[R_VPLL_TO_LPD_CTRL],
                                  VPLL_TO_LPD_CTRL, DIVISOR0);

    if (!divisor) {
        return 0;
    } else {
        return input_rate / (float)divisor;
    }
}

static void apll_ctrl_postw(RegisterInfo *reg, uint64_t val64)
{
    CRF_APB *s = XILINX_CRF_APB(reg->opaque);
    uint32_t source = FIELD_EX32(s->regs[R_APLL_CTRL], APLL_CTRL, BYPASS)
                    ? FIELD_EX32(s->regs[R_APLL_CTRL], APLL_CTRL, POST_SRC)
                    : FIELD_EX32(s->regs[R_APLL_CTRL], APLL_CTRL, PRE_SRC);

    /*
     * We must ensure that only one clock is bound to the apll internal clock.
     */
    qemu_clk_unbind(s->pss_ref_clk, s->apll_clk);
    qemu_clk_unbind(s->video_clk, s->apll_clk);
    qemu_clk_unbind(s->pss_alt_ref_clk, s->apll_clk);
    qemu_clk_unbind(s->aux_refclk, s->apll_clk);
    qemu_clk_unbind(s->gt_crx_ref_clk, s->apll_clk);

    switch (source) {
    case VIDEO_CLK:
        qemu_clk_bind(s->video_clk, s->apll_clk);
        break;
    case PSS_ALT_REF_CLK:
        qemu_clk_bind(s->pss_alt_ref_clk, s->apll_clk);
        break;
    case AUX_REF_CLK:
        qemu_clk_bind(s->aux_refclk, s->apll_clk);
        break;
    case GT_CRX_REF_CLK:
        qemu_clk_bind(s->gt_crx_ref_clk, s->apll_clk);
        break;
    default:
        qemu_clk_bind(s->pss_ref_clk, s->apll_clk);
        break;
    }
}

static void dpll_ctrl_postw(RegisterInfo *reg, uint64_t val64)
{
    CRF_APB *s = XILINX_CRF_APB(reg->opaque);
    uint32_t source = FIELD_EX32(s->regs[R_DPLL_CTRL], DPLL_CTRL, BYPASS)
                    ? FIELD_EX32(s->regs[R_DPLL_CTRL], DPLL_CTRL, POST_SRC)
                    : FIELD_EX32(s->regs[R_DPLL_CTRL], DPLL_CTRL, PRE_SRC);

    /*
     * We must ensure that only one clock is bound to the dpll internal clock.
     */
    qemu_clk_unbind(s->pss_ref_clk, s->dpll_clk);
    qemu_clk_unbind(s->video_clk, s->dpll_clk);
    qemu_clk_unbind(s->pss_alt_ref_clk, s->dpll_clk);
    qemu_clk_unbind(s->aux_refclk, s->dpll_clk);
    qemu_clk_unbind(s->gt_crx_ref_clk, s->dpll_clk);

    switch (source) {
    case VIDEO_CLK:
        qemu_clk_bind(s->video_clk, s->dpll_clk);
        break;
    case PSS_ALT_REF_CLK:
        qemu_clk_bind(s->pss_alt_ref_clk, s->dpll_clk);
        break;
    case AUX_REF_CLK:
        qemu_clk_bind(s->aux_refclk, s->dpll_clk);
        break;
    case GT_CRX_REF_CLK:
        qemu_clk_bind(s->gt_crx_ref_clk, s->dpll_clk);
        break;
    default:
        qemu_clk_bind(s->pss_ref_clk, s->dpll_clk);
        break;
    }
}

static void vpll_ctrl_postw(RegisterInfo *reg, uint64_t val64)
{
    CRF_APB *s = XILINX_CRF_APB(reg->opaque);
    uint32_t source = FIELD_EX32(s->regs[R_VPLL_CTRL], VPLL_CTRL, BYPASS)
                    ? FIELD_EX32(s->regs[R_VPLL_CTRL], VPLL_CTRL, POST_SRC)
                    : FIELD_EX32(s->regs[R_VPLL_CTRL], VPLL_CTRL, PRE_SRC);

    /*
     * We must ensure that only one clock is bound to the vpll internal clock.
     */
    qemu_clk_unbind(s->pss_ref_clk, s->vpll_clk);
    qemu_clk_unbind(s->video_clk, s->vpll_clk);
    qemu_clk_unbind(s->pss_alt_ref_clk, s->vpll_clk);
    qemu_clk_unbind(s->aux_refclk, s->vpll_clk);
    qemu_clk_unbind(s->gt_crx_ref_clk, s->vpll_clk);

    switch (source) {
    case VIDEO_CLK:
        qemu_clk_bind(s->video_clk, s->vpll_clk);
        break;
    case PSS_ALT_REF_CLK:
        qemu_clk_bind(s->pss_alt_ref_clk, s->vpll_clk);
        break;
    case AUX_REF_CLK:
        qemu_clk_bind(s->aux_refclk, s->vpll_clk);
        break;
    case GT_CRX_REF_CLK:
        qemu_clk_bind(s->gt_crx_ref_clk, s->vpll_clk);
        break;
    default:
        qemu_clk_bind(s->pss_ref_clk, s->vpll_clk);
        break;
    }
}

/*
 * This happen when apll get updated.
 * As we ensure that only one clk_pin can drive apll we can just do the
 * computation from input_rate.
 */
static uint64_t apll_update_rate(void *opaque, uint64_t input_rate)
{
    CRF_APB *s = XILINX_CRF_APB(opaque);
    bool bypass = FIELD_EX32(s->regs[R_APLL_CTRL], APLL_CTRL, BYPASS);
    bool reset = FIELD_EX32(s->regs[R_APLL_CTRL], APLL_CTRL, RESET);
    float div2 = FIELD_EX32(s->regs[R_APLL_CTRL], APLL_CTRL, DIV2) ? 0.5f
                                                                   : 1.0f;
    float integer = (float)(FIELD_EX32(s->regs[R_APLL_CTRL],
                                       APLL_CTRL, FBDIV));
    float frac = FIELD_EX32(s->regs[R_APLL_FRAC_CFG], APLL_FRAC_CFG, ENABLED)
                  ? (float)(FIELD_EX32(s->regs[R_APLL_FRAC_CFG],
                                       APLL_FRAC_CFG, DATA))
                  / 65536.0f
                  : 0.0f;

    if (bypass) {
        return input_rate;
    } else {
        if (reset) {
            /*
             * This is not supposed to happen user must ensure that BYPASS is
             * set before the PLL are reset.
             */
            qemu_log_mask(LOG_GUEST_ERROR,
                          "APLL is reseted but not bypassed.");
            return 0;
        } else {
            return input_rate * div2 * (integer + frac);
        }
    }
}

/*
 * This happen when dpll get updated.
 * As we ensure that only one clk_pin can drive dpll we can just do the
 * computation from input_rate.
 */
static uint64_t dpll_update_rate(void *opaque, uint64_t input_rate)
{
    CRF_APB *s = XILINX_CRF_APB(opaque);
    bool bypass = FIELD_EX32(s->regs[R_DPLL_CTRL], DPLL_CTRL, BYPASS);
    bool reset = FIELD_EX32(s->regs[R_DPLL_CTRL], DPLL_CTRL, RESET);
    float div2 = FIELD_EX32(s->regs[R_DPLL_CTRL], DPLL_CTRL, DIV2) ? 0.5f
                                                                 : 1.0f;
    float integer = (float)(FIELD_EX32(s->regs[R_DPLL_CTRL], DPLL_CTRL,
                                       FBDIV));
    float frac = FIELD_EX32(s->regs[R_DPLL_FRAC_CFG], DPLL_FRAC_CFG, ENABLED)
                  ? (float)(FIELD_EX32(s->regs[R_DPLL_FRAC_CFG],
                                       DPLL_FRAC_CFG, DATA))
                  / 65536.0f
                  : 0.0f;

    if (bypass) {
        return input_rate;
    } else {
        if (reset) {
            /*
             * This is not supposed to happen user must ensure that BYPASS is
             * set before the PLL are reset.
             */
            qemu_log_mask(LOG_GUEST_ERROR,
                          "DPLL is reseted but not bypassed.");
            return 0;
        } else {
            return input_rate * div2 * (integer + frac);
        }
    }
}

/*
 * This happen when vpll get updated.
 * As we ensure that only one clk_pin can drive vpll we can just do the
 * computation from input_rate.
 */
static uint64_t vpll_update_rate(void *opaque, uint64_t input_rate)
{
    CRF_APB *s = XILINX_CRF_APB(opaque);
    bool bypass = FIELD_EX32(s->regs[R_VPLL_CTRL], VPLL_CTRL, BYPASS);
    bool reset = FIELD_EX32(s->regs[R_VPLL_CTRL], VPLL_CTRL, RESET);
    float div2 = FIELD_EX32(s->regs[R_VPLL_CTRL], VPLL_CTRL, DIV2) ? 0.5f
                                                                   : 1.0f;
    float integer = (float)(FIELD_EX32(s->regs[R_VPLL_CTRL], VPLL_CTRL,
                                       FBDIV));
    float frac = FIELD_EX32(s->regs[R_VPLL_FRAC_CFG], VPLL_FRAC_CFG, ENABLED)
                  ? (float)(FIELD_EX32(s->regs[R_VPLL_FRAC_CFG],
                                       VPLL_FRAC_CFG, DATA))
                  / 65536.0f
                  : 0.0f;

    if (bypass) {
        return input_rate;
    } else {
        if (reset) {
            /*
             * This is not supposed to happen user must ensure that BYPASS is
             * set before the PLL are reset.
             */
            qemu_log_mask(LOG_GUEST_ERROR,
                          "VPLL is reseted but not bypassed.");
            return 0;
        } else {
            return input_rate * div2 * (integer + frac);
        }
    }
}

/*
 * FIXME: Only DP video reference clock is modeled here, others are missing.
 */
static uint64_t dp_video_update_rate(void *opaque, uint64_t input_rate)
{
    CRF_APB *s = XILINX_CRF_APB(opaque);
    bool clock_act = FIELD_EX32(s->regs[R_DP_VIDEO_REF_CTRL],
                                DP_VIDEO_REF_CTRL, CLKACT);
    uint32_t divisor0 = FIELD_EX32(s->regs[R_DP_VIDEO_REF_CTRL],
                                   DP_VIDEO_REF_CTRL, DIVISOR0);

    if ((!divisor0) || (!clock_act)) {
        return 0.0f;
    } else {
        return input_rate / (float)(divisor0);
    }
}

static void dp_video_ref_ctrl_postw(RegisterInfo *reg, uint64_t val64)
{
    CRF_APB *s = XILINX_CRF_APB(reg->opaque);
    uint32_t source = FIELD_EX32(s->regs[R_APLL_CTRL], APLL_CTRL, BYPASS)
                    ? FIELD_EX32(s->regs[R_APLL_CTRL], APLL_CTRL, POST_SRC)
                    : FIELD_EX32(s->regs[R_APLL_CTRL], APLL_CTRL, PRE_SRC);

    /*
     * We must ensure that only one clock is bound to the dp_video_ref
     * internal clock, so the callback have always the right rate in it.
     */
    qemu_clk_unbind(s->vpll_clk, s->dp_video_ref);
    qemu_clk_unbind(s->dpll_clk, s->dp_video_ref);

    switch (source) {
    case 0x00:
        qemu_clk_bind(s->vpll_clk, s->dp_video_ref);
        break;
    case 0x02:
        qemu_clk_bind(s->dpll_clk, s->dp_video_ref);
        break;
    default:
        abort();
        break;
    }
}

static RegisterAccessInfo crf_apb_regs_info[] = {
    {   .name = "ERR_CTRL",  .addr = A_ERR_CTRL,
    },{ .name = "IR_STATUS",  .addr = A_IR_STATUS,
        .w1c = 0x1,
        .post_write = ir_status_postw,
    },{ .name = "IR_MASK",  .addr = A_IR_MASK,
        .reset = 0x1,
        .ro = 0x1,
    },{ .name = "IR_ENABLE",  .addr = A_IR_ENABLE,
        .pre_write = ir_enable_prew,
    },{ .name = "IR_DISABLE",  .addr = A_IR_DISABLE,
        .pre_write = ir_disable_prew,
    },{ .name = "CRF_ECO",  .addr = A_CRF_ECO,
    },{ .name = "APLL_CTRL",  .addr = A_APLL_CTRL,
        .reset = 0x00012C08, /* We clear the reset field */
        .rsvd = 0xf88c80f6L,
        .post_write = apll_ctrl_postw,
    },{ .name = "APLL_CFG",  .addr = A_APLL_CFG,
        .rsvd = 0x1801210,
    },{ .name = "APLL_FRAC_CFG",  .addr = A_APLL_FRAC_CFG,
        .rsvd = 0x7e330000,
    },{ .name = "DPLL_CTRL",  .addr = A_DPLL_CTRL,
        .reset = 0x2C08,
        .rsvd = 0xf88c80f6L,
        .post_write = dpll_ctrl_postw,
    },{ .name = "DPLL_CFG",  .addr = A_DPLL_CFG,
        .rsvd = 0x1801210,
    },{ .name = "DPLL_FRAC_CFG",  .addr = A_DPLL_FRAC_CFG,
        .rsvd = 0x7e330000,
    },{ .name = "VPLL_CTRL",  .addr = A_VPLL_CTRL,
        .reset = 0x12808,
        .rsvd = 0xf88c80f6L,
        .post_write = vpll_ctrl_postw,
    },{ .name = "VPLL_CFG",  .addr = A_VPLL_CFG,
        .rsvd = 0x1801210,
    },{ .name = "VPLL_FRAC_CFG",  .addr = A_VPLL_FRAC_CFG,
        .rsvd = 0x7e330000,
    },{ .name = "PLL_STATUS",  .addr = A_PLL_STATUS,
        .reset = 0x3f,
        .rsvd = 0xc0,
        .ro = 0x3f,
    },{ .name = "APLL_TO_LPD_CTRL", .addr = A_APLL_TO_LPD_CTRL,
        .reset = 0x400,
        .rsvd = 0xc0ff,
        .post_write = apll_to_lpd_postw,
    },{ .name = "DPLL_TO_LPD_CTRL", .addr = A_DPLL_TO_LPD_CTRL,
        .reset = 0x400,
        .rsvd = 0xc0ff,
        .post_write = dpll_to_lpd_postw,
    },{ .name = "VPLL_TO_LPD_CTRL", .addr = A_VPLL_TO_LPD_CTRL,
        .reset = 0x400,
        .rsvd = 0xc0ff,
        .post_write = vpll_to_lpd_postw,
    },{ .name = "CPU_A9_CTRL", .addr = A_CPU_A9_CTRL,
        .reset = 0xf000400,
        .rsvd = 0xf0ffc0f8L,
    },{ .name = "DBG_TRACE_CTRL", .addr = A_DBG_TRACE_CTRL,
        .reset = 0x2500,
        .rsvd = 0xfeffc0f8L,
    },{ .name = "DBG_FPD_CTRL", .addr = A_DBG_FPD_CTRL,
        .reset = 0x1002500,
        .rsvd = 0xfeffc0f8L,
    },{ .name = "DP_VIDEO_REF_CTRL", .addr = A_DP_VIDEO_REF_CTRL,
        .reset = 0x1002300,
        .rsvd = 0xfeffc0f8L,
        .post_write = dp_video_ref_ctrl_postw,
    },{ .name = "DP_AUDIO_REF_CTRL", .addr = A_DP_AUDIO_REF_CTRL,
        .reset = 0x1002300,
        .rsvd = 0xfeffc0f8L,
    },{ .name = "DP_LINK_REF_CTRL", .addr = A_DP_LINK_REF_CTRL,
        .reset = 0x1203200,
        .rsvd = 0xfec0c0f8L,
    },{ .name = "DP_STC_REF_CTRL", .addr = A_DP_STC_REF_CTRL,
        .reset = 0x1203200,
        .rsvd = 0xfec0c0f8L,
    },{ .name = "DDR_CTRL", .addr = A_DDR_CTRL,
        .reset = 0x1000500,
        .rsvd = 0xfeffc0f8L,
    },{ .name = "GPU_REF_CTRL", .addr = A_GPU_REF_CTRL,
        .reset = 0x1500,
        .rsvd = 0xf8ffc0f8L,
    },{ .name = "AFI0_REF_CTRL", .addr = A_AFI0_REF_CTRL,
        .reset = 0x600,
        .rsvd = 0x7effc0f8,
    },{ .name = "AFI1_REF_CTRL", .addr = A_AFI1_REF_CTRL,
        .reset = 0x600,
        .rsvd = 0x7effc0f8,
    },{ .name = "AFI2_REF_CTRL", .addr = A_AFI2_REF_CTRL,
        .reset = 0x600,
        .rsvd = 0x7effc0f8,
    },{ .name = "AFI3_REF_CTRL", .addr = A_AFI3_REF_CTRL,
        .reset = 0x600,
        .rsvd = 0x7effc0f8,
    },{ .name = "AFI4_REF_CTRL", .addr = A_AFI4_REF_CTRL,
        .reset = 0x600,
        .rsvd = 0x7effc0f8,
    },{ .name = "AFI5_REF_CTRL", .addr = A_AFI5_REF_CTRL,
        .reset = 0x600,
        .rsvd = 0x7effc0f8,
    },{ .name = "SATA_REF_CTRL", .addr = A_SATA_REF_CTRL,
        .reset = 0x1001600,
        .rsvd = 0xfeffc0f8L,
    },{ .name = "PCIE_REF_CTRL", .addr = A_PCIE_REF_CTRL,
        .reset = 0x1500,
        .rsvd = 0xfeffc0f8L,
    },{ .name = "GDMA_REF_CTRL", .addr = A_GDMA_REF_CTRL,
        .reset = 0x1000500,
        .rsvd = 0xfeffc0f8L,
    },{ .name = "DPDMA_REF_CTRL", .addr = A_DPDMA_REF_CTRL,
        .reset = 0x1000500,
        .rsvd = 0xfeffc0f8L,
    },{ .name = "TOPSW_MAIN_CTRL", .addr = A_TOPSW_MAIN_CTRL,
        .reset = 0x1000500,
        .rsvd = 0xfeffc0f8L,
    },{ .name = "TOPSW_LSBUS_CTRL", .addr = A_TOPSW_LSBUS_CTRL,
        .reset = 0x1000800,
        .rsvd = 0xfeffc0f8L,
    },{ .name = "GTGREF0_REF_CTRL", .addr = A_GTGREF0_REF_CTRL,
        .reset = 0x800,
        .rsvd = 0xfeffc0f8L,
    },{ .name = "GTGREF1_REF_CTRL", .addr = A_GTGREF1_REF_CTRL,
        .reset = 0x800,
        .rsvd = 0xfeffc0f8L,
    },{ .name = "DFT300_REF_CTRL", .addr = A_DFT300_REF_CTRL,
        .reset = 0x800,
        .rsvd = 0xfeffc0f8L,
    },{ .name = "DFT270_REF_CTRL", .addr = A_DFT270_REF_CTRL,
        .reset = 0x800,
        .rsvd = 0xfeffc0f8L,
    },{ .name = "DFT250_REF_CTRL", .addr = A_DFT250_REF_CTRL,
        .reset = 0x800,
        .rsvd = 0xfeffc0f8L,
    },{ .name = "DFT125_REF_CTRL", .addr = A_DFT125_REF_CTRL,
        .reset = 0x800,
        .rsvd = 0xfeffc0f8L,
    },{ .name = "RST_FPD_TOP", .addr = A_RST_FPD_TOP,
        .reset = 0x71ffe,
        .rsvd = 0xf8e001,
    },{ .name = "RST_FPD_APU", .addr = A_RST_FPD_APU,
        .reset = 0x334f,
        .rsvd = 0xffcccc,
    },{ .name = "RST_DDR_SS", .addr = A_RST_DDR_SS,
        .reset = 0xf,
        .rsvd = 0xf0,
    }
};

static void crf_apb_reset(DeviceState *dev)
{
    CRF_APB *s = XILINX_CRF_APB(dev);
    unsigned int i;

    for (i = 0; i < ARRAY_SIZE(s->regs_info); ++i) {
        register_reset(&s->regs_info[i]);
    }

    ir_update_irq(s);

    /*
     * During reset, the clock selection registers bound the clock like this.
     */
    qemu_clk_bind(s->pss_ref_clk, s->apll_clk);
    qemu_clk_bind(s->pss_ref_clk, s->dpll_clk);
    qemu_clk_bind(s->pss_ref_clk, s->vpll_clk);
    qemu_clk_bind(s->vpll_clk, s->dp_video_ref);
}

static void crf_apb_realize(DeviceState *d, Error **errp)
{
    CRF_APB *s = XILINX_CRF_APB(d);

    qemu_clk_bind(s->apll_clk, s->apll_to_lpd);
    qemu_clk_bind(s->dpll_clk, s->dpll_to_lpd);
    qemu_clk_bind(s->vpll_clk, s->vpll_to_lpd);

    crf_apb_reset(d);
}

static void crf_apb_init(Object *obj)
{
    CRF_APB *s = XILINX_CRF_APB(obj);
    SysBusDevice *sbd = SYS_BUS_DEVICE(obj);
    RegisterInfoArray *reg_array;

    memory_region_init(&s->iomem, obj, TYPE_XILINX_CRF_APB, R_MAX * 4);
    reg_array = register_init_block32(DEVICE(obj), crf_apb_regs_info,
                                      ARRAY_SIZE(crf_apb_regs_info),
                                      s->regs_info, s->regs,
                                      &crf_apb_ops,
                                      XILINX_CRF_APB_ERR_DEBUG,
                                      R_RST_DDR_SS);
    memory_region_add_subregion(&s->iomem,
                                A_ERR_CTRL,
                                &reg_array->mem);

    sysbus_init_mmio(sbd, &s->iomem);
    sysbus_init_irq(sbd, &s->irq_ir);

    qemu_clk_init_device(obj, crf_clock);
}

static const VMStateDescription vmstate_crf_apb = {
    .name = TYPE_XILINX_CRF_APB,
    .version_id = 1,
    .minimum_version_id = 1,
    .minimum_version_id_old = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32_ARRAY(regs, CRF_APB, R_MAX),
        VMSTATE_END_OF_LIST(),
    }
};

static void crf_apb_class_init(ObjectClass *klass, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);

    dc->reset = crf_apb_reset;
    dc->vmsd = &vmstate_crf_apb;
    dc->realize = crf_apb_realize;
}

static const TypeInfo crf_apb_info = {
    .name          = TYPE_XILINX_CRF_APB,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(CRF_APB),
    .class_init    = crf_apb_class_init,
    .instance_init = crf_apb_init,
};

static void crf_apb_register_types(void)
{
    type_register_static(&crf_apb_info);
}

type_init(crf_apb_register_types)
