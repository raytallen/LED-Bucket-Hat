
#include <map>
#include <FastLED.h>
#include <images.h>

#define LED_PIN  6

#define COLOR_ORDER GRB
#define CHIPSET     WS2812B

#define BRIGHTNESS 16

// Helper functions for an two-dimensional XY matrix of pixels.
// Simple 2-D demo code is included as well.
//
//     XY(x,y) takes x and y coordinates and returns an LED index number,
//             for use like this:  leds[ XY(x,y) ] == CRGB::Red;
//             No error checking is performed on the ranges of x and y.

// Params for width and height
const uint8_t kMatrixHeight = 8;
const uint8_t kMatrixWidth = 32;

// Param for different pixel layouts
const bool    kMatrixSerpentineLayout = true;
const bool    kMatrixVertical = false;

#define NUM_LEDS (kMatrixWidth * kMatrixHeight)
CRGB leds_plus_safety_pixel[ NUM_LEDS + 1];
CRGB* const leds( leds_plus_safety_pixel + 1);

/* Set 'kMatrixSerpentineLayout' to false if your pixels are 
laid out all running the same way, like this:

    0 >  1 >  2 >  3 >  4
                        |
    .----<----<----<----'
    |
    5 >  6 >  7 >  8 >  9
                        |
    .----<----<----<----'
    |
   10 > 11 > 12 > 13 > 14
                        |
    .----<----<----<----'
    |
   15 > 16 > 17 > 18 > 19

Set 'kMatrixSerpentineLayout' to true if your pixels are 
laid out back-and-forth, like this:

    0 >  1 >  2 >  3 >  4
                        |
                        |
    9 <  8 <  7 <  6 <  5
    |
    |
   10 > 11 > 12 > 13 > 14
                       |
                       |
   19 < 18 < 17 < 16 < 15

Bonus vocabulary word: anything that goes one way 
in one row, and then backwards in the next row, and so on
is call "boustrophedon", meaning "as the ox plows."


This function will return the right 'led index number' for 
a given set of X and Y coordinates on your matrix.  
IT DOES NOT CHECK THE COORDINATE BOUNDARIES.  
That's up to you.  Don't pass it bogus values.

Use the "XY" function like this:

   for( uint8_t x = 0; x < kMatrixWidth; x++) {
     for( uint8_t y = 0; y < kMatrixHeight; y++) {
     
       // Here's the x, y to 'led index' in action: 
       leds[ XY( x, y) ] = CHSV( random8(), 255, 255);
     
     }
   }

*/

uint16_t XY( uint8_t x, uint8_t y )
{
  uint16_t i;
  
  if( kMatrixSerpentineLayout == false) {
    if (kMatrixVertical == false) {
      i = (x * kMatrixHeight) + y;
    } else {
      i = kMatrixWidth * (kMatrixHeight - (y+1))+x;
    }
  }

  if( kMatrixSerpentineLayout == true) {
    if (kMatrixVertical == false) {
      if( x & 0x01) {
        // Odd rows run backwards
        uint8_t reverseX = (kMatrixHeight - 1) - y;
        i = (x * kMatrixHeight) + reverseX;
      } else {
        // Even rows run forwards
        i = (x * kMatrixHeight) + y;
      }
    } else { // vertical positioning
      if ( y & 0x01) {
        i = kMatrixWidth * (kMatrixHeight - (y+1))+x;
      } else {
        i = kMatrixWidth * (kMatrixHeight - y) - (x+1);
      }
    }
  }
  
  return i;
}

// prints image to display
void print_image(char image_array[kMatrixHeight][kMatrixWidth][3]){
  int x, y;
  int m = 0;
  // memcpy(&leds, &image_array, 768);

  for(y = 0; y < kMatrixHeight; y++){
    for(x = 0; x < kMatrixWidth; x++){
      for(m = 0; m < 3; m++){
        leds[XY(x,y)][m] = image_array[y][x][m];
      }
    }
  }

  FastLED.show();
  delay(1);
}

//shifts 2d array in X and Y amounts
void shift_2d_array(char (&image_array)[kMatrixHeight][kMatrixWidth][3], char direction){
  char temp_array[kMatrixHeight][kMatrixWidth][3];
  memcpy(&temp_array, &image_array, sizeof(temp_array));

  int x,y,m;

  switch(direction){
    case 'r':{
      for(y=0; y<kMatrixHeight; y++){
        for(x=0; x<kMatrixWidth; x++){
          break;
        }
      }
    } 
    default: break;
  }
}

void rainbow_wave(int number_of_waves){
  int x, y, m;
  for(m = 0; m < kMatrixWidth*number_of_waves; m++){
    for(y = 0; y < kMatrixHeight; y++){
      for(x = 0; x < kMatrixWidth; x++){
        leds[XY(x,y)] = CHSV((x - m)*8,255,255);
      }
    }
    FastLED.show();
    delay(10);
  }
}

void flash_random_colours(int number_of_colours, int delay_length){
  int x;
  for(x = 0; x < number_of_colours; x++){
    int r = rand() % 256;
    fill_solid(leds, 256, CHSV(r, 255, 255));
    FastLED.show();
    delay(delay_length);
  }
  
}

void setup() {
  Serial.begin(9600);
  Serial.println("Started!");

  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalSMD5050);
  FastLED.setBrightness( BRIGHTNESS );
}


void loop()
{
  print_image(bucket_2d);
  delay(1000);
  print_image(pacman);
  delay(1000);
  rainbow_wave(2);
  delay(1);
  flash_random_colours(10, 200);
  delay(1);
}




