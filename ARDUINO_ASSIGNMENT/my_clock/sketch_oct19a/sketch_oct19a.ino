#include "LedControl.h"
LedControl lc = LedControl(13,11,12,4);

#define button_1 digitalRead(2)
#define button_2 digitalRead(3)
#define button_3 digitalRead(4)
#define home_button digitalRead(5)
#define pressed LOW


const int c = 261;
const int d = 294;
const int e = 329;
const int f = 349;
const int g = 391;
const int gS = 415;
const int a = 440;
const int aS = 455;
const int b = 466;
const int cH = 523;
const int cSH = 554;
const int dH = 587;
const int dSH = 622;
const int eH = 659;
const int fH = 698;
const int fSH = 740;
const int gH = 784;
const int gSH = 830;
const int aH = 880;
 
const int buzzerPin = 6;
const int ledPin1 = 8;
const int ledPin2 = 9;

int counter = 0;


int timer1_counter;
int UpdateCheck = millis();
long int t = 0;
int hour   = 12,
    minute = 34,
    second = 56
    ;
long int  TotalSecond = 0;
long int  CountDownSecond = 0;
int intensity = 15;
bool light = 1;
bool auto_intens = 0;
bool times_up = 0;
bool inverse = 0;

void setup() {
  noInterrupts(); 
  // put your setup code here, to run once:

  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);

  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  pinMode(5,INPUT_PULLUP);

  pinMode(A1,INPUT);

  lc.shutdown(0,false);// turn off power saving, enables display
  lc.shutdown(1,false);
  lc.shutdown(2,false);
  lc.shutdown(3,false);
  lc.setIntensity(0,15);// sets brightness (0~15 possible values)
  lc.setIntensity(1,15);
  lc.setIntensity(2,15);
  lc.setIntensity(3,15);
  lc.clearDisplay(0);// clear screen

  Serial.begin(9600);

  TCNT1 = timer1_counter;   // preload timer 
  TCCR1B |= (1 << CS12);    // 256 prescaler 
  TIMSK1 |= (1 << TOIE1);   // enable timer overfpressed interrupt

  TCCR1A  = 0;
  TCCR1B  = 0;
  TCNT1   = 3036;           
  TCCR1B |= (1 << CS12);    
  TIMSK1 |= (1 << TOIE1); 

  interrupts();

}

int number5[21][5] = {
  {0x00, 0x7e, 0x42, 0x7e, 0x00},
  {0x00, 0x44, 0x7e, 0x40, 0x00},
  {0x00, 0x64, 0x52, 0x4c, 0x00},
  {0x00, 0x4a, 0x4a, 0x7e, 0x00},
  {0x00, 0x1e, 0x10, 0x7e, 0x00},
  {0x00, 0x4e, 0x4a, 0x7a, 0x00},
  {0x00, 0x7e, 0x4a, 0x7a, 0x00},
  {0x00, 0x06, 0x02, 0x7e, 0x00},
  {0x00, 0x7e, 0x4a, 0x7e, 0x00},
  {0x00, 0x4e, 0x4a, 0x7e, 0x00},//9 เลข 9
  {0xff, 0x81, 0xbd, 0x81, 0xff},
  {0xff, 0xbb, 0x81, 0xbf, 0xff},
  {0xff, 0x9b, 0xad, 0xb3, 0xff},
  {0xff, 0xb5, 0xb5, 0x81, 0xff},
  {0xff, 0xe1, 0xef, 0x81, 0xff},
  {0xff, 0xb1, 0xb5, 0x85, 0xff},
  {0xff, 0x81, 0xb5, 0x85, 0xff},
  {0xff, 0xf9, 0xfd, 0x81, 0xff},
  {0xff, 0x81, 0xb5, 0x81, 0xff},
  {0xff, 0xb1, 0xb5, 0x81, 0xff},
  {0x00, 0x00, 0x00, 0x00, 0x00}
  };


