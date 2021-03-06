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

uint8_t frame[8] = {
    0xa5, 0xa5,
    0x5a, 0x5a,
    0xa5, 0xa5,
    0x5a, 0x5a,
};


void setup() 
{
    Serial.begin(9600);

    initialize_cube();
    delay(100);  
}

void loop() 
{
    static int i = 0;
    static int j = 0;
    
    for (j=0; j < 500; j += 1)
    {
        load_frame(frame, FRAME_RATE);
    }

}



