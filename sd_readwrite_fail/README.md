# Failure to Write to SD Card

I have been unable to verify that the raspberry pi pico can communicate with the sd module.

I started off trying to write to a sector on the sd card (it won't come up as a file when you mout it on a computer but would indicate if writing was successful.) That failed so I wanted to write a viewable .csv file to the card, so i can verify.


Continually ran into this error  

```
14:32:22.883 -> 
14:32:22.883 -> --- SD FAT32 CSV write test ---
14:32:23.896 -> f_mount failed, error code 3
14:32:23.896 -> (Check wiring first -- FatFs sees the same SPI bus as before.)
```

I've tried a handful of things. I took down one of my old projects so I could verify the module itself was not the issue. My old module still gave the same bug. I reduced the spi clock in `hw_config` to 400kHz but still the same error.
