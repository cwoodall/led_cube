/* LED CUBE
 *
 * Christopher Woodall
 * A BUILDS Production
 * MIT License 2012
 *
 * Stuff goes here...
 */
#include "LEDCube.h"
#include "NESController.h"

#define FRAME_RATE 500
#define NES_CLK 2
#define NES_LATCH 3
#define NES_IN 4
#define BAUDRATE 9600

uint8_t state = 0;
uint8_t bantime = 0;
uint8_t blinky_counter = 0;

uint8_t curx = 0;
uint8_t cury = 0;
uint8_t curz = 0;
uint8_t curset = 0;

NESController controller(NES_IN, NES_CLK, NES_LATCH);
uint8_t frame[8] = {
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
};

void setbit (uint8_t x, uint8_t y, uint8_t z)
{
  uint8_t slice;
  uint8_t mask;

  if(y < 2)
    slice = 2*z;
  else
    slice = (2*z)+1;
  
  if(y % 2 == 0)
    mask = 0x01 << x;
  else
    mask = 0x10 << x;

  frame[slice] |= mask;
} 
      
void unsetbit (uint8_t x, uint8_t y, uint8_t z)
{
  uint8_t slice;
  uint8_t mask;

  if(y < 2)
    slice = 2*z;
  else
    slice = (2*z)+1;
  
  if(y % 2 == 0)
    mask = ~(0x01 << x);
  else
    mask = ~(0x10 << x);

  frame[slice] &= mask;
}

void togglebit (uint8_t x, uint8_t y, uint8_t z)
{
  uint8_t slice;
  uint8_t mask;

  if(y < 2)
    slice = 2*z;
  else
    slice = (2*z)+1;
  
  if(y % 2 == 0)
    mask = (0x01 << x);
  else
    mask = (0x10 << x);

  frame[slice] ^= mask;
}

uint8_t readbit (uint8_t x, uint8_t y, uint8_t z)
{
  uint8_t slice;
  uint8_t mask;

  if(y < 2)
    slice = 2*z;
  else
    slice = (2*z)+1;
  
  if(y % 2 == 0)
    mask = (0x01 << x);
  else
    mask = (0x10 << x);

  return frame[slice] & mask;
}

void setup() 
{
//    Serial.begin(9600);


    initialize_cube();
    setbit(0,0,0);

    delay(200);  
}

void loop() 
{

   

  controller.update();

  uint8_t ban = state;
  state = controller.read();
  if(state != ban && bantime >= 20)
    {
      bantime = 0;
      //A
      if ((state | 0b11111110) != 0xFF) {
	if(!!readbit(curx,cury,curz) != curset) //if where we are doesn't match our set status
	  togglebit(curx,cury,curz);

	curz = (curz + 1) % 4;
	curset = (!!readbit(curx,cury,curz));
	setbit(curx,cury,curz);
      }
      //B
      if ((state | 0b11111101) != 0xFF) {
	
	if(!!readbit(curx,cury,curz) != curset) //if where we are doesn't match our set status
	  togglebit(curx,cury,curz);
	
	curz = (curz + 3) % 4;
	curset = (!!readbit(curx,cury,curz));
	setbit(curx,cury,curz);
      }
      //Select
      if ((controller.read() | 0b11111011) != 0xFF) {
	memset(frame,0x00,sizeof(frame));
	curset = 0;
      }
      //Start
      if ((controller.read() | 0b11110111) != 0xFF) {
	curset ^= 0x01;
      }
      //Up Arrow
      if ((state | 0b11101111) != 0xFF) {

	
	if(!!readbit(curx,cury,curz) != curset) //if where we are doesn't match our set status
	  togglebit(curx,cury,curz);
	
	curx = (curx + 1) % 4;
	curset = (!!readbit(curx,cury,curz));
	setbit(curx,cury,curz);


      }
      //Down Arrow
      if ((state | 0b11011111) != 0xFF) {

	
	if(!!readbit(curx,cury,curz) != curset) //if where we are doesn't match our set status
	  togglebit(curx,cury,curz);
	
	curx = (curx + 3) % 4;
	curset = (!!readbit(curx,cury,curz));
	setbit(curx,cury,curz);

      }
      //Left Arrow
      if ((state | 0b10111111) != 0xFF) {
	
	if(!!readbit(curx,cury,curz) != curset) //if where we are doesn't match our set status
	  togglebit(curx,cury,curz);
	
	cury = (cury + 1) % 4;
	curset = (!!readbit(curx,cury,curz));
	setbit(curx,cury,curz);

      }
      //Right Arrow
      if ((state | 0b01111111) != 0xFF) {
	
	if(!!readbit(curx,cury,curz) != curset) //if where we are doesn't match our set status
	  togglebit(curx,cury,curz);
	
	cury = (cury + 3) % 4;
	curset = (!!readbit(curx,cury,curz));
	setbit(curx,cury,curz);

      }
    }    
    blinky_counter += 1;
  
  
   if(blinky_counter == 200)
   {
     togglebit(curx,cury,curz);
   }
  
  load_frame(frame,800);
  bantime += 1;
}
