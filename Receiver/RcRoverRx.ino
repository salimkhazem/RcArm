/*
 * Author: Salim KHAZEM 
 * Purpose: RC Robotic Arm Controlled by using NRF24L01 
 * PART : Receiver Code 
 * Language:  C and Cpp 
 * Date : 18 September 2020 
 */


#include <SPI.h> 
#include <nRF24L01.h> 
#include <RF24.h> 
#include <Servo.h> 
//#include <Motor.h> 

/*
 * You can use the Motor Library for control DC Motor
 * For our cases here, we want to control Robotic Arm by using Servomotors  
 */

Servo Alpha; // Servo 1
Servo Beta;  // Servo 2 
Servo Sigma; // Servo 3 

int data[3];  // Variables which contains the receiver Position data f
char x[2]; 

RF24 radio (7,8);  // Initialize the Radio frequency module 

const byte address[6]="00001"; 
//const byte addr[6]="00002"; 

void setup() {
  Alpha.attach(3); // Servo 1 
  Beta.attach(5);  // Servo 2 
  Sigma.attach(6) ; // Servo 3 
  pinMode(LED_BUILTIN,OUTPUT);  

  
 

Serial.begin(9600); 
radio.begin();  // Start the NRF24L01 Communication and initialize parameters 
radio.openReadingPipe(0,address);  // Switch into the right address (00001) 
radio.setPALevel(RF24_PA_MAX);  

}

void loop() {
delay(5); 
radio.startListening();  // Listening for radiofrequency 

if(radio.available()) {
  digitalWrite(LED_BUILTIN,HIGH);  // Seto On  the led when we receive data  
  
  while (radio.available()) 
  { 
  radio.read(&data,sizeof(data)); // Reading data by using the read fucntion, here we use Pointers because the type of data in our case we use Integers so we have to specify address and pointers of data 
  Serial.print(data[0]); Serial.print("\t"); Serial.print(data[1]); Serial.print("\t"); Serial.println(data[2]); 
/*
 * For using this code, you muse calibrate your Servomotors in the Transmitter code 
 * 
 * 
 */
   Alpha.write(data[0]); // data[0] contains position for the Alpha Servo 
   Beta.write(data[1]); // data[1] contains position for the Alpha Servo 
   Sigma.write(data[2]); // data[2] contains position for the Alpha Servo 

  
 }
}
digitalWrite(LED_BUILTIN,LOW); 
}
