#Owned by Demiurge67@4PDA
#
#Copyright GNU act.
include $(TOPDIR)/rules.mk

PKG_NAME:=ext-sercomm
PKG_VERSION:=1.000
PKG_RELEASE:=1

PKG_MAINTAINER:=Created by Demiurge67@4PDA
include $(INCLUDE_DIR)/package.mk

define Package/ext-sercomm
  SECTION:=utils
  CATEGORY:=ROOter
  DEPENDS:=+ext-myrooter-basic +luci +luci-app-ddns +ddns-scripts +webconsole \
		+bwmon +464xlat +luci-ssl \
		+ext-theme +ext-login \
		+ca-bundle +ca-certificates \
		+luci-app-ksmbd +usb-storage \
		+luci-app-sqm +kmod-sched-cake +luci-app-nft-qos \
		+ext-command +ext-speedtest \
		+ext-extra +luci-app-openvpn +ext-wireguard +luci-app-youtubeUnblock \
		+usbmuxd +libusbmuxd-utils +libimobiledevice-utils +kmod-usb-net-ipheth \
		+usbutils +openssl-util +ethtool +ext-splashconfig \
		+nano +picocom +wget +luci-app-vpnbypass
  TITLE:=ROOter support Sercomm routers
  PKGARCH:=all
endef

define Package/ext-sercomm/description
  Helper scripts to enable ROOter Sercomm routers 
endef

define Build/Compile
endef

$(eval $(call BuildPackage,ext-sercomm))
