// SPDX-License-Identifier: GPL-2.0-or-later
// SPDX-FileCopyrightText: 2011 Sascha Hauer <s.hauer@pengutronix.de>, Pengutronix
// SPDX-FileCopyrightText: 2025 Alexander Schulz <code@schulzalex.de>, OpenX32 Project

#include <common.h>
#include <init.h>
#include <linux/sizes.h>
#include <mach/imx/imx25-regs.h>
#include <asm/armlinux.h>
#include <asm/mach-types.h>
#include <mach/imx/generic.h>
#include <mach/imx/esdctl.h>
#include <gpio.h>

#define USB_POWER		IMX_GPIO_NR(4, 11)

static int openx32_ram_fixup(void) {
	imx_esdctl_disable();
	arm_add_mem_device("ram0", MX25_CSD0_BASE_ADDR, SZ_64M);

	return 0;
}

static int openx32_init(void) {
	barebox_set_hostname("openx32");
	armlinux_set_architecture(MACH_TYPE_OPENX32);
	armlinux_set_serial(imx_uid());

	// IOMUXC_SW_PAD_CTL_GRP_DSE_CSPI1 = 0x02 -> Drive Strength = High
	writel(0x02, 0x43FAC450);

	// enable USB_POWER (asserted when high)
	gpio_request(USB_POWER, "USB_POWER");
	gpio_direction_output(USB_POWER, 1);
	gpio_set_value(USB_POWER, 1);

	return 0;
}

core_initcall(openx32_ram_fixup);

console_initcall(openx32_init);