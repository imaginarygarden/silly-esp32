#include "app/controller.h"

#include <freertos/FreeRTOS.h>
#include <esp_lvgl_port.h>

extern "C" {
    void app_main(void);
}

void app_main(void)
{
    Controller controller{};

    while (controller.active()) {
        controller.update();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
