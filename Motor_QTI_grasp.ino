#define motorLeft1 9
#define motorLeft2 10
#define motorRight1 5
#define motorRight2 6
int count = 0;

long RCtime(int sensPin) {
  long result = 0;
  pinMode(sensPin, OUTPUT);
  digitalWrite(sensPin, HIGH);
  delay(1);
  pinMode(sensPin, INPUT);
  digitalWrite(sensPin, LOW);
  while(digitalRead(sensPin)) {
    result++;
  }
  return result;
}

bool blackDetected(int sensPin) {
  if (RCtime(sensPin) > 500) {
    return true;
  } else {
    return false;
  }
}

void motorForward(int left, int right) {
  analogWrite(motorLeft1, left);
  analogWrite(motorLeft2, 0);
  analogWrite(motorRight1, right);
  analogWrite(motorRight2, 0);
}

void motorRotate(int left, int right, int sec) {
  analogWrite(motorLeft1, 0);
  analogWrite(motorLeft2, left);
  analogWrite(motorRight1, right);
  analogWrite(motorRight2, 0);
  delay(sec);
//  if (blackDetected(3) | blackDetected(4)) {
    motorStop();
//  }
  align();
//  delay(sec);
//  motorStop();
}

void motorStop() {
  analogWrite(motorLeft1, 0);
  analogWrite(motorLeft2, 0);
  analogWrite(motorRight1, 0);
  analogWrite(motorRight2, 0);
  delay(100);
}

void align() {
  if (blackDetected(4) == true && blackDetected(3) == false) {
    do {
      motorForward(120, 30);
      digitalWrite(12, LOW);
      delay(200);
      motorStop();
      return;
    } while(blackDetected(3) == false && blackDetected(4) == false);
  }
  if (blackDetected(4) == false && blackDetected(3) == true) {
    do {
      motorForward(30, 120);
      digitalWrite(12, LOW);
      delay(200);
      motorStop();
      return;
    } while(blackDetected(3) == false && blackDetected(4) == false);
  }
}

void pickUp() {
  analogWrite(A2, 0);
  analogWrite(A3, 150);
  delay(600);
  analogWrite(A2, 0);
  analogWrite(A3, 0);
  delay(1000);
  grasp();
  analogWrite(A2, 150);
  analogWrite(A3, 0);
  delay(900);
  analogWrite(A2, 0);
  analogWrite(A3, 0);
  delay(1000);
  count = 1;
}

void grasp() {
  analogWrite(A0, 150);
  analogWrite(A1, 0);
  delay(300);
  analogWrite(A0, 0);
  analogWrite(A1, 0);
}

void drop() {
  analogWrite(A2, 0);
  analogWrite(A3, 150);
  delay(600);
  analogWrite(A2, 0);
  analogWrite(A3, 0);
  delay(1000);
  openArm();
  analogWrite(A2, 150);
  analogWrite(A3, 0);
  delay(900);
  analogWrite(A2, 0);
  analogWrite(A3, 0);
  delay(1000);
  count = 0;
}

void openArm() {
  analogWrite(A0, 0);
  analogWrite(A1, 150);
  delay(300);
  analogWrite(A0, 0);
  analogWrite(A1, 0);
}

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(2, OUTPUT);
}

void loop() {
  Serial.print(blackDetected(4));         //4 : leftQTI
  Serial.print("\t");
  Serial.println(blackDetected(3));       //3 : rightQTI
  delay(10);
  
  if (blackDetected(3) == false & blackDetected(4) == false) {
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);
    digitalWrite(2, LOW);
    motorForward(70, 70);
  } else if (blackDetected(3) == true & blackDetected(4) == true) {
    motorStop();
    if (count == 0) {
      pickUp();
      motorRotate(150, 180, 1500);
      return;
    }
    if (count == 1) {
      drop();
      motorRotate(150, 180, 1500);
      return;
    }
  } else {
    align();
  }
}

