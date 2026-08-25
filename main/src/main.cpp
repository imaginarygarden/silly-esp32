#include "app/controller.h"

#include <esp_lvgl_port.h>

#include <freertos/FreeRTOS.h>

extern "C" {
    void app_main(void);
}

void app_main(void)
{
    Controller controller{};
    controller.init();

    while (controller.active()) {
        controller.update();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
