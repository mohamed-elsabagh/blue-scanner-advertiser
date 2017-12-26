#include "AppConfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/FreeRTOSConfig.h"
#include "freertos/task.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "bluetooth_application.h"

#define STACK_SIZE_2048 2048

StaticTask_t xBluetoothTaskBuffer;

StackType_t xStack_Bluetooth[ STACK_SIZE_2048 ];

void app_main(void)
{
    // Initialize NVS.
    esp_err_t ret = nvs_flash_init();

    if (ret == ESP_ERR_NVS_NO_FREE_PAGES) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK( ret );

    xTaskCreateStaticPinnedToCore(vBluetoothTask,       /* Function that implements the task. */
                                  "vBluetoothTask",     /* Text name for the task. */
                                  STACK_SIZE_2048,       /* Number of indexes in the xStack array. */
                                  NULL,                  /* Parameter passed into the task. */
                                  osPriorityNormal,      /* Priority at which the task is created. */
                                  xStack_Bluetooth,      /* Array to use as the task's stack. */
                                  &xBluetoothTaskBuffer, /* Variable to hold the task's data structure. */
                                  0                      /*  0 for PRO_CPU, 1 for APP_CPU, or tskNO_AFFINITY which allows the task to run on both */
                                  );
}
