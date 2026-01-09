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

    /* Первый чип на 0000:00:01.0 (bus 0, slot 1) */
    if (pdev->bus->number == 0 && PCI_SLOT(pdev->devfn) == 1) {
        pr_info(PFX "-> Первый BCM4331 (0000:00:01.0). Заполняем SPROM из pci/1/1/\n");

        memset(out, 0, sizeof(struct ssb_sprom));
        
        /* Аппаратный ID одинаков для обоих чипов */
        out->dev_id = 0x4331;
        out->revision = 9;  /* sromrev=9 */
        
        /* BOARD FLAGS из NVRAM: pci/1/1/boardflags=0x80001200 */
        out->boardflags_lo = 0x1200;  /* Младшие 16 бит */
        out->boardflags_hi = 0x8000;  /* Старшие 16 бит */
        
        /* BOARD FLAGS 2: pci/1/1/boardflags2=0x00100000 */
        out->boardflags2_lo = 0x0000;  /* Младшие 16 бит */
        out->boardflags2_hi = 0x0010;  /* Старшие 16 бит */
        
        /* Антенны и цепи */
        out->ant_available_bg = 0x07;  /* rxchain=7 для 2.4 ГГц */
        out->ant_available_a = 0x00;   /* 5 ГГц антенны отключены */
        out->txchain = 0x07;
        out->rxchain = 0x07;
        
        /* Мощность 2.4 ГГц (максимальная) */
        out->maxpwr_bg = 0x64;  /* maxp2ga0=0x64 (значение как есть) */
        
        /* Калибровка усилителя 2.4 ГГц */
        out->pa0b0 = 0x1AAD;  /* pa2gw1a0=0x1AAD */
        out->pa0b1 = 0x1CAD;  /* pa2gw1a1=0x1CAD */
        out->pa0b2 = 0x19F1;  /* pa2gw1a2=0x19F1 */
        
        /* MCS для 802.11n в 2.4 ГГц */
        /* mcsbw202gpo=0xFC955555 -> преобразуем в два u16 */
        out->mcs2gpo[0] = 0xFC95;
        out->mcs2gpo[1] = 0x5555;
        out->mcs2gpo[2] = 0xFC95;
        out->mcs2gpo[3] = 0x5555;
        
        /* MAC-адрес из NVRAM: pci/1/1/macaddr */
        memcpy(out->il0mac, "\x60\xA4\x4C\xD1\xFA\x20", ETH_ALEN);
        memcpy(out->et0mac, out->il0mac, ETH_ALEN);
        memcpy(out->et1mac, out->il0mac, ETH_ALEN);
        
        /* Ревизия регистров */
        out->regrev = 0x42;  /* regrev=66 (0x42) */
        
        pr_info(PFX "-> SPROM для первого чипа готов. boardflags_hi=0x%04x\n", 
                out->boardflags_hi);
        return 0;
    }

    /* Второй чип на 0000:01:01.0 (bus 1, slot 1) */
    if (pdev->bus->number == 1 && PCI_SLOT(pdev->devfn) == 1) {
        pr_info(PFX "-> Второй BCM4331 (0000:01:01.0). Заполняем SPROM из pci/2/1/\n");

        memset(out, 0, sizeof(struct ssb_sprom));
        
        /* Аппаратный ID одинаков для обоих чипов */
        out->dev_id = 0x4331;
        out->revision = 9;  /* sromrev=9 */
        
        /* КРИТИЧЕСКИ ВАЖНО: флаги для 5 ГГц */
        /* pci/2/1/boardflags=0x90000200 */
        out->boardflags_lo = 0x0200;  /* Младшие 16 бит */
        out->boardflags_hi = 0x9000;  /* Старшие 16 бит (SSB_BFL2_5GHZ | SSB_BFL2_5GHP) */
        
        /* BOARD FLAGS 2: pci/2/1/boardflags2=0x00200000 */
        out->boardflags2_lo = 0x0000;  /* Младшие 16 бит */
        out->boardflags2_hi = 0x0020;  /* Старшие 16 бит */
        
        /* Антенны и цепи */
        out->ant_available_a = 0x07;   /* rxchain=7 для 5 ГГц */
        out->ant_available_bg = 0x07;  /* также 3 антенны для 2.4 ГГц */
        out->txchain = 0x07;
        out->rxchain = 0x07;
        
        /* Мощность для 5 ГГц (берём значения как есть из NVRAM) */
        out->maxpwr_a = 0x5E;   /* maxp5ga0=0x5E */
        out->maxpwr_ah = 0x5E;  /* maxp5gha0=0x5E */
        out->maxpwr_al = 0x40;  /* maxp5gla0=0x40 */
        
        /* Калибровка усилителя 5 ГГц */
        out->pa1b0 = 0x1663;  /* pa5gw1a0=0x1663 */
        out->pa1b1 = 0x1676;  /* pa5gw1a1=0x1676 */
        out->pa1b2 = 0x15FA;  /* pa5gw1a2=0x15FA */
        
        out->pa1lob0 = 0x1637;  /* pa5glw1a0=0x1637 */
        out->pa1lob1 = 0x1591;
        out->pa1lob2 = 0x1591;
        
        out->pa1hib0 = 0x160D;  /* pa5ghw1a0=0x160D */
        out->pa1hib1 = 0x16C3;
        out->pa1hib2 = 0x1684;
        
        /* MCS для 802.11n в 5 ГГц */
        /* mcsbw205gmpo=0x75311111 */
        out->mcs5gpo[0] = 0x7531;
        out->mcs5gpo[1] = 0x1111;
        out->mcs5gpo[2] = 0x7531;
        out->mcs5gpo[3] = 0x1111;
        
        /* mcsbw205glpo=0x00000000 */
        out->mcs5glpo[0] = 0x0000;
        out->mcs5glpo[1] = 0x0000;
        out->mcs5glpo[2] = 0x0000;
        out->mcs5glpo[3] = 0x0000;
        
        /* mcsbw205ghpo=0x75311111 */
        out->mcs5ghpo[0] = 0x7531;
        out->mcs5ghpo[1] = 0x1111;
        out->mcs5ghpo[2] = 0x7531;
        out->mcs5ghpo[3] = 0x1111;
        
        /* MAC-адрес из NVRAM: pci/2/1/macaddr */
        memcpy(out->il0mac, "\x60\xA4\x4C\xD1\xFA\x24", ETH_ALEN);
        memcpy(out->et0mac, out->il0mac, ETH_ALEN);
        memcpy(out->et1mac, out->il0mac, ETH_ALEN);
        
        /* Ревизия регистров */
        out->regrev = 0x26;  /* regrev=38 (0x26) */
        
        /* Дополнительные параметры */
        out->parefldo = 0x3C;  /* parefldovoltage=60 (0x3C) */
        
        pr_info(PFX "-> SPROM для второго чипа готов. boardflags_hi=0x%04x\n", 
                out->boardflags_hi);
        return 0;
    }

    /* Для остальных устройств */
    pr_debug(PFX "-> Неизвестное устройство %s\n", pci_name(pdev));
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
