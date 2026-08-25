#include <esp_lvgl_port.h>
#include <freertos/FreeRTOS.h>

#include "app/controller.h"

extern "C" {
void app_main(void);
}

void app_main(void) {
    Controller controller{};
    controller.init();

    while (controller.active()) {
        controller.update();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
