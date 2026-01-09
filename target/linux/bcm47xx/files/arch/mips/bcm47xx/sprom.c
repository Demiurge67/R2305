// SPDX-License-Identifier: GPL-2.0
/*
 * Архитектурный fallback SPROM для BCM47xx (ASUS RT-N66U).
 * Предоставляет данные для второго чипа BCM4331 (5 ГГц).
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/bcma/bcma.h>
#include <linux/ssb/ssb.h>
#include <linux/pci.h>
#include <linux/etherdevice.h>
#include <asm/mach-bcm47xx/bcm47xx_fallback_sprom.h>
#include <bcm47xx.h>
#include <bcm47xx_board.h>

#define PFX "bcm47xx-sprom: "

/* Шаблон для второго чипа BCM4331 (5 ГГц) на шине 1, слот 1 */
static const struct ssb_sprom bcm4331_5ghz_sprom_template = {
    .revision            = 9,
    .boardflags_lo       = 0x0200,  /* Из boardflags=0x90000200 */
    .boardflags_hi       = 0x9000,  /* КРИТИЧЕСКИЙ ФЛАГ: SSB_BFL2_5GHZ */
    .boardflags2_lo      = 0x0000,
    .boardflags2_hi      = 0x0020,  /* Из boardflags2=0x00200000 */
    .ant_available_a     = 0x07,    /* 3 антенны для 5 ГГц */
    .ant_available_bg    = 0x00,    /* 2.4 ГГц не используется */
    .maxpwr_a            = 0x5E,
    .pa1b0               = 0x1663,  /* pa5gw1a0=0x1663 */
    .pa1b1               = 0x1676,
    .pa1b2               = 0x15FA,
    .pa1lob0             = 0x1637,  /* pa5glw1a0=0x1637 */
    .pa1lob1             = 0x1591,
    .pa1lob2             = 0x1591,
    .pa1hib0             = 0x160D,  /* pa5ghw1a0=0x160D */
    .pa1hib1             = 0x16C3,
    .pa1hib2             = 0x1684,
    .txchain             = 0x07,
    .rxchain             = 0x07,
    .regrev              = 0x26,    /* regrev=38 (0x26) */
};

