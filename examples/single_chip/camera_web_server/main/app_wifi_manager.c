/*
Copyright (c) 2017-2020 Tony Pottier

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

@file user_main.c
@author Tony Pottier
@brief Entry point for the ESP32 application.
@see https://idyl.io
@see https://github.com/tonyp7/esp32-wifi-manager
*/

#include <stdio.h>
#include <string.h>
#include <esp_wifi.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"

#include "wifi_manager.h"
#include "http_app.h"
#include "app_otau.h"

extern esp_err_t camera_handler(httpd_req_t *req);

/* @brief tag used for ESP serial console messages */
static const char TAG[] = "app_wifi_manager";
EventGroupHandle_t wifi_event_group;

void cb_connection_ok(void *pvParameter){
	ESP_LOGI(TAG, "I have a connection!");
    xEventGroupSetBits(wifi_event_group, CONNECTED_BIT);
}

void app_wifi_manager_main()
{
    wifi_event_group = xEventGroupCreate();
    
    if(NULL == wifi_event_group){
        ESP_LOGE(TAG,"Failed to create wifi_event_group!");
        return;
    }
    
    wifi_manager_set_callback(WM_EVENT_STA_GOT_IP, &cb_connection_ok);
    http_app_set_handler_hook(HTTP_GET, &camera_handler);

	/* start the wifi manager */
	wifi_manager_start();

	/* set custom handler for the http server
	 * Now navigate to /helloworld to see the custom page
	 * */
	//http_app_set_handler_hook(HTTP_GET, &my_get_handler);

}
