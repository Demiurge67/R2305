#ifndef __BCM47XX_FALLBACK_SPROM_H
#define __BCM47XX_FALLBACK_SPROM_H

#include <linux/types.h>

struct bcma_bus;
struct ssb_sprom;

int bcm47xx_register_fallback_sprom(void);

#endif /* _BCM47XX_FALLBACK_SPROM_H */
