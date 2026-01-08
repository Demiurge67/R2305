/*
 * Broadcom specific AMBA
 * SPROM reading
 *
 * Copyright 2011, 2012, Hauke Mehrtens <hauke@hauke-m.de>
 *
 * Licensed under the GNU/GPL. See COPYING for details.
 */

#include "bcma_private.h"
#include <linux/string.h>
#include <linux/ssb/ssb.h>
#include <linux/platform_device.h>
#include <linux/bcma/bcma.h>
#include <linux/bcma/bcma_regs.h>
#include <bcm47xx_fallback_sprom.h>
#include <linux/pci.h>
#include <linux/io.h>
#include <linux/dma-mapping.h>
#include <linux/slab.h>

static int(*get_fallback_sprom)(struct bcma_bus *dev, struct ssb_sprom *out);

/**
 * bcma_arch_register_fallback_sprom - Registers a method providing a
 * fallback SPROM if no SPROM is found.
 *
 * @sprom_callback: The callback function.
 *
 * With this function the architecture implementation may register a
 * callback handler which fills the SPROM data structure. The fallback is
 * used for PCI based BCMA devices, where no valid SPROM can be found
 * in the shadow registers and to provide the SPROM for SoCs where BCMA is
 * to controll the system bus.
 *
 * This function is useful for weird architectures that have a half-assed
 * BCMA device hardwired to their PCI bus.
 *
 * This function is available for architecture code, only. So it is not
 * exported.
 */
 
static struct ssb_sprom bcm47xx_sprom;
 
