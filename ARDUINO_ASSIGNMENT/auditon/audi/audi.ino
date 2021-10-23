#include"LedControl.h"
void print(int,byte);
void input_game(int);
int one_key =(digitalRead(2));
int two_key =(digitalRead(3));
int three_key =(digitalRead(4));
int four_key =(digitalRead(5));
int x_joystick =(analogRead(A0));
int y_joystick =(analogRead(A1));
int restart_key =(digitalRead(7));
int CLK = 11;
int CS = 12;
int DIN = 13;
LedControl lc=LedControl(DIN,CLK,CS,4); 

byte one[8]={0x00,0x02,0x02,0xfe,0xfe,0x42,0x02,0x00};
byte two[8]={0x00,0x62,0xf2,0x92,0x8a,0x8e,0x46,0x00};
byte three[8]={0x00,0x6c,0xfe,0x92,0x92,0xc6,0x44,0x00};
byte four[8]={0x00,0x08,0x08,0xfe,0x48,0x38,0x18,0x00};
//byte small_one[8]={0x00,0x00,0x10,0xf0,0x50,0x00,0x00,0x00};
//byte small_two[8]={0x00,0x00,0x68,0x98,0x48,0x00,0x00,0x00};
//byte small_three[8]={0x00,0x00,0x6c,0x92,0x44,0x00,0x00,0x00};
//byte small_four[8]={0x00,0x10,0xfc,0x50,0x30,0x00,0x00,0x00};
//byte small_up[8]={0x00,0x10,0x30,0x7e,0x30,0x10,0x00,0x00};
//byte small_down[8]={0x00,0x08,0x0c,0x7e,0x0c,0x08,0x00,0x00};
//byte small_left[8]={0x00,0x08,0x08,0x08,0x3e,0x1c,0x08,0x00};
//byte small_right[8]={0x00,0x08,0x1c,0x3e,0x08,0x08,0x08,0x00};
byte up[8]={0x00,0x10,0x38,0x7C,0xFE,0x38,0x38,0x38}; //5
byte down[8]={0x38,0x38,0x38,0x38,0xFE,0x7C,0x38,0x10}; //6
byte left[8]={0x00,0x10,0x30,0x7F,0xFF,0x7F,0x30,0x10}; //7
byte right[8]={0x00,0x08,0x0C,0xFE,0xFF,0xFE,0x0C,0x08}; //8

int score = 0;
int health ;
int game[3][2]; //game[?][0]=showed text // game[?][1]=input text


int pause_generate =0;



void start_game(){
  health= 5;
  score = 0;
  pause_generate =0;

  print(3,three);
  delay(1000);
  print(2,two);
  delay(1000);
  print(1,one);
  delay(1000);
  
  
  lc.clearDisplay(3);
  lc.clearDisplay(2);
  lc.clearDisplay(1); 
  delay(500);  
}

void end_game(){
 for(int i=0;i<8;i++){
  for(int j=0;j<8;j++){
    for(int k=1;k<4;k++){
    lc.setLed(k,i,j,1);
    }
 }
}
delay(1000);
lc.clearDisplay(1);
lc.clearDisplay(2);
lc.clearDisplay(3);
delay(500);
}
void print(int address,byte character[]){
  
  for(int i=0;i<8;i++){
    lc.setRow(address,i,character[i]);
    }
}

/*void generate_game(int random,int address,int character){   //address start at 1
  
  if(random==1){print(address,one); game[address-1][0]=1}
  if(random==2){print(address,two); game[address-1][0]=2}
  if(random==3){print(address,three); game[address-1][0]=3}
  if(random==4){print(address,four); game[address-1][0]=4}
  if(random==5){print(address,up); game[address-1][0]=5}
  if(random==6){print(address,down); game[address-1][0]=6}
  if(random==7){print(address,left); game[address-1][0]=7}
  if(random==8){print(address,right); game[address-1][0]=8}
 
  
  
}*/


void input_game(int i){
if(digitalRead(2)==0) {game[i][1]=1; while(digitalRead(2)==0)delay(10);  }
if(two_key==0) {game[i][1]=2; while(two_key==0)delay(10); }
if(three_key==0) {game[i][1]=3; while(three_key==0)delay(10);}
if(four_key==0) {game[i][1]=4;  while(four_key==0)delay(10);}
if((x_joystick >300 && x_joystick<600) && y_joystick>700) {game[i][1]=5; while((x_joystick>300 && x_joystick<600) && y_joystick>700)delay(10);}
if((x_joystick >300 && x_joystick<400) && y_joystick<250)  {game[i][1]=6; while((x_joystick>300 && x_joystick<400) && y_joystick<250)delay(10);}
if(x_joystick<200 && (y_joystick>410 && y_joystick<700)) {game[i][1]=7; while(x_joystick<200 && (y_joystick>410 && y_joystick<700))delay(10);}
if(x_joystick>900 && (y_joystick>300 && y_joystick<590)) {game[i][1]=8; while(x_joystick>900 && (y_joystick>300 && y_joystick<590))delay(10);}
    
}


/*void text_create{
   int random;
  int series[3][2];
  
    
  for(int i=0;i<3;i++){
   random =rand()%8+1;
    series[j][0]= random;
    if(series[i][0]==1)print(i+1,one);
    if(series[i][0]==2)print(i+1,two);
    if(series[i][0]==3)print(i+1,three);
    if(series[i][0]==4)print(i+1,four);
    if(series[i][0]==5)print(i+1,up);
    if(series[i][0]==6)print(i+1,down);
    if(series[i][0]==7)print(i+1,left);
    if(series[i][0]==8)print(i+1,right);
    
  
}*/
void check_game(int i){
  
if(game[i][0]==game[i][1]){score++;}
if(game[i][0]!=game[i][1]){health--;}


} 




void setup() {

  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
 
  for(int i=0;i<4;i++){
   lc.shutdown(i,0);
   lc.setIntensity(i,0.5);
  }
   Serial.begin(9600);
  }
  

void loop() {
  game[3][0]=-1;
  int address=1;
  int random =rand()%8+1;
  if(pause_generate=0 && health!=0){
    if(random==1){print(address,one); game[address-1][0]=1;}
    if(random==2){print(address,two); game[address-1][0]=2;}
    if(random==3){print(address,three); game[address-1][0]=3;}
    if(random==4){print(address,four); game[address-1][0]=4;}
    if(random==5){print(address,up); game[address-1][0]=5;}
    if(random==6){print(address,down); game[address-1][0]=6;}
    if(random==7){print(address,left); game[address-1][0]=7;}
    if(random==8){print(address,right); game[address-1][0]=8;}
  }
  input_game(address-1);
  if(pause_generate=1)
  {
    for(int i=0;i<3;i++){
     check_game(i); 
    }
  }
  if(health<=0){
    end_game();
    start_game();
  }
address++;
if(game[3][0]!=-1)pause_generate =1;
if(address==3){
address=1;

}
}