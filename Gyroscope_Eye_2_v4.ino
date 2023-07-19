// ESP32 Guide: https://RandomNerdTutorials.com/esp32-mpu-6050-accelerometer-gyroscope-arduino/
// ESP8266 Guide: https://RandomNerdTutorials.com/esp8266-nodemcu-mpu-6050-accelerometer-gyroscope-arduino/
// Arduino Guide: https://RandomNerdTutorials.com/arduino-mpu-6050-accelerometer-gyroscope/

#include <Adafruit_MPU6050.h>
//#include <Adafruit_Sensor.h>
//#include <Wire.h>
#include "iris.h" 

Adafruit_MPU6050 mpu;

#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite eyeballSprite = TFT_eSprite(&tft); // Sprite for meter reading
TFT_eSprite pupilSprite   = TFT_eSprite(&tft); // Sprite for meter reading

int positionz = 50; // Starts at -120 degrees
int positionx = 50; // Starts at -120 degrees

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
  eyeballSprite.fillSprite(TFT_WHITE);

  pupilSprite.createSprite(140,140);
  pupilSprite.setSwapBytes(true);
  pupilSprite.pushImage(0,0,140,140,iris);
  // Position 50,50 is the start x and y coordinates
  pupilSprite.pushToSprite(&eyeballSprite,50,50,TFT_WHITE);

  eyeballSprite.pushSprite(0,0);
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  plotPupil(g.gyro.x,g.gyro.y,g.gyro.z);
  delay(10);
}

// =======================================================================================
// Move the needle to a new position
// =======================================================================================

void plotPupil(int16_t gyro_x, int16_t gyro_y, int16_t gyro_z)
{
  Serial.print("Gyro_X:");
  Serial.print(gyro_x);
  Serial.print(",");
  Serial.print("Gyro_Y:");
  Serial.print(gyro_y);
  Serial.print(",");
  Serial.print("Gyro_Z:");
  Serial.println(gyro_z);
  gyro_z=gyro_z/-1;
  gyro_x=gyro_x/-1;

  if(gyro_z==0){
    positionz=50+((positionz-50)*0.75);
  }else{
    positionz=positionz+(gyro_z*3);
    if(positionz<0){
      positionz=0;
    }else if(positionz>100){
      positionz=100;
    }
  }
  if(gyro_x==0){
    positionx=50+((positionx-50)*0.75);
  }else{
    positionx=positionx+(gyro_x*4);
    if(positionx<0){
      positionx=0;
    }else if(positionx>100){
      positionx=100;
    }
  }

//  Serial.print("New_X:");
//  Serial.print(positionx);
//  Serial.print(",");
//  Serial.print("New_Y:");
//  Serial.println(positiony);

  eyeballSprite.fillSprite(TFT_WHITE);

  pupilSprite.pushImage(0,0,140,140,iris);
  // Position 50,50 is the start z and y coordinates
  pupilSprite.pushToSprite(&eyeballSprite,positionz,positionx,TFT_WHITE);
  pupilSprite.setSwapBytes(true);

  eyeballSprite.pushSprite(0,0);

}