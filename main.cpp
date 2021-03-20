#include <iostream>
#include <wiringPi.h>
#include <softPwm.h>
#include <wiringPiI2C.h>
#include <softServo.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>

using namespace std;

int fd;
double accX, accY, accZ, gyroX, gyroY, gyroZ, temp;
long int ldrValue1, ldrValue2, ldrValue3, ldrValue4;
int counter;
int servoPostition;

void ConfigPwmGpio(int ConfigPwmGpio)
{
    pinMode(ConfigPwmGpio, OUTPUT);
    digitalWrite(ConfigPwmGpio, LOW);
    softPwmCreate(ConfigPwmGpio, 0, 100);
}

int readMPU6050(int Mpu6050Addr)
{
    int val = (wiringPiI2CReadReg8(fd, Mpu6050Addr) << 8) +  wiringPiI2CReadReg8(fd, Mpu6050Addr+1);
    if (val >= 0x8000)
    val = -(65536 - val);
    return val;
}

void testServoCode()
{
    servoPostition = 0;
    counter = 0;
    while (counter <= 200){
        digitalWrite(4,HIGH);
        delay(20 - servoPostition);
        digitalWrite(4,LOW);
        delay(servoPostition);
        counter++;
    }
    servoPostition = 5;
    counter = 0;
    while (counter <= 200){
        digitalWrite(4,HIGH);
        delay(20 - servoPostition);
        digitalWrite(4,LOW);
        delay(servoPostition);
        counter++;
    }
    servoPostition = 10;
    counter = 0;
    while (counter <= 200){
        digitalWrite(4,HIGH);
        delay(20 - servoPostition);
        digitalWrite(4,LOW);
        delay(servoPostition);
        counter++;
    }
    servoPostition = 15;
    counter = 0;
    while (counter <= 200){
        digitalWrite(4,HIGH);
        delay(20 - servoPostition);
        digitalWrite(4,LOW);
        delay(servoPostition);
        counter++;
    }
    servoPostition = 20;
    counter = 0;
    while (counter <= 200){
        digitalWrite(4,HIGH);
        delay(20 - servoPostition);
        digitalWrite(4,LOW);
        delay(servoPostition);
        counter++;
    }
    servoPostition = 15;
    counter = 0;
    while (counter <= 200){
        digitalWrite(4,HIGH);
        delay(20 - servoPostition);
        digitalWrite(4,LOW);
        delay(servoPostition);
        counter++;
    }
    servoPostition = 10;
    counter = 0;
    while (counter <= 200){
        digitalWrite(4,HIGH);
        delay(20 - servoPostition);
        digitalWrite(4,LOW);
        delay(servoPostition);
        counter++;
    }
    servoPostition = 5;
    counter = 0;
    while (counter <= 200){
        digitalWrite(4,HIGH);
        delay(20 - servoPostition);
        digitalWrite(4,LOW);
        delay(servoPostition);
        counter++;
    }
    servoPostition = 0;
    counter = 0;
    while (counter <= 200){
        digitalWrite(4,HIGH);
        delay(20 - servoPostition);
        digitalWrite(4,LOW);
        delay(servoPostition);
        counter++;
    }
}

void readLdrValues()
{
    struct timespec now;
    struct timespec last;
    long int diffTime = 0;
    for (int ldrPin = 0; ldrPin < 4; ++ldrPin){
        pinMode(ldrPin, OUTPUT);
        digitalWrite(ldrPin, LOW);
        delay(100);
        pinMode(ldrPin, INPUT);
        clock_gettime(CLOCK_REALTIME, &last);

        while (digitalRead(ldrPin) != 1){
            diffTime = (last.tv_nsec - now.tv_nsec);
        }

        switch(ldrPin){
            case 0:
                ldrValue1 = diffTime; 
            case 1:
                ldrValue2 = diffTime;
            case 2:
                ldrValue3 = diffTime;
            case 3:
                ldrValue4 = diffTime;
            break;
        }
        pinMode(ldrPin, INPUT);
    }
}

int main (void)
{
    cout << "Main function executed\n"; 
    
    //initialize

    //test area

    //wiringPiI2cSetup
    fd = wiringPiI2CSetup (0x68);             //Initialize i2c system. returns
    wiringPiI2CWriteReg8 (fd, 0x6B, 0x00);    //disable sleep mode of GY-6050 sensor module (MPU-6050)
    //cout << "fd value is: " << fd << "\n";
    //cout << "Register read for adress 0x6B returns: " << wiringPiI2CReadReg8(fd, 0x6B) << "\n";

    //Config servo pins (17,18,19,20)
    pinMode(17, OUTPUT); //set servo 1 controll pin
    pinMode(18, OUTPUT); //set servo 2 controll pin
    pinMode(19, OUTPUT); //set servo 3 controll pin
    pinMode(20, OUTPUT); //set servo 4 controll pin
    softPwmCreate(17, 0, 200); //create pwm controll pin for servo 1
    softPwmCreate(18, 0, 200); //create pwm controll pin for servo 2
    softPwmCreate(19, 0, 200); //create pwm controll pin for servo 3
    softPwmCreate(20, 0, 200); //create pwm controll pin for servo 4

    //config ldr pins (0,1,2,3)
    pinMode(0, INPUT);
    pinMode(1, INPUT);
    pinMode(2, INPUT);
    pinMode(3, INPUT); 

    while(1)
    {
        // Test Read LDR values
        /*
        readLdrValues();
        cout << "LDR value 1: " << ldrValue1 << "\n";
        cout << "LDR value 2: " << ldrValue2 << "\n";
        cout << "LDR value 3: " << ldrValue3 << "\n";
        cout << "LDR value 4: " << ldrValue4 << "\n";
        */

        // Test servo's
        testServoCode();

        // Readout and scale temperature measurementsensor values (in degree celsius)
        temp = readMPU6050(0x41);
        temp = (temp/340) + 36.53;

        // Readout and scale accelerometer measurements (full scale range +/- 2g)
        accX = readMPU6050(0x3B);
        accX = accX/16384;
        accY = readMPU6050(0x3D);
        accY = accY/16384;
        accZ = readMPU6050(0x3F);
        accZ = accZ/16384;

        // Readout and scale gyroscope measurements (full scale range +/- 250 degrees/second)
        gyroX = readMPU6050(0x43);
        gyroX = gyroX/131;
        gyroY = readMPU6050(0x45);
        gyroY = gyroY/131;
        gyroZ = readMPU6050(0x47);
        gyroZ = gyroZ/131;

        cout << "Temperature: " << temp << " degree celsius\n";
        
        cout << "Acceleration X: " << accX << "\n";
        cout << "Acceleration Y: " << accY << "\n";
        cout << "Acceleration Z: " << accZ << "\n";

        cout << "Gyro X: " << gyroX << "\n";
        cout << "Gyro Y: " << gyroY << "\n";
        cout << "Gyro Z: " << gyroZ << "\n";
        
        break;
    }
 
    return 0;    
}