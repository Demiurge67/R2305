#Owned by DairyMan@Whirlpool
#
#Copyright GNU act.
include $(TOPDIR)/rules.mk

PKG_NAME:=ext-rooter-basic-no-modem
PKG_VERSION:=0.500
PKG_RELEASE:=1

PKG_MAINTAINER:=Created by DM/makefile by Demiurge67@4pda
include $(INCLUDE_DIR)/package.mk

define Package/ext-rooter-basic-no-modem
  SECTION:=utils
  CATEGORY:=ROOter
  SUBMENU:=Basic Support
  DEPENDS:=+luci-compat +kmod-nls-utf8 \
	    +iptables-nft +ip6tables-nft \
	    +kmod-ipt-nat +kmod-ipt-nat-extra +kmod-ipt-nat6 +kmod-ipt-offload \
	    +kmod-ip6tables-extra \
	    +ip6tables-mod-nat +iptables-mod-extra \
	    +https-dns-proxy +luci-app-https-dns-proxy \
	    +wireless-tools +ext-buttons +xxd +kmod-tcp-bbr 
  TITLE:=ROOter support for router without usbmodems
  PKGARCH:=all
endef

define Package/ext-rooter-basic-no-modem/description
  Helper scripts to enable ROOter to router without modem 
endef


define Build/Compile
endef

define Package/ext-rooter-basic-no-modem/install
	$(CP) ./files/* $(1)/


endef

$(eval $(call BuildPackage,ext-rooter-basic-no-modem))
