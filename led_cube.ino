/* LED CUBE
 *
 * Christopher Woodall
 * A BUILDS Production
 * MIT License 2012
 *
 * Stuff goes here...
 */
#include "LEDCube.h"
#define FRAME_RATE 500

uint8_t buf[5] = { 0, 0, 0, 0, 0 };

uint8_t frames[4][8] = {
    { 0xA5, 0xA5,
      0xA5, 0xA5,
      0xA5, 0xA5,
      0xA5, 0xA5 },
    { 0x5A, 0x5A,
      0x5A, 0x5A,
      0x5A, 0x5A,
      0x5A, 0x5A },
};

uint8_t frame1[8] = {0};

void setup() 
{
    initialize_cube();
    delay(100);  
}

void loop() 
{
    int i = 0;
    int j = 0;

    for (i = 0; i < 2; i += 1) 
    {
        for (j = 0; j < 1000; j += 1)
        {
            load_frame(frames[i], FRAME_RATE);
        }
    }
/*
    for (i = 0; i < 16; i += 1)
    {
        for (j = 0; j < 8; j += 1) {
            frame1[j] += 0x11;
        }

        for (j = 0; j < 100; j += 1) {
            load_frame(frame1, FRAME_RATE);
        }
    }
    for (j = 0; j < 8; j += 1)
    {
      frame1[j] = 0;
    }
*/
}



