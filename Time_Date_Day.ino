//Time_Date_Day
#ifdef ESP32
#include <WiFi.h>
#else
  #include <WiFi.h>
#endif
#include <time.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire, -1); 

const char* ssid = "Shruthi PG_2.4G main"; 
const char* password = "9663734906";
 
int GMTOffset = 19800;  // 5 hours * 60 minutes/hour + 30 minutes = 19800 seconds
int daylightOffset = 0;  // Replace with your daylight savings offset in seconds
int frame = 0;
#define FRAME_DELAY (42)
#define FRAME_WIDTH (48)
#define FRAME_HEIGHT (48)
#define FRAME_COUNT (sizeof(frames) / sizeof(frames[0]))
const byte PROGMEM frames[][288] = {
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,127,254,0,0,0,7,255,255,224,0,0,31,128,1,248,0,0,124,0,0,62,0,1,224,0,0,7,128,7,128,0,0,1,224,14,0,127,254,0,112,28,3,255,255,192,56,120,15,128,1,240,30,224,60,0,0,60,7,96,240,0,0,15,6,49,192,3,192,3,140,31,128,127,254,1,248,14,3,240,15,192,112,4,7,128,1,224,32,0,30,0,0,120,0,0,56,0,0,28,0,0,112,15,240,14,0,0,224,127,254,6,0,0,113,240,15,142,0,0,59,192,3,220,0,0,31,0,0,248,0,0,14,0,0,112,0,0,0,15,240,0,0,0,0,31,248,0,0,0,0,112,14,0,0,0,0,224,7,0,0,0,0,112,14,0,0,0,0,56,28,0,0,0,0,28,56,0,0,0,0,14,112,0,0,0,0,7,224,0,0,0,0,3,192,0,0,0,0,1,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,127,254,0,0,0,7,255,255,224,0,0,31,128,1,248,0,0,124,0,0,62,0,1,224,0,0,7,128,7,128,0,0,1,224,14,0,127,254,0,112,28,3,255,255,192,56,120,15,128,1,240,30,224,60,0,0,60,7,96,240,0,0,15,6,49,192,3,192,3,140,31,128,127,254,1,248,14,3,240,15,192,112,4,7,128,1,224,32,0,30,0,0,120,0,0,56,0,0,28,0,0,112,15,240,14,0,0,224,127,254,6,0,0,113,240,15,142,0,0,59,192,3,220,0,0,31,0,0,248,0,0,14,0,0,112,0,0,0,15,240,0,0,0,0,31,248,0,0,0,0,112,14,0,0,0,0,224,7,0,0,0,0,112,14,0,0,0,0,56,28,0,0,0,0,28,56,0,0,0,0,14,112,0,0,0,0,7,224,0,0,0,0,3,192,0,0,0,0,1,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,127,254,0,0,0,7,255,255,224,0,0,31,128,1,248,0,0,124,0,0,62,0,1,224,0,0,7,128,7,128,0,0,1,224,14,0,127,254,0,112,28,3,255,255,192,56,120,15,128,1,240,30,224,60,0,0,60,7,96,240,0,0,15,6,49,192,3,192,3,140,31,128,127,254,1,248,14,3,240,15,192,112,4,7,128,1,224,32,0,30,0,0,120,0,0,56,0,0,28,0,0,112,15,240,14,0,0,224,127,254,6,0,0,113,240,15,142,0,0,59,192,3,220,0,0,31,0,0,248,0,0,14,0,0,112,0,0,0,15,240,0,0,0,0,31,248,0,0,0,0,112,14,0,0,0,0,224,7,0,0,0,0,112,14,0,0,0,0,56,28,0,0,0,0,28,56,0,0,0,0,14,112,0,0,0,0,7,224,0,0,0,0,3,192,0,0,0,0,1,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,127,254,0,0,0,7,255,255,224,0,0,31,128,1,248,0,0,124,0,0,62,0,1,224,0,0,7,128,7,128,0,0,1,224,14,0,127,254,0,112,28,3,255,255,192,56,120,15,128,1,240,30,224,60,0,0,60,7,96,240,0,0,15,6,49,192,3,192,3,140,31,128,127,254,1,248,14,3,240,15,192,112,4,7,128,1,224,32,0,30,0,0,120,0,0,56,0,0,28,0,0,112,15,240,14,0,0,224,127,254,6,0,0,113,240,15,142,0,0,59,192,3,220,0,0,31,0,0,248,0,0,14,0,0,112,0,0,0,15,240,0,0,0,0,31,248,0,0,0,0,112,14,0,0,0,0,224,7,0,0,0,0,112,14,0,0,0,0,56,28,0,0,0,0,28,56,0,0,0,0,14,112,0,0,0,0,7,224,0,0,0,0,3,192,0,0,0,0,1,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,127,254,0,0,0,7,255,255,224,0,0,31,128,1,248,0,0,124,0,0,62,0,1,224,0,0,7,128,7,128,0,0,1,224,14,0,127,254,0,112,28,3,255,255,192,56,120,15,128,1,240,30,224,60,0,0,60,7,96,240,0,0,15,6,49,192,63,252,3,140,31,129,255,255,129,248,14,7,192,3,224,112,4,31,0,0,248,32,0,60,0,0,60,0,0,112,7,224,14,0,0,224,63,252,7,0,0,112,248,31,14,0,0,59,192,3,220,0,0,31,0,0,248,0,0,14,0,0,112,0,0,4,15,240,32,0,0,0,31,248,0,0,0,0,120,30,0,0,0,0,224,7,0,0,0,0,112,14,0,0,0,0,56,28,0,0,0,0,28,56,0,0,0,0,14,112,0,0,0,0,7,224,0,0,0,0,3,192,0,0,0,0,1,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,63,252,0,0,0,3,255,255,192,0,0,31,128,1,248,0,0,124,0,0,62,0,1,224,0,0,7,128,3,128,0,0,1,192,14,0,63,252,0,112,28,3,255,255,192,56,56,15,128,1,240,28,96,60,0,0,60,14,96,112,15,240,14,6,49,192,255,255,3,140,59,131,224,7,193,220,30,15,0,0,240,120,12,28,0,0,56,48,0,120,0,0,28,0,0,224,15,240,7,0,0,224,127,254,7,0,0,113,224,7,142,0,0,59,128,1,220,0,0,31,0,0,248,0,0,14,0,0,112,0,0,0,7,224,0,0,0,0,31,248,0,0,0,0,120,30,0,0,0,0,224,7,0,0,0,0,112,14,0,0,0,0,56,28,0,0,0,0,28,56,0,0,0,0,14,112,0,0,0,0,7,224,0,0,0,0,3,192,0,0,0,0,1,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,63,252,0,0,0,3,255,255,192,0,0,31,192,3,248,0,0,126,0,0,126,0,1,240,0,0,15,128,3,192,0,0,3,192,15,0,63,252,0,240,28,3,255,255,192,56,56,15,192,3,240,28,96,60,0,0,60,14,224,112,0,0,14,7,113,224,3,192,7,142,59,128,127,254,1,220,31,3,224,7,192,248,14,15,0,0,240,112,0,28,0,0,56,0,0,56,0,0,28,0,0,224,15,240,7,0,0,224,127,254,7,0,0,113,240,15,14,0,0,59,192,3,220,0,0,31,0,0,248,0,0,12,0,0,112,0,0,0,0,0,0,0,0,0,1,128,0,0,0,0,31,248,0,0,0,0,62,124,0,0,0,0,240,15,0,0,0,0,96,7,0,0,0,0,112,14,0,0,0,0,56,28,0,0,0,0,28,56,0,0,0,0,14,112,0,0,0,0,7,224,0,0,0,0,3,192,0,0,0,0,1,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,127,254,0,0,0,7,255,255,192,0,0,31,128,1,248,0,0,124,0,0,62,0,1,224,0,0,7,128,7,128,0,0,1,224,14,0,63,252,0,112,28,3,255,255,192,56,112,15,192,3,240,12,224,60,0,0,60,7,224,240,0,0,15,7,113,192,0,0,3,142,59,128,0,0,1,220,31,0,0,0,0,248,12,0,0,0,0,48,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,240,0,0,0,0,127,254,0,0,0,1,224,7,128,0,0,7,128,1,224,0,0,14,0,0,112,0,0,28,15,240,56,0,0,28,63,252,56,0,0,14,224,7,112,0,0,7,128,1,224,0,0,3,0,0,192,0,0,0,15,240,0,0,0,0,63,252,0,0,0,0,112,14,0,0,0,0,224,7,0,0,0,0,112,14,0,0,0,0,56,28,0,0,0,0,28,56,0,0,0,0,14,112,0,0,0,0,7,224,0,0,0,0,3,192,0,0,0,0,1,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,63,252,0,0,0,1,252,63,128,0,0,7,128,1,224,0,0,28,0,0,56,0,0,112,31,248,14,0,0,224,255,255,7,0,1,131,192,7,193,128,3,15,0,0,240,192,1,156,0,0,57,128,0,248,0,0,31,0,0,96,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,240,0,0,0,0,62,124,0,0,0,0,127,254,0,0,0,0,255,255,0,0,0,0,112,14,0,0,0,0,224,7,0,0,0,0,112,14,0,0,0,0,56,28,0,0,0,0,28,56,0,0,0,0,14,112,0,0,0,0,7,224,0,0,0,0,3,192,0,0,0,0,1,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,192,0,0,0,0,28,56,0,0,0,0,97,134,0,0,0,0,159,249,0,0,0,1,179,205,0,0,0,0,223,251,0,0,0,0,60,60,0,0,0,0,240,15,0,0,0,0,96,6,0,0,0,0,48,12,0,0,0,0,24,24,0,0,0,0,12,48,0,0,0,0,6,112,0,0,0,0,7,224,0,0,0,0,3,192,0,0,0,0,1,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,240,0,0,0,0,63,252,0,0,0,0,112,14,0,0,0,0,224,7,0,0,0,0,112,14,0,0,0,0,56,28,0,0,0,0,28,56,0,0,0,0,14,112,0,0,0,0,7,224,0,0,0,0,3,192,0,0,0,0,1,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,240,0,0,0,0,31,248,0,0,0,0,112,14,0,0,0,0,224,7,0,0,0,0,112,14,0,0,0,0,56,28,0,0,0,0,28,56,0,0,0,0,14,112,0,0,0,0,7,224,0,0,0,0,3,192,0,0,0,0,1,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,240,0,0,0,0,31,248,0,0,0,0,112,14,0,0,0,0,224,7,0,0,0,0,112,14,0,0,0,0,56,28,0,0,0,0,28,56,0,0,0,0,14,112,0,0,0,0,7,224,0,0,0,0,3,192,0,0,0,0,1,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,240,0,0,0,0,31,248,0,0,0,0,112,14,0,0,0,0,224,7,0,0,0,0,112,14,0,0,0,0,56,28,0,0,0,0,28,56,0,0,0,0,14,112,0,0,0,0,7,224,0,0,0,0,3,192,0,0,0,0,1,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,240,0,0,0,0,31,248,0,0,0,0,112,14,0,0,0,0,224,7,0,0,0,0,112,14,0,0,0,0,56,28,0,0,0,0,28,56,0,0,0,0,14,112,0,0,0,0,7,224,0,0,0,0,3,192,0,0,0,0,1,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,240,0,0,0,0,31,248,0,0,0,0,112,14,0,0,0,0,224,7,0,0,0,0,112,14,0,0,0,0,56,28,0,0,0,0,28,56,0,0,0,0,14,112,0,0,0,0,7,224,0,0,0,0,3,192,0,0,0,0,1,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,240,0,0,0,0,31,248,0,0,0,0,112,14,0,0,0,0,224,7,0,0,0,0,112,14,0,0,0,0,56,28,0,0,0,0,28,56,0,0,0,0,14,112,0,0,0,0,7,224,0,0,0,0,3,192,0,0,0,0,1,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,240,0,0,0,0,31,248,0,0,0,0,112,14,0,0,0,0,224,7,0,0,0,0,112,14,0,0,0,0,56,28,0,0,0,0,28,56,0,0,0,0,14,112,0,0,0,0,7,224,0,0,0,0,3,192,0,0,0,0,1,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,31,248,0,0,0,0,49,140,0,0,0,0,255,255,0,0,0,0,255,255,0,0,0,0,112,14,0,0,0,0,224,7,0,0,0,0,112,14,0,0,0,0,56,28,0,0,0,0,28,56,0,0,0,0,14,112,0,0,0,0,7,224,0,0,0,0,3,192,0,0,0,0,1,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,31,248,0,0,0,0,255,255,0,0,0,3,224,7,192,0,0,15,0,0,240,0,0,28,63,252,56,0,0,56,248,31,28,0,0,115,192,3,206,0,0,63,0,0,252,0,0,30,0,0,120,0,0,8,0,0,16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,240,0,0,0,0,63,252,0,0,0,0,124,62,0,0,0,0,240,15,0,0,0,0,96,6,0,0,0,0,48,12,0,0,0,0,24,24,0,0,0,0,12,48,0,0,0,0,6,112,0,0,0,0,7,224,0,0,0,0,3,192,0,0,0,0,1,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,255,0,0,0,7,255,255,224,0,0,31,128,1,248,0,0,124,0,0,62,0,0,240,0,0,15,0,3,192,63,252,3,192,7,1,255,255,128,224,14,7,128,1,224,112,24,28,0,0,120,56,28,120,0,0,30,56,14,224,0,0,7,112,7,192,0,0,3,224,3,128,0,0,1,192,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,240,0,0,0,0,127,254,0,0,0,0,248,31,0,0,0,1,192,3,128,0,0,7,7,224,224,0,0,3,31,248,192,0,0,3,248,31,128,0,0,1,239,247,128,0,0,0,63,252,0,0,0,0,112,14,0,0,0,0,224,7,0,0,0,0,112,14,0,0,0,0,56,28,0,0,0,0,28,56,0,0,0,0,14,112,0,0,0,0,7,224,0,0,0,0,3,192,0,0,0,0,1,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,127,254,0,0,0,7,255,255,192,0,0,31,128,1,248,0,0,124,0,0,62,0,1,224,0,0,7,128,7,128,0,0,1,224,14,0,63,252,0,112,28,3,255,255,192,56,112,15,192,3,240,12,224,60,0,0,60,7,224,240,0,0,15,7,113,192,0,0,3,142,59,128,0,0,1,220,31,0,0,0,0,248,12,0,0,0,0,48,0,0,31,248,0,0,0,0,255,254,0,0,0,1,240,15,128,0,0,7,128,1,224,0,0,30,0,0,120,0,0,56,7,224,28,0,0,56,63,252,28,0,0,24,252,63,24,0,0,31,224,7,248,0,0,15,128,1,240,0,0,6,0,0,96,0,0,0,0,0,0,0,0,0,15,240,0,0,0,0,63,252,0,0,0,0,112,14,0,0,0,0,224,7,0,0,0,0,112,14,0,0,0,0,56,28,0,0,0,0,28,56,0,0,0,0,14,112,0,0,0,0,7,224,0,0,0,0,3,192,0,0,0,0,1,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,63,252,0,0,0,3,255,255,192,0,0,31,192,3,248,0,0,126,0,0,126,0,1,240,0,0,15,128,3,192,0,0,3,192,15,0,63,252,0,240,28,3,255,255,192,56,56,15,192,3,240,28,96,60,0,0,60,14,224,112,0,0,14,7,113,224,3,192,7,142,59,128,127,254,1,220,31,3,224,7,192,248,14,15,0,0,240,112,0,28,0,0,56,0,0,56,0,0,28,0,0,224,15,240,7,0,0,224,127,254,7,0,0,113,240,15,14,0,0,59,192,3,220,0,0,31,0,0,248,0,0,12,0,0,112,0,0,0,0,0,0,0,0,0,1,128,0,0,0,0,31,248,0,0,0,0,62,124,0,0,0,0,240,15,0,0,0,0,96,7,0,0,0,0,112,14,0,0,0,0,56,28,0,0,0,0,28,56,0,0,0,0,14,112,0,0,0,0,7,224,0,0,0,0,3,192,0,0,0,0,1,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,63,252,0,0,0,3,255,255,192,0,0,31,128,1,248,0,0,124,0,0,62,0,1,224,0,0,7,128,3,128,0,0,1,192,14,0,63,252,0,112,28,3,255,255,192,56,56,15,128,1,240,28,96,60,0,0,60,14,96,112,15,240,14,6,49,192,255,255,3,140,59,131,224,7,193,220,30,15,0,0,240,120,12,28,0,0,56,48,0,120,0,0,28,0,0,224,15,240,7,0,0,224,127,254,7,0,0,113,224,7,142,0,0,59,128,1,220,0,0,31,0,0,248,0,0,14,0,0,112,0,0,0,7,224,0,0,0,0,31,248,0,0,0,0,120,30,0,0,0,0,224,7,0,0,0,0,112,14,0,0,0,0,56,28,0,0,0,0,28,56,0,0,0,0,14,112,0,0,0,0,7,224,0,0,0,0,3,192,0,0,0,0,1,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,127,254,0,0,0,7,255,255,224,0,0,31,128,1,248,0,0,124,0,0,62,0,1,224,0,0,7,128,7,128,0,0,1,224,14,0,127,254,0,112,28,3,255,255,192,56,120,15,128,1,240,30,224,60,0,0,60,7,96,240,0,0,15,6,49,192,63,252,3,140,31,129,255,255,129,248,14,7,192,3,224,112,4,31,0,0,248,32,0,60,0,0,60,0,0,112,7,224,14,0,0,224,63,252,7,0,0,112,248,31,14,0,0,59,192,3,220,0,0,31,0,0,248,0,0,14,0,0,112,0,0,4,15,240,32,0,0,0,31,248,0,0,0,0,120,30,0,0,0,0,224,7,0,0,0,0,112,14,0,0,0,0,56,28,0,0,0,0,28,56,0,0,0,0,14,112,0,0,0,0,7,224,0,0,0,0,3,192,0,0,0,0,1,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,127,254,0,0,0,7,255,255,224,0,0,31,128,1,248,0,0,124,0,0,62,0,1,224,0,0,7,128,7,128,0,0,1,224,14,0,127,254,0,112,28,3,255,255,192,56,120,15,128,1,240,30,224,60,0,0,60,7,96,240,0,0,15,6,49,192,3,192,3,140,31,128,127,254,1,248,14,3,240,15,192,112,4,7,128,1,224,32,0,30,0,0,120,0,0,56,0,0,28,0,0,112,15,240,14,0,0,224,127,254,6,0,0,113,240,15,142,0,0,59,192,3,220,0,0,31,0,0,248,0,0,14,0,0,112,0,0,0,15,240,0,0,0,0,31,248,0,0,0,0,112,14,0,0,0,0,224,7,0,0,0,0,112,14,0,0,0,0,56,28,0,0,0,0,28,56,0,0,0,0,14,112,0,0,0,0,7,224,0,0,0,0,3,192,0,0,0,0,1,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,127,254,0,0,0,7,255,255,224,0,0,31,128,1,248,0,0,124,0,0,62,0,1,224,0,0,7,128,7,128,0,0,1,224,14,0,127,254,0,112,28,3,255,255,192,56,120,15,128,1,240,30,224,60,0,0,60,7,96,240,0,0,15,6,49,192,3,192,3,140,31,128,127,254,1,248,14,3,240,15,192,112,4,7,128,1,224,32,0,30,0,0,120,0,0,56,0,0,28,0,0,112,15,240,14,0,0,224,127,254,6,0,0,113,240,15,142,0,0,59,192,3,220,0,0,31,0,0,248,0,0,14,0,0,112,0,0,0,15,240,0,0,0,0,31,248,0,0,0,0,112,14,0,0,0,0,224,7,0,0,0,0,112,14,0,0,0,0,56,28,0,0,0,0,28,56,0,0,0,0,14,112,0,0,0,0,7,224,0,0,0,0,3,192,0,0,0,0,1,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,127,254,0,0,0,7,255,255,224,0,0,31,128,1,248,0,0,124,0,0,62,0,1,224,0,0,7,128,7,128,0,0,1,224,14,0,127,254,0,112,28,3,255,255,192,56,120,15,128,1,240,30,224,60,0,0,60,7,96,240,0,0,15,6,49,192,3,192,3,140,31,128,127,254,1,248,14,3,240,15,192,112,4,7,128,1,224,32,0,30,0,0,120,0,0,56,0,0,28,0,0,112,15,240,14,0,0,224,127,254,6,0,0,113,240,15,142,0,0,59,192,3,220,0,0,31,0,0,248,0,0,14,0,0,112,0,0,0,15,240,0,0,0,0,31,248,0,0,0,0,112,14,0,0,0,0,224,7,0,0,0,0,112,14,0,0,0,0,56,28,0,0,0,0,28,56,0,0,0,0,14,112,0,0,0,0,7,224,0,0,0,0,3,192,0,0,0,0,1,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};
 
