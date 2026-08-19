#include "core/display_driver.h"
#include "core/board_config.h"
#include "driver/i2c_master.h"
#include "esp_lcd_ili9341.h"
#include "esp_lcd_touch_ft5x06.h"
#include "esp_log.h"
#include "esp_lvgl_port.h"

static const char *TAG = "display_driver";

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

static esp_lcd_touch_handle_t init_touch(void)
{
    const i2c_master_bus_config_t bus_config = {
        .i2c_port = BOARD_TOUCH_I2C_PORT,
        .sda_io_num = BOARD_TOUCH_PIN_SDA,
        .scl_io_num = BOARD_TOUCH_PIN_SCL,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .flags = {
            .enable_internal_pullup = true,
        },
    };

    i2c_master_bus_handle_t i2c_bus = NULL;
    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_config, &i2c_bus));

    // Assign fields individually because the component's C initializer macro uses
    // a designator order rejected by C++20.
    esp_lcd_panel_io_i2c_config_t io_config = {};
    io_config.dev_addr = BOARD_TOUCH_I2C_ADDRESS;
    io_config.scl_speed_hz = BOARD_TOUCH_I2C_CLOCK_HZ;
    io_config.control_phase_bytes = 1;
    io_config.dc_bit_offset = 0;
    io_config.lcd_cmd_bits = 8;
    io_config.flags.disable_control_phase = 1;

    esp_lcd_panel_io_handle_t io_handle = NULL;
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_i2c(i2c_bus, &io_config, &io_handle));

    const esp_lcd_touch_config_t touch_config = {
        .x_max = BOARD_LCD_H_RES,
        .y_max = BOARD_LCD_V_RES,
        .rst_gpio_num = BOARD_TOUCH_PIN_RESET,
        .int_gpio_num = BOARD_TOUCH_PIN_INTERRUPT,
        .levels = {
            .reset = 0,
            .interrupt = 0,
        },
        // These are the native FT6336G coordinates for the ES3C28P BSP.
        .flags = {
            .swap_xy = false,
            .mirror_x = false,
            .mirror_y = false,
        },
    };

    esp_lcd_touch_handle_t touch_handle = NULL;
    ESP_ERROR_CHECK(esp_lcd_touch_new_i2c_ft5x06(
        io_handle, &touch_config, &touch_handle));
    return touch_handle;
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

void DisplayDriver::init(void) {
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

    ESP_LOGI(TAG, "Initializing FT6336G touch: SDA=%d SCL=%d RST=%d INT=%d address=0x%02x",
             BOARD_TOUCH_PIN_SDA, BOARD_TOUCH_PIN_SCL, BOARD_TOUCH_PIN_RESET,
             BOARD_TOUCH_PIN_INTERRUPT, BOARD_TOUCH_I2C_ADDRESS);

    esp_lcd_touch_handle_t touch_handle = init_touch();
    const lvgl_port_touch_cfg_t touch_config = {
        .disp = display,
        .handle = touch_handle,
    };
    if (lvgl_port_add_touch(&touch_config) == NULL) {
        ESP_LOGE(TAG, "Failed to register touch input with LVGL");
        return;
    }

    set_backlight(true);
    ESP_LOGI(TAG, "LVGL display and touch are ready");
}
