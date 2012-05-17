#include "Arduino.h"

/*
class LEDCube
{
    volatile uint8_t *clock_port;
    volatile uint8_t clock_pin;
    volatile uint8_t *gnd_port;
    volatile uint8_t *shift_port;
public:
    LEDCube(volatile uint8_t *clk, volatile uint8_t clk_p, 
                     volatile uint8_t *gnd, volatile uint8_t *shift);

    void clock();
    void writeFrame();
    void writeBuffer();
    void clear();
};
*/

/** 
 * void clock_cube() 
 * Just pulls shift register pin low then high.
 * This will shift the register once.
 *
 * TODO: Need to make more generic (should not effect other pins on PORTD)
 */
void clock_cube();

void initialize_cube();

/**
 * void load_cube(uint8_t buf[5]) 
 * 
 * Takes buf[5], a 5 long array of uint8_t's, which describes the
 * rows and ground planes. buf[0:3] will describe the "rows" (vertical slices)
 * and buf[4] will describe the ground slices. Only the lower 4 bits of the 
 * uint8_t's are used. (NOTE: This could be compressed to using 3 uint8_ts instead
 * of 5, but it is not... Deal with it)
 *
 * TODO
 */
void load_cube(uint8_t buf[5]);

void load_frame(uint8_t frames[8], uint8_t frame_delay);

void clear_cube();
