/* 
 *  Sketch to check the change of state for State sensors in a PLC driven machine
 *  The LED indicators are taken in the order of importance.
 *  RED -> HIGH IMPORTANCE
 *  YELLOW -> MEDIUM IMPORTANCE
 *  GREEN -> MEDIUM IMPORTANCE
 */


/* Global Variables */
unsigned long outerLoopStartTime = millis();
unsigned long outerLoopDelayTime = 5000;

unsigned long RedLedBlinkTime = millis();
unsigned long RedLedBlinkDelay = 250;

unsigned long YellowLedBlinkTime = millis();
unsigned long YellowLedBlinkDelay = 500;

unsigned long GreenLedBlinkTime = millis();
unsigned long GreenLedBlinkDelay = 500;
/* Timing variables, Allows for parallel imitation of delay() function */


/*LED pins*/
int LEDs[3] = {22,23,24};
int buttonState[3] = {0, 0, 0}; 
int lastButtonState[3]= {0, 0, 0};

/* LED order 
{Red, Yellow, Green}
*/

void setup() {
  //INnstantiate Serial Comms
  Serial.begin(9600);
  Serial.println("Program begins");

  //Instantiate the LED pins value holders
  for(int i = 0; i < 3; i++) {
    pinMode(LEDs[i], INPUT);      //Instantiate the LED pins to be read as inputs
  }

  //Set default values for the LED pin value holders
  for(int i = 0; i < 3; i++) {
    LEDs[i] = 0;      //Instantiate default values for the LEDs
  }
}

void loop() {
  unsigned long innerLoopStartTime = millis();
  //Run the loop every 5 secs
  if (innerLoopStartTime - outerLoopStartTime > outerLoopDelayTime) {
    //Reset the General timer
    outerLoopStartTime += outerLoopDelayTime;
    
    //Read in values for all the pins
    for(int i = 0; i < 3; i++) {
      buttonState[i] = digitalRead(LEDs[i]);      //Instantiate default values for the LEDs
    }
    
    //Check for the changes in the red pin every 0.25s
    if (innerLoopStartTime - RedLedBlinkTime > RedLedBlinkDelay) {
      //Reset the Red LED check timer
      RedLedBlinkTime += RedLedBlinkDelay;
      if(buttonState[0] != lastButtonState[0]){
        //Adjust the last state
        lastButtonState[0] = buttonState[0];
        //Check if the change was positive
        if(buttonState[0] == HIGH) {
          //Send notification Pulse for 
          Serial.println("RED Pin turned on!!");
        }
      }
    }

    //Check for changes in Yellow pins every 0.5s
    if (innerLoopStartTime - YellowLedBlinkTime > YellowLedBlinkDelay) {
      //Reset the Red LED check timer
      YellowLedBlinkTime += YellowLedBlinkDelay;
      if(buttonState[1] != lastButtonState[1]){
        //Adjust the last state
        lastButtonState[1] = buttonState[1];
        //Check if the change was positive
        if(buttonState[1] == HIGH) {
          //Send notification Pulse for 
          Serial.println("Yellow Pin turned on!!");
        }
      }
    }

    //Check for changes in Green pins every 0.5s
    if (innerLoopStartTime - GreenLedBlinkTime > GreenLedBlinkDelay) {
      //Reset the Red LED check timer
      GreenLedBlinkTime += GreenLedBlinkDelay;
      if(buttonState[2] != lastButtonState[2]){
        //Adjust the last state
        lastButtonState[2] = buttonState[2];
        //Check if the change was positive
        if(buttonState[2] == HIGH) {
          //Send notification Pulse for 
          Serial.println("Green Pin turned on!!");
        }
      }
    }


    
  }
}
