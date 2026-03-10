### I2C bus
This is a very easy and compact ESP-IDF component that we used in our Sensoria.cat C5 model since the new versions of IDF won't accept anymore the old "legacy" I2C methods:

- i2c_param_config
- i2c_driver_install

The i2c_bus component gives you a single, shared ESP‑IDF “new I2C master” bus instance (i2c_master_bus_handle_t) and a small device-handle cache (i2c_master_dev_handle_t per 7‑bit address + speed). The benefits are:

- Avoids i2c_driver_install() conflicts: on targets like ESP32‑C5 (and generally with the new IDF I2C API), legacy drivers/components that try to install/configure the bus repeatedly can fail. i2c_bus_init() makes bus creation a one-time operation.
- Eliminates double-initialization bugs: many third‑party libraries “own” the I2C bus and reconfigure pins/clock; with i2c_bus_get_dev() each component just asks for a handle and doesn’t restart the peripheral.
Simple, consistent access pattern: you initialize once in app_main(), then each sensor/RTC/display uses its own cached i2c_master_dev_handle_t, making transactions cleaner and reducing “random” I2C errors caused by competing init code.
- Central place to tune bus settings: glitch filter, internal pullups, queue depth, etc. live in one file, so you can adjust bus reliability without hunting through multiple components.

### IDF I2C Master

https://docs.espressif.com/projects/esp-idf/en/stable/esp32c5/api-reference/peripherals/i2c.html This is for example the status of C5. If you try to build any component that has i2c_driver_install on it will fail. In this component we are using already the new way to instantiate the I2C bus. It does have only the essential part, it just starts the I2C and you can then get a handle from each of your I2C peripherals, without the need to starting it again in every component like many libraries do (Getting a lot of errors because of failed starts)

**With this idea in mind what you can do in your app_main**

1) start once I2C adding the component i2c_bus (CMakeLists) and header i2c_bus.h in your main file. Then in app_main start the bus using:

i2c_bus_init(SDA, SCL)

2) For each device get a handle using:

i2c_bus_get_dev(0x65, 40000)

Then you can use that i2c_master_dev_handle_t each time you want to speak to that particular device.