#ifndef __BCM47XX_FALLBACK_SPROM_H
#define __BCM47XX_FALLBACK_SPROM_H

#include <linux/types.h>

struct bcma_sprom;

/**
 * struct bcma_fallback_sprom_info - Information to match device for fallback SPROM
 */
struct bcma_fallback_sprom_info {
	u16 bus;     /* PCI bus number */
	u16 slot;    /* PCI slot number */
	u16 func;    /* PCI function number */
	u16 vendor;  /* PCI vendor ID */
	u16 device;  /* PCI device ID */
};

/**
 * bcm47xx_register_fallback_sprom - Register a fallback SPROM
 */
int bcm47xx_register_fallback_sprom(const struct bcma_fallback_sprom_info *info,
				    const u16 *sprom_data, size_t size);

/**
 * bcm47xx_get_fallback_sprom - Get fallback SPROM for device
 */
int bcm47xx_get_fallback_sprom(const struct bcma_fallback_sprom_info *info,
			       struct bcma_sprom *out);

#endif /* __BCM47XX_FALLBACK_SPROM_H */
