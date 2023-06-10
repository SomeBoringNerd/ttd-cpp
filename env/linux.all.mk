CC := g++
CFLAGS := $(CFLAGS) -fpic

LIB_DIRS := \
	/usr/local/lib

INCLUDE_DIRS := \
	/usr/local/include

BUILD_FLAGS := \
	$(BUILD_FLAGS) \
	-pthread

LINK_LIBRARIES := \
	$(LINK_LIBRARIES) \
	stdc++fs \
	X11

PRODUCTION_LINUX_ICON := logo

PRODUCTION_LINUX_APP_NAME := Pixel Plight
PRODUCTION_LINUX_APP_COMMENT := Small rpg
