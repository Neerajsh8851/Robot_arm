
#include<Servo.h>
#define BASE_PIN 9
#define SHOULDER_PIN 6
#define ELBOW_PIN 5
#define WRIST_PIN 3
#define GRIPPER PIN 11

class RobotArm
{
  private:
    Servo base;
    Servo shoulder;
    Servo elbow;
    Servo wrist;
    Servo grip;

    int baseAngle = 90;
    int shoulderAngle = 90;
    int elbowAngle = 90;
    int wristAngle = 90;
    int gripAngle = 90;

  public:
    void setServoPins(int p1, int p2, int p3, int p4, int p5)
    {
      base.attach(p1);
      shoulder.attach(p2);
      elbow.attach(p3);
      wrist.attach(p4);
      grip.attach(p5);
    }

    void init()
    {
      base.write(90);
      shoulder.write(90);
      elbow.write(90);
      wrist.write(90);
      grip.write(90);
    }


    // control the base at the base of arm
    void rotateLeft(int dr)
    {
      baseAngle += dr;
      if (baseAngle > 180) baseAngle = 180;
      base.write(baseAngle);
    }

    void rotateRight(int dr)
    {
      baseAngle -= dr;
      if (baseAngle < 0) baseAngle = 0;
      base.write(baseAngle);
    }


    // control the servo 2 at the shoulder of arm
    void openShoulder(int dr)
    {
      shoulderAngle -= dr;
      if (shoulderAngle < 0) shoulderAngle = 0;
      shoulder.write(shoulderAngle);
    }

    void closeShoulder(int dr)
    {
      shoulderAngle += dr;
      if (shoulderAngle > 180) shoulderAngle = 180;
      shoulder.write(shoulderAngle);
    }


    // control the elbow at the elbow
    void openElbow(int dr)
    {
      elbowAngle += dr;
      if (elbowAngle > 180) elbowAngle = 180;
      elbow.write(elbowAngle);
    }

    void closeElbow(int dr)
    {
      elbowAngle -= dr;
      if (elbowAngle < 0) elbowAngle = 0;
      elbow.write(elbowAngle);
    }


    // control the wrist at the wrist of arm
    void wristLeft(int dr)
    {
      wristAngle += dr;
      if (wristAngle > 180) wristAngle = 180;
      wrist.write(wristAngle);
    }

    void wristRight(int dr)
    {
      wristAngle -= dr;
      if (wristAngle < 0) wristAngle = 0;
      wrist.write(wristAngle);
    }


    // control the grip at the gripper of arm
    void openGrip(int dr)
    {
      gripAngle -= dr;
      if (gripAngle < 0) gripAngle = 0;
      grip.write(gripAngle);
    }

    void closeGrip(int dr)
    {
      gripAngle += dr;
      if (gripAngle > 90) gripAngle = 90;
      grip.write(gripAngle);
    }

};




#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library.
// On an arduino UNO:       A4(SDA), A5(SCL)
#define OLED_RESET 4
#define SCREEN_ADDRESS 0x3c

class Console {
  private:
    Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
  public:
    void init() {
      // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
      if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;); // Don't proceed, loop forever
      }

      display.display();
      delay(2000);

      display.clearDisplay();
    }
};




//----------------------------------
//    STARTS FROM HERE
//----------------------------------

int moveServoData = -1;
RobotArm arm;

void setup() {
  Serial.begin(230400);
  while (!Serial) {
    ;
  }

  pinMode(BASE_PIN, OUTPUT); //Set the servo interface as the output interface
  pinMode(SHOULDER_PIN, OUTPUT); //Set the servo interface as the output interface
  pinMode(ELBOW_PIN, OUTPUT); //Set the servo interface as the output interface
  pinMode(WRIST_PIN, OUTPUT); //Set the servo interface as the output interface
  pinMode(GRIPPER_PIN, OUTPUT); //Set the servo interface as the output interface

  arm.setServoPins(BASE_PIN, SHOULDER_PIN, ELBOW_PIN, WRIST_PIN, GRIPPER_PIN);
  arm.init();
  Console console;
  console.init();
}



void loop() {
  while (Serial.available()) {
    moveServoData = Serial.read();

    // process inputs
    switch (moveServoData)
    {
      case 'a': arm.rotateLeft(2);      break;
      case 'd': arm.rotateRight(2);     break;
      case 'w': arm.closeElbow(1);      break;
      case 's': arm.openElbow(1);       break;
      case 'q': arm.openGrip(2);        break;
      case 'e': arm.closeGrip(2);       break;
      case 'i': arm.closeShoulder(1);   break;
      case 'k': arm.openShoulder(1);    break;
      case 'j': arm.wristLeft(2);       break;
      case 'l': arm.wristRight(2);      break;
      case '>': Serial.println('<');    break;    // very important for handshake
    }

    delay(15);
  }
}
