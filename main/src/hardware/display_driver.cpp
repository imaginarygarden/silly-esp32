#include "hardware/display_driver.h"

#include "driver/i2c_master.h"
#include "esp_heap_caps.h"
#include "esp_lcd_ili9341.h"
#include "esp_lcd_touch_ft5x06.h"
#include "esp_log.h"
#include "esp_lvgl_port.h"
#include "hardware/board_config.h"

namespace {

constexpr char TAG[] = "display_driver";
constexpr size_t DISPLAY_BUFFER_PIXELS =
    BOARD_LCD_NATIVE_H_RES * BOARD_LVGL_BUFFER_LINES;

esp_lcd_panel_io_handle_t create_lcd_io() {
    const spi_bus_config_t bus_config = {
        .mosi_io_num = BOARD_LCD_PIN_MOSI,
        .miso_io_num = BOARD_LCD_PIN_MISO,
        .sclk_io_num = BOARD_LCD_PIN_SCLK,
        .quadwp_io_num = GPIO_NUM_NC,
        .quadhd_io_num = GPIO_NUM_NC,
        .max_transfer_sz = DISPLAY_BUFFER_PIXELS * sizeof(uint16_t),
    };
    ESP_ERROR_CHECK(spi_bus_initialize(BOARD_LCD_SPI_HOST, &bus_config,
                                       BOARD_LCD_SPI_DMA_CHANNEL));

    const esp_lcd_panel_io_spi_config_t io_config = {
        .cs_gpio_num = BOARD_LCD_PIN_CS,
        .dc_gpio_num = BOARD_LCD_PIN_DC,
        .spi_mode = BOARD_LCD_SPI_MODE,
        .pclk_hz = BOARD_LCD_PIXEL_CLOCK_HZ,
        .trans_queue_depth = BOARD_LCD_TRANSACTION_QUEUE_DEPTH,
        .lcd_cmd_bits = BOARD_LCD_COMMAND_BITS,
        .lcd_param_bits = BOARD_LCD_PARAMETER_BITS,
    };

    esp_lcd_panel_io_handle_t io = nullptr;
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi(
        static_cast<esp_lcd_spi_bus_handle_t>(BOARD_LCD_SPI_HOST), &io_config,
        &io));
    return io;
}

esp_lcd_panel_handle_t create_lcd_panel(esp_lcd_panel_io_handle_t io) {
    const esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = BOARD_LCD_PIN_RESET,
        .rgb_ele_order = BOARD_LCD_COLOR_ORDER,
        .bits_per_pixel = BOARD_LCD_BITS_PER_PIXEL,
    };

    esp_lcd_panel_handle_t panel = nullptr;
    ESP_ERROR_CHECK(esp_lcd_new_panel_ili9341(io, &panel_config, &panel));
    ESP_ERROR_CHECK(esp_lcd_panel_reset(panel));
    ESP_ERROR_CHECK(esp_lcd_panel_init(panel));
    ESP_ERROR_CHECK(esp_lcd_panel_invert_color(panel, BOARD_LCD_INVERT_COLORS));
    ESP_ERROR_CHECK(esp_lcd_panel_swap_xy(panel, BOARD_LCD_NATIVE_SWAP_XY));
    ESP_ERROR_CHECK(esp_lcd_panel_mirror(panel, BOARD_LCD_NATIVE_MIRROR_X,
                                         BOARD_LCD_NATIVE_MIRROR_Y));
    ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel, true));
    return panel;
}

esp_lcd_touch_handle_t create_touch() {
    const i2c_master_bus_config_t bus_config = {
        .i2c_port = BOARD_TOUCH_I2C_PORT,
        .sda_io_num = BOARD_TOUCH_PIN_SDA,
        .scl_io_num = BOARD_TOUCH_PIN_SCL,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = BOARD_TOUCH_I2C_GLITCH_FILTER_COUNT,
        .flags = {.enable_internal_pullup = BOARD_TOUCH_I2C_INTERNAL_PULLUPS},
    };

    i2c_master_bus_handle_t bus = nullptr;
    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_config, &bus));

    // Field assignment avoids a designator-order issue in the component's C
    // macro.
    esp_lcd_panel_io_i2c_config_t io_config = {};
    io_config.dev_addr = BOARD_TOUCH_I2C_ADDRESS;
    io_config.scl_speed_hz = BOARD_TOUCH_I2C_CLOCK_HZ;
    io_config.control_phase_bytes = BOARD_TOUCH_I2C_CONTROL_PHASE_BYTES;
    io_config.dc_bit_offset = BOARD_TOUCH_I2C_DC_BIT_OFFSET;
    io_config.lcd_cmd_bits = BOARD_TOUCH_I2C_COMMAND_BITS;
    io_config.flags.disable_control_phase =
        BOARD_TOUCH_I2C_DISABLE_CONTROL_PHASE;

    esp_lcd_panel_io_handle_t io = nullptr;
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_i2c(bus, &io_config, &io));

    const esp_lcd_touch_config_t touch_config = {
        .x_max = BOARD_LCD_NATIVE_H_RES,
        .y_max = BOARD_LCD_NATIVE_V_RES,
        .rst_gpio_num = BOARD_TOUCH_PIN_RESET,
        .int_gpio_num = BOARD_TOUCH_PIN_INTERRUPT,
        .levels =
            {
                .reset = BOARD_TOUCH_RESET_LEVEL,
                .interrupt = BOARD_TOUCH_INTERRUPT_LEVEL,
            },
        .flags =
            {
                .swap_xy = BOARD_TOUCH_NATIVE_SWAP_XY,
                .mirror_x = BOARD_TOUCH_NATIVE_MIRROR_X,
                .mirror_y = BOARD_TOUCH_NATIVE_MIRROR_Y,
            },
    };

    esp_lcd_touch_handle_t touch = nullptr;
    ESP_ERROR_CHECK(esp_lcd_touch_new_i2c_ft5x06(io, &touch_config, &touch));
    return touch;
}

