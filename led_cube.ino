/* LED CUBE
 *
 * Christopher Woodall
 * A BUILDS Production
 * MIT License 2012
 *
 * Stuff goes here...
 */
/** 
 * void clock_cube() 
 * Just pulls shift register pin low then high.
 * This will shift the register once.
 *
 * TODO: Need to make more generic (should not effect other pins on PORTD)
 */
void clock_cube() {
  PORTD = 0x00; // Pull shift register clock pin low
  PORTD = 0xF0; // Pull shift register clock pin high
}

/**
 * void load(uint8_t buf[5]) 
 * 
 * Takes buf[5], a 5 long array of uint8_t's, which describes the
 * rows and ground planes. buf[0:3] will describe the "rows" (vertical slices)
 * and buf[4] will describe the ground slices. Only the lower 4 bits of the 
 * uint8_t's are used. (NOTE: This could be compressed to using 3 uint8_ts instead
 * of 5, but it is not... Deal with it)
 *
 * TODO
 */
void load(uint8_t buf[5]) {
  PORTC = 0; // Turn off all GND planes so that you don't see "shadows"
  // Load in new "rows"
  for (int i = 0; i < 4; i++)
  {
    PORTB = buf[i];
    clock_cube();
  }
  // Turn on appropriate GND planes
  PORTC = buf[4];
}

void load_frame(uint8_t frames[8]) {
  uint8_t buf[5] = {0};
  uint8_t i = 0;
  for (i = 0; i < 8; i +=1) {
    // Fun with bitwise logics!
    //
    // Here we set buf[0:3] with their appropriate values for each horizontal ground plane.
    // buf[0] and buf[1] will get set on odd values of i (~i&0x01 will evaluate to 1 for 
    // odd numbers and 0 for even). 
    // buf[2] and buf[3] will be set for odd numbers (i&0x01 will evaluate to 1 for evens 0 
    // for odds).
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
    // This can be conveniently represented by a shift one to the right and then shifting a 1
    // to the right by the plane number
    buf[0] = frames[i] * (~i&0x01);
    buf[1] = (frames[i] >> 4) * (~i&0x01);
    buf[2] = frames[i] * (i&1);
    buf[3] = (frames[i] >> 4) * (i&0x01);
    buf[4] = (1<<(i>>1));
    
    // load into the buffer
    load(buf);
    
    // clean up
    clear();
  }
}

void clear() {
  uint8_t buf[5] = {0};
  load(buf);
}

void setup() {
  DDRB = 0xFF;
  DDRC = 0xFF;
  DDRD = 0xFF;
  PORTB = 0x00;
  PORTC = 0x00;
  PORTD = 0xF0;
  
  clear();
  delay(100);  

}

uint8_t buf[5] = {0,0,0,0, 0};
uint8_t frame1[8] = { 0x33, 0x00,
                      0x33, 0x00,
                      0x00, 0x00,
                      0x00, 0x00 };
                     
uint8_t frame2[8] = { 0x00, 0x33,
                      0x00, 0x33,
                      0x00, 0x00,
                      0x00, 0x00 };

uint8_t frame3[8] = { 0x00, 0xCC,
                      0x00, 0xCC,
                      0x00, 0x00,
                      0x00, 0x00};
                      
uint8_t frame4[8] = { 0xCC, 0x00,
                      0xCC, 0x00,
                      0x00, 0x00,
                      0x00, 0x00};      

uint8_t frame5[8] = { 0x00, 0x00,
                      0x00, 0x00,
                      0xCC, 0x00,
                      0xCC, 0x00 };
                     
uint8_t frame6[8] = { 0x00, 0x00,
                      0x00, 0x00,
                      0x00, 0xCC,
                      0x00, 0xCC };

uint8_t frame7[8] = { 0x00, 0x00,
                      0x00, 0x00,
                      0x00, 0x33,
                      0x00, 0x33};
uint8_t frame8[8] = { 0x00, 0x00,
                      0x00, 0x00,
                      0x33, 0x00,
                      0x33, 0x00};                 
void loop() {
  int k = 0;
  int j = 0;
  int i = 0;
  
  for (k = 0; k < 2200; k += 1) {
    load_frame(frame1);
    delayMicroseconds(250);
  }
  for (k = 0; k < 2200; k += 1) {
    load_frame(frame2);
    delayMicroseconds(250);
  }

  for (k = 0; k < 2200; k += 1) {
    load_frame(frame3);
    delayMicroseconds(250);
  }
  for (k = 0; k < 2200; k += 1) {
    load_frame(frame4);
    delayMicroseconds(250);
  }

  for (k = 0; k < 2200; k += 1) {
    load_frame(frame5);
    delayMicroseconds(250);
  }

  for (k = 0; k < 2200; k += 1) {
    load_frame(frame6);
    delayMicroseconds(250);
  }

  for (k = 0; k < 2200; k += 1) {
    load_frame(frame7);
    delayMicroseconds(250);
  }

  for (k = 0; k < 2200; k += 1) {
    load_frame(frame8);
    delayMicroseconds(250);
  }
}


