#define LED_RED             5
#define LED_GREEN           3
#define LED_BLUE            6

#define LED_BUTTON          2
#define LED_POTENTIOMETER   0

const unsigned long LEDInterval = 50;
const unsigned long LEDButtonInterval = 250;
const unsigned long LEDPotentiometerInterval = 15;
const unsigned long LEDCycleInterval = 0;

unsigned long CurrentTime = 0;
unsigned long LEDTimer = 0;
unsigned long LEDButtonTimer = 0;
unsigned long LEDCycleTimer = 0;

unsigned short int LEDCounter = 0;
unsigned short int LEDValue = 255;
unsigned short int LEDPotentiometerCounter = 0;
unsigned short int LEDPotentiometerValue = 0;
unsigned short int LEDCycleCounter = 0;
unsigned short int LEDCycleRed = 0;
unsigned short int LEDCycleGreen = 0;
unsigned short int LEDCycleBlue = 0;

void setup() {
  Serial.begin(115200);

  delay(300);

  pinMode(LED_GREEN,OUTPUT);
  pinMode(LED_RED,OUTPUT);
  pinMode(LED_BLUE,OUTPUT);
  pinMode(LED_BUTTON,INPUT);
}

void loop() {
  CurrentTime = millis();
  LEDPotentiometerValue += analogRead(LED_POTENTIOMETER);
  LEDPotentiometerCounter++;
  if(LEDPotentiometerCounter >= LEDPotentiometerInterval){
    LEDValue = constrain(
      map(
        constrain(
          static_cast<float>(LEDPotentiometerValue) / static_cast<float>(LEDPotentiometerInterval)
          ,440,890)
        ,440,890,0,255)
      ,0,250);
    LEDPotentiometerValue = 0;
    LEDPotentiometerCounter = 0;
  }
  if( CurrentTime - LEDButtonTimer >= LEDButtonInterval && digitalRead(LED_BUTTON) == HIGH){
    LEDButtonTimer = CurrentTime;
    LEDCounter++;
    LEDCycleCounter = 0;
  }
  if( CurrentTime - LEDTimer >= LEDInterval ){
    LEDTimer = CurrentTime;
    LEDTick();
  }
}

void LEDTick(){
  
  switch(LEDCounter){
    case 0:
      analogWrite(LED_BLUE,0);
      analogWrite(LED_GREEN,0);
      analogWrite(LED_RED,0);
      break;
    case 1:
      analogWrite(LED_GREEN,LEDValue);
      analogWrite(LED_RED,0);
      analogWrite(LED_BLUE,0);
      break;
    case 2:
      analogWrite(LED_RED,LEDValue);
      analogWrite(LED_GREEN,0);
      analogWrite(LED_BLUE,0);
      break;
    case 3:
      analogWrite(LED_BLUE,LEDValue);
      analogWrite(LED_GREEN,0);
      analogWrite(LED_RED,0);
      break;
    case 4:
      analogWrite(LED_BLUE,LEDValue);
      analogWrite(LED_GREEN,LEDValue);
      analogWrite(LED_RED,0);
      break;
    case 5:
      analogWrite(LED_BLUE,LEDValue);
      analogWrite(LED_GREEN,0);
      analogWrite(LED_RED,LEDValue);
      break;
    case 6:
      analogWrite(LED_BLUE,0);
      analogWrite(LED_GREEN,LEDValue);
      analogWrite(LED_RED,LEDValue);
      break;
    case 7:
      analogWrite(LED_BLUE,LEDValue);
      analogWrite(LED_GREEN,LEDValue);
      analogWrite(LED_RED,LEDValue);
      break;
    case 8:
      switch(LEDCycleCounter){
        case 0:
          LEDCycleBlue = 255;
          LEDCycleGreen = 255;
          LEDCycleRed = 0;
          LEDCycleCounter++;
          break;
        case 1:
          LEDCycleGreen--;
          LEDCycleRed++;
          if(LEDCycleRed >= 255){
            LEDCycleCounter++;
          }
          break;
        case 2:
          LEDCycleGreen++;
          LEDCycleRed--;
          if(LEDCycleGreen >= 254){
            LEDCycleCounter++;
          }
          break;
        default:
          LEDCycleCounter = 0;
          break;
      }
      LEDCycleWrite();
      break;
    case 9:
      switch(LEDCycleCounter){
        case 0:
          LEDCycleBlue = 255;
          LEDCycleGreen = 255;
          LEDCycleRed = 0;
          LEDCycleCounter++;
          break;
        case 1:
          LEDCycleGreen--;
          LEDCycleBlue--;
          if(LEDCycleBlue <= 200){
            LEDCycleCounter++;
          }
          break;
        case 2:
          LEDCycleGreen++;
          LEDCycleBlue++;
          if(LEDCycleGreen >= 254){
            LEDCycleCounter++;
          }
          break;
        default:
          LEDCycleCounter = 0;
          break;
      }
      LEDCycleWrite();
      break;
    case 10:
      switch(LEDCycleCounter){
        case 0:
          LEDCycleBlue = 0;
          LEDCycleGreen = 0;
          LEDCycleRed = 255;
          LEDCycleCounter++;
          break;
        case 1:
          LEDCycleGreen++;
          if(LEDCycleGreen >= 255){
            LEDCycleCounter++;
          }
          break;
        case 2:
          LEDCycleRed--;
          if(LEDCycleRed <= 0){
            LEDCycleCounter++;
          }
          break;
        case 3:
          LEDCycleBlue++;
          if(LEDCycleBlue >= 255){
            LEDCycleCounter++;
          }
          break;
        case 4:
          LEDCycleGreen--;
          if(LEDCycleGreen <= 0){
            LEDCycleCounter++;
          }
          break;
        case 5:
          LEDCycleRed++;
          if(LEDCycleRed >= 255){
            LEDCycleCounter++;
          }
          break;
        case 6:
          LEDCycleBlue--;
          if(LEDCycleBlue <= 0){
            LEDCycleCounter++;
          }
          break;
        default:
          LEDCycleCounter = 0;
          break;
      }
      LEDCycleWrite();
      break;
    case 11:
      switch(LEDCycleCounter){
        case 0:
          LEDCycleRed = 255;
          LEDCycleGreen = 0;
          LEDCycleBlue = 0;
          LEDCycleCounter++;
          break;
        case 1:
          LEDCycleRed = 0;
          LEDCycleGreen = 0;
          LEDCycleBlue = 0;
          LEDCycleCounter++;
          break;
        case 2:
          LEDCycleRed = 0;
          LEDCycleGreen = 0;
          LEDCycleBlue = 255;
          LEDCycleCounter++;
          break;
        case 3:
          LEDCycleRed = 0;
          LEDCycleGreen = 0;
          LEDCycleBlue = 0;
          LEDCycleCounter = 0;
          break;
        default:
          LEDCycleCounter = 0;
          break;
      }
      LEDCycleWrite();
      break;
    default:
      LEDCounter = 0;
      break;
  }
}

void LEDCycleWrite(){
  analogWrite(
    LED_RED,
    static_cast<float>(LEDCycleRed)
      * static_cast<float>(static_cast<float>(LEDValue)
                             / static_cast<float>(255))
  );
  analogWrite(
    LED_GREEN,
    static_cast<float>(LEDCycleGreen)
      * static_cast<float>(static_cast<float>(LEDValue)
                             / static_cast<float>(255))
  );
  analogWrite(
    LED_BLUE,
    static_cast<float>(LEDCycleBlue)
      * static_cast<float>(static_cast<float>(LEDValue)
                             / static_cast<float>(255))
  );
}


