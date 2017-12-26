/**********************************************************************
* - Description:		blue-scanner-driver
* - File:				bluetooth_driver.c
* - Compiler:			xtensa-esp32
* - Debugger:			USB2USART
* - Author:				Mohamed El-Sabagh
* - Target:				ESP32
* - Created:			2017-12-24
* - Last changed:		2017-12-24
*
**********************************************************************/
#include "bluetooth_driver.h"
#include "blue_gattc.h"
#include "blue_gatts.h"

#define TAG                 "BLUETOOTH_TAG"

static void vGattsInit();
static void vGattcInit();

static uint8_t bluetooth_initialized = 0;

void vBluetoothInit(uint8_t bluetooth_mode)
{
    esp_err_t ret;

    if (bluetooth_initialized == 0)
    {
        esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
        ret = esp_bt_controller_init(&bt_cfg);
        if (ret) {
            ESP_LOGE(TAG, "%s initialize controller failed, error code = %x\n", __func__, ret);
            return;
        }

        ret = esp_bt_controller_enable(ESP_BT_MODE_BTDM);
        if (ret) {
            ESP_LOGE(TAG, "%s enable controller failed, error code = %x\n", __func__, ret);
            return;
        }

        bluetooth_initialized = 1;
    }

    ret = esp_bluedroid_init();
    if (ret) {
        ESP_LOGE(TAG, "%s init bluetooth failed, error code = %x\n", __func__, ret);
        return;
    }

    ret = esp_bluedroid_enable();
    if (ret) {
        ESP_LOGE(TAG, "%s enable bluetooth failed, error code = %x\n", __func__, ret);
        return;
    }

    if (bluetooth_mode == BLUETOOTH_GATT_DUAL || BLUETOOTH_GATT_DUAL == BLUETOOTH_GATT_ADVERTISER)
    {
        vGattsInit();
    }

    if (bluetooth_mode == BLUETOOTH_GATT_DUAL || BLUETOOTH_GATT_DUAL == BLUETOOTH_GATT_SCANNER)
    {
        vGattcInit();
    }

    esp_err_t local_mtu_ret = esp_ble_gatt_set_local_mtu(500);
    if (local_mtu_ret){
        ESP_LOGE(TAG, "set local  MTU failed, error code = %x", local_mtu_ret);
    }
}

void vBluetoothDeInit()
{
    esp_err_t ret;
    ret = esp_bluedroid_disable();
    if (ret) {
        ESP_LOGE(TAG, "%s disable bluetooth failed, error code = %x\n", __func__, ret);
        return;
    }

    ret = esp_bluedroid_deinit();
    if (ret) {
        ESP_LOGE(TAG, "%s deinit bluetooth failed, error code = %x\n", __func__, ret);
        return;
    }
}

void vGattsInit()
{
    esp_err_t ret;

    ret = esp_ble_gatts_register_callback(gatts_event_handler);
    if (ret){
        ESP_LOGE(TAG, "gatts register error, error code = %x", ret);
        return;
    }
    ret = esp_ble_gap_register_callback(gap_event_handler);
    if (ret){
        ESP_LOGE(TAG, "gap register error, error code = %x", ret);
        return;
    }
    ret = esp_ble_gatts_app_register(PROFILE_A_APP_ID_SERVER);
    if (ret){
        ESP_LOGE(TAG, "gatts app register error, error code = %x", ret);
        return;
    }
}

void vGattcInit()
{
    esp_err_t ret;

    //register the  callback function to the gap module
    ret = esp_ble_gap_register_callback(esp_gap_cb);
    if (ret){
        ESP_LOGE(TAG, "%s gap register failed, error code = %x\n", __func__, ret);
        return;
    }

    //register the callback function to the gattc module
    ret = esp_ble_gattc_register_callback(esp_gattc_cb);
    if(ret){
        ESP_LOGE(TAG, "%s gattc register failed, error code = %x\n", __func__, ret);
        return;
    }

    ret = esp_ble_gattc_app_register(PROFILE_A_APP_ID_CLIENT);
    if (ret){
        ESP_LOGE(TAG, "%s gattc app register failed, error code = %x\n", __func__, ret);
    }
}
