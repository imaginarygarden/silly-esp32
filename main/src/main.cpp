#include <iostream>
#include <format>

#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "esp_err.h"
#include "esp_lcd_ili9341.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "esp_log.h"
#include "esp_lvgl_port.h"
#include "board_config.h"
#include "lvgl.h"

extern "C" {
    void app_main(void);
}

static const char *TAG = "display";

static esp_lcd_panel_io_handle_t init_panel_io(void)
{
    const spi_bus_config_t bus_config = {
        .mosi_io_num = BOARD_LCD_PIN_MOSI,
        .miso_io_num = BOARD_LCD_PIN_MISO,
        .sclk_io_num = BOARD_LCD_PIN_SCLK,
        .quadwp_io_num = GPIO_NUM_NC,
        .quadhd_io_num = GPIO_NUM_NC,
        .max_transfer_sz = BOARD_LCD_H_RES * BOARD_LVGL_BUFFER_LINES * sizeof(uint16_t),
    };
    ESP_ERROR_CHECK(spi_bus_initialize(BOARD_LCD_SPI_HOST, &bus_config, SPI_DMA_CH_AUTO));

    const esp_lcd_panel_io_spi_config_t io_config = {
        .cs_gpio_num = BOARD_LCD_PIN_CS, 
        .dc_gpio_num = BOARD_LCD_PIN_DC,
        .spi_mode = 0,
        .pclk_hz = BOARD_LCD_PIXEL_CLOCK_HZ,
        .trans_queue_depth = 10,
        .lcd_cmd_bits = 8,
        .lcd_param_bits = 8,
    };

    esp_lcd_panel_io_handle_t io_handle = NULL;
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi(
        (esp_lcd_spi_bus_handle_t)BOARD_LCD_SPI_HOST, &io_config, &io_handle));
    return io_handle;
}

static esp_lcd_panel_handle_t init_panel(esp_lcd_panel_io_handle_t io_handle)
{
    const esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = BOARD_LCD_PIN_RESET,
        .rgb_ele_order = BOARD_LCD_COLOR_ORDER,
        .bits_per_pixel = 16,
    };

    esp_lcd_panel_handle_t panel_handle = NULL;
    ESP_ERROR_CHECK(esp_lcd_new_panel_ili9341(io_handle, &panel_config, &panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_init(panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_invert_color(panel_handle, BOARD_LCD_INVERT_COLORS));
    ESP_ERROR_CHECK(esp_lcd_panel_swap_xy(panel_handle, BOARD_LCD_SWAP_XY));
    ESP_ERROR_CHECK(esp_lcd_panel_mirror(
        panel_handle, BOARD_LCD_MIRROR_X, BOARD_LCD_MIRROR_Y));
    ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel_handle, true));
    return panel_handle;
}

static void set_backlight(bool on)
{
    const gpio_config_t config = {
        .pin_bit_mask = 1ULL << BOARD_LCD_PIN_BACKLIGHT,
        .mode = GPIO_MODE_OUTPUT,
    };
    ESP_ERROR_CHECK(gpio_config(&config));
    ESP_ERROR_CHECK(gpio_set_level(
        BOARD_LCD_PIN_BACKLIGHT,
        on ? BOARD_LCD_BACKLIGHT_ON_LEVEL : !BOARD_LCD_BACKLIGHT_ON_LEVEL));
}

static void create_demo_ui(void)
{
    lv_obj_t *screen = lv_screen_active();
    lv_obj_set_style_bg_color(screen, lv_color_hex(0x101820), LV_PART_MAIN);

    lv_obj_t *title = lv_label_create(screen);
    lv_label_set_text(title, "ESP32-S3 + LVGL");
    lv_obj_set_style_text_color(title, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_set_style_text_font(title, &lv_font_montserrat_14, LV_PART_MAIN);
    lv_obj_align(title, LV_ALIGN_CENTER, 0, -25);

    lv_obj_t *status = lv_label_create(screen);
    lv_label_set_text(status, "Display initialized successfully");
    lv_obj_set_style_text_color(status, lv_color_hex(0x35D07F), LV_PART_MAIN);
    lv_obj_align(status, LV_ALIGN_CENTER, 0, 18);
}

void run(void)
{
    set_backlight(false);

    ESP_LOGI(TAG, "Initializing ES3C28P display: CS=%d DC=%d CLK=%d MOSI=%d BL=%d",
             BOARD_LCD_PIN_CS, BOARD_LCD_PIN_DC, BOARD_LCD_PIN_SCLK,
             BOARD_LCD_PIN_MOSI, BOARD_LCD_PIN_BACKLIGHT);

    esp_lcd_panel_io_handle_t io_handle = init_panel_io();
    esp_lcd_panel_handle_t panel_handle = init_panel(io_handle);

    const lvgl_port_cfg_t lvgl_config = ESP_LVGL_PORT_INIT_CONFIG();
    ESP_ERROR_CHECK(lvgl_port_init(&lvgl_config));

    const lvgl_port_display_cfg_t display_config = {
        .io_handle = io_handle,
        .panel_handle = panel_handle,
        .buffer_size = BOARD_LCD_H_RES * BOARD_LVGL_BUFFER_LINES,
        .double_buffer = true,
        .hres = BOARD_LCD_H_RES,
        .vres = BOARD_LCD_V_RES,
        .monochrome = false,
        .rotation = {
            .swap_xy = BOARD_LCD_SWAP_XY,
            .mirror_x = BOARD_LCD_MIRROR_X,
            .mirror_y = BOARD_LCD_MIRROR_Y,
        },
        .flags = {
            .buff_dma = true,
            .swap_bytes = true,
        },
    };

    lv_display_t *display = lvgl_port_add_disp(&display_config);
    if (display == NULL) {
        ESP_LOGE(TAG, "Failed to register the display with LVGL");
        return;
    }

    set_backlight(true);
    if (lvgl_port_lock(0)) {
        create_demo_ui();
        lvgl_port_unlock();
    }
    ESP_LOGI(TAG, "LVGL is ready");
}

void app_main(void)
{
    std::cout << std::format("{}\n", "wassup");
    // run();
}
