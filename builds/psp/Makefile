PSPSDK=$(shell psp-config --pspsdk-path)
TOOLCHAIN_DIR?=$(shell psp-config --pspdev-path)/psp

TARGET = Player
SOURCES = ../../src ../../../liblcf/src ../../../liblcf/src/generated
CPPFILES = $(foreach dir,$(SOURCES), $(wildcard $(dir)/*.cpp))
OBJS = $(CPPFILES:.cpp=.o)
INCLUDES = $(SOURCES)

INCDIR = $(foreach dir,$(INCLUDES), $(CURDIR)/$(dir))
CFLAGS = -G0 -g0 -O2 -Wall -DPSP -DPSPUI -DNDEBUG \
         -DPPSSPP_COMPATIBLE -fomit-frame-pointer -ffast-math \
         -ffunction-sections -Wl,--gc-sections
#-DPSPUI_SCALE
#-DLCF_SUPPORT_ICU
#CFLAGS +=  -DHAVE_WILDMIDI -DHAVE_TREMOR
CXXFLAGS = -std=gnu++14 $(CFLAGS) -fno-exceptions -fno-rtti

PSP_EBOOT_TITLE = EasyRPG Player
PSP_EBOOT_ICON = "144x80.png"
PSP_EBOOT_PIC1 = "480x272.png"
EXTRA_TARGETS = EBOOT.PBP

CFLAGS += -I$(TOOLCHAIN_DIR)/include/pixman-1 \
          -I$(TOOLCHAIN_DIR)/include

LIBS = -L$(TOOLCHAIN_DIR)/lib -L$(PSPSDK)/../lib \
       -lpixman-1 -lpng -lz \
       -lglib2d -lpspvram \
       -lpsprtc -lpsphprm \
       -lpspgu -lpsppower \
       -lpspdebug -lstdc++ -lm \
       -ljpeg -lfmt \
       -licui18n -licuuc -licudata
#-lWildMidi -lvorbisidec -logg

%.o: %.cpp
	@echo "Compiling $(notdir $^)..."
	@$(CXX) $(CXXFLAGS) -c $< -o $@

BUILD_PRX = 1
#PSP_FW_VERSION = 371
#PSP_LARGE_MEMORY ?= 1
#USE_USER_LIBS = 1
#ENCRYPT ?= 0

include $(PSPSDK)/lib/build.mak
