include $(TOPDIR)/rules.mk

PKG_NAME:=libjpeg-turbo
PKG_VERSION:=2.1.4
PKG_RELEASE:=2

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=@SF/$(PKG_NAME)
PKG_HASH:=d3ed26a1131a13686dfca4935e520eb7c90ae76fbc45d98bb50a8dc86230342b

PKG_MAINTAINER:=Rosen Penev <rosenp@gmail.com>
PKG_LICENSE:=BSD-3-Clause IJG zlib
PKG_LICENSE_FILES:=LICENSE.md
PKG_CPE_ID:=cpe:/a:libjpeg-turbo:libjpeg-turbo

# Allows ASM compilation for speed
PKG_BUILD_FLAGS:=no-mips16

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/libjpeg-turbo/Default
  TITLE:=libjpeg-turbo
  URL:=https://www.libjpeg-turbo.org/
endef

define Package/libjpeg-turbo
  $(call Package/libjpeg-turbo/Default)
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE+= runtime library
  PROVIDES:=libjpeg
endef

define Package/libjpeg-turbo-utils
  $(call Package/libjpeg-turbo/Default)
  SECTION:=utils
  CATEGORY:=Utilities
  SUBMENU:=Image Manipulation
  DEPENDS:=+libjpeg-turbo
  TITLE+= manipulation tools
  PROVIDES:=jpeg-tools
endef

define Package/libjpeg-turbo/description
	libjpeg-turbo is a speed focused fork of libjpeg.
endef

define Package/libjpeg-turbo-utils/description
	These are the JPEG utilities that come with libjpeg-turbo.
endef

CMAKE_OPTIONS += \
	-DENABLE_SHARED=ON \
	-DENABLE_STATIC=ON \
	-DREQUIRE_SIMD=OFF \
	-DWITH_12BIT=OFF \
	-DWITH_ARITH_DEC=OFF \
	-DWITH_ARITH_ENC=OFF \
	-DWITH_JAVA=OFF \
	-DWITH_JPEG7=OFF \
	-DWITH_JPEG8=OFF \
	-DWITH_MEM_SRCDST=ON \
	-DWITH_SIMD=O$(if $(findstring mips,$(CONFIG_ARCH)),FF,N) \
	-DWITH_TURBOJPEG=OFF

ifneq ($(findstring arm,$(CONFIG_ARCH)),)
ifeq ($(findstring neon,$(CONFIG_CPU_TYPE)),)
	CMAKE_OPTIONS += -DWITH_SIMD=OFF
endif
endif

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_INSTALL_DIR)/usr/include/*.h $(1)/usr/include/
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libjpeg.so* $(1)/usr/lib/
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libjpeg.a $(1)/usr/lib/
	$(INSTALL_DIR) $(1)/usr/lib/pkgconfig
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/pkgconfig/*.pc $(1)/usr/lib/pkgconfig/
	$(SED) 's,/usr/include,$$$${prefix}/include,g' $(1)/usr/lib/pkgconfig/libjpeg.pc
	$(SED) 's,/usr/lib,$$$${exec_prefix}/lib,g' $(1)/usr/lib/pkgconfig/libjpeg.pc
endef

define Package/libjpeg-turbo/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libjpeg.so* $(1)/usr/lib
endef

define Package/libjpeg-turbo-utils/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/rdjpgcom $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/wrjpgcom $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/cjpeg $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/djpeg $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/jpegtran $(1)/usr/bin
endef

$(eval $(call BuildPackage,libjpeg-turbo))
$(eval $(call BuildPackage,libjpeg-turbo-utils))
