/*
This code reads the Analog Voltage output from the
LV-MaxSonar sensors
If you wish for code with averaging, please see
playground.arduino.cc/Main/MaxSonar
Please note that we do not recommend using averaging with our sensors.
Mode and Median filters are recommended.
*/

const int anPin1 = 0;
long distance1;

void setup() {
  Serial.begin(9600);  // sets the serial port to 9600
}

void read_sensors(){
  /*
  Scale factor is (Vcc/512) per inch. A 5V supply yields ~9.8mV/in
  Arduino analog pin goes from 0 to 1024, so the value has to be divided by 2 to get the actual inches
  */
  distance1 = analogRead(anPin1)/2;
}

void print_all(){
  Serial.print("S1");
  Serial.print(" ");
  Serial.print(distance1);
  Serial.print("inches");
  Serial.println();
}

void loop() {
  read_sensors();
  print_all();
  delay(50); 
}
