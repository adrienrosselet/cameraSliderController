/*
  ReadAnalogVoltage

  Reads an analog input on pin 0, converts it to voltage, and prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/ReadAnalogVoltage
*/

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  
  pinMode(9, OUTPUT);//G4 
  digitalWrite(9, LOW);//caution there is a driving n type mosfet (LOW means blocking)
  //pinMode(8, OUTPUT);//G3
  //digitalWrite(8, LOW);
  //pinMode(7, OUTPUT);//G2
  //digitalWrite(7, LOW);
  pinMode(10, OUTPUT);//G1
  digitalWrite(10, LOW); //caution there is a driving n type mosfet (LOW means blocking)

  pinMode(0, INPUT);
  DDRA |= (1 << PA7); //pin 7 as output
  DDRB |= (1 << PB2); //pin 8 as output
  TCCR0A = 2<<COM0A0 | 2<<COM0B0 | 1<<WGM00; //pwm phase correct
  TCCR0B = 0<<WGM02 | 1<<CS00;
  OCR0B = 0;//pin7 always low, blocking
  OCR0A = 0;//pin 8 always low, blocking
}

// the loop routine runs over and over again forever:

void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(0)/2; //the division maps to 0-512
  if(sensorValue>255){
      OCR0B = 0;//pin7 always low
      digitalWrite(9, LOW);
      digitalWrite(10, HIGH);
      OCR0A = sensorValue-256; //pwm is pin 8
    }
    else{
      OCR0A = 0;//pin 8 always low
      digitalWrite(10, LOW); 
      digitalWrite(9, HIGH);//high
      OCR0B = 255-sensorValue; //pwm on pin 7
    }
}
