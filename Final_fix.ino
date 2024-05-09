#include <EEPROM.h>

int red=18; //RGB LED RED
int blue=19; //RGB LED blue
int green=21; //RGB LED green


int led1=25;
int led2=26;
int led3=27;
int pwm=255;
int coil=23;
int count1=0;
int button1=13;
int button2=12;
int button3=14;
int sound_pin=15;
int mode=0;

const long blinkInterval = 1000;

const long totalBlinkDuration = 600000;

unsigned long previousMillis = 0;
unsigned long blinkStartTime = 0;
bool blinkEnabled = false;


void setup() {
  EEPROM.begin(500);

  pinMode(sound_pin, INPUT);
  Serial.begin(9600);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);

  pinMode(red,OUTPUT);
  pinMode(blue,OUTPUT);
  pinMode(green,OUTPUT);

  pinMode(coil,OUTPUT);
  mode=EEPROM.read(1);
  Serial.println("Srating......");
  Serial.println(mode);
  //mode=5;
}

void loop() {
  Serial.println(mode);

  

  if(touchRead(button1) < 10) { //Push button pressed
  delay(50);
  Serial.printf("Button 1 Pressed!\n");
  mode=1;
  EEPROM.put(1, 1);
  EEPROM.commit();
  Serial.println(EEPROM.read(1));
  }
  if(touchRead(button2) < 10) { //Push button pressed
  delay(50);
  Serial.printf("Button 2 Pressed!\n");
  mode=4;
  EEPROM.put(1, 4);
  EEPROM.commit();
  Serial.println(EEPROM.read(1));
  }
  
  if(touchRead(button3) < 10) { //Push button pressed
  delay(50);
  Serial.printf("Button 3 Pressed!\n");
  mode=5;
  EEPROM.put(1, 5);
  EEPROM.commit();
  Serial.println(EEPROM.read(1));
  }
  
  if(mode==1){
    
    analogWrite(coil, pwm*0.4);
    digitalWrite(green, HIGH);
    digitalWrite(blue, LOW);
    digitalWrite(red, LOW);
    led_blink();
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    count1=count1+1;
    if(count1>=5){
      count1=0;
      mode=2;
    }
  } 
  else if(mode==2){
      analogWrite(coil,pwm*0.6);
      digitalWrite(green, LOW);
      digitalWrite(blue, HIGH);
      digitalWrite(red, LOW);
      led_blink();
      count1=count1+1;

      if(count1>=5){
        if (mode==2 && !blinkEnabled) {\
            blinkEnabled = true;
            blinkStartTime = millis();
            previousMillis = blinkStartTime;
        }
        count1=0;
        mode=3;
      }
  }
  else if(mode==3){
      analogWrite(coil,pwm*0.8);
      digitalWrite(green, LOW);
      digitalWrite(blue, LOW);
      digitalWrite(red, HIGH);
    if (blinkEnabled) {
      unsigned long currentMillis = millis();
      Serial.println(sound_pin);
      if(digitalRead(sound_pin)==0){
          mode=0;
          digitalWrite(led1, LOW);
          digitalWrite(led2, LOW);
          digitalWrite(led3, LOW);
          digitalWrite(green, LOW);
          digitalWrite(blue, LOW);
          digitalWrite(red, LOW);
          analogWrite(coil,0);
          blinkEnabled = false;
        }

      if (currentMillis - previousMillis >= blinkInterval) {
        previousMillis = currentMillis;

        digitalWrite(led1, !digitalRead(led1));
      }

      if (currentMillis - blinkStartTime >= totalBlinkDuration) {

        blinkEnabled = false;
        digitalWrite(led1, LOW);
        
        
      }
    }
         
  }

  else if(mode==4){
     analogWrite(coil, pwm*0.5);
     digitalWrite(green, LOW);
      digitalWrite(blue, HIGH);
      digitalWrite(red, LOW);
     digitalWrite(led2, HIGH);
    digitalWrite(led1, LOW);
    digitalWrite(led3, LOW);

     if(digitalRead(sound_pin)==0){
        mode=0;
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
        digitalWrite(led3, LOW);
        digitalWrite(green, LOW);
        digitalWrite(blue, LOW);
        digitalWrite(red, LOW);
          
        analogWrite(coil,0);

      } 
    }

  else if(mode==5){
     analogWrite(coil, pwm*0.75);
     digitalWrite(led3, HIGH);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);

    digitalWrite(green, LOW);
      digitalWrite(blue, LOW);
      digitalWrite(red, HIGH);

     if(digitalRead(sound_pin)==0){
        mode=0;
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
        digitalWrite(led3, LOW);
        digitalWrite(green, LOW);
        digitalWrite(blue, LOW);
        digitalWrite(red, LOW);
        analogWrite(coil,0);
      } 
    }
  
  else if (mode==10){
        digitalWrite(led1, LOW);
        analogWrite(coil,0);
      }


}

void led_blink(){
    digitalWrite(led1,HIGH );
    delay(1000);
    digitalWrite(led1, LOW);
    delay(1000);
}