void DefDigTimeShow (int h,int m,int s){

  if(h>=0){
  ShowNum((h/10)+10*inverse,0,0,0);
  ShowNum((h%10)+10*inverse,0,5,0);
  ShowNum((h%10)+10*inverse,1,-3,0);
  }
  else
  {
  ShowNum(20,0,0,0);
  ShowNum(20,0,5,0);
  ShowNum(20,1,-3,0);
  }

  if(!inverse){
    lc.setLed(1,0,5,0);
    lc.setLed(1,1,5,0);
    lc.setLed(1,2,5,1);
    lc.setLed(1,3,5,0);
    lc.setLed(1,4,5,0);
    lc.setLed(1,5,5,1);
    lc.setLed(1,6,5,0);
    lc.setLed(1,7,5,0);
  }else{
    lc.setLed(1,0,5,1);
    lc.setLed(1,1,5,1);
    lc.setLed(1,2,5,0);
    lc.setLed(1,3,5,1);
    lc.setLed(1,4,5,1);
    lc.setLed(1,5,5,0);
    lc.setLed(1,6,5,1);
    lc.setLed(1,7,5,1);
  }
  
  

  if(m>=0){
  ShowNum((m/10)+10*inverse,1,3,0);
  ShowNum((m%10)+10*inverse,2,0,0);
  }
  else{
  ShowNum(20,1,3,0);
  ShowNum(20,2,0,0);
  }
  if(!inverse){
    lc.setLed(2,0,2,0);
    lc.setLed(2,1,2,0);
    lc.setLed(2,2,2,1);
    lc.setLed(2,3,2,0);
    lc.setLed(2,4,2,0);
    lc.setLed(2,5,2,1);
    lc.setLed(2,6,2,0);
    lc.setLed(2,7,2,0);
  }else{
    lc.setLed(2,0,2,1);
    lc.setLed(2,1,2,1);
    lc.setLed(2,2,2,0);
    lc.setLed(2,3,2,1);
    lc.setLed(2,4,2,1);
    lc.setLed(2,5,2,0);
    lc.setLed(2,6,2,1);
    lc.setLed(2,7,2,1);
  }
  if(s>=0){
  ShowNum((s/10)+10*inverse,2,6,0);
  ShowNum((s/10)+10*inverse,3,-2,0);
  ShowNum((s%10)+10*inverse,3,3,0);
  }else{
  ShowNum(20,2,6,0);
  ShowNum(20,3,-2,0);
  ShowNum(20,3,3,0);
  }
  
}

void ShowNum(int num , int cube , int x , int y){

  for(int i=0;i<5;i++)
    lc.setColumn(cube,abs(7-x)-i,number5[num][i]);
  
}

ISR(TIMER1_OVF_vect) {

   TCNT1 = 3036; 
   TimeUpdate ();
   TotalSecond++;
   CountDownSecond--;
   if(auto_intens)
      auto_intensity_adjust();
    
   //Serial.println("TIME++ ");
   //Serial.print(hour);Serial.print(" ");Serial.print(minute);Serial.print(" ");Serial.print(second);Serial.print("\n");
    
}

void TimeUpdate (){

    TotalSecond%=86400;
    second += 1;
    minute += second / 60;
    second %= 60;
    hour   += minute / 60;
    minute %= 60;
    hour   %= 24; 
  
}

void TimeSet (){
  
  int newH = hour,newM = minute,newS = second;
  int state = 0;
  /*Serial.print(newH);Serial.print(" ");Serial.print(newM);Serial.print(" ");Serial.print(newS);Serial.print(" ");
  Serial.println("TimeSet!!\n");*/
  while(home_button!=pressed){
    Serial.print("TIME SET!!\n");
    DefDigTimeShow(newH,newM,newS);
    delay(100);
    switch(state){
      
      case 0: DefDigTimeShow(newH,newM,-1);
              if(button_1==pressed)newS++;
              if(button_2==pressed)newS--;
              if(newS > 59)
                newS = 0;
              if(newS < 0)
                newS = 59;
              break;
      case 1: DefDigTimeShow(newH,-1,newS);
              if(button_1==pressed)newM++;
              if(button_2==pressed)newM--;
              if(newM > 59)
                newM = 0;
              if(newM < 0)
                newM = 59;
              break;
      case 2: DefDigTimeShow(-1,newM,newS);
              if(button_1==pressed)newH++;
              if(button_2==pressed)newH--;
              if(newH > 23)
                newH = 0;
              if(newH < 0)
                newH = 23;
              break;

    }
    if(button_3==pressed)
      state++;
    if(state>2)
      state = 0;
    while(button_3==pressed)
      delay(1);
    
  }
  hour   = newH;
  minute = newM;
  second = newS;
  /*Serial.print(hour);Serial.print(" ");Serial.print(minute);Serial.print(" ");Serial.print(second);Serial.print(" ");
  Serial.println("END!!\n");*/

}

