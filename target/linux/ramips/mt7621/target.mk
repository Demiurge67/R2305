#
# Copyright (C) 2009 OpenWrt.org
#

SUBTARGET:=mt7621
BOARDNAME:=MT7621 based boards
FEATURES+=spi nand ramdisk rtc usb minor
CPU_TYPE:=24kc
KERNELNAME:=vmlinux vmlinuz
# make Kernel/CopyImage use $LINUX_DIR/vmlinuz
IMAGES_DIR:=../../..

DEFAULT_PACKAGES += wpad-basic-mbedtls uboot-envtools

define Target/Description
	Build firmware images for Ralink MT7621 based boards.
endef

