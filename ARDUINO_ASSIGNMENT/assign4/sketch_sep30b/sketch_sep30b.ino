#include "LedControl.h" //  need the library
LedControl lc=LedControl(13,11,10,4); //

int PosX[]={6,6,6,5,4,4,3,2,2,2,3,3,3,3,2,1,1},PosY[]={7,6,5,5,5,6,6,6,5,4,4,3,2,1,1,1,0};
int Map[][8]={
  {191,139,161,229,207,209,133,253}
};

void Display(int *Box)
{
  for(int i=0;i<8;i++,Box++)
  {
    for(int j=7;j>=0;j--)
    {
      lc.setLed(0,i,7-j,((*Box)>>j)&1);
      delay(1);
      //lc.setLed(0,i,7-j,0);
    }
  }
}

void Player()
{
  for(int i=0;i<17;i++)
  {
  lc.setLed(0,PosY[i],PosX[i],true);
  delay(10);
  lc.setLed(0,PosY[i],PosX[i],false); 
  delay(10);
  }
}

void setup()
{
  // the zero refers to the MAX7219 number, it is zero for 1 chip
  lc.shutdown(0,false);// turn off power saving, enables display
  lc.shutdown(1,false);
  lc.shutdown(2,false);
  lc.shutdown(3,false);
  lc.setIntensity(0,1);// sets brightness (0~15 possible values)
  lc.setIntensity(0,1);
  lc.setIntensity(0,1);
  lc.setIntensity(0,1);
  lc.clearDisplay(0);// clear screen
  //Display(Map[0]);
}
void loop()
{
  //for(int i=0;i<8;i++)
    //lc.setLed(0,1,1,1);
  //Player();
}