void CountDownAndTimer (){
  
  while(home_button!=pressed){
    
    TotalSecond = 0;
    DefDigTimeShow(-1,-1,-1);
    delay(100);
     while(button_3!=pressed && home_button!=pressed){
      Serial.print("Timer!!\n");
      DefDigTimeShow(TotalSecond/3600%24,TotalSecond/60%60,TotalSecond%60 );
    }
    while(button_3==pressed)
      delay(1);
      
    long int TmpCountDownSecond = 0;
    int state = 0;
    while(button_3!=pressed && home_button!=pressed){
      
      while(button_1!=pressed || button_2!=pressed){
        if(home_button==pressed)
          break;
        Serial.print("Setting CountDown!!\n");
        if(button_3==pressed)
          state++;
        state%=3;
        
        DefDigTimeShow(TmpCountDownSecond/3600%24,TmpCountDownSecond/60%60,TmpCountDownSecond%60 );
        delay(100);
        switch(state){
        
          case 0: DefDigTimeShow(TmpCountDownSecond/3600%24,TmpCountDownSecond/60%60,-1 );
                  if(button_1==pressed)
                    TmpCountDownSecond++;
                  if(button_2==pressed)
                    TmpCountDownSecond--;
                  break;
           case 1: DefDigTimeShow(TmpCountDownSecond/3600%24,-1,TmpCountDownSecond%60 );
                  if(button_1==pressed)
                    TmpCountDownSecond+=60;
                  if(button_2==pressed)
                    TmpCountDownSecond-=60;
                  break;
            case 2: DefDigTimeShow(-1,TmpCountDownSecond/60%60,TmpCountDownSecond%60 );
                  if(button_1==pressed)
                    TmpCountDownSecond+=3600;
                  if(button_2==pressed)
                    TmpCountDownSecond-=3600;
                  break;

        }
      }
      if(home_button==pressed)
        break;
      DefDigTimeShow(-1,-1,-1);
      while(button_1==pressed && button_2==pressed)
        delay(1);
      CountDownSecond = TmpCountDownSecond;

      while(button_3!=pressed && home_button!=pressed && CountDownSecond > 0){

        Serial.print("COUNTING DOWN!!\n");
        DefDigTimeShow(CountDownSecond/3600%24,CountDownSecond/60%60,CountDownSecond%60 );
        
      }

      int t = millis();
      times_up = 1;
      while(button_3!=pressed && home_button!=pressed){

          Serial.print("TIMES UP!!\n");
          DefDigTimeShow(0,0,0);
          if(times_up){
            play_song();
            times_up = 0;
          }
          if(millis() - t > 100){
  
             DefDigTimeShow(-1,-1,-1);
             t = millis();
             
          }
            
        
      }
      
    
    }
    while(button_3==pressed)
      delay(1);

    
  }
}

void auto_intensity_adjust (){

  int light = analogRead(A1);
  //Serial.print(light);Serial.print(' ');
  intensity = map(light,200,700,15,1);
  //Serial.println(intensity);
  light_up();
  
}

void intensity_adjust (){

  while(home_button != pressed){
    Serial.print("intensity_adjust!!\n");
    DefDigTimeShow(0,0,0);
    if(button_1 == pressed)
      intensity ++;
    if(button_2 == pressed)
      intensity --;
    if(button_3 == pressed){
      auto_intens = !auto_intens;
    while(button_3 == pressed)
      delay(1);
       if(auto_intens)
          Serial.print("Auto_adjust!!\n");
       else
          Serial.print("Manual_adjust!!\n");
    }
      
    if(intensity > 15)
      intensity = 15;
    if(intensity < 1)
      intensity = 1;
    for(int i=0;i<4;i++)
      lc.setIntensity(i,intensity);
    
  }
    
}

