/*
 * Fallback SPROM support for BCM47xx
 *
 * Copyright (C) 2024 FixRTN66U
 */

#include <linux/types.h>
#include <linux/pci.h>
#include <linux/ssb/ssb.h>
#include <linux/bcma/bcma.h>
#include <asm/mach-bcm47xx/bcm47xx_fallback_sprom.h>

/* Сырые данные SPROM для BCM4331 (128 слов = 256 байт) */
static const u16 bcm4331_raw_sprom[] = {
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

struct fallback_sprom_entry {
	struct list_head list;
	struct bcma_fallback_sprom_info info;
	const u16 *sprom_data;
	size_t size;
};

static LIST_HEAD(fallback_sproms);
static DEFINE_SPINLOCK(fallback_sproms_lock);

int bcm47xx_register_fallback_sprom(const struct bcma_fallback_sprom_info *info,
				    const u16 *sprom_data, size_t size)
{
	struct fallback_sprom_entry *entry;
	
	if (!info || !sprom_data || size < SSB_SPROMSIZE_WORDS_R4 * 2)
		return -EINVAL;
	
	entry = kzalloc(sizeof(*entry), GFP_KERNEL);
	if (!entry)
		return -ENOMEM;
	
	memcpy(&entry->info, info, sizeof(*info));
	entry->sprom_data = sprom_data;
	entry->size = size;
	
	spin_lock(&fallback_sproms_lock);
	list_add_tail(&entry->list, &fallback_sproms);
	spin_unlock(&fallback_sproms_lock);
	
	return 0;
}
EXPORT_SYMBOL(bcm47xx_register_fallback_sprom);

int bcm47xx_get_fallback_sprom(const struct bcma_fallback_sprom_info *info,
			       struct bcma_sprom *out)
{
	struct fallback_sprom_entry *entry;
	int found = 0;
	
	if (!info || !out)
		return -EINVAL;
	
	spin_lock(&fallback_sproms_lock);
	list_for_each_entry(entry, &fallback_sproms, list) {
		if ((entry->info.bus == info->bus &&
		     entry->info.slot == info->slot &&
		     entry->info.func == info->func) ||
		    (entry->info.device == info->device &&
		     entry->info.vendor == info->vendor)) {
			
			const u16 *sprom = entry->sprom_data;
			
			/* Очистка структуры */
			memset(out, 0, sizeof(*out));
			
			/* Парсинг сырых данных */
			out->revision = sprom[SSB_SPROM_REVISION] & SSB_SPROM_REVISION_REV;
			out->dev_id = sprom[SSB_SPROM_DEVICEID];
			out->dev_id_override = 1;
			
			/* Калибровочные данные 2.4 ГГц */
			out->pa0b0 = sprom[SSB_SPROM4_PA0B0];
			out->pa0b1 = sprom[SSB_SPROM4_PA0B1];
			out->pa0b2 = sprom[SSB_SPROM4_PA0B2];
			
			/* Калибровочные данные 5 ГГц */
			out->pa1b0 = sprom[SSB_SPROM4_PA1B0];
			out->pa1b1 = sprom[SSB_SPROM4_PA1B1];
			out->pa1b2 = sprom[SSB_SPROM4_PA1B2];
			
			/* Антенны */
			out->ant_available_bg = sprom[SSB_SPROM4_ANTAVAIL_BG];
			out->ant_available_a = sprom[SSB_SPROM4_ANTAVAIL_A];
			
			/* Флаги платы */
			out->boardflags_lo = sprom[SSB_SPROM4_BOARDFLAGS_LO];
			out->boardflags_hi = sprom[SSB_SPROM4_BOARDFLAGS_HI];
			
			found = 1;
			break;
		}
	}
	spin_unlock(&fallback_sproms_lock);
	
	return found ? 0 : -ENOENT;
}

EXPORT_SYMBOL(bcm47xx_get_fallback_sprom);

static int __init bcm47xx_sprom_init(void)
{
	struct bcma_fallback_sprom_info info;
	int err;
	
	/* Первый BCM4331 (phy0) - шина 0, слот 1, dev_id 0x4332 */
	memset(&info, 0, sizeof(info));
	info.bus = 0;
	info.slot = 1;
	info.func = 0;
	info.vendor = 0x14e4;
	info.device = 0x4331;
	
	/* Копируем сырые данные и меняем dev_id на 0x4332 */
	u16 *sprom_copy_4332 = kmemdup(bcm4331_raw_sprom, sizeof(bcm4331_raw_sprom), GFP_KERNEL);
	if (!sprom_copy_4332)
		return -ENOMEM;
	
	sprom_copy_4332[SSB_SPROM_DEVICEID] = 0x4332; /* Меняем dev_id */
	
	err = bcm47xx_register_fallback_sprom(&info, sprom_copy_4332, sizeof(bcm4331_raw_sprom));
	if (err)
		kfree(sprom_copy_4332);
	
	/* Второй BCM4331 (phy1) - шина 1, слот 1, dev_id 0x4333 */
	info.bus = 1;
	info.slot = 1;
	
	u16 *sprom_copy_4333 = kmemdup(bcm4331_raw_sprom, sizeof(bcm4331_raw_sprom), GFP_KERNEL);
	if (!sprom_copy_4333)
		return 0; /* Первая регистрация уже выполнена */
	
	sprom_copy_4333[SSB_SPROM_DEVICEID] = 0x4333; /* Меняем dev_id */
	
	err = bcm47xx_register_fallback_sprom(&info, sprom_copy_4333, sizeof(bcm4331_raw_sprom));
	if (err)
		kfree(sprom_copy_4333);
	
	return 0;
}
arch_initcall(bcm47xx_sprom_init);


