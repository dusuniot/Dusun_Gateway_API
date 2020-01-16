ROOTDIR=$(shell pwd)
WORKDIR=$(ROOTDIR)/build
VERSION=V1.0.3

targets			+= Zigbee_test

.PHONY: targets

all : $(targets)

srcs		+= $(ROOTDIR)/test.c
srcs		+= $(ROOTDIR)/cmd.c
srcs		+= $(ROOTDIR)/parse_argv.c
srcs	  := $(subst .cpp,.c,$(srcs))

objs 		:= $(subst $(ROOTDIR),$(WORKDIR), $(subst .c,.o,$(srcs)))
objs		+= $(ROOTDIR)/../rbsdk/$(VERSION)/lib/librbsdk.a

-include $(ROOTDIR)/make/arch.mk
-include $(ROOTDIR)/make/rules.mk

$(eval $(call LinkApp,test,$(objs)))

	
