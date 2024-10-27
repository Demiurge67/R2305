#Owned by DairyMan@Whirlpool
#
#Copyright GNU act.
include $(TOPDIR)/rules.mk

PKG_NAME:=ext-xiaomi-x6s
PKG_VERSION:=1.000
PKG_RELEASE:=1

PKG_MAINTAINER:=Created by DM/makefile by Cobia@whirlpool
include $(INCLUDE_DIR)/package.mk

define Package/ext-xiaomi-x6s
  SECTION:=utils
  CATEGORY:=ROOter
  DEPENDS:=+ext-rooter-basic-no-modem +luci +luci-app-ddns +ddns-scripts +webconsole \
		+bwmon +464xlat +luci-app-rootervpn +ext-wireguard \
		+ext-theme +luci-theme-argon +luci-theme-argondark +ext-login \
		+ca-bundle +ca-certificates +luci-theme-materialgrey\
		+mesh-mesh +mesh-wpad +kmod-mtd-rw \
		+luci-app-sqm +kmod-sched-cake +luci-app-nft-qos \
		+ext-command +ext-speedtest +iperf3 \
		+openvpn-easy-rsa +openvpn-openssl \
		+ext-extra +luci-app-wol \
		+luci-app-shadowsocks-libev +shadowsocks-libev-config +shadowsocks-libev-ss-local \
		+shadowsocks-libev-ss-redir +shadowsocks-libev-ss-server +shadowsocks-libev-ss-tunnel \
		+luci-app-v2raya +v2raya +v2ray-core +v2ray-geoip +v2ray-geosite +v2ray-geosite-ir \
		+luci-ssl +openssl-util +ethtool +ext-splashconfig \
		+nano +picocom +wget +luci-app-vpnbypass    
  TITLE:=ROOter support xiaomi-x6s 
  PKGARCH:=all
endef

define Package/ext-xiaomi-x6s/description
  Helper scripts to enable ROOter support xiaomi-x6s
endef


define Build/Compile
endef

$(eval $(call BuildPackage,ext-xiaomi-x6s))
