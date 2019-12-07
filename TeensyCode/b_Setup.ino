//setup
void setup(){


  //Open Serial Ports
  USER_SERIAL.begin(38400);
  COMMAND_SERIAL.begin(38400);
  MAESTRO_SERIAL.begin(9600); //9600 for Maestro servo controller
  MAESTRO_SERIAL.write(170);

#if defined(GIMBAL_ENABLE)//Gimbal Enable
  GimbalOut.begin(GIMBAL_PPM_PIN);
#endif//end gimbal enable

#if defined(OLED_ENABLE)//OLED Enable
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.display();
#endif//End OLED Enable
  delay(2000);

#if defined(USER_SERIAL_VERVOSE_TRANSMIT)
  USER_SERIAL.println("Started setup");
#endif

  //Set pinmode for LED pins
  pinMode(BUTTON_RGB_PIN,BUTTON_RGB_MODE);
  pinMode(LED_RUNNING,OUTPUT);
  pinMode(LED_ERROR,OUTPUT);
  pinMode(LED_RGB_RED,OUTPUT);
  pinMode(LED_RGB_GRE,OUTPUT);
  pinMode(LED_RGB_BLU,OUTPUT);

  //Verify All servos are in place

}
