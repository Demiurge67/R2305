#Owned by Demiurge67@4pda
#
#Copyright GNU act.
include $(TOPDIR)/rules.mk

PKG_NAME:=ext-Hilink7621a
PKG_VERSION:=2.000
PKG_RELEASE:=2

PKG_MAINTAINER:=Created by DM/makefile by Demiurge67@4pda
include $(INCLUDE_DIR)/package.mk

define Package/ext-Hilink7621a
  SECTION:=utils
  CATEGORY:=ROOter
  DEPENDS:=+ext-myrooter-basic +luci +luci-app-ddns \
  		+ddns-scripts +webconsole \
		+bwmon +464xlat +luci-ssl \
		+luci-theme-argondark +luci-theme-materialgrey \
		+ext-theme +ext-login \
		+ca-bundle +ca-certificates \
		+luci-app-ksmbd +usb-storage +luci-app-openvpn \
		+ext-command +ext-speedtest +ext-extra \
		+usbmuxd +libusbmuxd-utils +libimobiledevice-utils +kmod-usb-net-ipheth \
		+usbutils +openssl-util +ethtool +ext-splashconfig \
		+nano +picocom +wget
  TITLE:=ROOter support Hilink7621a routers
  PKGARCH:=all
endef

define Package/ext-Hilink7621a/description
  Helper scripts to enable ROOter Hilink7621a routers
endef


define Build/Compile
endef

$(eval $(call BuildPackage,ext-Hilink7621a))
