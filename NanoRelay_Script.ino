/**
 * NanoRelay
 * Author: Pau Balcells Sanchez
 * Pitt Vibrant Media Lab: 2023
 */
 
 //User specific Parameters//
 
  //In 1 delay: duration of time in ms that In 1 pin needs to be pulled low before it leads to a trigger event
  const int duration1 = 100;
  //In 1 delay: period of time after a trigger event that no further input from In 1 will be accepted, in ms
  const int delay1 = 10;
  
  //In 2 duration and delay same as In1 but for the In 2 pin
  const int duration2 = 100;
  const int delay2 = 10;
  // In 2 multpiple: Number of discrete trigger events in In 2 pin before output is triggered
  const int mult2 = 1;
  
  // Analog in high threshold: value on Analog In, in volts, that triggers output when reached or exceeded.  If blank, does not respond no matter how high the value
  const int analogHigh = 4;
  //Analog in low threshold: value on Analog In, in volts; triggers output if value is lower than this
  const int analogLow = 6;
  
  //Upon trigger event, delay before relay is activated
  const int relayDelay = 0;
  //Time, in ms, that relay is activated
  const int relayDuration = 100;
  //Number of times the relay is activated after a single trigger event
  const int relayMultiple = 1;
  //Delay between multiple activations (if “Relay multiple” is >1)
  const int relayInterval = 0;
  
  //Upon trigger event, delay before output is activated
  const int outDelay = 0;
  //Time, in ms, that output is activated
  const int outDuration = 100;
  //Number of times the output is activated after a single trigger event
  const int outMultiple = 1;
  //Delay between multiple activations (if “Output multiple” is >1)
  const int outInterval = 0;
  //duration after the end of all outputs before any input is accepted
  const int outPause = 0;
  


//Set pins//
const int in1 = 5;
const int in2 = 6;
const int relayActivation = 7;
const int vin = 30;
const int out = 20;
const int analogIn = 22;
const int fiveV = 27;


// Associate physical button states with their output//
#define UP          HIGH
#define DOWN        LOW

//Programming//
volatile int in1_state = UP;
volatile int in2_state = DOWN;
volatile unsigned long in1_last_input = 0;
volatile unsigned long in1_hold_duration = 0;
volatile unsigned long in2_last_input = 0;
volatile unsigned long in2_hold_duration = 0;

// TRIGGER //
const long trigger_active_period = 35; // Roughly 1/30 s
volatile int trigger_button_state = UP;
volatile unsigned long trigger_button_last_input = 0;

// RELAY //
volatile int relay_state = LOW;
volatile int gate_output = LOW;
volatile int trigger_output = LOW;

//ANALOG//
volatile int analog_state = LOW;


//GENERAL TIMING//
const long contactBounce = 50;


void setup(){
  Serial.begin(9600);

  
  pinMode(in1, INPUT);
  pinMode(in2, INPUT);
  pinMode(relayActivation, OUTPUT);
  pinMode(out, OUTPUT);
  pinMode(analogIn, INPUT);
  
  attachInterrupt(digitalPinToInterrupt(in1), isr_in1, CHANGE);
}

void loop(){
  
  if(analogRead(analogIn) < analogLow && analogRead(analogIn) >= analogHigh && analogHigh != 0 ){
    relayRun(); 
    relay_state = LOW;
  }
  
}

void isr_in1(){
  
  if(millis() - in1_last_input >= duration1){  
    if (millis() - in1_last_input >= contactBounce){
      in1_last_input = millis();
    }
    
    if(in1_state == DOWN){
      in1_state = UP;
    } else {
      in1_state = DOWN;
      relay_state = UP;
      relayRun();
    }
  }  
  
    delay(delay1);
}


void relayRun(){
  for (int i = 0; i < relayMultiple; i++){
    delay(relayDelay);
    relay_state = UP;
    digitalWrite(relayActivation, relay_state);
    long relayStart = millis();
    while(millis() - relayStart < relayDuration){
      delay(outDelay);
      for (int j = 0; j < outMultiple; j++){
        long outStart = millis();
        while(millis() - outStart < outDuration){
          digitalWrite(out, HIGH);
        }
        delay(outInterval);
      }
      
    }
    delay(relayInterval);
  }
  delay(outPause);
}
