
#include <Servo.h>
#include <Stream.h>
int servopin1 = 9;    //Define servo interface digital interface 9
int servopin2 = 6;    //Define servo interface digital interface 6
int servopin3 = 5;    //Define servo interface digital interface 5
int servopin4 = 3;    //Define servo interface digital interface 3
int servopin5 = 11;   //Define servo interface digital interface 11

int moveServoData;
// servo data
int servo1Angle = 90;
int servo2Angle = 90;
int servo3Angle = 90;
int servo4Angle = 90;
int servo5Angle = 90;

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

boolean autoLock = false;
//boolean key_mouse_lock = false;
boolean closeLock = false;

void setup() {
  pinMode(servopin1, OUTPUT); //Set the servo interface as the output interface
  pinMode(servopin2, OUTPUT); //Set the servo interface as the output interface
  pinMode(servopin3, OUTPUT); //Set the servo interface as the output interface
  pinMode(servopin4, OUTPUT); //Set the servo interface as the output interface
  pinMode(servopin5, OUTPUT); //Set the servo interface as the output interface

  Serial.begin(9600);

  servo1.attach(servopin1);
  servo2.attach(servopin2);
  servo3.attach(servopin3);
  servo4.attach(servopin4);
  servo5.attach(servopin5);
  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  servo4.write(90);
  servo5.write(90);
  delay(20);

}
void loop() {
  delay(20);

  do {
    moveServoData = Serial.read();

    // dont waste time
    if (moveServoData == -1) {
      return;
    }

    // process inputs
    if (base(moveServoData)) continue;
    if (shoulder(moveServoData)) continue;
    if (elbow(moveServoData)) continue;
    if (rotate(moveServoData)) continue;
    if (gripper(moveServoData)) continue;



    if (moveServoData == 'n') {
      autoLock = true;
      //    key_mouse_lock = false;
      closeLock = false;
    }

    // send an ack in response
    if (moveServoData == 's') {
      Serial.println('a');
    }

  } while (Serial.available() > 0);
}


bool base(int moveServoData) {
  if (moveServoData == 'o') {
    autoLock = false;
    closeLock = false;
    servo1Angle++;
    if (servo1Angle >= 180) {
      servo1Angle = 180;
    }
    servo1.write(servo1Angle);
    return true;
  }

  if (moveServoData == 'p') {
    autoLock = false;
    closeLock = false;
    servo1Angle--;
    if (servo1Angle <= 0) {
      servo1Angle = 0;
    }
    servo1.write(servo1Angle);
    return true;
  }

  return false;
}


bool shoulder(int moveServoData) {
  if (moveServoData == 'u') {
    autoLock = false;
    closeLock = false;
    servo2Angle++;
    if (servo2Angle >= 180) {
      servo2Angle = 180;
    }
    servo2.write(servo2Angle);
    return true;
  }

  if (moveServoData == 'i') {
    autoLock = false;
    closeLock = false;
    servo2Angle--;
    if (servo2Angle <= 0) {
      servo2Angle = 0;
    }
    servo2.write(servo2Angle);
    return true;
  }
  return false;
}

bool elbow(int moveServoData) {
  if (moveServoData == 't') {
    autoLock = false;
    closeLock = false;
    servo3Angle++;
    if (servo3Angle >= 180) {
      servo3Angle = 180;
    }
    servo3.write(servo3Angle);
    return true;
  }


  if (moveServoData == 'y') {
    autoLock = false;
    closeLock = false;
    servo3Angle--;
    if (servo3Angle <= 0) {
      servo3Angle = 0;
    }
    servo3.write(servo3Angle);
    return true;
  }

  return false;
}

bool rotate(int moveServoData) {
  if (moveServoData == 'e') {
    autoLock = false;
    closeLock = false;
    servo4Angle++;
    if (servo4Angle >= 180) {
      servo4Angle = 180;
    }
    servo4.write(servo4Angle);
    return true;
  }


  if (moveServoData == 'r') {
    autoLock = false;
    closeLock = false;
    servo4Angle--;
    if (servo4Angle <= 0) {
      servo4Angle = 0;
    }
    servo4.write(servo4Angle);
    return  true;
  }

  return false;
}

bool gripper(int moveServoData) {
  if (moveServoData == 'q') {
    autoLock = false;
    closeLock = false;
    servo5Angle++;
    if (servo5Angle >= 90) {
      servo5Angle = 90;
    }
    servo5.write(servo5Angle);
    return true;
  }


  if (moveServoData == 'w') {
    autoLock = false;
    closeLock = false;
    servo5Angle--;
    if (servo5Angle <= 35) {
      servo5Angle = 35;
    }
    servo5.write(servo5Angle);
    return true;
  }

  return false;
}

