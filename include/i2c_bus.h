#pragma once

#include "sdkconfig.h"

#include "esp_err.h"
#include <stdint.h>
#include "driver/i2c_master.h"

#ifdef __cplusplus
extern "C" {
#endif

esp_err_t i2c_bus_init(int sda_gpio, int scl_gpio);

/**
 * @brief Get (and cache) a device handle for a 7-bit address on the shared I2C bus.
 *
 * @param addr7 7-bit I2C address (e.g. 0x68)
 * @param speed_hz Bus speed for this device (e.g. 100000 or 400000)
 */
i2c_master_dev_handle_t i2c_bus_get_dev(uint8_t addr7, uint32_t speed_hz);

/**
 * @brief Probe the I2C bus to check if a device at addr7 responds.
 *
 * @param addr7 7-bit I2C address
 * @param timeout_ms Timeout in milliseconds
 * @return ESP_OK if device responds, error code otherwise
 */
esp_err_t i2c_bus_probe(uint8_t addr7, int timeout_ms);

#ifdef __cplusplus
}
#endif