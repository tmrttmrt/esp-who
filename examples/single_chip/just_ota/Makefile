#
# This is a project Makefile. It is assumed the directory this Makefile resides in is a
# project subdirectory.
#
CFLAGS := -Os
PROJECT_NAME := OTAU_server

#COMPONENTS := main pthread console mdns partition_table esptool_py esp32 esp_eth app_update esp_common \
#              spi_flash soc bootloader bootloader_support efuse freertos xtensa esp_rom heap log \
#              driver mbedtls nvs_flash esp_event esp_wifi tcpip_adapter lwip vfs newlib esp_core_dump \
#              espcoredump app_trace wpa_supplicant esp_ringbuf ota_server 

SOLUTION_PATH ?= $(abspath $(shell pwd))/../../..

EXTRA_COMPONENT_DIRS += $(SOLUTION_PATH)/components/ota_server
include $(IDF_PATH)/make/project.mk

ota: app
	curl ${ESP32_IP}:8032 --data-binary @- < build/$(PROJECT_NAME).bin