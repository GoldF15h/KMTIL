#include <TEA5767Radio.h>
#include <Wire.h>

//Constants:
TEA5767 Radio = TEA5767(); //Pinout SLC and SDA - Arduino uno pins A5 and A4


//Variables:
double old_frequency;
double frequency;
int search_mode = 0;
int search_direction;
unsigned long last_pressed;
unsigned char buf[5];
int stereo;
int signal_level;
double current_freq;
unsigned long current_millis = millis();
int inByte;
int flag=0;

void setup () {
  //Init
 
  Serial.begin(115200);
  Radio.init();
  Radio.setFrequency(90.0); //On power on go to station 95.2
  pinMode(A0,INPUT);
}

void loop () {
  Serial.println(Radio.getFrequency());
  //Serial.println("running");
}