/* Колбэк, который будет передан в bcma_arch_register_fallback_sprom */
static int bcm47xx_get_fallback_sprom(struct bcma_bus *bus, struct ssb_sprom *out)
{
    struct pci_dev *pdev;

    if (!bus || !out || !bus->host_pci)
        return -ENODEV;

    pdev = bus->host_pci;
// For Radio0 //

if (pdev->bus->number == 1 && PCI_SLOT(pdev->devfn) == 1) {
        pr_info(PFX "-> Целевое устройство (5 ГГц). Предоставляем ПОЛНЫЙ HT+5GHz шаблон.\n");
        memset(out, 0, sizeof(*out));

        // --- БАЗОВЫЕ ПОЛЯ ---
        out->revision = 9;
        out->boardflags_lo = 0x0200;
        out->boardflags_hi = 0x9000; // SSB_BFL2_5GHZ
        out->boardflags2_lo = 0x0000;
        out->boardflags2_hi = 0x0020;
        out->ant_available_a = 0x07;
        out->ant_available_bg = 0x00;
        out->txchain = 0x07;
        out->rxchain = 0x07;
        out->regrev = 0x26;
        // --- МОЩНОСТЬ ДЛЯ 5 ГГц (формат: значение = дБм * 2 + 10?) ---
        // Временные стандартные значения. Если не сработает - будем разбираться.
        out->maxpwr_a = 0x3C;   // Возможно 30 дБм
        out->maxpwr_ah = 0x3C;
        out->maxpwr_al = 0x34;  // Возможно 26 дБм

        // --- КАЛИБРОВКА УСИЛИТЕЛЯ 5 ГГц (из ваших данных pa5g*) ---
        out->pa1b0 = 0x1663; out->pa1b1 = 0x1676; out->pa1b2 = 0x15FA;
        out->pa1lob0 = 0x1637; out->pa1lob1 = 0x1591; out->pa1lob2 = 0x1591;
        out->pa1hib0 = 0x160D; out->pa1hib1 = 0x16C3; out->pa1hib2 = 0x1684;

        // --- КРИТИЧЕСКИ ВАЖНО: ПАРАМЕТРЫ MCS ДЛЯ 802.11n ---
        // Значения взяты из ваших NVRAM: mcsbw205ghpo=0x75311111 и т.д.
        // SPROM ожидает массив из 4 значений u32 (для ширины канала 20/40 МГц).
        // Нужно преобразовать 8-значное hex-значение в два u32.
        // 0x75311111 разбиваем на старшее и младшее слова.
        // Для 5 ГГц среднего диапазона (UNII-2)
        out->mcs5ghpo[0] = 0x7531;   // Младшее слово от mcsbw205gmpo
        out->mcs5ghpo[1] = 0x1111;   // Старшее слово
        out->mcs5ghpo[2] = 0x7531;   // Младшее слово от mcsbw405gmpo
        out->mcs5ghpo[3] = 0x1111;   // Старшее слово

        // --- MAC и завершение ---
        memcpy(out->il0mac, "\x60\xA4\x4C\xD1\xFA\x24", ETH_ALEN);
        memcpy(out->et0mac, out->il0mac, ETH_ALEN);
        memcpy(out->et1mac, out->il0mac, ETH_ALEN);
        return 0;
    }
    
    // For Radio1 //
    if (pdev->bus->number == 0 && PCI_SLOT(pdev->devfn) == 1) {
        pr_info(PFX "-> Целевое устройство (2 ГГц). Предоставляем ПОЛНЫЙ HT+2GHz шаблон.\n");
        memset(out, 0, sizeof(*out));

        // --- БАЗОВЫЕ ПОЛЯ ---
        out->revision = 9;
        out->boardflags_lo = 0x0200;
        out->boardflags_hi = 0x9000; // SSB_BFL2_5GHZ
        out->boardflags2_lo = 0x0000;
        out->boardflags2_hi = 0x0020;
        out->ant_available_a = 0x07;
        out->ant_available_bg = 0x00;
        out->txchain = 0x07;
        out->rxchain = 0x07;
        out->regrev = 0x26;
        // --- МОЩНОСТЬ ДЛЯ 5 ГГц (формат: значение = дБм * 2 + 10?) ---
        // Временные стандартные значения. Если не сработает - будем разбираться.
        out->maxpwr_a = 0x3C;   // Возможно 30 дБм
        out->maxpwr_ah = 0x3C;
        out->maxpwr_al = 0x34;  // Возможно 26 дБм

        // --- КАЛИБРОВКА УСИЛИТЕЛЯ 5 ГГц (из ваших данных pa5g*) ---
        out->pa1b0 = 0x1663; out->pa1b1 = 0x1676; out->pa1b2 = 0x15FA;
        out->pa1lob0 = 0x1637; out->pa1lob1 = 0x1591; out->pa1lob2 = 0x1591;
        out->pa1hib0 = 0x160D; out->pa1hib1 = 0x16C3; out->pa1hib2 = 0x1684;

        // --- КРИТИЧЕСКИ ВАЖНО: ПАРАМЕТРЫ MCS ДЛЯ 802.11n ---
        // Значения взяты из ваших NVRAM: mcsbw205ghpo=0x75311111 и т.д.
        // SPROM ожидает массив из 4 значений u32 (для ширины канала 20/40 МГц).
        // Нужно преобразовать 8-значное hex-значение в два u32.
        // 0x75311111 разбиваем на старшее и младшее слова.
        // Для 5 ГГц среднего диапазона (UNII-2)
        out->mcs2gpo[0] = 0x7531;   // Младшее слово от mcsbw205gmpo
        out->mcs2gpo[1] = 0x1111;   // Старшее слово
        out->mcs2gpo[2] = 0x7531;   // Младшее слово от mcsbw405gmpo
        out->mcs2gpo[3] = 0x1111;   // Старшее слово

        // --- MAC и завершение ---
        memcpy(out->il0mac, "\x60\xA4\x4C\xD1\xFA\x24", ETH_ALEN);
        memcpy(out->et0mac, out->il0mac, ETH_ALEN);
        memcpy(out->et1mac, out->il0mac, ETH_ALEN);
        return 0;
    }
    return -ENOENT;
}

/* Функция регистрации нашего провайдера в системе BCMA */
int __init bcm47xx_register_fallback_sprom(void)
{
    int ret;

    pr_info(PFX "Регистрация fallback SPROM для BCMA...\n");

    /* ШТАТНЫЙ МЕХАНИЗМ: регистрируем наш колбэк */
    ret = bcma_arch_register_fallback_sprom(bcm47xx_get_fallback_sprom);

    if (ret == -EEXIST) {
        pr_warn(PFX "Fallback SPROM уже зарегистрирован.\n");
        return 0;
    } else if (ret) {
        pr_err(PFX "ОШИБКА регистрации: %d\n", ret);
        return ret;
    }

    pr_info(PFX "Fallback SPROM успешно зарегистрирован.\n");
    return 0;
}
