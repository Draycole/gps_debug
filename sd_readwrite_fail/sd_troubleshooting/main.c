/**
 * main.c
 *
 * Mounts a FAT32-formatted (i've formatted the card multiple
 * times) SD card and writes one line to test.csv.
 * This uses the FatFs library via no-OS-FatFS-SD-SPI-RPi-Pico (instead
 * of talking to raw sectors) -- so the result is an actual file that i 
 * can open on my pc with the dongle.
 *
 * output: USB serial (stdio_init_all). baud 115200.
 */

#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "ff.h"   

int main(void) {
    stdio_init_all();
    sleep_ms(3000); // allow some time to open the serial monitor before output starts

    printf("\n--- SD FAT32 CSV write test ---\n");

    FATFS fs;
    FIL file;
    FRESULT fr;

    fr = f_mount(&fs, "0:", 1); // the '1' forces mount now rather than on first access
    if (fr != FR_OK) {
        printf("f_mount failed, error code %d\n", fr);
        printf("(Check wiring first -- FatFs sees the same SPI bus as before.)\n");
        while (true) tight_loop_contents();
    }
    printf("Card mounted OK.\n");

    // create test.csv and open it for writing (or overwrite if there's already one) 
    fr = f_open(&file, "0:/test.csv", FA_CREATE_ALWAYS | FA_WRITE);
    if (fr != FR_OK) {
        printf("f_open failed, error code %d\n", fr);
        f_unmount("0:");
        while (true) tight_loop_contents();
    }
    printf("test.csv opened for writing.\n");

    // write a random header row + one data row
    const char *line = "sensor,value\r\nmpu6050,42\r\n";
    UINT bytes_written = 0;
    fr = f_write(&file, line, strlen(line), &bytes_written);
    if (fr != FR_OK) {
        printf("f_write failed, error code %d\n", fr);
    } else {
        printf("Wrote %u bytes to test.csv\n", bytes_written);
    }

    // close + unmount so the FAT table gets flushed properly.
    f_close(&file);
    f_unmount("0:");

    printf("Done. Eject the card and check for test.csv on your computer.\n");

    while (true) tight_loop_contents();
}