/**********************************************************************
* - Description:		blue-scanner-driver
* - File:				bluetooth_driver.h
* - Compiler:			xtensa-esp32
* - Debugger:			USB2USART
* - Author:				Mohamed El-Sabagh
* - Target:				ESP32
* - Created:			2017-12-24
* - Last changed:		2017-12-24
*
**********************************************************************/
#ifndef BLUETOOTH_DRIVER_H_
#define BLUETOOTH_DRIVER_H_

#include <stdint.h>
#include "esp_bt.h"

#define BLUETOOTH_GATT_SCANNER          0
#define BLUETOOTH_GATT_ADVERTISER       1

/*** esp_ble_power_type_t ***/
// ESP_BLE_PWR_TYPE_CONN_HDL0  = 0,            /*!< For connection handle 0 */
// ESP_BLE_PWR_TYPE_CONN_HDL1  = 1,            /*!< For connection handle 1 */
// ESP_BLE_PWR_TYPE_CONN_HDL2  = 2,            /*!< For connection handle 2 */
// ESP_BLE_PWR_TYPE_CONN_HDL3  = 3,            /*!< For connection handle 3 */
// ESP_BLE_PWR_TYPE_CONN_HDL4  = 4,            /*!< For connection handle 4 */
// ESP_BLE_PWR_TYPE_CONN_HDL5  = 5,            /*!< For connection handle 5 */
// ESP_BLE_PWR_TYPE_CONN_HDL6  = 6,            /*!< For connection handle 6 */
// ESP_BLE_PWR_TYPE_CONN_HDL7  = 7,            /*!< For connection handle 7 */
// ESP_BLE_PWR_TYPE_CONN_HDL8  = 8,            /*!< For connection handle 8 */
// ESP_BLE_PWR_TYPE_ADV        = 9,            /*!< For advertising */
// ESP_BLE_PWR_TYPE_SCAN       = 10,           /*!< For scan */
// ESP_BLE_PWR_TYPE_DEFAULT    = 11,           /*!< For default, if not set other, it will use default value */
// ESP_BLE_PWR_TYPE_NUM        = 12,           /*!< TYPE numbers */

/*** esp_power_level_t ***/
// ESP_PWR_LVL_N14 = 0,            /*!< Corresponding to -14dbm */
// ESP_PWR_LVL_N11 = 1,            /*!< Corresponding to -11dbm */
// ESP_PWR_LVL_N8  = 2,            /*!< Corresponding to  -8dbm */
// ESP_PWR_LVL_N5  = 3,            /*!< Corresponding to  -5dbm */
// ESP_PWR_LVL_N2  = 4,            /*!< Corresponding to  -2dbm */
// ESP_PWR_LVL_P1  = 5,            /*!< Corresponding to   1dbm */
// ESP_PWR_LVL_P4  = 6,            /*!< Corresponding to   4dbm */
// ESP_PWR_LVL_P7  = 7,            /*!< Corresponding to   7dbm */

void vBluetoothInit(uint8_t bluetooth_mode);
void vBluetoothDeInit();
void vSetTxPower(esp_ble_power_type_t power_type, esp_power_level_t power_level);
void vSetAdvDataDriver(uint8_t * _data);

#endif
