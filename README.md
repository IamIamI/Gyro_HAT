# Gyro_HAT - WIP (Feb-2023)
This is a project to make a hat with two round TFT displays that track your movement.

The build includes;
  - An ESP32
  - A MPU-6050 Gyroscope/Accelerometer
  
The build is pretty straight forward. And the concept pretty simple. 
When you move the board left or right, the x-axis of the gyro changes, and that pushes the iris to left or right.

![alt text](https://github.com/IamIamI/Gyro_HAT/blob/main/Gyro_eye.jpg?raw=true)

The code is pretty clunky still, i hadn't figured out how sprites worked, and also the movement was smoothed out
using an example code from the tft_espi library, but this one feels very slow. I'll make a faster, cleaner version soon

# v0.0.1
The script can run standalone, when you rotate the board left/right the x-axis of the iris changes.
When you rotate in the y-axis, the iris moves up and down (see video).
Again, it's clunky and not optimized, WIP!!!!
