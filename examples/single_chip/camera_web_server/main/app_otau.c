#include "app_otau.h"

static void ota_server_task(void * param)
{
//    xEventGroupWaitBits(wifi_event_group, CONNECTED_BIT, false, true, portMAX_DELAY);
    ota_server_start();
    vTaskDelete(NULL);
}

void app_otau_main(){
    xTaskCreate(&ota_server_task, "ota_server_task", 4096, NULL, 5, NULL);
}