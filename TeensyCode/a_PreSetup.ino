//Pre-Setup

//Enable return data for userSerial
#define USER_SERIAL_VERBOSE_TRANSMIT

//Enable OLED use
//#define OLED_ENABLE

//Enable Gimbal use
//#define GIMBAL_ENABLE

//Serial Ports
#define USER_SERIAL Serial
#define DXL_SERIAL Serial1
#define TEENSY_USB_SERIAL Serial
#define COMMAND_SERIAL Serial2
#define MAESTRO_SERIAL Serial4


#if defined(__AVR__)
#error "Sorry, This code requires Teensy 3.x"
#endif

//Libraries

#include "WalkerLeg.h"
#include "DXLServo.h"
#include "MaestroServo.h"

//#include<ax12Serial.h>   //KurtE's bioloid library https://github.com/KurtE/BioloidSerial
//#include<BioloidSerial.h> //KurtE's bioloid library https://github.com/KurtE/BioloidSerial

#include<math.h> //enable use of cosf and sinf to use FPU

#include <i2c_t3.h> //Teensy3.x I2C library to use hardware i2c

#if defined(GIMBAL_ENABLE)//Gimbal Library
#include <PulsePosition.h>
#endif // end gimbal library

#include <SPI.h>
//#include <Wire.h>//Conflicts with i2c_t3

#if defined(OLED_ENABLE) //Libraries for OLED
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h> //https://github.com/adafruit/Adafruit_SSD1306
#endif //End OLED libraries




//Error LED
#define LED_RUNNING 12 //red led by Xbee
#define LED_ERROR 24 //yellow led by Xbee

//UI LEDs
#define LED_RGB_ON HIGH //On state for LEDs
#define LED_RGB_OFF LOW //Off state for LEDS
#define LED_RGB_RED 23 //red LED on indicator button
#define LED_RGB_GRE 22 //green LED on indicator button
#define LED_RGB_BLU 21 //blue LED on indicator button
#define BUTTON_RGB_PIN 20 //the button on the indicator button
#define BUTTON_RGB_MODE INPUT_PULLUP //pinmode for the indicator button pin


#define ServoI2C Wire1

#define NUM_LEGS 6
//idealy remove and handle in leg class
#define NUM_SERVOS_PER_LEG 3

//Move Mode --------------------------------------
#define MOVE_MODE_WALK_PERIODIC 0
#define MOVE_MODE_CRAWL_PERIODIC 1
#define MOVE_MODE_SWERVE 2
#define MOVE_MODE_LEG_PLACE 3
#define MOVE_MODE_WALK_RULE 4 //Not written yet

uint8_t move_mode = MOVE_MODE_WALK_PERIODIC;

//Error States
uint8_t error_state = 0;//Error state is the current error
#define ERROR_DXL 0 //an error with dynamixel communications, indicated by bit 0 of ErrorState
#define ERROR_CMD 1 //more than set amount of time passed between command packets, bit 1 of ErrorState




//Variable used to check servo states
int servo_check_val[NUM_LEGS][NUM_SERVOS_PER_LEG] = {
  0
};


//Variables used for command Data in Inputs
int8_t input_x;
int8_t input_y;
int8_t input_z;
int8_t input_rx;
int8_t input_ry;
int8_t input_rz;
uint8_t input_buttons;
uint8_t input_extend1;
uint8_t input_extend2;



//GaitGenControlVars
int gait_period = 2000; //walk period
int gait_move_x = 0;
int gait_move_y = 0;
int gait_step_height = 0;
float gait_move_z_rot = 0;
int gait_body_x = 0;
int gait_body_y = 0;
int gait_body_z = 0;
float gait_body_pitch = 0;
float gait_body_roll = 0;
float gait_body_yaw = 0;


//Gimbal definitions
#if defined GIMBAL_ENABLE
PulsePositionOutput GimbalOut;
#define GIMBAL_PPM_PIN 5
#endif
int cam_pan = 0;//Unused by GG
int cam_tilt = 0;//Unused by GG
int gimbal_mode = 0;


