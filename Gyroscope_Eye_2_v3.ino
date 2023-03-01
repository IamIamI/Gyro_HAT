// ESP32 Guide: https://RandomNerdTutorials.com/esp32-mpu-6050-accelerometer-gyroscope-arduino/
// ESP8266 Guide: https://RandomNerdTutorials.com/esp8266-nodemcu-mpu-6050-accelerometer-gyroscope-arduino/
// Arduino Guide: https://RandomNerdTutorials.com/arduino-mpu-6050-accelerometer-gyroscope/

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include "iris.h" 

Adafruit_MPU6050 mpu;

#define TFT_MOSI 23
#define TFT_SCLK 18
#define TFT_CS   19  // Chip select control pin
#define TFT_DC   16  // Data Command control pin
#define TFT_RST   4  // Reset pin (could connect to RST pin)

#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite eyeballSprite = TFT_eSprite(&tft); // Sprite for meter reading
TFT_eSprite pupilSprite   = TFT_eSprite(&tft); // Sprite for meter reading


// Include the jpeg decoder library
//#include <TJpg_Decoder.h>

//uint16_t* tft_buffer;
//bool      buffer_loaded = false;
//uint16_t  spr_width = 0;
//uint16_t  bg_color =0;
int x =1;
int y =1;
//bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap)
//{
  // Stop further decoding as image is running off bottom of screen
//  if ( y >= tft.height() ) return 0;

  // This function will clip the image block rendering automatically at the TFT boundaries
//  tft.pushImage(x, y, w, h, bitmap);

  // Return 1 to decode next block
 // return 1;
//}


void setup(void) {
  Serial.begin(115200);

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);

  tft.init();
  tft.setRotation(2);
  tft.setSwapBytes(true);
  tft.fillScreen(TFT_WHITE);

  eyeballSprite.createSprite(240, 240);
  pupilSprite.createSprite(140,140);
  pupilSprite.setSwapBytes(true);
  // drawPupil(x, y, 70, TFT_MAGENTA);
  //  drawPupil(50, 50, 70, 000000);
  //delay(2000);
  eyeballSprite.fillSprite(TFT_WHITE);
  pupilSprite.pushImage(0,0,140,140,iris);
  pupilSprite.pushToSprite(&eyeballSprite,50,50,TFT_WHITE);
  eyeballSprite.pushSprite(0,0);
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  //Serial.print(g.gyro.x);
  //Serial.print(" ");
  //Serial.print(g.gyro.y);
  //Serial.print(" ");
  //Serial.println(g.gyro.z);

//  eyeballSprite.fillSprite(TFT_WHITE);
//  pupilSprite.pushImage(0,0,140,140,iris);
//  pupilSprite.pushToSprite(&eyeballSprite,x,50,TFT_WHITE);
//  eyeballSprite.pushSprite(0,0);
 // x++;
 // if(x>150){
 //   x=-50;
 //   y++;
 // }
 // if(y>100){
 //   y=-10;
 // }
 // Serial.print(x);
 // Serial.print(" ");
 // Serial.print(y);
 // Serial.println(" ");
  plotPupil(g.gyro.x,g.gyro.y,5);
  delay(100);
}

// =======================================================================================
// Move the needle to a new position
// =======================================================================================
void plotPupil2(int16_t positionx, int16_t positiony, uint16_t ms_delay)
{
  static int16_t old_positionx = 50; // Starts at -120 degrees
  static int16_t old_positiony = 50; // Starts at -120 degrees
  positionx += 8;
  positionx = positionx*6.25;
  positiony += 8;
  positiony = positiony*6.25;
  Serial.print(positionx);
  Serial.print(" ");
  Serial.println(positiony);

  // Move the needle until new position reached
  while ((positionx != old_positionx) && (positiony != old_positiony)) {

    if (old_positionx < positionx){
      old_positionx++;
    } else if (old_positionx > positionx){
        old_positionx--;
    }
    if (old_positiony < positiony){
      old_positiony++;
    } else if (old_positiony > positiony){
        old_positiony--;
    }

    // Only plot needle at even values to improve plotting performance
    if ( ((old_positionx & 1) == 0) && ((old_positionx & 1) == 0))
    {
      //Serial.println(old_position);
      // Draw the needle in the new position, black in needle image is transparent
      eyeballSprite.fillSprite(TFT_WHITE);
      pupilSprite.pushImage(0,0,140,140,iris);
      pupilSprite.pushToSprite(&eyeballSprite,old_positionx,old_positiony,TFT_WHITE);
      
      //Serial.print("Mankey");
      // Wait before next update
      delay(ms_delay);
    }

    eyeballSprite.pushSprite(0,0);

    // Slow needle down slightly as it approaches the new position
    if ((abs(old_positionx - positionx) < 10) || (abs(old_positiony - positiony) < 10)) ms_delay += ms_delay / 5;
  }
}


void plotPupil(int16_t angle, int16_t positiony, uint16_t ms_delay)
{
  static int16_t old_angle = 0; // Starts at -120 degrees

  // Bounding box parameters
  static int16_t min_x;
  static int16_t min_y;
  static int16_t max_x;
  static int16_t max_y;

  angle = angle*6.25;

  // Move the needle until new angle reached
  while (angle != old_angle) {

    if (old_angle < angle) old_angle+=2;
    else old_angle-=2;

    // Only plot needle at even values to improve plotting performance
    if ( (old_angle & 1) == 0)
    {

      eyeballSprite.fillSprite(TFT_WHITE);
      pupilSprite.pushImage(0,0,140,140,iris);
      pupilSprite.pushToSprite(&eyeballSprite,(old_angle+50),positiony,TFT_WHITE);

      // Wait before next update
      delay(ms_delay);
    }

    // Update the number at the centre of the dial
    eyeballSprite.pushSprite(0,0);

    // Slow needle down slightly as it approaches the new position
    if (abs(old_angle - angle) < 10) ms_delay += ms_delay / 10;
  }
}