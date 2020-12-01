

int control_pin = 11;
int control_pin2 = 2;
float val=0;
float map_val;
const byte interruptPin = 3;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // pinMode(10, OUTPUT);
  Timer1.initialize(1500000);         // initialize timer1, and set a 1/2 second period
//  Timer1.pwm(control_pin, 50);                // setup pwm on pin 9, 50% duty cycle
  Timer1.attachInterrupt(callback);  // attaches callback() as a timer overflow interrupt

  pinMode(control_pin2,OUTPUT);
  int myEraser=7;
  TCCR3B&=~myEraser;
  int prescaler = 5;
  TCCR3B|= prescaler;

   
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, FALLING);
}

void callback(){ 
//  Serial.print("val:");
//  Serial.println(map_val);
  Serial.println("aaaa");
  analogWrite(control_pin2,255);
  delay(000);
  Serial.println("ssss");
  analogWrite(control_pin2,map_val);
  //Timer1.setPwmDuty(control_pin, map_val);
  
}
// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  float sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float pressure = (sensorValue*3) * (5.0 / 1023.0);
  float input_val=analogRead(A1);
  val=input_val * (100.0/1000.0);
  float voltage=val/20.0;
  map_val=val * (2.5);
  float output = analogRead(control_pin);
  analogWrite(control_pin2,map_val);
   // print out the value you read:

//  Serial.print("pressure:");
//  Serial.println(pressure);
//  Serial.print("Duty_cycle_voltage :");
//  Serial.println(voltage);

  //Serial.println(output);
  
}

void blink() {
  Serial.println("aa");
  analogWrite(control_pin2,0);
  delay(50000);
  Serial.println("ss");
  analogWrite(control_pin2,map_val);
}