//OLED definitions
#if defined(OLED_ENABLE)//Open OLED Definitions
#define OLED_RESET 27
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
//My OLED definitions
#define OLED_HEIGHT 32
#define OLED_WIDTH 128
#define OLED_I2C Wire

#endif//End OLED Definitions

//Limits and id for each motor in the design in order  min, max, ID
//ServoLimits
const int kLeg0Limits[NUM_SERVOS_PER_LEG][2] = {//min,max
  {1000, 2000}, //Leg0 Coxa
  {1000, 2000}, //Leg0 Femur
  {1000, 2000}, //Leg0 Tibia
};
const int kLeg1Limits[NUM_SERVOS_PER_LEG][2] = {//min,max
  {1000, 2000}, //Leg1 Coxa
  {1000, 2000}, //Leg1 Femur
  {1000, 2000}, //Leg1 Tibia
};
const int kLeg2Limits[NUM_SERVOS_PER_LEG][2] = {//min,max
  {1000, 2000}, //Leg2 Coxa
  {1000, 2000}, //Leg2 Femur
  {1000, 2000}, //Leg2 Tibia
};
const int kLeg3Limits[NUM_SERVOS_PER_LEG][2] = {//min,max
  {1000, 2000}, //Leg3 Coxa
  {1000, 2000}, //Leg3 Femur
  {1000, 2000}, //Leg3 Tibia
};
const int kLeg4Limits[NUM_SERVOS_PER_LEG][2] = {//min,max
  {1000, 2000}, //Leg4 Coxa
  {1000, 2000}, //Leg4 Femur
  {1000, 2000}, //Leg4 Tibia
};
const int kLeg5Limits[NUM_SERVOS_PER_LEG][2] = {//min,max
  {1000, 2000}, //Leg5 Coxa
  {1000, 2000}, //Leg5 Femur
  {1000, 2000}, //Leg5 Tibia
};
const int kLeg0IDs[NUM_SERVOS_PER_LEG] = {0,1,2};
const int kLeg1IDs[NUM_SERVOS_PER_LEG] = {3,4,5};
const int kLeg2IDs[NUM_SERVOS_PER_LEG] = {6,7,8};
const int kLeg3IDs[NUM_SERVOS_PER_LEG] = {9,10,11};
const int kLeg4IDs[NUM_SERVOS_PER_LEG] = {12,13,14};
const int kLeg5IDs[NUM_SERVOS_PER_LEG] = {15,16,17};


//Initial Positions of legs, used in GaitGen
//Leg 0 (front left)
#define LEG0_INIT_X 65
#define LEG0_INIT_Y 65
#define LEG0_INIT_Z -100
//Leg1 (front right)
#define LEG1_INIT_X 65
#define LEG1_INIT_Y -65
#define LEG1_INIT_Z -100
//Leg2 (back right)
#define LEG2_INIT_X -65
#define LEG2_INIT_Y -65
#define LEG2_INIT_Z -100
//Leg3 (back left
#define LEG3_INIT_X -65
#define LEG3_INIT_Y 65
#define LEG3_INIT_Z -100
//Leg4 (mid right)
#define LEG4_INIT_X 0
#define LEG4_INIT_Y -90
#define LEG4_INIT_Z -100
//Leg5 (mid left)
#define LEG5_INIT_X 0
#define LEG5_INIT_Y 90
#define LEG5_INIT_Z -100

const int kInitialPositions [NUM_LEGS] [3] = {//x,y,z
  {LEG0_INIT_X, LEG0_INIT_Y, LEG0_INIT_Z},//Leg0
  {LEG1_INIT_X, LEG1_INIT_Y, LEG1_INIT_Z},//Leg1
  {LEG2_INIT_X, LEG2_INIT_Y, LEG2_INIT_Z},//Leg2
  {LEG3_INIT_X, LEG3_INIT_Y, LEG3_INIT_Z},//Leg3
  {LEG4_INIT_X, LEG4_INIT_Y, LEG4_INIT_Z},//Leg4
  {LEG5_INIT_X, LEG5_INIT_Y, LEG5_INIT_Z} //Leg5
};