void light_up (){

  for(int i=0;i<4;i++)
      lc.setIntensity(i,intensity);
  light = 1;
}

void dim(){

  for(int i=intensity;i>=1;i--){
      for(int j=0;j<4;j++){
        lc.setIntensity(j,i);
        delay(10);
      }
  }   
  light = 0;
}

void play_song()
{
  Serial.println("PLAY_SONG!!");
  //Play first section
  firstSection();
 
  //Play second section
  secondSection();
 
  //Variant 1
  beep(f, 250);  
  beep(gS, 500);  
  beep(f, 350);  
  beep(a, 125);
  beep(cH, 500);
  beep(a, 375);  
  beep(cH, 125);
  beep(eH, 650);
 
  delay(500);
 
  //Repeat second section
 /* secondSection();*/
 
  //Variant 2
  beep(f, 250);  
  beep(gS, 500);  
  beep(f, 375);  
  beep(cH, 125);
  beep(a, 500);  
  beep(f, 375);  
  beep(cH, 125);
  beep(a, 650);  
 
  delay(650);
}
 
void beep(int note, int duration)
{ 
  duration /= 2;
  //Play tone on buzzerPin
  tone(buzzerPin, note, duration);
 
  //Play different LED depending on value of 'counter'
  if(counter % 2 == 0)
  {
    digitalWrite(ledPin1, HIGH);
    delay(duration);
    digitalWrite(ledPin1, LOW);
  }else
  {
    digitalWrite(ledPin2, HIGH);
    delay(duration);
    digitalWrite(ledPin2, LOW);
  }
 
  //Stop tone on buzzerPin
  noTone(buzzerPin);
 
  delay(50);
 
  //Increment counter
  counter++;
}
 
void firstSection()
{
  beep(a, 500);
  beep(a, 500);    
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);  
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 650);
 
  delay(500);
 
  beep(eH, 500);
  beep(eH, 500);
  beep(eH, 500);  
  beep(fH, 350);
  beep(cH, 150);
  beep(gS, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 650);
 
  delay(500);
}
 
void secondSection()
{
  beep(aH, 500);
  beep(a, 300);
  beep(a, 150);
  beep(aH, 500);
  beep(gSH, 325);
  beep(gH, 175);
  beep(fSH, 125);
  beep(fH, 125);    
  beep(fSH, 250);
 
  delay(325);
 
  beep(aS, 250);
  beep(dSH, 500);
  beep(dH, 325);  
  beep(cSH, 175);  
  beep(cH, 125);  
  beep(b, 125);  
  beep(cH, 250);  
 
  delay(350);
}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.print("HOME!!\n");
  if( button_1 == pressed || button_2 == pressed || button_3 == pressed || home_button == pressed){
      delay(200);
      int st = !button_1*4 + !button_2*2 + !button_3; 
      Serial.println(st);

      
      light_up();
      if( st == 6 )
        intensity_adjust();
      if( st == 3 ){
        inverse = !inverse;
        if(inverse)
          Serial.print("inverse!!\n");
        else
          Serial.print("not inverse!!\n");
      }
      while( button_2 == pressed && button_3 == pressed)
        delay(1);
      if( st == 4 )
         TimeSet();
      if( st == 2 )
        CountDownAndTimer();
      if( st == 1 ){
        TotalSecond+=3600;
        hour++;
      }
      t = millis();
    
  }else if( millis() - t > 5000 && light && !auto_intens ){
    
    dim();
    
  }
  //Serial.print(t);Serial.print(' ');Serial.println(millis() - t);
  DefDigTimeShow(hour,minute,second);
  
    
  /*Serial.print('\n');
  for(int i=2;i<=5;i++){
    Serial.print(i);
    if(digitalRead(i)==pressed){
      Serial.print("pressed ");
    }else{
      Serial.print("HIGH ");
    }
  }*/
  
}