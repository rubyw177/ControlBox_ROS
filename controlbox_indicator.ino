// ROS Lib
#include <ros.h>
#include <pesan_pkg/Controlbox.h>
// Keypad Lib
#include <Key.h>
#include <Keypad.h>

// User Define
#define led_green 2
#define led_yellow 3
#define led_blue 4
#define saklar 13
bool oldState;
bool newState;
char tempKey = '-';

ros::NodeHandle nh;

pesan_pkg::Controlbox control_msg;
ros::Publisher pub_key("controlbox_cmd", &control_msg);

// Keypad's Columns and Rows
const byte rows = 4;
const byte cols = 4;

char keys[rows][cols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// Keypad's Rows and Cols Pins
byte rowPins[rows] = {12, 11, 10, 9};
byte colPins[cols] = {8, 7, 6, 5};

// Keypad Object
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

void setup()
{
  Serial.begin(57600);
  nh.initNode();
  nh.advertise(pub_key);
  pinMode(led_green, OUTPUT);
  pinMode(led_yellow, OUTPUT);
  pinMode(led_blue, OUTPUT);
  pinMode(saklar, INPUT);
}

void loop()
{
  // Get which key is pressed
  char key_in = keypad.getKey();
  if (key_in != NO_KEY) {
    control_msg.key = key_in;
    tempKey = key_in;
  }
  else {control_msg.key = tempKey;}

  // Read switch digital state (high or low)
  if (digitalRead(saklar) == HIGH) {control_msg.state = true;}
  else if (digitalRead(saklar) == LOW) {control_msg.state = false;}
  
  newState = control_msg.state;

//  TODO: tambahin kode nyala lampu led sesuai kondisi key
//
//  switch (key_in) {
//    case 0:
//      digitalWrite(led_blue, );
//      digitalWrite(led_yellow, );
//      digitalWrite(led_green, );
//      break;
//    case 0:
//      digitalWrite(led_blue, );
//      digitalWrite(led_yellow, );
//      digitalWrite(led_green, );
//      break;
//    case 0:
//      digitalWrite(led_blue, );
//      digitalWrite(led_yellow, );
//      digitalWrite(led_green, );
//      break;
//    case 0:
//      digitalWrite(led_blue, );
//      digitalWrite(led_yellow, );
//      digitalWrite(led_green, );
//      break;
//    case 0:
//      digitalWrite(led_blue, );
//      digitalWrite(led_yellow, );
//      digitalWrite(led_green, );
//      break;
//    case 0:
//      digitalWrite(led_blue, );
//      digitalWrite(led_yellow, );
//      digitalWrite(led_green, );
//      break;
//    case 0:
//      digitalWrite(led_blue, );
//      digitalWrite(led_yellow, );
//      digitalWrite(led_green, );
//      break;
//    case 0:
//      digitalWrite(led_blue, );
//      digitalWrite(led_yellow, );
//      digitalWrite(led_green, );
//      break;
//  }
//
//  Bisa 8 kombinasi karena ada 3 led
  
  // check for any new changes in the data
  if (key_in != NO_KEY || newState != oldState) {pub_key.publish(&control_msg);}
  
  oldState = newState;
  
  nh.spinOnce();
}