int bcm47xx_get_fallback_sprom(struct ssb_bus *bus, struct ssb_sprom *out)
#if defined(CONFIG_SSB_PCIHOST)
int bcm47xx_get_fallback_ssb_sprom(struct ssb_bus *bus, struct ssb_sprom *out)
{
	if (bus->hosttype == BCMA_HOSTTYPE_PCI) {
		if (bus->host_pci->bus->number != fallback_sprom.pci_bus ||
		    PCI_SLOT(bus->host_pci->devfn) != fallback_sprom.pci_dev)
			pr_warn("bcma_fallback_sprom: pci bus/device num mismatch: expected %i/%i, but got %i/%i\n",
				fallback_sprom.pci_bus, fallback_sprom.pci_dev,
				bus->host_pci->bus->number,
				PCI_SLOT(bus->host_pci->devfn));
		if (fallback_sprom.override_devid)
			bus->host_pci->device = fallback_sprom.sprom.dev_id;
		memcpy(out, &fallback_sprom.sprom, sizeof(struct ssb_sprom));
		return 0;
	} else {
		printk(KERN_ERR PFX "unable to fill SPROM for given bustype.\n");
if (bus->bustype == SSB_BUSTYPE_PCI) {
	memcpy(out, &bcm47xx_sprom, sizeof(struct ssb_sprom));
int bcm47xx_get_fallback_sprom(struct ss
		return -EINVAL;
	}
}
#endif

#if defined(CONFIG_BCMA_HOST_PCI)
static __initconst u16 bcm4313_sprom[] = {
	0x2801, 0x0000, 0x0510, 0x14e4, 0x0078, 0xedbe, 0x0000, 0x2bc4,
	0x2a64, 0x2964, 0x2c64, 0x3ce7, 0x46ff, 0x47ff, 0x0c00, 0x0820,
	0x0030, 0x1002, 0x9f28, 0x5d44, 0x8080, 0x1d8f, 0x0032, 0x0100,
	0xdf00, 0x71f5, 0x8400, 0x0083, 0x8500, 0x2010, 0x0001, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x1008, 0x0305, 0x0000, 0x0000, 0x0000, 0x0000,
	0x4727, 0x8000, 0x0002, 0x0000, 0x1f30, 0x1800, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x5372, 0x1215, 0x2a00, 0x0800, 0x0800, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0003, 0xffff, 0x88ff, 0xffff, 0x0003, 0x0202,
	0xffff, 0x0011, 0x007a, 0x0000, 0x0000, 0x0000, 0x0000, 0x0201,
	0x0000, 0x7800, 0x7c0a, 0x0398, 0x0008, 0x0000, 0x0000, 0x0000,
	0x0044, 0x1684, 0xfd0d, 0xff35, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0048, 0xfed2, 0x15d9, 0xfac6, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0008,
};

static __initconst u16 bcm43131_sprom[] = {
	0x2801, 0x0000, 0x05f7, 0x14e4, 0x0070, 0xedbe, 0x1c00, 0x2bc4,
	0x2a64, 0x2964, 0x2c64, 0x3ce7, 0x46ff, 0x47ff, 0x0c00, 0x0820,
	0x0030, 0x1002, 0x9f28, 0x5d44, 0x8080, 0x1d8f, 0x0032, 0x0100,
	0xdf00, 0x71f5, 0x8400, 0x0083, 0x8500, 0x2010, 0x0001, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x1008, 0x0305, 0x0000, 0x0000, 0x0000, 0x0000,
	0x43aa, 0x8000, 0x0002, 0x0000, 0x1f30, 0x1800, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x5372, 0x1280, 0x0200, 0x0000, 0x8800, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0003, 0xffff, 0x88ff, 0xffff, 0x0002, 0x0202,
	0xffff, 0x0022, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0415,
	0x0000, 0x7800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x204c, 0xfe96, 0x192c, 0xfa15, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x204c, 0xfe91, 0x1950, 0xfa0a, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0x0000, 0x4444, 0x4444, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x4444, 0x4444, 0x4444, 0x4444, 0x6666, 0x6666, 0x6666,
	0x6666, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0x0008,
};

static __initconst u16 bcm43217_sprom[] = {
	0x2801, 0x0000, 0x05e9, 0x14e4, 0x0070, 0xedbe, 0x0000, 0x2bc4,
	0x2a64, 0x2964, 0x2c64, 0x3ce7, 0x46ff, 0x47ff, 0x0c00, 0x0820,
	0x0030, 0x1002, 0x9f28, 0x5d44, 0x8080, 0x1d8f, 0x0032, 0x0100,
	0xdf00, 0x71f5, 0x8400, 0x0083, 0x8500, 0x2010, 0x0001, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x1008, 0x0305, 0x0000, 0x0000, 0x0000, 0x0000,
	0x43a9, 0x8000, 0x0002, 0x0000, 0x1f30, 0x1800, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x5372, 0x1252, 0x0200, 0x0000, 0x9800, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0003, 0xffff, 0x88ff, 0xffff, 0x0003, 0x0202,
	0xffff, 0x0033, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0415,
	0x0000, 0x7800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x204c, 0xfe96, 0x192c, 0xfa15, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x204c, 0xfe91, 0x1950, 0xfa0a, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0x0000, 0x4444, 0x4444, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x4444, 0x4444, 0x4444, 0x4444, 0x6666, 0x6666, 0x6666,
	0x6666, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0x7a08,
};

static __initconst u16 bcm43225_sprom[] = {
	0x2801, 0x0000, 0x04da, 0x14e4, 0x0078, 0xedbe, 0x0000, 0x2bc4,
	0x2a64, 0x2964, 0x2c64, 0x3ce7, 0x46ff, 0x47ff, 0x0c00, 0x0820,
	0x0030, 0x1002, 0x9f28, 0x5d44, 0x8080, 0x1d8f, 0x0032, 0x0100,
	0xdf00, 0x71f5, 0x8400, 0x0083, 0x8500, 0x2010, 0x0001, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0x1008, 0x0005, 0xffff, 0xffff, 0xffff, 0xffff,
	0x4357, 0x8000, 0x0002, 0x0000, 0x1f30, 0x1800, 0x0000, 0x0000,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0x5372, 0x1200, 0x0200, 0x0000, 0x1000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x88ff, 0xffff, 0xffff, 0x0303, 0x0202,
	0xffff, 0x0033, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x0325,
	0xffff, 0x7800, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0x204e, 0xfead, 0x1611, 0xfa9a, 0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0x204e, 0xfec1, 0x1674, 0xfab2, 0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0x0000, 0x5555, 0x5555, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x5555, 0x7555, 0x5555, 0x7555, 0x5555, 0x7555, 0x5555,
	0x7555, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0002, 0x0000, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0x0008,
};

static __initconst u16 bcm43227_sprom[] = {
	0x2801, 0x0000, 0x0543, 0x14e4, 0x0070, 0xedbe, 0x0000, 0x2bc4,
	0x2a64, 0x2964, 0x2c64, 0x3ce7, 0x46ff, 0x47ff, 0x0c00, 0x0820,
	0x0030, 0x1002, 0x9f28, 0x5d44, 0x8080, 0x1d8f, 0x0032, 0x0100,
	0xdf00, 0x71f5, 0x8400, 0x0083, 0x8500, 0x2010, 0x0001, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x1008, 0x0305, 0x0000, 0x0000, 0x0000, 0x0000,
	0x4358, 0x8000, 0x0002, 0x0000, 0x1f30, 0x1800, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x5372, 0x1402, 0x0200, 0x0000, 0x0800, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0003, 0xffff, 0x88ff, 0xffff, 0x0003, 0x0202,
	0xffff, 0x0033, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0415,
	0x0000, 0x7800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x204c, 0xff36, 0x16d2, 0xfaae, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x204c, 0xfeca, 0x159b, 0xfa80, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0x0000, 0x4444, 0x4444, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x4444, 0x4444, 0x4444, 0x4444, 0x6666, 0x6666, 0x6666,
	0x6666, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0x0008,
};

static __initconst u16 bcm43228_sprom[] = {
	0x2801, 0x0000, 0x0011, 0x1028, 0x0070, 0xedbe, 0x0000, 0x2bc4,
	0x2a64, 0x2964, 0x2c64, 0x3ce7, 0x46ff, 0x47ff, 0x0c00, 0x0820,
	0x0030, 0x1002, 0x9f28, 0x5d44, 0x8080, 0x1d8f, 0x0032, 0x0100,
	0xdf00, 0x71f5, 0x8400, 0x0083, 0x8500, 0x2010, 0x0001, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x1008, 0x0305, 0x0000, 0x0000, 0x0000, 0x0000,
	0x4359, 0x8000, 0x0002, 0x0000, 0x1f30, 0x1800, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x5372, 0x1203, 0x0200, 0x0000, 0x0800, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0003, 0xffff, 0x88ff, 0xffff, 0x0303, 0x0202,
	0xffff, 0x0033, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0215,
	0x0215, 0x7800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x204c, 0xff73, 0x1762, 0xfaa4, 0x3e34, 0x3434, 0xfea1, 0x154c,
	0xfad0, 0xfea1, 0x144c, 0xfafb, 0xfe7b, 0x13fe, 0xfafc, 0x0000,
	0x204c, 0xff41, 0x16a3, 0xfa8f, 0x3e34, 0x3434, 0xfe97, 0x1446,
	0xfb05, 0xfe97, 0x1346, 0xfb32, 0xfeb9, 0x1516, 0xfaee, 0x0000,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0x0000, 0x4444, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x4444, 0x4444, 0x4444, 0x4444, 0x8888, 0x8888, 0x8888,
	0x8888, 0x0000, 0x0000, 0x0000, 0x0000, 0x3333, 0x3333, 0x3333,
	0x3333, 0x0000, 0x0000, 0x0000, 0x0000, 0x3333, 0x3333, 0x3333,
	0x3333, 0x0000, 0x0000, 0x0000, 0x0000, 0x3333, 0x3333, 0x3333,
	0x3333, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xf008,
};

static __initconst u16 bcm4331_sprom[] = {
	0x2801, 0x0000, 0x0525, 0x14e4, 0x0078, 0xedbe, 0x0000, 0x2bc4,
	0x2a64, 0x2964, 0x2c64, 0x3ce7, 0x46ff, 0x47ff, 0x0c00, 0x0820,
	0x0030, 0x1002, 0x9f28, 0x5d44, 0x8080, 0x1d8f, 0x0032, 0x0100,
	0xdf00, 0x71f5, 0x8400, 0x0083, 0x8500, 0x2010, 0x0001, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0x1010, 0x0005, 0xffff, 0xffff, 0xffff, 0xffff,
	0x4331, 0x8000, 0x0002, 0x0000, 0x1f30, 0x1800, 0x0000, 0x0000,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0x5372, 0x1104, 0x0200, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0xffff, 0x88ff, 0xffff, 0x0707, 0x0202,
	0xff02, 0x0077, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x0325,
	0x0325, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0x2048, 0xfe56, 0x16f2, 0xfa44, 0x3e3c, 0x3c3c, 0xfe77, 0x1657,
	0xfa75, 0xffff, 0xffff, 0xffff, 0xfe76, 0x15da, 0xfa85, 0x0000,
	0x2048, 0xfe5c, 0x16b5, 0xfa56, 0x3e3c, 0x3c3c, 0xfe7c, 0x169d,
	0xfa6b, 0xffff, 0xffff, 0xffff, 0xfe7a, 0x1597, 0xfa97, 0x0000,
	0x2048, 0xfe68, 0x1734, 0xfa46, 0x3e3c, 0x3c3c, 0xfe7f, 0x15e4,
	0xfa94, 0xffff, 0xffff, 0xffff, 0xfe7d, 0x1582, 0xfa9f, 0x0000,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0x0009,
};

#endif  /* CONFIG_BCMA_HOST_PCI */


#if defined(CONFIG_BCMA_HOST_PCI)
	case SPROM_BCM4313:
		memcpy(&template_sprom, &bcm4313_sprom,
                       sizeof(bcm4313_sprom));
		size = ARRAY_SIZE(bcm4313_sprom);
		break;
	case SPROM_BCM43131:
		memcpy(&template_sprom, &bcm43131_sprom,
		       sizeof(bcm43131_sprom));
		size = ARRAY_SIZE(bcm43131_sprom);
		break;
	case SPROM_BCM43217:
		memcpy(&template_sprom, &bcm43217_sprom,
		       sizeof(bcm43217_sprom));
		size = ARRAY_SIZE(bcm43217_sprom);
		break;
	case SPROM_BCM43225:
		memcpy(&template_sprom, &bcm43225_sprom,
		       sizeof(bcm43225_sprom));
		size = ARRAY_SIZE(bcm43225_sprom);
		break;
	case SPROM_BCM43227:
		memcpy(&template_sprom, &bcm43227_sprom,
		       sizeof(bcm43227_sprom));
		size = ARRAY_SIZE(bcm43227_sprom);
		break;
	case SPROM_BCM43228:
		memcpy(&template_sprom, &bcm43228_sprom,
		       sizeof(bcm43228_sprom));
		size = ARRAY_SIZE(bcm43228_sprom);
		break;
	case SPROM_BCM4331:
		memcpy(&template_sprom, &bcm4331_sprom, sizeof(&bcm4331_sprom));
		size = ARRAY_SIZE(bcm4331_sprom);
		break;
#endif
 /* FIXME: use lib_sprom after submission upstream */
 
int bcma_arch_register_fallback_sprom(int (*sprom_callback)(struct bcma_bus *bus, struct ssb_sprom *out))
{
	if (get_fallback_sprom)
		return -EEXIST;
	get_fallback_sprom = sprom_callback;

	return 0;
}

static int bcma_fill_sprom_with_fallback(struct bcma_bus *bus, struct ssb_sprom *out)
{
	int err;

	if (get_fallback_sprom)
		err = get_fallback_sprom(bus, out);

#ifdef CONFIG_BCMA_FALLBACK_SPROM
	if (!get_fallback_sprom || err)
		err = bcma_get_fallback_sprom(bus, out);
#else
	if (!get_fallback_sprom)
		err = -ENOENT;
#endif /* CONFIG_BCMA_FALLBACK_SPROM */

	if (err) {
		bcma_warn(bus, "Using fallback SPROM failed (err %d)\n", err);
		return err;
	}

	bcma_debug(bus, "Using SPROM revision %d provided by platform.\n",
		   bus->sprom.revision);

	return 0;
}

/**************************************************
 * R/W ops.
 **************************************************/

static void bcma_sprom_read(struct bcma_bus *bus, u16 offset, u16 *sprom,
			    size_t words)
{
	int i;
	for (i = 0; i < words; i++)
		sprom[i] = bcma_read16(bus->drv_cc.core, offset + (i * 2));
}

/**************************************************
 * Validation.
 **************************************************/

static inline u8 bcma_crc8(u8 crc, u8 data)
{
	/* Polynomial:   x^8 + x^7 + x^6 + x^4 + x^2 + 1   */
	static const u8 t[] = {
		0x00, 0xF7, 0xB9, 0x4E, 0x25, 0xD2, 0x9C, 0x6B,
		0x4A, 0xBD, 0xF3, 0x04, 0x6F, 0x98, 0xD6, 0x21,
		0x94, 0x63, 0x2D, 0xDA, 0xB1, 0x46, 0x08, 0xFF,
		0xDE, 0x29, 0x67, 0x90, 0xFB, 0x0C, 0x42, 0xB5,
		0x7F, 0x88, 0xC6, 0x31, 0x5A, 0xAD, 0xE3, 0x14,
		0x35, 0xC2, 0x8C, 0x7B, 0x10, 0xE7, 0xA9, 0x5E,
		0xEB, 0x1C, 0x52, 0xA5, 0xCE, 0x39, 0x77, 0x80,
		0xA1, 0x56, 0x18, 0xEF, 0x84, 0x73, 0x3D, 0xCA,
		0xFE, 0x09, 0x47, 0xB0, 0xDB, 0x2C, 0x62, 0x95,
		0xB4, 0x43, 0x0D, 0xFA, 0x91, 0x66, 0x28, 0xDF,
		0x6A, 0x9D, 0xD3, 0x24, 0x4F, 0xB8, 0xF6, 0x01,
		0x20, 0xD7, 0x99, 0x6E, 0x05, 0xF2, 0xBC, 0x4B,
		0x81, 0x76, 0x38, 0xCF, 0xA4, 0x53, 0x1D, 0xEA,
		0xCB, 0x3C, 0x72, 0x85, 0xEE, 0x19, 0x57, 0xA0,
		0x15, 0xE2, 0xAC, 0x5B, 0x30, 0xC7, 0x89, 0x7E,
		0x5F, 0xA8, 0xE6, 0x11, 0x7A, 0x8D, 0xC3, 0x34,
		0xAB, 0x5C, 0x12, 0xE5, 0x8E, 0x79, 0x37, 0xC0,
		0xE1, 0x16, 0x58, 0xAF, 0xC4, 0x33, 0x7D, 0x8A,
		0x3F, 0xC8, 0x86, 0x71, 0x1A, 0xED, 0xA3, 0x54,
		0x75, 0x82, 0xCC, 0x3B, 0x50, 0xA7, 0xE9, 0x1E,
		0xD4, 0x23, 0x6D, 0x9A, 0xF1, 0x06, 0x48, 0xBF,
		0x9E, 0x69, 0x27, 0xD0, 0xBB, 0x4C, 0x02, 0xF5,
		0x40, 0xB7, 0xF9, 0x0E, 0x65, 0x92, 0xDC, 0x2B,
		0x0A, 0xFD, 0xB3, 0x44, 0x2F, 0xD8, 0x96, 0x61,
		0x55, 0xA2, 0xEC, 0x1B, 0x70, 0x87, 0xC9, 0x3E,
		0x1F, 0xE8, 0xA6, 0x51, 0x3A, 0xCD, 0x83, 0x74,
		0xC1, 0x36, 0x78, 0x8F, 0xE4, 0x13, 0x5D, 0xAA,
		0x8B, 0x7C, 0x32, 0xC5, 0xAE, 0x59, 0x17, 0xE0,
		0x2A, 0xDD, 0x93, 0x64, 0x0F, 0xF8, 0xB6, 0x41,
		0x60, 0x97, 0xD9, 0x2E, 0x45, 0xB2, 0xFC, 0x0B,
		0xBE, 0x49, 0x07, 0xF0, 0x9B, 0x6C, 0x22, 0xD5,
		0xF4, 0x03, 0x4D, 0xBA, 0xD1, 0x26, 0x68, 0x9F,
	};
	return t[crc ^ data];
}

static u8 bcma_sprom_crc(const u16 *sprom, size_t words)
{
	int word;
	u8 crc = 0xFF;

	for (word = 0; word < words - 1; word++) {
		crc = bcma_crc8(crc, sprom[word] & 0x00FF);
		crc = bcma_crc8(crc, (sprom[word] & 0xFF00) >> 8);
	}
	crc = bcma_crc8(crc, sprom[words - 1] & 0x00FF);
	crc ^= 0xFF;

	return crc;
}

static int bcma_sprom_check_crc(const u16 *sprom, size_t words)
{
	u8 crc;
	u8 expected_crc;
	u16 tmp;

	crc = bcma_sprom_crc(sprom, words);
	tmp = sprom[words - 1] & SSB_SPROM_REVISION_CRC;
	expected_crc = tmp >> SSB_SPROM_REVISION_CRC_SHIFT;
	if (crc != expected_crc)
		return -EPROTO;

	return 0;
}

static int bcma_sprom_valid(struct bcma_bus *bus, const u16 *sprom,
			    size_t words)
{
	u16 revision;
	int err;

	err = bcma_sprom_check_crc(sprom, words);
	if (err)
		return err;

	revision = sprom[words - 1] & SSB_SPROM_REVISION_REV;
	if (revision != 8 && revision != 9 && revision != 10) {
		pr_err("Unsupported SPROM revision: %d\n", revision);
		return -ENOENT;
	}

	bus->sprom.revision = revision;
	bcma_debug(bus, "Found SPROM revision %d\n", revision);

	return 0;
}

/**************************************************
 * SPROM extraction.
 **************************************************/

#define SPOFF(offset)	((offset) / sizeof(u16))

#define SPEX(_field, _offset, _mask, _shift)	\
	bus->sprom._field = ((sprom[SPOFF(_offset)] & (_mask)) >> (_shift))

#define SPEX32(_field, _offset, _mask, _shift)	\
	bus->sprom._field = ((((u32)sprom[SPOFF((_offset)+2)] << 16 | \
				sprom[SPOFF(_offset)]) & (_mask)) >> (_shift))

#define SPEX_ARRAY8(_field, _offset, _mask, _shift)	\
	do {	\
		SPEX(_field[0], _offset +  0, _mask, _shift);	\
		SPEX(_field[1], _offset +  2, _mask, _shift);	\
		SPEX(_field[2], _offset +  4, _mask, _shift);	\
		SPEX(_field[3], _offset +  6, _mask, _shift);	\
		SPEX(_field[4], _offset +  8, _mask, _shift);	\
		SPEX(_field[5], _offset + 10, _mask, _shift);	\
		SPEX(_field[6], _offset + 12, _mask, _shift);	\
		SPEX(_field[7], _offset + 14, _mask, _shift);	\
	} while (0)

static s8 sprom_extract_antgain(const u16 *in, u16 offset, u16 mask, u16 shift)
{
	u16 v;
	u8 gain;

	v = in[SPOFF(offset)];
	gain = (v & mask) >> shift;
	if (gain == 0xFF) {
		gain = 8; /* If unset use 2dBm */
	} else {
		/* Q5.2 Fractional part is stored in 0xC0 */
		gain = ((gain & 0xC0) >> 6) | ((gain & 0x3F) << 2);
	}

	return (s8)gain;
}

static void bcma_sprom_extract_r8(struct bcma_bus *bus, const u16 *sprom)
{
	u16 v, o;
	int i;
	static const u16 pwr_info_offset[] = {
		SSB_SROM8_PWR_INFO_CORE0, SSB_SROM8_PWR_INFO_CORE1,
		SSB_SROM8_PWR_INFO_CORE2, SSB_SROM8_PWR_INFO_CORE3
	};
	BUILD_BUG_ON(ARRAY_SIZE(pwr_info_offset) !=
			ARRAY_SIZE(bus->sprom.core_pwr_info));

	for (i = 0; i < 3; i++) {
		v = sprom[SPOFF(SSB_SPROM8_IL0MAC) + i];
		*(((__be16 *)bus->sprom.il0mac) + i) = cpu_to_be16(v);
	}

	SPEX(board_rev, SSB_SPROM8_BOARDREV, ~0, 0);
	SPEX(board_type, SSB_SPROM1_SPID, ~0, 0);

	SPEX(txpid2g[0], SSB_SPROM4_TXPID2G01, SSB_SPROM4_TXPID2G0,
	     SSB_SPROM4_TXPID2G0_SHIFT);
	SPEX(txpid2g[1], SSB_SPROM4_TXPID2G01, SSB_SPROM4_TXPID2G1,
	     SSB_SPROM4_TXPID2G1_SHIFT);
	SPEX(txpid2g[2], SSB_SPROM4_TXPID2G23, SSB_SPROM4_TXPID2G2,
	     SSB_SPROM4_TXPID2G2_SHIFT);
	SPEX(txpid2g[3], SSB_SPROM4_TXPID2G23, SSB_SPROM4_TXPID2G3,
	     SSB_SPROM4_TXPID2G3_SHIFT);

	SPEX(txpid5gl[0], SSB_SPROM4_TXPID5GL01, SSB_SPROM4_TXPID5GL0,
	     SSB_SPROM4_TXPID5GL0_SHIFT);
	SPEX(txpid5gl[1], SSB_SPROM4_TXPID5GL01, SSB_SPROM4_TXPID5GL1,
	     SSB_SPROM4_TXPID5GL1_SHIFT);
	SPEX(txpid5gl[2], SSB_SPROM4_TXPID5GL23, SSB_SPROM4_TXPID5GL2,
	     SSB_SPROM4_TXPID5GL2_SHIFT);
	SPEX(txpid5gl[3], SSB_SPROM4_TXPID5GL23, SSB_SPROM4_TXPID5GL3,
	     SSB_SPROM4_TXPID5GL3_SHIFT);

	SPEX(txpid5g[0], SSB_SPROM4_TXPID5G01, SSB_SPROM4_TXPID5G0,
	     SSB_SPROM4_TXPID5G0_SHIFT);
	SPEX(txpid5g[1], SSB_SPROM4_TXPID5G01, SSB_SPROM4_TXPID5G1,
	     SSB_SPROM4_TXPID5G1_SHIFT);
	SPEX(txpid5g[2], SSB_SPROM4_TXPID5G23, SSB_SPROM4_TXPID5G2,
	     SSB_SPROM4_TXPID5G2_SHIFT);
	SPEX(txpid5g[3], SSB_SPROM4_TXPID5G23, SSB_SPROM4_TXPID5G3,
	     SSB_SPROM4_TXPID5G3_SHIFT);

	SPEX(txpid5gh[0], SSB_SPROM4_TXPID5GH01, SSB_SPROM4_TXPID5GH0,
	     SSB_SPROM4_TXPID5GH0_SHIFT);
	SPEX(txpid5gh[1], SSB_SPROM4_TXPID5GH01, SSB_SPROM4_TXPID5GH1,
	     SSB_SPROM4_TXPID5GH1_SHIFT);
	SPEX(txpid5gh[2], SSB_SPROM4_TXPID5GH23, SSB_SPROM4_TXPID5GH2,
	     SSB_SPROM4_TXPID5GH2_SHIFT);
	SPEX(txpid5gh[3], SSB_SPROM4_TXPID5GH23, SSB_SPROM4_TXPID5GH3,
	     SSB_SPROM4_TXPID5GH3_SHIFT);

	SPEX(boardflags_lo, SSB_SPROM8_BFLLO, ~0, 0);
	SPEX(boardflags_hi, SSB_SPROM8_BFLHI, ~0, 0);
	SPEX(boardflags2_lo, SSB_SPROM8_BFL2LO, ~0, 0);
	SPEX(boardflags2_hi, SSB_SPROM8_BFL2HI, ~0, 0);

	SPEX(alpha2[0], SSB_SPROM8_CCODE, 0xff00, 8);
	SPEX(alpha2[1], SSB_SPROM8_CCODE, 0x00ff, 0);

	/* Extract cores power info info */
	for (i = 0; i < ARRAY_SIZE(pwr_info_offset); i++) {
		o = pwr_info_offset[i];
		SPEX(core_pwr_info[i].itssi_2g, o + SSB_SROM8_2G_MAXP_ITSSI,
			SSB_SPROM8_2G_ITSSI, SSB_SPROM8_2G_ITSSI_SHIFT);
		SPEX(core_pwr_info[i].maxpwr_2g, o + SSB_SROM8_2G_MAXP_ITSSI,
			SSB_SPROM8_2G_MAXP, 0);

		SPEX(core_pwr_info[i].pa_2g[0], o + SSB_SROM8_2G_PA_0, ~0, 0);
		SPEX(core_pwr_info[i].pa_2g[1], o + SSB_SROM8_2G_PA_1, ~0, 0);
		SPEX(core_pwr_info[i].pa_2g[2], o + SSB_SROM8_2G_PA_2, ~0, 0);

		SPEX(core_pwr_info[i].itssi_5g, o + SSB_SROM8_5G_MAXP_ITSSI,
			SSB_SPROM8_5G_ITSSI, SSB_SPROM8_5G_ITSSI_SHIFT);
		SPEX(core_pwr_info[i].maxpwr_5g, o + SSB_SROM8_5G_MAXP_ITSSI,
			SSB_SPROM8_5G_MAXP, 0);
		SPEX(core_pwr_info[i].maxpwr_5gh, o + SSB_SPROM8_5GHL_MAXP,
			SSB_SPROM8_5GH_MAXP, 0);
		SPEX(core_pwr_info[i].maxpwr_5gl, o + SSB_SPROM8_5GHL_MAXP,
			SSB_SPROM8_5GL_MAXP, SSB_SPROM8_5GL_MAXP_SHIFT);

		SPEX(core_pwr_info[i].pa_5gl[0], o + SSB_SROM8_5GL_PA_0, ~0, 0);
		SPEX(core_pwr_info[i].pa_5gl[1], o + SSB_SROM8_5GL_PA_1, ~0, 0);
		SPEX(core_pwr_info[i].pa_5gl[2], o + SSB_SROM8_5GL_PA_2, ~0, 0);
		SPEX(core_pwr_info[i].pa_5g[0], o + SSB_SROM8_5G_PA_0, ~0, 0);
		SPEX(core_pwr_info[i].pa_5g[1], o + SSB_SROM8_5G_PA_1, ~0, 0);
		SPEX(core_pwr_info[i].pa_5g[2], o + SSB_SROM8_5G_PA_2, ~0, 0);
		SPEX(core_pwr_info[i].pa_5gh[0], o + SSB_SROM8_5GH_PA_0, ~0, 0);
		SPEX(core_pwr_info[i].pa_5gh[1], o + SSB_SROM8_5GH_PA_1, ~0, 0);
		SPEX(core_pwr_info[i].pa_5gh[2], o + SSB_SROM8_5GH_PA_2, ~0, 0);
	}

	SPEX(fem.ghz2.tssipos, SSB_SPROM8_FEM2G, SSB_SROM8_FEM_TSSIPOS,
	     SSB_SROM8_FEM_TSSIPOS_SHIFT);
	SPEX(fem.ghz2.extpa_gain, SSB_SPROM8_FEM2G, SSB_SROM8_FEM_EXTPA_GAIN,
	     SSB_SROM8_FEM_EXTPA_GAIN_SHIFT);
	SPEX(fem.ghz2.pdet_range, SSB_SPROM8_FEM2G, SSB_SROM8_FEM_PDET_RANGE,
	     SSB_SROM8_FEM_PDET_RANGE_SHIFT);
	SPEX(fem.ghz2.tr_iso, SSB_SPROM8_FEM2G, SSB_SROM8_FEM_TR_ISO,
	     SSB_SROM8_FEM_TR_ISO_SHIFT);
	SPEX(fem.ghz2.antswlut, SSB_SPROM8_FEM2G, SSB_SROM8_FEM_ANTSWLUT,
	     SSB_SROM8_FEM_ANTSWLUT_SHIFT);

	SPEX(fem.ghz5.tssipos, SSB_SPROM8_FEM5G, SSB_SROM8_FEM_TSSIPOS,
	     SSB_SROM8_FEM_TSSIPOS_SHIFT);
	SPEX(fem.ghz5.extpa_gain, SSB_SPROM8_FEM5G, SSB_SROM8_FEM_EXTPA_GAIN,
	     SSB_SROM8_FEM_EXTPA_GAIN_SHIFT);
	SPEX(fem.ghz5.pdet_range, SSB_SPROM8_FEM5G, SSB_SROM8_FEM_PDET_RANGE,
	     SSB_SROM8_FEM_PDET_RANGE_SHIFT);
	SPEX(fem.ghz5.tr_iso, SSB_SPROM8_FEM5G, SSB_SROM8_FEM_TR_ISO,
	     SSB_SROM8_FEM_TR_ISO_SHIFT);
	SPEX(fem.ghz5.antswlut, SSB_SPROM8_FEM5G, SSB_SROM8_FEM_ANTSWLUT,
	     SSB_SROM8_FEM_ANTSWLUT_SHIFT);

	SPEX(ant_available_a, SSB_SPROM8_ANTAVAIL, SSB_SPROM8_ANTAVAIL_A,
	     SSB_SPROM8_ANTAVAIL_A_SHIFT);
	SPEX(ant_available_bg, SSB_SPROM8_ANTAVAIL, SSB_SPROM8_ANTAVAIL_BG,
	     SSB_SPROM8_ANTAVAIL_BG_SHIFT);
	SPEX(maxpwr_bg, SSB_SPROM8_MAXP_BG, SSB_SPROM8_MAXP_BG_MASK, 0);
	SPEX(itssi_bg, SSB_SPROM8_MAXP_BG, SSB_SPROM8_ITSSI_BG,
	     SSB_SPROM8_ITSSI_BG_SHIFT);
	SPEX(maxpwr_a, SSB_SPROM8_MAXP_A, SSB_SPROM8_MAXP_A_MASK, 0);
	SPEX(itssi_a, SSB_SPROM8_MAXP_A, SSB_SPROM8_ITSSI_A,
	     SSB_SPROM8_ITSSI_A_SHIFT);
	SPEX(maxpwr_ah, SSB_SPROM8_MAXP_AHL, SSB_SPROM8_MAXP_AH_MASK, 0);
	SPEX(maxpwr_al, SSB_SPROM8_MAXP_AHL, SSB_SPROM8_MAXP_AL_MASK,
	     SSB_SPROM8_MAXP_AL_SHIFT);
	SPEX(gpio0, SSB_SPROM8_GPIOA, SSB_SPROM8_GPIOA_P0, 0);
	SPEX(gpio1, SSB_SPROM8_GPIOA, SSB_SPROM8_GPIOA_P1,
	     SSB_SPROM8_GPIOA_P1_SHIFT);
	SPEX(gpio2, SSB_SPROM8_GPIOB, SSB_SPROM8_GPIOB_P2, 0);
	SPEX(gpio3, SSB_SPROM8_GPIOB, SSB_SPROM8_GPIOB_P3,
	     SSB_SPROM8_GPIOB_P3_SHIFT);
	SPEX(tri2g, SSB_SPROM8_TRI25G, SSB_SPROM8_TRI2G, 0);
	SPEX(tri5g, SSB_SPROM8_TRI25G, SSB_SPROM8_TRI5G,
	     SSB_SPROM8_TRI5G_SHIFT);
	SPEX(tri5gl, SSB_SPROM8_TRI5GHL, SSB_SPROM8_TRI5GL, 0);
	SPEX(tri5gh, SSB_SPROM8_TRI5GHL, SSB_SPROM8_TRI5GH,
	     SSB_SPROM8_TRI5GH_SHIFT);
	SPEX(rxpo2g, SSB_SPROM8_RXPO, SSB_SPROM8_RXPO2G,
	     SSB_SPROM8_RXPO2G_SHIFT);
	SPEX(rxpo5g, SSB_SPROM8_RXPO, SSB_SPROM8_RXPO5G,
	     SSB_SPROM8_RXPO5G_SHIFT);
	SPEX(rssismf2g, SSB_SPROM8_RSSIPARM2G, SSB_SPROM8_RSSISMF2G, 0);
	SPEX(rssismc2g, SSB_SPROM8_RSSIPARM2G, SSB_SPROM8_RSSISMC2G,
	     SSB_SPROM8_RSSISMC2G_SHIFT);
	SPEX(rssisav2g, SSB_SPROM8_RSSIPARM2G, SSB_SPROM8_RSSISAV2G,
	     SSB_SPROM8_RSSISAV2G_SHIFT);
	SPEX(bxa2g, SSB_SPROM8_RSSIPARM2G, SSB_SPROM8_BXA2G,
	     SSB_SPROM8_BXA2G_SHIFT);
	SPEX(rssismf5g, SSB_SPROM8_RSSIPARM5G, SSB_SPROM8_RSSISMF5G, 0);
	SPEX(rssismc5g, SSB_SPROM8_RSSIPARM5G, SSB_SPROM8_RSSISMC5G,
	     SSB_SPROM8_RSSISMC5G_SHIFT);
	SPEX(rssisav5g, SSB_SPROM8_RSSIPARM5G, SSB_SPROM8_RSSISAV5G,
	     SSB_SPROM8_RSSISAV5G_SHIFT);
	SPEX(bxa5g, SSB_SPROM8_RSSIPARM5G, SSB_SPROM8_BXA5G,
	     SSB_SPROM8_BXA5G_SHIFT);

	SPEX(pa0b0, SSB_SPROM8_PA0B0, ~0, 0);
	SPEX(pa0b1, SSB_SPROM8_PA0B1, ~0, 0);
	SPEX(pa0b2, SSB_SPROM8_PA0B2, ~0, 0);
	SPEX(pa1b0, SSB_SPROM8_PA1B0, ~0, 0);
	SPEX(pa1b1, SSB_SPROM8_PA1B1, ~0, 0);
	SPEX(pa1b2, SSB_SPROM8_PA1B2, ~0, 0);
	SPEX(pa1lob0, SSB_SPROM8_PA1LOB0, ~0, 0);
	SPEX(pa1lob1, SSB_SPROM8_PA1LOB1, ~0, 0);
	SPEX(pa1lob2, SSB_SPROM8_PA1LOB2, ~0, 0);
	SPEX(pa1hib0, SSB_SPROM8_PA1HIB0, ~0, 0);
	SPEX(pa1hib1, SSB_SPROM8_PA1HIB1, ~0, 0);
	SPEX(pa1hib2, SSB_SPROM8_PA1HIB2, ~0, 0);
	SPEX(cck2gpo, SSB_SPROM8_CCK2GPO, ~0, 0);
	SPEX32(ofdm2gpo, SSB_SPROM8_OFDM2GPO, ~0, 0);
	SPEX32(ofdm5glpo, SSB_SPROM8_OFDM5GLPO, ~0, 0);
	SPEX32(ofdm5gpo, SSB_SPROM8_OFDM5GPO, ~0, 0);
	SPEX32(ofdm5ghpo, SSB_SPROM8_OFDM5GHPO, ~0, 0);

	/* Extract the antenna gain values. */
	bus->sprom.antenna_gain.a0 = sprom_extract_antgain(sprom,
							   SSB_SPROM8_AGAIN01,
							   SSB_SPROM8_AGAIN0,
							   SSB_SPROM8_AGAIN0_SHIFT);
	bus->sprom.antenna_gain.a1 = sprom_extract_antgain(sprom,
							   SSB_SPROM8_AGAIN01,
							   SSB_SPROM8_AGAIN1,
							   SSB_SPROM8_AGAIN1_SHIFT);
	bus->sprom.antenna_gain.a2 = sprom_extract_antgain(sprom,
							   SSB_SPROM8_AGAIN23,
							   SSB_SPROM8_AGAIN2,
							   SSB_SPROM8_AGAIN2_SHIFT);
	bus->sprom.antenna_gain.a3 = sprom_extract_antgain(sprom,
							   SSB_SPROM8_AGAIN23,
							   SSB_SPROM8_AGAIN3,
							   SSB_SPROM8_AGAIN3_SHIFT);

	SPEX(leddc_on_time, SSB_SPROM8_LEDDC, SSB_SPROM8_LEDDC_ON,
	     SSB_SPROM8_LEDDC_ON_SHIFT);
	SPEX(leddc_off_time, SSB_SPROM8_LEDDC, SSB_SPROM8_LEDDC_OFF,
	     SSB_SPROM8_LEDDC_OFF_SHIFT);

	SPEX(txchain, SSB_SPROM8_TXRXC, SSB_SPROM8_TXRXC_TXCHAIN,
	     SSB_SPROM8_TXRXC_TXCHAIN_SHIFT);
	SPEX(rxchain, SSB_SPROM8_TXRXC, SSB_SPROM8_TXRXC_RXCHAIN,
	     SSB_SPROM8_TXRXC_RXCHAIN_SHIFT);
	SPEX(antswitch, SSB_SPROM8_TXRXC, SSB_SPROM8_TXRXC_SWITCH,
	     SSB_SPROM8_TXRXC_SWITCH_SHIFT);

	SPEX(opo, SSB_SPROM8_OFDM2GPO, 0x00ff, 0);

	SPEX_ARRAY8(mcs2gpo, SSB_SPROM8_2G_MCSPO, ~0, 0);
	SPEX_ARRAY8(mcs5gpo, SSB_SPROM8_5G_MCSPO, ~0, 0);
	SPEX_ARRAY8(mcs5glpo, SSB_SPROM8_5GL_MCSPO, ~0, 0);
	SPEX_ARRAY8(mcs5ghpo, SSB_SPROM8_5GH_MCSPO, ~0, 0);

	SPEX(rawtempsense, SSB_SPROM8_RAWTS, SSB_SPROM8_RAWTS_RAWTEMP,
	     SSB_SPROM8_RAWTS_RAWTEMP_SHIFT);
	SPEX(measpower, SSB_SPROM8_RAWTS, SSB_SPROM8_RAWTS_MEASPOWER,
	     SSB_SPROM8_RAWTS_MEASPOWER_SHIFT);
	SPEX(tempsense_slope, SSB_SPROM8_OPT_CORRX,
	     SSB_SPROM8_OPT_CORRX_TEMP_SLOPE,
	     SSB_SPROM8_OPT_CORRX_TEMP_SLOPE_SHIFT);
	SPEX(tempcorrx, SSB_SPROM8_OPT_CORRX, SSB_SPROM8_OPT_CORRX_TEMPCORRX,
	     SSB_SPROM8_OPT_CORRX_TEMPCORRX_SHIFT);
	SPEX(tempsense_option, SSB_SPROM8_OPT_CORRX,
	     SSB_SPROM8_OPT_CORRX_TEMP_OPTION,
	     SSB_SPROM8_OPT_CORRX_TEMP_OPTION_SHIFT);
	SPEX(freqoffset_corr, SSB_SPROM8_HWIQ_IQSWP,
	     SSB_SPROM8_HWIQ_IQSWP_FREQ_CORR,
	     SSB_SPROM8_HWIQ_IQSWP_FREQ_CORR_SHIFT);
	SPEX(iqcal_swp_dis, SSB_SPROM8_HWIQ_IQSWP,
	     SSB_SPROM8_HWIQ_IQSWP_IQCAL_SWP,
	     SSB_SPROM8_HWIQ_IQSWP_IQCAL_SWP_SHIFT);
	SPEX(hw_iqcal_en, SSB_SPROM8_HWIQ_IQSWP, SSB_SPROM8_HWIQ_IQSWP_HW_IQCAL,
	     SSB_SPROM8_HWIQ_IQSWP_HW_IQCAL_SHIFT);

	SPEX(bw40po, SSB_SPROM8_BW40PO, ~0, 0);
	SPEX(cddpo, SSB_SPROM8_CDDPO, ~0, 0);
	SPEX(stbcpo, SSB_SPROM8_STBCPO, ~0, 0);
	SPEX(bwduppo, SSB_SPROM8_BWDUPPO, ~0, 0);

	SPEX(tempthresh, SSB_SPROM8_THERMAL, SSB_SPROM8_THERMAL_TRESH,
	     SSB_SPROM8_THERMAL_TRESH_SHIFT);
	SPEX(tempoffset, SSB_SPROM8_THERMAL, SSB_SPROM8_THERMAL_OFFSET,
	     SSB_SPROM8_THERMAL_OFFSET_SHIFT);
	SPEX(phycal_tempdelta, SSB_SPROM8_TEMPDELTA,
	     SSB_SPROM8_TEMPDELTA_PHYCAL,
	     SSB_SPROM8_TEMPDELTA_PHYCAL_SHIFT);
	SPEX(temps_period, SSB_SPROM8_TEMPDELTA, SSB_SPROM8_TEMPDELTA_PERIOD,
	     SSB_SPROM8_TEMPDELTA_PERIOD_SHIFT);
	SPEX(temps_hysteresis, SSB_SPROM8_TEMPDELTA,
	     SSB_SPROM8_TEMPDELTA_HYSTERESIS,
	     SSB_SPROM8_TEMPDELTA_HYSTERESIS_SHIFT);
}

/*
 * Indicates the presence of external SPROM.
 */
static bool bcma_sprom_ext_available(struct bcma_bus *bus)
{
	u32 chip_status;
	u32 srom_control;
	u32 present_mask;

	if (bus->drv_cc.core->id.rev >= 31) {
		if (!(bus->drv_cc.capabilities & BCMA_CC_CAP_SPROM))
			return false;

		srom_control = bcma_read32(bus->drv_cc.core,
					   BCMA_CC_SROM_CONTROL);
		return srom_control & BCMA_CC_SROM_CONTROL_PRESENT;
	}

	/* older chipcommon revisions use chip status register */
	chip_status = bcma_read32(bus->drv_cc.core, BCMA_CC_CHIPSTAT);
	switch (bus->chipinfo.id) {
	case BCMA_CHIP_ID_BCM4313:
		present_mask = BCMA_CC_CHIPST_4313_SPROM_PRESENT;
		break;

	case BCMA_CHIP_ID_BCM4331:
		present_mask = BCMA_CC_CHIPST_4331_SPROM_PRESENT;
		break;

	default:
		return true;
	}

	return chip_status & present_mask;
}

/*
 * Indicates that on-chip OTP memory is present and enabled.
 */
static bool bcma_sprom_onchip_available(struct bcma_bus *bus)
{
	u32 chip_status;
	u32 otpsize = 0;
	bool present;

	chip_status = bcma_read32(bus->drv_cc.core, BCMA_CC_CHIPSTAT);
	switch (bus->chipinfo.id) {
	case BCMA_CHIP_ID_BCM4313:
		present = chip_status & BCMA_CC_CHIPST_4313_OTP_PRESENT;
		break;

	case BCMA_CHIP_ID_BCM4331:
		present = chip_status & BCMA_CC_CHIPST_4331_OTP_PRESENT;
		break;
	case BCMA_CHIP_ID_BCM43142:
	case BCMA_CHIP_ID_BCM43224:
	case BCMA_CHIP_ID_BCM43225:
		/* for these chips OTP is always available */
		present = true;
		break;
	case BCMA_CHIP_ID_BCM43131:
	case BCMA_CHIP_ID_BCM43217:
	case BCMA_CHIP_ID_BCM43227:
	case BCMA_CHIP_ID_BCM43228:
	case BCMA_CHIP_ID_BCM43428:
		present = chip_status & BCMA_CC_CHIPST_43228_OTP_PRESENT;
		break;
	default:
		present = false;
		break;
	}

	if (present) {
		otpsize = bus->drv_cc.capabilities & BCMA_CC_CAP_OTPS;
		otpsize >>= BCMA_CC_CAP_OTPS_SHIFT;
	}

	return otpsize != 0;
}

/*
 * Verify OTP is filled and determine the byte
 * offset where SPROM data is located.
 *
 * On error, returns 0; byte offset otherwise.
 */
static int bcma_sprom_onchip_offset(struct bcma_bus *bus)
{
	struct bcma_device *cc = bus->drv_cc.core;
	u32 offset;

	/* verify OTP status */
	if ((bcma_read32(cc, BCMA_CC_OTPS) & BCMA_CC_OTPS_GU_PROG_HW) == 0)
		return 0;

	/* obtain bit offset from otplayout register */
	offset = (bcma_read32(cc, BCMA_CC_OTPL) & BCMA_CC_OTPL_GURGN_OFFSET);
	return BCMA_CC_SPROM + (offset >> 3);
}

int bcma_sprom_get(struct bcma_bus *bus)
{
	u16 offset = BCMA_CC_SPROM;
	u16 *sprom;
	static const size_t sprom_sizes[] = {
		SSB_SPROMSIZE_WORDS_R4,
		SSB_SPROMSIZE_WORDS_R10,
		SSB_SPROMSIZE_WORDS_R11,
	};
	int i, err = 0;

	if (!bus->drv_cc.core)
		return -EOPNOTSUPP;

	if (!bcma_sprom_ext_available(bus)) {
		bool sprom_onchip;

		/*
		 * External SPROM takes precedence so check
		 * on-chip OTP only when no external SPROM
		 * is present.
		 */
		sprom_onchip = bcma_sprom_onchip_available(bus);
		if (sprom_onchip) {
			/* determine offset */
			offset = bcma_sprom_onchip_offset(bus);
		}
		if (!offset || !sprom_onchip) {
			/*
			 * Maybe there is no SPROM on the device?
			 * Now we ask the arch code if there is some sprom
			 * available for this device in some other storage.
			 */
			err = bcma_fill_sprom_with_fallback(bus, &bus->sprom);
			return err;
		}
	}

	if (bus->chipinfo.id == BCMA_CHIP_ID_BCM4331 ||
	    bus->chipinfo.id == BCMA_CHIP_ID_BCM43431)
		bcma_chipco_bcm4331_ext_pa_lines_ctl(&bus->drv_cc, false);

	bcma_debug(bus, "SPROM offset 0x%x\n", offset);
	for (i = 0; i < ARRAY_SIZE(sprom_sizes); i++) {
		size_t words = sprom_sizes[i];

		sprom = kcalloc(words, sizeof(u16), GFP_KERNEL);
		if (!sprom)
			return -ENOMEM;

		bcma_sprom_read(bus, offset, sprom, words);
		err = bcma_sprom_valid(bus, sprom, words);
		if (!err)
			break;

		kfree(sprom);
	}

	if (bus->chipinfo.id == BCMA_CHIP_ID_BCM4331 ||
	    bus->chipinfo.id == BCMA_CHIP_ID_BCM43431)
		bcma_chipco_bcm4331_ext_pa_lines_ctl(&bus->drv_cc, true);

	if (err) {
		bcma_warn(bus, "Invalid SPROM read from the PCIe card, trying to use fallback SPROM\n");
		err = bcma_fill_sprom_with_fallback(bus, &bus->sprom);
	} else {
		bcma_sprom_extract_r8(bus, sprom);
		kfree(sprom);
	}

	return err;
}
