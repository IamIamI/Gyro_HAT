# Gyro_HAT - WIP (Feb-2023)
This is a project to make a hat with two round TFT displays that track your movement.

The build includes;
 - An ESP32
 - A GY-521 MPU-6050 gyro/accelerometer module
 - Two round GC9A01 based TFT displays (or one if you want to make a cyclops)

To make it portable you also will need the following;
 - A 3.7v Lithium battery
 - TP4056 03962A Lithium Battery charger module
 - One HT7333-A 3.3V 0.25A LDO Linear Voltage Regulator
 - A 100uF and 100nf capacitor

The concept is pretty straight forward. 
When you move your head from left to right or up and down, the gyro registers the g-forces in those directions and moves the iris in the same direction.
I tried to also apply a bit of smoothing the way James Burton on youtube tried with his animatronics by taking a portion of the old position and a portion of the new position. The close the new position comes to the old position the more slow down there is.


# v0.4 (current version 19-07-2023)
This is probably the finalized version. 
I might have a plan to add some tiny servo's to be able to give eyelids or eyebrows.

The current schematic looks as followed;


##Wiring
| ESP32 | MPU-6050 Gyro | GC9A01 TFT |
| ---|---|--- |
| Pin 4 | - | RST |
| Pin 19 | - | CS |
| Pin 16 | - | DC |
| Pin 23 | - | SDA |
| Pin 18 | - | SCL |
| 3V3 | VCC | VCC |
| GND | GND | GND |
| Pin 21 | SDA | - |
| Pin 22 | SCL | - |
| - | XDA | - |
| - | XCL | - |
| - | ADO | - |
| - | INT | - |

The code uses the TFT_eSPI library, which you need to set to be use the GC9A01 drivers.
Go to your Arduino libraries folder (default is C:\Users\<your_username>\Documents\Arduino\libraries\TFT_eSPI)
Open User_Setup.h
Comment out line 45 (#define ILI9341_DRIVER) by adding two slashes '//' to the start of the line
Uncomment line 65 (//#define GC9A01_DRIVER) by removing the two slashes '//'at the start of the line
Uncomment line 201-265, these are defininng the default pins used for the TFT display, however we'll be using our own
Add the following lines anywhere you want in the file;
 - #define TFT_MOSI 23
 - #define TFT_SCLK 18
 - #define TFT_CS   22
 - #define TFT_DC   16
 - #define TFT_RST   4

Save.
Now you can upload the 'Gyroscope_Eye_2_v4.ino' script

And the actual hat now looks like this;


<img src="https://github.com/IamIamI/Gyro_HAT/blob/main/images/IMG_20230715_161058.jpg?raw=true" width="400" />

This is how the hat looks in motion;

[<img src="https://github.com/IamIamI/Gyro_HAT/blob/main/images/video1-3.jpg" width="400"/>](https://youtube.com/shorts/zsiIzT4D0e4)

There is still space for improvement, reduction of size, i'm currently using a 1100mah battery, but i assume could get away with a much tinier battery.
The ESP32 i'm using also has a bunch of unused features so i could probably go for a smaller ESP32 type and solder directly onto the board to reduce some bulk.
Also the wires are a bit too long


# v0.3
I added a battery in the schematic, and put the ESP32 on a bootleg breakout board with an on/off switch. 
This way the whole thing is now portable but still works. 

<img src="https://github.com/IamIamI/Gyro_HAT/blob/main/images/IMG_20230715_155742.jpg?raw=true" width="400" />

[<img src="https://github.com/IamIamI/Gyro_HAT/blob/main/images/video2-3.jpg" width="400"/>](https://youtube.com/shorts/ydfomyhoa2s)


# v0.2
The second eye is added, initially i had the eyes in a mirrored position which required additional calculations, but i've decided it will work just as well if they are in the same orientation.
That way troubleshooting will also become easier, if one works but the other not at least it's not the code.

[<img src="https://github.com/IamIamI/Gyro_HAT/blob/main/images/video1-3.jpg" width="400"/>](https://youtu.be/Phr1z9wUe3c)


# v0.1
The script can run standalone, when you rotate the board left/right the x-axis of the iris changes.
When you rotate in the y-axis, the iris moves up and down.
Again, it's clunky and not optimized, WIP!!!!
The eye now works properly but it's very jagged

<img src="https://github.com/IamIamI/Gyro_HAT/blob/main/images/IMG_20230123_200207.jpg?raw=true" width="400" />



