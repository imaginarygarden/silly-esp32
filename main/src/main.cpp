#include "core/controller.h"

#include <freertos/FreeRTOS.h>
#include <esp_lvgl_port.h>

extern "C" {
    void app_main(void);
}

void app_main(void)
{
    Controller controller{};

    while (controller.isRunning()) {
        if (lvgl_port_lock(0)) {
            controller.update();
            lvgl_port_unlock();
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
