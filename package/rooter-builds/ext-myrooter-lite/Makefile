#Owned by Demiurge67@4PDA
#
#Copyright GNU act.
include $(TOPDIR)/rules.mk

PKG_NAME:=ext-myrooter-lite
PKG_VERSION:=1.000
PKG_RELEASE:=1

PKG_MAINTAINER:=Created by Demiurge67@4PDA
include $(INCLUDE_DIR)/package.mk

define Package/ext-myrooter-lite
  SECTION:=utils
  CATEGORY:=ROOter
  DEPENDS:=+luci +ext-myrooter-basic +ext-logo \
  		+ext-theme +ext-login +luci-theme-materialgrey +luci-theme-argon \
		+luci-app-ddns +ddns-scripts \
		+bwmon +464xlat +webconsole +kmod-mtd-rw \
		+ca-bundle +ca-certificates +usb-storage \
		+kmod-sched-cake +luci-app-nft-qos \
		+ext-command +ext-speedtest \
		+ext-wireguard +luci-app-v2raya +v2ray-geoip +v2ray-geosite \
		+openvpn-easy-rsa +openvpn-openssl \
		+usbmuxd +libusbmuxd-utils +libimobiledevice-utils +kmod-usb-net-ipheth \
		+luci-ssl +usbutils +openssl-util +ethtool +ext-splashconfig \
		+nano +picocom +luci-app-vpnbypass
  TITLE:=ROOter support w/o MWan3 for 16meg and larger routers
  PKGARCH:=all
endef

define Package/ext-myrooter-lite/description
  Helper scripts to enable ROOter w/o MWan3 on 16meg and larger routers
endef

define Build/Compile
endef

$(eval $(call BuildPackage,ext-myrooter-lite))
