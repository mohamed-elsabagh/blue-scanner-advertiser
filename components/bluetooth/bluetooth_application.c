/**********************************************************************
* - Description:		blue-scanner-driver
* - File:				bluetooth_application.c
* - Compiler:			xtensa-esp32
* - Debugger:			USB2USART
* - Author:				Mohamed El-Sabagh
* - Target:				ESP32
* - Created:			2017-12-24
* - Last changed:		2017-12-24
*
**********************************************************************/
#include "bluetooth_application.h"
#include "bluetooth_driver.h"
#include "AppConfig.h"

/**
  * @brief  FreeRTOS task for handling bluetooth.
  * @param  None
  * @retval None
  */
void vBluetoothTask(void *arg)
{
	for(;;)
	{
		// Intializing bluetooth in scanner mode for 60 seconds
        vBluetoothInit(BLUETOOTH_GATT_SCANNER);

        vTaskDelay( 60000 / portTICK_RATE_MS );

        vBluetoothDeInit();

        vTaskDelay( 10000 / portTICK_RATE_MS );

		vSetTxPower(ESP_BLE_PWR_TYPE_DEFAULT, ESP_PWR_LVL_P7);

		uint8_t raw_adv_data[] = {
		        0x02, 0x02, 0x02,
		        0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02
		};

		vSetAdvDataDriver(raw_adv_data);

        // Intializing bluetooth in advertiser mode for 60 seconds
        vBluetoothInit(BLUETOOTH_GATT_ADVERTISER);

        vTaskDelay( 60000 / portTICK_RATE_MS );

        vBluetoothDeInit();

        vTaskDelay( 10000 / portTICK_RATE_MS );
	}

	vTaskDelete(NULL);
}
