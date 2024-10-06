#Owned by Demiurge67@4pda
#
#Copyright GNU act.
include $(TOPDIR)/rules.mk

PKG_NAME:=ext-Hilink7621a
PKG_VERSION:=1.000
PKG_RELEASE:=1

PKG_MAINTAINER:=Created by DM/makefile by Demiurge67@4pda
include $(INCLUDE_DIR)/package.mk

define Package/ext-Hilink7621a
  SECTION:=utils
  CATEGORY:=ROOter
  DEPENDS:=+ext-rooter-basic +luci +luci-app-ddns +ddns-scripts +webconsole \
		+bwmon +464xlat +luci-app-rootervpn +ext-wireguard \
		+ext-theme +luci-theme-argon +luci-theme-argondark +ext-login \
		+ca-bundle +ca-certificates \
		+luci-app-ksmbd +usb-storage +kmod-mtd-rw \
		+luci-app-sqm +kmod-sched-cake +luci-app-nft-qos \
		+ext-command +ext-speedtest \
		+openvpn-easy-rsa +openvpn-openssl \
		+ext-extra +luci-app-wol \
		+kmod-mhi-bus +kmod-mhi-net +kmod-mhi-pci-generic +kmod-mhi-wwan-ctrl \
		+kmod-mhi-wwan-mbim +kmod-qrtr-mhi +kmod-qrtr \
		+usbmuxd +libusbmuxd-utils +libimobiledevice-utils +kmod-usb-net-ipheth \
		+luci-ssl +usbutils +openssl-util +ethtool +ext-splashconfig \
		+nano +picocom +wget +luci-app-vpnbypass +qfirehose   
  TITLE:=ROOter support Hilink7621a routers
  PKGARCH:=all
endef

define Package/ext-Hilink7621a/description
  Helper scripts to enable ROOter Hilink7621a routers
endef


define Build/Compile
endef

$(eval $(call BuildPackage,ext-Hilink7621a))
