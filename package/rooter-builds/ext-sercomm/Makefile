#Owned by DairyMan@Whirlpool
#
#Copyright GNU act.
include $(TOPDIR)/rules.mk

PKG_NAME:=ext-sercomm
PKG_VERSION:=1.000
PKG_RELEASE:=1

PKG_MAINTAINER:=Created by DM/makefile by Cobia@whirlpool
include $(INCLUDE_DIR)/package.mk

define Package/ext-sercomm
  SECTION:=utils
  CATEGORY:=ROOter
  DEPENDS:=+ext-rooter-basic +luci +luci-app-ddns +ddns-scripts +webconsole \
		+bwmon +464xlat +luci-app-rootervpn +ext-wireguard \
		+ext-theme +luci-theme-argon +luci-theme-argondark +ext-login \
		+ca-bundle +ca-certificates +luci-theme-materialgrey\
		+luci-app-ksmbd +usb-storage \
		+luci-app-sqm +kmod-sched-cake +luci-app-nft-qos \
		+ext-command +ext-speedtest \
		+openvpn-easy-rsa +openvpn-openssl \
		+ext-extra +luci-app-wol \
		+usbmuxd +libusbmuxd-utils +libimobiledevice-utils +kmod-usb-net-ipheth \
		+luci-ssl +usbutils +openssl-util +ethtool +ext-splashconfig \
		+nano +picocom +wget +luci-app-vpnbypass +qfirehose   
  TITLE:=ROOter support Sercomm routers
  PKGARCH:=all
endef

define Package/ext-sercomm/description
  Helper scripts to enable ROOter Sercomm routers
endef


define Build/Compile
endef

$(eval $(call BuildPackage,ext-sercomm))
