/**
    @file i2c_128x32_graphics.c
    @brief This program implements the physical small display. It is a modified version of Stealthy Labs' libssd1306 program.
    @author Ryan Cook
    @author Brandon Luu
    @date 09/23/2023
*/

/*
 * COPYRIGHT: 2020. Stealthy Labs LLC.
 * DATE: 2020-01-15
 * SOFTWARE: libssd1306-i2c
 * LICENSE: Refer license file
 */
#include "ssd1306_i2c.h"
#include <stdio.h>
#include <string.h>

    int printString(char *str) {

        char str1[17];
        char str2[17];
        char str3[256];

        strncpy(str1, str, 16);
        str1[16] = '\0';

        size_t len = strlen(str);
        if (len <= 16) {
        str2[0] = '\0';
        str3[0] = '\0';
    }
    else if (len <= 32) {
        strncpy(str2, str + 16, len - 16);
        str2[len - 16] = '\0';
        str3[0] = '\0';
    }
    else {
        strncpy(str2, str + 16, 16);
        str2[16] = '\0';
        strncpy(str3, str + 32, len - 32);
        str3[11] = '.';
        str3[12] = '.';
        str3[13] = '.';
        str3[len - 32] = '\0';
    }

    printf("[Screen] String1: %s\n", str1);
    printf("[Screen] String2: %s\n", str2);
    printf("[Screen] String3: %s\n", str3);

    fprintf(stderr, "DEBUG: Using library version: %s\n", ssd1306_i2c_version());
	const char *filename = "/dev/i2c-1";
    ssd1306_i2c_t *oled = ssd1306_i2c_open(filename, 0x3c, 128, 64, NULL);
    if (!oled) {
        return -1;
    }
    if (ssd1306_i2c_display_initialize(oled) < 0) {
        fprintf(stderr, "ERROR: Failed to initialize the display. Check if it is connected !\n");
        ssd1306_i2c_close(oled);
        return -1;
    }
    ssd1306_framebuffer_t *fbp = ssd1306_framebuffer_create(oled->width, oled->height, oled->err);

    // ssd1306_i2c_display_clear(oled);
    // for (uint8_t i = oled->height - 1; i < oled->height; ++i) {
    //     for (uint8_t j = 0; j < oled->width; ++j)
    //         ssd1306_framebuffer_put_pixel(fbp, j, i, true);
    // }
    // ssd1306_framebuffer_hexdump(fbp);
    // ssd1306_framebuffer_bitdump(fbp);
    // ssd1306_framebuffer_clear(fbp);
    ssd1306_framebuffer_box_t bbox;
#ifdef LIBSSD1306_HAVE_UNISTR_H
// This string is the input
// parameters are (idk, text, idk, y component, x component, font, font size, idk)
    ssd1306_framebuffer_draw_text(fbp, str1, 0, 0, 20, SSD1306_FONT_DEFAULT, 3, &bbox);
    ssd1306_framebuffer_draw_text(fbp, str2, 0, 20, 35, SSD1306_FONT_DEFAULT, 3, &bbox);
    ssd1306_framebuffer_draw_text(fbp, str3, 0, 40, 50, SSD1306_FONT_DEFAULT, 3, &bbox);
#else
    ssd1306_framebuffer_draw_text(fbp, "1234567890123456789", 0, 0, 20, SSD1306_FONT_DEFAULT, 3, &bbox);
#endif
    // ssd1306_framebuffer_bitdump(fbp);
    ssd1306_i2c_display_update(oled, fbp);
    sleep(1);

    uint8_t scroll_data[6] = { 0x00 /* PAGE 0 */, 0x06 /* 2 frames */, 0x07 /* PAGE 7 */ };
    ssd1306_i2c_run_cmd(oled, SSD1306_I2C_CMD_SCROLL_ACTIVATE, 0, 0);
    fprintf(stderr, "INFO: Starting left horizontal scroll test\n");
    //the final parameter is the speed but I don't know how fast it can go
    ssd1306_i2c_run_cmd(oled, SSD1306_I2C_CMD_SCROLL_LEFT_HORIZONTAL, scroll_data, 2);
    // fprintf(stderr, "INFO: Activating left horizontal scroll test and waiting 10 seconds...\n");
    sleep(100);
    fprintf(stderr, "INFO: Deactivating left horizontal scroll test\n");
    ssd1306_i2c_run_cmd(oled, SSD1306_I2C_CMD_SCROLL_DEACTIVATE, 0, 0);
    //This turns the power off
    ssd1306_i2c_run_cmd(oled, SSD1306_I2C_CMD_POWER_OFF, 0, 0);
    ssd1306_framebuffer_destroy(fbp);
    fbp = NULL;
    ssd1306_i2c_close(oled);
    oled = NULL;
	return 0;
    }

int main (int argc, char* argv[])
{
    if (argc <= 1) {
        printf("A string is required to display it on the screen\n");
        return -1;
    }

    char* mystring = argv[1];

    // Concatenate the arguments
    for (int i = 2; i < argc; i++) {
        char newstr[strlen(argv[i])];
        strcpy(newstr, argv[i]);
        strcat(mystring, " ");
        strcat(mystring, newstr);
    }

    // Display it!
    printString(mystring);
}

