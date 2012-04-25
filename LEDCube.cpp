#include "LEDCube.h"
/*
LEDCube::LEDCube(volatile uint8_t *clk, volatile uint8_t clk_p, 
                 volatile uint8_t *gnd, volatile uint8_t *shift)
{
    clk_port = clk;
    clock_pin = clk_p;
    gnd_port = gnd;
    shift_port = shift;

    clk_port |= (1 << clock_pin);
    gnd_port |= 0x0F;
    shift_port |= 0x0F;

    this->clear();
}

void LEDCube::clock()
{
    this->clock_port &= ~(0<<(this->clock_pin));
    this->clock_port |= 1<<(this->clock_pin);
}
*/

void initialize_cube() 
{
    DDRB |= 0x0F;
    DDRC |= 0x0F;
    DDRD |= 0x80;
    
    clear_cube();
}

/** 
 * void clock_cube() 
 * Just pulls shift register pin low then high.
 * This will shift the register once.
 *
 * TODO: Need to make more generic (should not effect other pins on PORTD)
 */
void clock_cube() 
{
    PORTD &= ~(1<<7); // Pull shift register clock pin low
    PORTD |= (1<<7); // Pull shift register clock pin high
}

/**
 * void load_cube(uint8_t buf[5]) 
 * 
 * Takes buf[5], a 5 long array of uint8_t's, which describes the
 * rows and ground planes. buf[0:3] will describe the "rows" (vertical slices)
 * and buf[4] will describe the ground slices. Only the lower 4 bits of the 
 * uint8_t's are used. (NOTE: This could be compressed to using 3 uint8_ts instead
 * of 5, but it is not... Deal with it)
 *
 */
void load_cube(uint8_t *buf) 
{
    static int i = 0;
    PORTC &= 0xF0; // Turn off all GND planes so that you don't see "shadows"
    // Load in new "rows"
    
    for (i = 0; i < 4; i++)
    {
        PORTB &= 0xF0;
        PORTB |= 0x0F & buf[i];
        clock_cube();
    }

    delayMicroseconds(2);
    // Turn on appropriate GND planes
    PORTC |= 0x0F & buf[4];
}

void load_frame(uint8_t *frame, uint8_t _delay) 
{
    uint8_t buf[5] = {0};
    uint8_t i = 0;
    for (i = 0; i < 8; i +=1) 
    {
        // Fun with bitwise logics!
        //
        // Here we set buf[0:3] with their appropriate values for each 
        // horizontal ground plane.
        // 
        // buf[0] and buf[1] will get set on odd values of i (~i&0x01 
        // will evaluate to 1 for odd numbers and 0 for even). buf[2] 
        // and buf[3] will be set for odd numbers (i&0x01 will evaluate 
        // to 1 for evens 0 for odds).
        //
        // buf[4] gets set to indicate which plane is being loaded:
        //   index  |  plane
        //     0    |    0
        //     1    |    0
        //     2    |    1
        //     3    |    1
        //     4    |    2
        //     5    |    2
        //     6    |    3
        //     7    |    3
        // 
        // 0 is the lowest plane and 3 is the top plane. The rest of the planes 
        // are labeled as you would assume
        //
        // This can be conveniently represented by a shift one to the right and 
        // then shifting a 1 to the right by the plane number.
        buf[0] = (frame[i]) * (~i&0x01);
        buf[1] = (frame[i]>>4) * (~i&0x01);
        buf[2] = (frame[i]) * (i&1);
        buf[3] = (frame[i]>>4) * (i&0x01);
        buf[4] = (1<<(i>>1));
    
        // load into the buffer
        load_cube(buf);
        delayMicroseconds(_delay);
    }
}

void clear_cube() 
{
    uint8_t buf[5] = {0};
    load_cube(buf);
}
