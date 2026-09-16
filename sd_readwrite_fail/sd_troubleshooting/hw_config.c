/**
 * hw_config.c
 *
 * tells the no-OS-FatFS-SD-SPI-RPi-Pico library which physical pins and
 * SPI peripheral the SD card is wired to. The library calls the functions
 * at the bottom of this file internally.
 *
 * wiring (using pico's spi default 0):
 *   Pico GP16 -> SD MISO
 *   Pico GP17 -> SD CS
 *   Pico GP18 -> SD SCK
 *   Pico GP19 -> SD MOSI
 */

#include "hw_config.h"

static spi_t spis[] = {
    {
        .hw_inst = spi0,
        .miso_gpio = 16,
        .mosi_gpio = 19,
        .sck_gpio  = 18,
        .baud_rate = 400 * 1000, // started at the 12.5 MHz default. reduced to 400Mhz still no change.
                                    // handles the slow-clock init internally
    }
};

// describes one SD card: which SPI it's on, and which pin is its CS.
// pcName "0:" is the drive letter used in f_mount()/paths.
static sd_card_t sd_cards[] = {
    {
        .pcName = "0:",
        .spi = &spis[0],
        .ss_gpio = 17,          // chip select pin
        .use_card_detect = false // set true + add cd_gpio if the module has a CD pin wired (it doubt ours does but for good measure)
    }
};

// --- boilerplate the library expects to find.---

size_t spi_get_num(void) { return count_of(spis); }

spi_t *spi_get_by_num(size_t num) {
    if (num < spi_get_num()) return &spis[num];
    return NULL;
}

size_t sd_get_num(void) { return count_of(sd_cards); }

sd_card_t *sd_get_by_num(size_t num) {
    if (num < sd_get_num()) return &sd_cards[num];
    return NULL;
}
