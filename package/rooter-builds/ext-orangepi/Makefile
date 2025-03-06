#Owned by Demiurge67@4pda
#
#Copyright GNU act.
include $(TOPDIR)/rules.mk

PKG_NAME:=ext-orangepi
PKG_VERSION:=1.000
PKG_RELEASE:=1

PKG_MAINTAINER:=Created by DM/makefile by Demiurge67@4pda
include $(INCLUDE_DIR)/package.mk

define Package/ext-orangepi
  SECTION:=utils
  CATEGORY:=ROOter
  DEPENDS:=+ext-myrooter-basic +luci +luci-app-ddns +ddns-scripts +webconsole \
		+bwmon +464xlat +luci-ssl \
		+ext-theme +ext-login +gdisk +cgdisk +sgdisk \
		+luci-theme-argondark +luci-theme-materialgrey \
		+ca-bundle +ca-certificates \
		+luci-app-ksmbd +usb-storage \
		+ext-command +ext-speedtest \
		+ext-extra +luci-app-v2raya +v2ray-geoip +v2ray-geosite \
		+usbmuxd +libusbmuxd-utils +libimobiledevice-utils +kmod-usb-net-ipheth \
		+usbutils +openssl-util +ethtool +ext-splashconfig \
		+kmod-nft-queue +kmod-nf-conntrack +luci-app-youtubeUnblock\
		+luci-app-nft-qos +luci-app-https-dns-proxy \
		+nano +picocom +wget
  TITLE:=ROOter support OrangePi routers
  PKGARCH:=all
endef

define Package/ext-orangepi/description
  Helper scripts to enable ROOter OrangePi routers
endef


define Build/Compile
endef

$(eval $(call BuildPackage,ext-orangepi))