void setup() { 
  Serial.begin(115200); 

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1); 
  display.setCursor(0,0);
  display.setTextColor(WHITE);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
    display.clearDisplay();
  display.drawBitmap(40, 8, frames[frame], FRAME_WIDTH, FRAME_HEIGHT, 1);
  display.display();
  frame = (frame + 1) % FRAME_COUNT;
  
  }

  Serial.println("Connected to Wi-Fi!");

  // Set GMT offset to IST (Indian Standard Time)
  configTime(GMTOffset, daylightOffset, "pool.ntp.org", "time.nist.gov");
}

 
void loop() {
  time_t rawtime = time(nullptr);
  struct tm* timeinfo = localtime(&rawtime);

  Serial.print("Time: ");
  Serial.print(timeinfo->tm_hour);
  Serial.print(":");
  Serial.print(timeinfo->tm_min);
  Serial.print(":");
  Serial.println(timeinfo->tm_sec);

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);

  // Time
  display.setCursor(15, 0);
  display.print(timeinfo->tm_hour);
  display.print(":");
  if( timeinfo->tm_min < 10)
    display.print("0");
  display.print(timeinfo->tm_min);
  display.print(":");
  if( timeinfo->tm_sec < 10)
    display.print("0");
  display.println(timeinfo->tm_sec);

  // Date
  display.setTextSize(2);
  display.setCursor(5, 25);
  display.print(timeinfo->tm_mday);
  display.print(" ");
  switch(timeinfo->tm_mon + 1) {
    case 1:
      display.print("Jan");
      break;
    case 2:
      display.print("Feb");
      break;
    case 3:
      display.print("Mar");
      break;
    case 4:
      display.print("Apr");
      break;
    case 5:
      display.print("May");
      break;
    case 6:
      display.print("Jun");
      break;
    case 7:
      display.print("Jul");
      break;
    case 8:
      display.print("Aug");
      break;
    case 9:
      display.print("Sep");
      break;
    case 10:
      display.print("Oct");
      break;
    case 11:
      display.print("Nov");
      break;
    case 12:
      display.print("Dec");
      break;
  }
  display.print(" ");
  display.println(1900 + timeinfo->tm_year);

  // Day
  display.setTextSize(2);
  display.setCursor(30, 50);
  switch(timeinfo->tm_wday) {
    case 0:
      display.print("Sunday");
      break;
    case 1:
      display.print("Monday");
      break;
    case 2:
      display.print("Tuesday");
      break;
    case 3:
      display.print("Wednesay");
      break;
    case 4:
      display.print("Thursday");
      break;
    case 5:
      display.print("Friday");
      break;
    case 6:
      display.print("Saturday");
      break;
  }

  display.display();
 
  delay(1000); 
}