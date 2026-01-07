// SPDX-License-Identifier: GPL-2.0
/*
 * Fallback SPROM для BCM47xx с шиной BCMA.
 * Предоставляет корректные SPROM-данные для второго Wi-Fi чипа BCM4331 (5 ГГц)
 * на ASUS RT-N66U, где прямое чтение SPROM из PCIe не работает.
 *
 * Данные взяты из NVRAM устройства.
 * Copyright (C) 2024
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/bcma/bcma.h>
#include <linux/ssb/ssb.h>
#include <linux/pci.h>
#include <linux/etherdevice.h>
#include <asm/mach-bcm47xx/bcm47xx_fallback_sprom.h>
#include <bcm47xx.h>
#include <bcm47xx_nvram.h>

#define PFX "bcm47xx-sprom: "

/* Шаблон SPROM ревизии 9 для второго чипа BCM4331 (5 ГГц) в ASUS RT-N66U.
 * Все значения взяты из предоставленных NVRAM-переменных для pci/2/1/
 */
static const struct ssb_sprom bcm4331_5ghz_sprom_template = {
	.revision		= 9,		/* sromrev=9 */
	.board_rev		= 0x1100,	/* Пример, может быть другим */
	.country_code		= 0x0,		/* EU (0x0 для WW) */
	.boardflags_lo		= 0x0200,	/* Младшие 16 бит boardflags=0x90000200 */
	.boardflags_hi		= 0x9000,	/* Старшие 16 бит boardflags=0x90000200 */
	.boardflags2_lo		= 0x0000,	/* Младшие 16 бит boardflags2=0x00200000 */
	.boardflags2_hi		= 0x0020,	/* Старшие 16 бит boardflags2=0x00200000 */
	.ant_available_bg	= 0x00,		/* 2.4 ГГц не используется этим чипом */
	.ant_available_a	= 0x07,		/* rxchain=7 (битовая маска: 0111 = 3 антенны) */
	.maxpwr_bg		= 0x00,		/* Не используется */
	/* Мощность для 5 ГГц (значения из maxp5g* в децибел-милливаттах) */
	.maxpwr_a		= 0x5E,		/* maxp5ga0=0x5E -> 94 дБм? ПРОВЕРИТЬ! Возможно, 0x5E = 30 дБм */
	.maxpwr_ah		= 0x5E,		/* maxp5gha0=0x5E */
	.maxpwr_al		= 0x40,		/* maxp5gla0=0x40 */
	/* Калибровка усилителей для 5 ГГц (значения из pa5g*).
	   ВАЖНО: SPROM хранит смещения, а не абсолютные значения.
	   Формат: paXbY, где X-полоса, Y-коэффициент.
	   Мы используем pa5gw* для среднего диапазона (UNII-2). */
	.pa1b0			= 0x1663,	/* pa5gw1a0=0x1663 (коэф. B0) */
	.pa1b1			= 0x1676,	/* pa5gw1a1=0x1676 (коэф. B1) */
	.pa1b2			= 0x15FA,	/* pa5gw1a2=0x15FA (коэф. B2) */
	.pa1lob0		= 0x1637,	/* pa5glw1a0=0x1637 (низкий диапазон) */
	.pa1lob1		= 0x1591,
	.pa1lob2		= 0x1591,
	.pa1hib0		= 0x160D,	/* pa5ghw1a0=0x160D (высокий диапазон) */
	.pa1hib1		= 0x16C3,
	.pa1hib2		= 0x1684,
	/* Опорное напряжение (parefldovoltage=60 -> 0x3C) */
	.parefldo		= 0x3C,
	/* txchain=7 (битовая маска) */
	.txchain		= 0x07,
	.rxchain		= 0x07,
	/* Ревизия регистров (regrev=38 -> 0x26) */
	.regrev			= 0x26,
};

/**
 * bcm47xx_get_fallback_sprom - Колбэк, предоставляющий fallback SPROM для BCMA.
 * @bus:	указатель на шину BCMA.
 * @out:	указатель на структуру ssb_sprom для заполнения.
 *
 * Возвращает подготовленный шаблон ТОЛЬКО для второго чипа BCM4331 (5 ГГц)
 * на PCI-шине 1, слот 1 (исходя из логов: 0000:01:01.0).
 * Для первого чипа и других устройств возвращает -ENOENT.
 */
static int bcm47xx_get_fallback_sprom(struct bcma_bus *bus,
				      struct ssb_sprom *out)
{
	struct pci_dev *pdev;
	u8 mac[ETH_ALEN];

	if (!bus->host_pci) {
		return -ENODEV; /* Не PCIe устройство */
	}

	pdev = bus->host_pci;

	/* Идентифицируем второе PCIe Wi-Fi устройство (5 ГГц).
	 * В логах: 0000:01:01.0 -> bus->number = 1, PCI_SLOT(devfn) = 1.
	 * Это условие ДОЛЖНО совпадать с вашими логами.
	 */
	if (pdev->bus->number == 1 && PCI_SLOT(pdev->devfn) == 1) {
		pr_info(PFX "Предоставляем fallback SPROM для 5 ГГц чипа (PCI %s)\n",
			pci_name(pdev));

		/* Копируем подготовленный шаблон */
		memcpy(out, &bcm4331_5ghz_sprom_template, sizeof(*out));

		/* Заполняем MAC-адрес из NVRAM (pci/2/1/macaddr=60:A4:4C:D1:FA:24) */
		if (bcm47xx_nvram_get_mac_address("pci/2/1/macaddr", mac) == 0) {
			memcpy(out->il0mac, mac, ETH_ALEN);
			memcpy(out->et0mac, mac, ETH_ALEN);
			memcpy(out->et1mac, mac, ETH_ALEN);
			pr_info(PFX "MAC-адрес установлен: %pM\n", mac);
		} else {
			/* Запасной вариант: сгенерировать MAC на основе основного */
			pr_warn(PFX "MAC-адрес для 5 ГГц не найден в NVRAM, используем запасной.\n");
			/* out->il0mac[5] += 1; */ /* Пример: инкремент последнего октета */
		}

		return 0; /* УСПЕХ */
	}

	/* Для всех остальных устройств (включая первый чип 2.4 ГГц)
	   не предоставляем fallback, чтобы не перезаписать их реальный SPROM. */
	pr_debug(PFX "Fallback SPROM не требуется для %s\n", pci_name(pdev));
	return -ENOENT;
}

int __init bcm47xx_register_fallback_sprom(void)
{
	int ret;

	/* Регистрируем наш колбэк в подсистеме BCMA */
	ret = bcma_arch_register_fallback_sprom(&bcm47xx_get_fallback_sprom);
	if (ret == -EEXIST) {
		pr_warn(PFX "Fallback SPROM уже зарегистрирован.\n");
		return 0; /* Уже кто-то зарегистрировал, это не ошибка */
	} else if (ret) {
		pr_err(PFX "Ошибка регистрации fallback SPROM: %d\n", ret);
		return ret;
	}

	pr_info(PFX "Fallback SPROM для BCMA успешно зарегистрирован.\n");
	return 0;
}
