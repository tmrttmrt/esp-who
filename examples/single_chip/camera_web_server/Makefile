#
# This is a project Makefile. It is assumed the directory this Makefile resides in is a
# project subdirectory.
#

PROJECT_NAME := camera_web_server

SOLUTION_PATH ?= $(abspath $(shell pwd))/../../..

include $(SOLUTION_PATH)/components/component_conf.mk
include $(IDF_PATH)/make/project.mk

ota: app 
	echo "factory" | curl ${ESP32_IP}:8032  -H "Content-Type: text/parameters" --data-binary @- | true 
	sleep 3 
	curl ${ESP32_IP}:8032 -H "Content-Type: application/octet-stream" --data-binary @- < build/$(PROJECT_NAME).bin
