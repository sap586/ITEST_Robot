int whiteLeft;
int whiteRight;
int motorLeft1 = 9;
int motorLeft2 = 10;
int motorRight1 = 5;
int motorRight2 = 6;

void setup() {
  Serial.begin(9600);
  pinMode(motorLeft1, OUTPUT);
  pinMode(motorLeft2, OUTPUT);
  pinMode(motorRight1, OUTPUT);
  pinMode(motorRight2, OUTPUT);

  analogWrite(motorLeft1, 90);
  analogWrite(motorLeft2, 0);
  analogWrite(motorRight1, 90);
  analogWrite(motorRight2, 0);
  delay(5000);
}

void loop() {
  whiteLeft = whiteDetect(3);
  whiteRight = whiteDetect(4);
  Serial.print(whiteLeft);
  Serial.print("\t");
  Serial.println(whiteRight);
  
  if (whiteLeft == 1 && whiteRight == 1) {
    analogWrite(motorLeft1, 90);
    analogWrite(motorLeft2, 0);
    analogWrite(motorRight1, 90);
    analogWrite(motorRight2, 0);
  } else if (whiteLeft == 1 && whiteRight == 0) {
    analogWrite(motorLeft1, 150);
    analogWrite(motorLeft2, 0);
    analogWrite(motorRight1, 60);
    analogWrite(motorRight2, 0);
  } else if (whiteLeft == 0 && whiteRight == 1) {
    analogWrite(motorLeft1, 60);
    analogWrite(motorLeft2, 0);
    analogWrite(motorRight1, 150);
    analogWrite(motorRight2, 0);
  } else {
    analogWrite(motorLeft1, 0);
    analogWrite(motorLeft2, 0);
    analogWrite(motorRight1, 0);
    analogWrite(motorRight2, 0);
  }
}


long RCtime(int sensPin){
   long result = 0;
   pinMode(sensPin, OUTPUT);       // make pin OUTPUT
   digitalWrite(sensPin, HIGH);    // make pin HIGH to discharge capacitor - study the schematic
   delay(1);                       // wait a  ms to make sure cap is discharged

   pinMode(sensPin, INPUT);        // turn pin into an input and time till pin goes low
   digitalWrite(sensPin, LOW);     // turn pullups off - or it won't work
   while(digitalRead(sensPin)){    // wait for pin to go low
      result++;
   }

   return result;                   // report results   
}

int whiteDetect(int sensPin) {
  if (RCtime(sensPin) > 50) {
    return 0;
  } else {
    return 1;
  }
}
