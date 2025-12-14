// SPDX-License-Identifier: GPL-2.0-or-later
// SPDX-FileCopyrightText: 2011 Sascha Hauer <s.hauer@pengutronix.de>, Pengutronix
// SPDX-FileCopyrightText: 2025 Alexander Schulz <code@schulzalex.de>, OpenX32 Project

#include <common.h>
#include <init.h>
#include <mach/imx/imx25-regs.h>
#include <mach/imx/esdctl.h>
#include <asm/barebox-arm.h>


extern char __dtb_imx25_openx32_start[];

static void __noreturn openx32_start(void)
{
	void *fdt;
	fdt = __dtb_imx25_openx32_start + get_runtime_offset();
	imx25_barebox_entry(fdt);
}

ENTRY_FUNCTION(start_imx25_openx32, r0, r1, r2)
{
	arm_setup_stack(MX25_IRAM_BASE_ADDR + MX25_IRAM_SIZE);
	arm_cpu_lowlevel_init();
	openx32_start();
}