#ARCH								:= mips
ARCH								:= MT7620

ifeq ($(ARCH),mips)
CROSSTOOLDIR				:=/opt/au/qsdk-dusun/qsdk
export	STAGING_DIR	:= $(CROSSTOOLDIR)/staging_dir
export	PATH				:=$(PATH):$(STAGING_DIR)/toolchain-mips_34kc_gcc-4.8-linaro_uClibc-1.0.14/bin
CROSS_CFLAGS				:= -I$(CROSSTOOLDIR)/staging_dir/toolchain-mips_34kc_gcc-4.8-linaro_uClibc-1.0.14/usr/include
CROSS_LDFLAGS				:= -L$(CROSSTOOLDIR)/staging_dir/toolchain-mips_34kc_gcc-4.8-linaro_uClibc-1.0.14/usr/lib
CROSS								:= mips-openwrt-linux-
endif

ifeq ($(ARCH),MT7620)
CROSSTOOLDIR 				:= /home/au/all/gwork/openwrt
CROSS   						:= mipsel-openwrt-linux-
export  STAGING_DIR	:= $(CROSSTOOLDIR)/staging_dir
export  PATH				:= $(PATH):$(STAGING_DIR)/toolchain-mipsel_24kec+dsp_gcc-4.8-linaro_uClibc-0.9.33.2/bin

CROSS_CFLAGS				:= -I$(CROSSTOOLDIR)/staging_dir/toolchain-mipsel_24kec+dsp_gcc-4.8-linaro_uClibc-0.9.33.2/usr/include
CROSS_CFLAGS				+= -I$(CROSSTOOLDIR)/staging_dir/target-mipsel_24kec+dsp_uClibc-0.9.33.2/usr/include
CROSS_LDFLAGS			:= -L$(CROSSTOOLDIR)/staging_dir/toolchain-mipsel_24kec+dsp_gcc-4.8-linaro_uClibc-0.9.33.2/usr/lib
CROSS_LDFLAGS			+= -L$(CROSSTOOLDIR)/staging_dir/target-mipsel_24kec+dsp_uClibc-0.9.33.2/usr/lib/ 
endif

GCC 		:= $(CROSS)gcc
CXX			:= $(CROSS)g++
AR			:= $(CROSS)ar
AS			:= $(CROSS)gcc
RANLIB	:= $(CROSS)ranlib
STRIP 	:= $(CROSS)strip
OBJCOPY	:= $(CROSS)objcopy
OBJDUMP := $(CROSS)objdump
SIZE		:= $(CROSS)size
LD			:= $(CROSS)ld
MKDIR		:= mkdir -p

CFLAGS							:= -Wall -g -O2 -I$(ROOTDIR)/libs/osi/include  -I$(ROOTDIR)/libs/other/include 
CFLAGS							+= -I$(ROOTDIR)/../rbsdk/$(VERSION)/include
CFLAGS							+= -fPIC
CFLAGS							+= -fpermissive
CXXFLAGS						:= -std=c++0x 
CXXFLAGS						+= $(CFLAGS)
TARGET_CFLAGS				+= $(CROSS_CFLAGS) 


LDFLAGS							:= -lm -lrt -ldl -lpthread -ljson-c -lubox -lblobmsg_json -lubus -lcares -lmosquitto -lssl -lcrypto
LDFLAGS							+= -lstdc++
TARGET_LDFLAGS			+= $(CROSS_LDFLAGS)
