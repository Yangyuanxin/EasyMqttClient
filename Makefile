CROSS_COMPILE = 
AS		= $(CROSS_COMPILE)as
LD		= $(CROSS_COMPILE)ld
CC		= $(CROSS_COMPILE)gcc
CPP		= $(CC) -E
AR		= $(CROSS_COMPILE)ar
NM		= $(CROSS_COMPILE)nm

STRIP		= $(CROSS_COMPILE)strip
OBJCOPY		= $(CROSS_COMPILE)objcopy
OBJDUMP		= $(CROSS_COMPILE)objdump

export AS LD CC CPP AR NM
export STRIP OBJCOPY OBJDUMP

CFLAGS := -std=gnu99 -Wall -O3 -g

CFLAGS += -I $(shell pwd)/
CFLAGS += -I $(shell pwd)/EasyMqtt/
CFLAGS += -I $(shell pwd)/ThirdPart/Mqtt/common/
CFLAGS += -I $(shell pwd)/ThirdPart/Mqtt/mqtt/
CFLAGS += -I $(shell pwd)/ThirdPart/Mqtt/mqttclient/
CFLAGS += -I $(shell pwd)/ThirdPart/Mqtt/network/
CFLAGS += -I $(shell pwd)/ThirdPart/Mqtt/network/mbedtls/configs/
CFLAGS += -I $(shell pwd)/ThirdPart/Mqtt/network/mbedtls/include/
CFLAGS += -I $(shell pwd)/ThirdPart/Mqtt/network/mbedtls/library/
CFLAGS += -I $(shell pwd)/ThirdPart/Mqtt/network/mbedtls/wrapper/
CFLAGS += -I $(shell pwd)/ThirdPart/Mqtt/platform/linux/

LDFLAGS := -lpthread -lm -g

export CFLAGS LDFLAGS

TOPDIR := $(shell pwd)
export TOPDIR

TARGET := a.out

obj-y += main.o
obj-y += $(shell pwd)/EasyMqtt/
obj-y += $(shell pwd)/ThirdPart/Mqtt/common/
obj-y += $(shell pwd)/ThirdPart/Mqtt/mqtt/
obj-y += $(shell pwd)/ThirdPart/Mqtt/mqttclient/
obj-y += $(shell pwd)/ThirdPart/Mqtt/network/
obj-y += $(shell pwd)/ThirdPart/Mqtt/network/mbedtls/library/
obj-y += $(shell pwd)/ThirdPart/Mqtt/network/mbedtls/wrapper/
obj-y += $(shell pwd)/ThirdPart/Mqtt/platform/linux/

all : start_recursive_build $(TARGET)
	@echo $(TARGET) has been built!
	rm -f $(shell find -name "built-in.o") $(shell find -name "*.d")
	find . -name "*.o" -exec mv -t OutPut/ {} +

start_recursive_build:
	rm -f $(shell find -name "*.o")
	rm -f $(shell find -name "*.d")
	rm -f $(TARGET)
	make -C ./ -f $(TOPDIR)/Makefile.build

$(TARGET) : built-in.o
	$(CC) -o $(TARGET) built-in.o $(LDFLAGS)

clean:
	rm -f $(shell find -name "*.o")
	rm -f $(shell find -name "*.d")
	rm -f $(TARGET)