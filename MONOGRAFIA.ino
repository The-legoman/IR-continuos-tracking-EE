#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

//Declare servo objects
Servo servo1;
Servo servo2;

//Set Analog IR input pin #s
int ir1 = 2;
int ir2 = 3;
int ir3 = 4;
int ir4 = 5;


//Important variables used along the code
int deg = 20;
int pos1 = 90;
int pos2 = 90;
int smooth = 10;
//Consider including an LCD display to tweak the settings and or mute functions such as axis and things



void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

   lcd.begin(16, 2);

  //Attach servos to pins 11 and 10
   servo1.attach(10);
   servo2.attach(11);
   
  // make the IR pin an input:
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);

  //Set servos to center (90) postition
  servo1.write(90);
  servo2.write(90);

 
}



void loop() {
  // read the input pin:
  int ir1state = digitalRead(ir1);  
  int ir2state = digitalRead(ir2);
  int ir3state = digitalRead(ir3);
  int ir4state = digitalRead(ir4);

    //DOWN
    if(ir1state==0 && ir3state==0 && ir4state==1 && ir2state==1){  
        for(int x = 0; x <=deg; x++){
          pos2++;
          servo2.write(pos2);
          delay(smooth);
          
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("1 y 3");
      }

      //UP
    }else if(ir4state==0 && ir2state==0 && ir1state==1 && ir3state==1){
        for(int x = 0; x <=deg; x++){
          pos2--;
          servo2.write(pos2);
          delay(smooth);
        
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("4 y 2");
      }

      //RIGHT
    }else if(ir1state==0 && ir4state==0 && ir3state==1 && ir2state==1){
        for(int x = 0; x <=deg; x++){
          pos1--;
          servo1.write(pos1);
          delay(smooth);
        
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("1 y 4");
      }

      //LEFT
    }else if(ir3state==0 && ir2state==0 && ir1state==1 && ir4state==1){
        for(int x = 0; x <=deg; x++){
          pos1++;
          servo1.write(pos1);
          delay(smooth);
        
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("2 y 3");
      }

      
    }else if(ir1state==0){
        for(int x = 0; x <=deg; x++){
        pos2++;
        servo2.write(pos2);
                
        pos1--;
        servo1.write(pos1);
        delay(smooth);
        
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("1");
         
      }
    }else if(ir2state==0){
        for(int x = 0; x <=deg; x++){
        pos2--;
        servo2.write(pos2);
                
        pos1++;
        servo1.write(pos1);
        delay(smooth);
       
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("2");
      }
    }else if(ir3state==0){
        for(int x = 0; x <=deg; x++){
        pos2++;
        servo2.write(pos2);
                
        pos1++;
        servo1.write(pos1);
        delay(smooth);
        
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("3");
      } 
    }else if(ir4state==0){
        for(int x = 0; x <=deg; x++){
        pos2--;
        servo2.write(pos2);
                
        pos1--;
        servo1.write(pos1);
        delay(smooth);
        
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("4");
      }
    }

  //The general idea is to nest IF statements on each other, remember the default position for the IR reciever is a 1, you can declare this as a simple logical proposal
  //Tweak the delay to achieve smooth sailing                                                                                                                                               

  
  // print out the state of the IR sensors for Multiple plotting in the serial monitor:
  Serial.print(ir1state);
    Serial.print(" ");
  Serial.print(ir2state);
    Serial.print(" ");
  Serial.print(ir3state);
    Serial.print(" ");
  Serial.println(ir4state);
  delay(1);        // delay in between reads for stability
}