//Dimensions used in leg calculations
#define COXA_LENGTH 10
#define FEMUR_LENGTH 80
#define TIBIA_LENGTH 142
#define TARSUS_LENGTH 25


//Dimensions used to convert to local leg coords
//radius is 110mm
#define COG_X 55 // distance that the legs are in left and right of the COG (center of gravity)
#define COG_Y 95 // distance that the legs are in front and behind the COG
#define COG_CENT 110 //distance the middle legs are from the COG in the x axis
//Period of the status LED
unsigned int led_running_period = 2000;

//Variable used to output from functions
uint8_t current_voltage = 0; //battery voltage in tenths
unsigned long last_voltage_read = 0;
unsigned long time_1;
unsigned long last_cycle_start = 0;
unsigned int last_cycle_time = 0;



DXLServo leg0_servos[] = {DXLServo(1, &DXL_SERIAL), DXLServo(2, &DXL_SERIAL), DXLServo(3, &DXL_SERIAL)};
DXLServo leg1_servos[] = {DXLServo(4, &DXL_SERIAL), DXLServo(5, &DXL_SERIAL), DXLServo(6, &DXL_SERIAL)};
DXLServo leg2_servos[] = {DXLServo(7, &DXL_SERIAL), DXLServo(8, &DXL_SERIAL), DXLServo(9, &DXL_SERIAL)};
DXLServo leg3_servos[] = {DXLServo(10, &DXL_SERIAL), DXLServo(11, &DXL_SERIAL), DXLServo(12, &DXL_SERIAL)};
DXLServo leg4_servos[] = {DXLServo(13, &DXL_SERIAL), DXLServo(14, &DXL_SERIAL), DXLServo(15, &DXL_SERIAL)};
DXLServo leg5_servos[] = {DXLServo(16, &DXL_SERIAL), DXLServo(17, &DXL_SERIAL), DXLServo(18, &DXL_SERIAL)};

MyServo *leg0_servos_ptrs[] = {&leg0_servos[0], &leg0_servos[1], &leg0_servos[2]};
MyServo *leg1_servos_ptrs[] = {&leg1_servos[0], &leg1_servos[1], &leg1_servos[2]};
MyServo *leg2_servos_ptrs[] = {&leg2_servos[0], &leg2_servos[1], &leg2_servos[2]};
MyServo *leg3_servos_ptrs[] = {&leg3_servos[0], &leg3_servos[1], &leg3_servos[2]};
MyServo *leg4_servos_ptrs[] = {&leg4_servos[0], &leg4_servos[1], &leg4_servos[2]};
MyServo *leg5_servos_ptrs[] = {&leg5_servos[0], &leg5_servos[1], &leg5_servos[2]};




WalkerLeg leg0 = WalkerLeg(-55, 95, 0, 0.0, COXA_LENGTH, FEMUR_LENGTH, TIBIA_LENGTH, TARSUS_LENGTH, leg0_servos_ptrs);
WalkerLeg leg1 = WalkerLeg(55, 95, 0, 0, COXA_LENGTH, FEMUR_LENGTH, TIBIA_LENGTH, TARSUS_LENGTH, leg1_servos_ptrs);
WalkerLeg leg2 = WalkerLeg(55, -95, 0, 0, COXA_LENGTH, FEMUR_LENGTH, TIBIA_LENGTH, TARSUS_LENGTH, leg2_servos_ptrs);
WalkerLeg leg3 = WalkerLeg(-55, -95, 0, 0, COXA_LENGTH, FEMUR_LENGTH, TIBIA_LENGTH, TARSUS_LENGTH, leg3_servos_ptrs);
WalkerLeg leg4 = WalkerLeg(110, 0, 0, 0, COXA_LENGTH, FEMUR_LENGTH, TIBIA_LENGTH, TARSUS_LENGTH, leg4_servos_ptrs);
WalkerLeg leg5 = WalkerLeg(110, 0, 0, 0, COXA_LENGTH, FEMUR_LENGTH, TIBIA_LENGTH, TARSUS_LENGTH, leg5_servos_ptrs);
