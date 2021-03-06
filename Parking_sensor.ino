//Arduino Parking Sensor
//By Mikolaj Henzel, 2020
//Mention me if you want to use it
//GitHub: Henzelix
//Instagram: @mikolajhenzel

#include <LiquidCrystal.h> //Including LCD library

//Buzzer pins
int buzzer = 13;

//Ultrasonic sensor pins
int echoPin = 2;
int trigPin = 3;

//RGB diode pins
int redPin = 4;
int greenPin = 5;
int bluePin = 6;

//Long and Duration variables
long duration;
int distance;

LiquidCrystal lcd(7, 8, 12, 11, 10, 9); //LCD pins

void setup() {
    pinMode(trigPin, OUTPUT); //Setting Trigger pin as an OUTPUT PIN - trigger sends ultrasonic wave that bounces off from an object
    pinMode(echoPin, INPUT); //Setting Echo pin as an INPUT PIN - echo receives bounced wave and saves it as DURATION
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
    pinMode(buzzer, OUTPUT);
    Serial.begin(9600);
}

void loop() {

    lcd.begin(16, 2); //Describning LCD display - 16 columns and 2 rows
    
    //IMPORTANT INFO - there are 2 types of RGB diodes:
    //Most common are with KATHODE on second leg, but there is also type with anode on the second leg.
    //I have ones with anode (rarer)
    //So, that's a scheme:
    //Anode: Turned off - HIGH, Turned on - LOW
    //Kathode: Turned off - LOW, Turned on - HIGH
    //If you don't know which one do you have - you just need to check with switching from 5V to GND or vice versa
    
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, HIGH);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH); //Ultrasonic result
    distance = duration*0.034/2; //Operation to change DURATION value to cm
    if(distance <= 14 && distance > 9){ //If distance is lesser or equal 14 and is greater than 9, then...
        digitalWrite(redPin, HIGH);
        digitalWrite(greenPin, LOW);
        digitalWrite(bluePin, HIGH);
        //Printing result to serial monitor and on LCD
        lcd.setCursor(0, 0);
        Serial.print(distance);
        lcd.print(distance);
        lcd.print("cm");
        tone(buzzer, 1200);
        delay(600);
        noTone(buzzer);
    }
    if(distance <= 9 && distance > 4){ //If distance is lesser or equal 9 and is greater than 4, then...
        digitalWrite(redPin, LOW);
        digitalWrite(greenPin, LOW);
        digitalWrite(bluePin, HIGH);
        Serial.print(distance);
        lcd.print(distance);
        lcd.print("cm");
        tone(buzzer, 1250);
        delay(200);
        noTone(buzzer);
        lcd.setCursor(0, 0);
    }
    if(distance <= 4){ //If distance is lesser or equal 4, then...
        digitalWrite(redPin, LOW);
        digitalWrite(greenPin, HIGH);
        digitalWrite(bluePin, HIGH);
        lcd.setCursor(0, 0);
        Serial.print(distance);
        lcd.print(distance);
        lcd.print("cm");
        tone(buzzer, 1300);
        delay(200);
        noTone(buzzer);
    }
    else{ //else do...
      noTone(buzzer);
    }
    
    //Printing results in cm to serial monitor and on LCD
    lcd.setCursor(0, 0);
    Serial.print(distance);
    lcd.print(distance);
    lcd.print("cm");
    delay(100);
}
