ITI_QT_GPIO_VERSION = 1.0
ITI_QT_GPIO_SITE = /home/youhana/iti_QT/REPO/QT_ITI/Task4_RpiLED
ITI_QT_GPIO_SITE_METHOD = local
ITI_QT_GPIO_OVERRIDE_SRCDIR = /home/youhana/iti_QT/REPO/QT_ITI/Task4_RpiLED

ITI_QT_GPIO_DEPENDENCIES = qt6base

ITI_QT_GPIO_CONF_OPTS = \
	-DCMAKE_BUILD_TYPE=Release

# for fonts
define ITI_QT_GPIO_INSTALL_FONTS
    mkdir -p $(TARGET_DIR)/usr/share/fonts
    cp $(ITI_QT_GPIO_PKGDIR)/fonts/*.ttf $(TARGET_DIR)/usr/share/fonts/
endef

# set environment
define ITI_QT_GPIO_INSTALL_ENV
    mkdir -p $(TARGET_DIR)/etc/profile.d
    echo 'export QT_QPA_FONTDIR=/usr/share/fonts' > $(TARGET_DIR)/etc/profile.d/qt-env.sh
    echo 'export LC_ALL=C' >> $(TARGET_DIR)/etc/profile.d/qt-env.sh
endef

ITI_QT_GPIO_POST_INSTALL_TARGET_HOOKS += ITI_QT_GPIO_INSTALL_FONTS
ITI_QT_GPIO_POST_INSTALL_TARGET_HOOKS += ITI_QT_GPIO_INSTALL_ENV

$(eval $(cmake-package))