#ifndef __BCM47XX_FALLBACK_SPROM_H
#define __BCM47XX_FALLBACK_SPROM_H

#include <linux/types.h>

/* Регистрация функции fallback SPROM для архитектуры BCM47xx.
 * Должна вызываться из init-кода платформы.
 */
int bcm47xx_register_fallback_sprom(void);

#endif /* __BCM47XX_FALLBACK_SPROM_H */
