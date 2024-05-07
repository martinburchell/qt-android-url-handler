# =============================================================================
# Parts of Qt
# =============================================================================

QT += widgets  # required to #include <QApplication>

# =============================================================================
# Overall configuration
# =============================================================================

CONFIG += mobility
CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS


# =============================================================================
# Compiler and linker flags
# =============================================================================

gcc {
    QMAKE_CXXFLAGS += -Werror  # warnings become errors
}

if (gcc | clang):!ios:!android {
    QMAKE_CXXFLAGS += -Wno-deprecated-copy
}

gcc {
    QMAKE_CXXFLAGS += -fvisibility=hidden
}

# =============================================================================
# Build targets
# =============================================================================

TARGET = qt-android-url-handler
TEMPLATE = app

# -----------------------------------------------------------------------------
# Architecture
# -----------------------------------------------------------------------------

linux : {
    CONFIG += static
}

android {
    ANDROID_PACKAGE_SOURCE_DIR = $${PWD}/android
    DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/res/values/libs.xml
}

# =============================================================================
# Source files
# =============================================================================

SOURCES += \
    main.cpp \
    urlhandler.cpp

HEADERS += \
    urlhandler.h

OTHER_FILES += \
    android/AndroidManifest.xml \
    android/src/org/example/example/CustomActivity.java
