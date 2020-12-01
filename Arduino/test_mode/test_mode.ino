#include "HX711.h"

#define calibration_factor 400.0 //This value is obtained using the SparkFun_HX711_Calibration sketch
#define DOUT  3
#define CLK  4
#define cal_out 0.015
#define kp 100
#define kd 10
HX711 scale;
int control_pin = 2;
int tm = 0;
float error=0;
float error_d=0;
float error_temp=0;
float map_val=0;
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(control_pin,OUTPUT);
  int myEraser=7;
  TCCR3B&=~myEraser;
  int prescaler = 5;
  TCCR3B|= prescaler;
  
  scale.begin(DOUT, CLK);
  //scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0
  
}

// the loop routine runs over and over again forever:
void loop() {
  tm += 1; 
  // read the input on analog pin 0:
  float sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float pressure = (sensorValue*3) * (5.0 / 1023.0);
  
  float input_val=analogRead(A1);
  float val=input_val * (100.0/1023.0);
  float voltage=val/20.0;
  float force_output=100;
  float force_reading=force()-200;
//  error = force_reading-force_output;
//  if(force_output<force_reading){
//    map_val=error*100 ;
//    map_val=min(map_val,255);
//  }
//  else{
//    map_val*=0.912 ;
//    map_val=max(map_val,0);
//    
//  }
  
//  if(force_reading < 650 && force_reading > 500 ){
//    map_val*=0.912 ;
//    map_val=max(map_val,0);
//  }
//  else{

  map_val=val * (2.5);
//  }  
//  if((tm % 10) < 1 ){
//    analogWrite(control_pin,0); 
//  }
//  else{
//    analogWrite(control_pin,map_val); 
//  }
//  if(tm > 10){
//    tm = 0;  
//  }
  analogWrite(control_pin,map_val); 
   // print out the value you read:
//  Serial.print("val:");
//  Serial.println(map_val);
//  Serial.print("pressure:");
//  Serial.println(pressure);
//  Serial.print("Duty_cycle_voltage :");
//  Serial.println(voltage);
  Serial.println(force_reading); //scale.get_units() returns a float
  
}

float force(){
  return scale.read()*cal_out;
}