void set_backlight(bool enabled) {
    const gpio_config_t config = {
        .pin_bit_mask = 1ULL << BOARD_LCD_PIN_BACKLIGHT,
        .mode = GPIO_MODE_OUTPUT,
    };
    ESP_ERROR_CHECK(gpio_config(&config));
    ESP_ERROR_CHECK(gpio_set_level(BOARD_LCD_PIN_BACKLIGHT,
                                   enabled ? BOARD_LCD_BACKLIGHT_ON_LEVEL
                                           : !BOARD_LCD_BACKLIGHT_ON_LEVEL));
}

lv_display_t* create_lvgl_display(esp_lcd_panel_io_handle_t io,
                                  esp_lcd_panel_handle_t panel) {
    const lvgl_port_cfg_t port_config = {
        .task_priority = BOARD_LVGL_TASK_PRIORITY,
        .task_stack = BOARD_LVGL_TASK_STACK_SIZE,
        .task_affinity = BOARD_LVGL_TASK_AFFINITY,
        .task_max_sleep_ms = BOARD_LVGL_TASK_MAX_SLEEP_MS,
        .task_stack_caps = BOARD_LVGL_TASK_STACK_CAPS,
        .timer_period_ms = BOARD_LVGL_TIMER_PERIOD_MS,
    };
    ESP_ERROR_CHECK(lvgl_port_init(&port_config));

    const lvgl_port_display_cfg_t display_config = {
        .io_handle = io,
        .panel_handle = panel,
        .buffer_size = DISPLAY_BUFFER_PIXELS,
        .double_buffer = BOARD_LVGL_DOUBLE_BUFFER,
        .hres = BOARD_LCD_NATIVE_H_RES,
        .vres = BOARD_LCD_NATIVE_V_RES,
        .monochrome = false,
        .rotation =
            {
                .swap_xy = BOARD_LCD_NATIVE_SWAP_XY,
                .mirror_x = BOARD_LCD_NATIVE_MIRROR_X,
                .mirror_y = BOARD_LCD_NATIVE_MIRROR_Y,
            },
        .color_format = LV_COLOR_FORMAT_RGB565,
        .flags =
            {
                .buff_dma = BOARD_LVGL_BUFFER_DMA,
                .buff_spiram = BOARD_LVGL_BUFFER_SPIRAM,
                .sw_rotate = BOARD_LVGL_SOFTWARE_ROTATION,
                .swap_bytes = BOARD_LVGL_SWAP_RGB565_BYTES,
                .full_refresh = BOARD_LVGL_FULL_REFRESH,
                .direct_mode = BOARD_LVGL_DIRECT_MODE,
            },
    };

    lv_display_t* display = lvgl_port_add_disp(&display_config);
    ESP_ERROR_CHECK(display ? ESP_OK : ESP_ERR_NO_MEM);

    ESP_ERROR_CHECK(lvgl_port_lock(0) ? ESP_OK : ESP_ERR_TIMEOUT);
    lv_display_set_rotation(display, BOARD_LCD_ROTATION);
    lvgl_port_unlock();
    return display;
}

}  // namespace

DisplayDriver::DisplayDriver() { init(); }

void DisplayDriver::init() {
    set_backlight(false);
    ESP_LOGI(TAG, "Initializing %dx%d display, rotation=%d",
             BOARD_LCD_NATIVE_H_RES, BOARD_LCD_NATIVE_V_RES,
             static_cast<int>(BOARD_LCD_ROTATION));

    const auto io = create_lcd_io();
    const auto panel = create_lcd_panel(io);
    lv_display_t* display = create_lvgl_display(io, panel);

    const lvgl_port_touch_cfg_t touch_config = {
        .disp = display,
        .handle = create_touch(),
    };
    ESP_ERROR_CHECK(lvgl_port_add_touch(&touch_config) ? ESP_OK
                                                       : ESP_ERR_NO_MEM);

    set_backlight(true);
    ESP_LOGI(TAG, "Display and touch are ready (%dx%d)",
             lv_display_get_horizontal_resolution(display),
             lv_display_get_vertical_resolution(display));
}
