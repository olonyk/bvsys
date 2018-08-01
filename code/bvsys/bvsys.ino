#include <Wire.h>
#include <LCD16x2.h>

#define BTN_1   0x01
#define BTN_2   0x02
#define BTN_3   0x04
#define BTN_4   0x08

LCD16x2 lcd;

int buttons;
int mode;
int point;

int pinMoist_1 = A0;
int pinMoist_2 = A1;

/*
 * mode:
 *    0:  View current status.
 *    1:  Set moisture threshold.
 *    2:  Set water time.
 *    3:  Set clock
 * 
 */
 
void setup() {
  Wire.begin();
  lcd.lcdClear();

  mode = 0;
  point = 0;
}

void loop() {
  buttons = lcd.readButtons();
  if(buttons & BTN_1){
    mode++;
    point = 0;
    if(mode > 3){
      mode = 0;
    }
  }
  if(mode == 0){
    modeViewStatus();
  }
  if(mode == 1){
    modeSetMoisture();
  }
  if(mode == 2){
    modeSetClock();
  }
  water();
    
  delay(100);
}

void modeViewStatus(){
  lcd.lcdClear();

  int moist = readSensor(pinMoist_1);
  char str[10] ="";
  sprintf(str, "Moist sens 1: %02d  ", moist );
  lcd.lcdGoToXY(1,1);
  lcd.lcdWrite(str);

  moist = readSensor(pinMoist_2);
  sprintf(str, "Moist sens 1: %02d  ", moist );
  lcd.lcdGoToXY(1,2);
  lcd.lcdWrite(str);
}

void modeSetMoisture(){
  lcd.lcdClear();
  lcd.lcdGoToXY(1,1);
  lcd.lcdWrite("Set Moisture");
}

void modeSetClock(){
  lcd.lcdClear();
  lcd.lcdGoToXY(1,1);
  lcd.lcdWrite("Set Clock");
}

void water(){
  
}

int readSensor(int pin){
  int output_value = analogRead(pin);
  return map(output_value, 0, 1023, 0, 100);
}

