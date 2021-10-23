 #include<Wire.h>
#include <TEA5767Radio.h> 

TEA5767Radio radio = TEA5767Radio();            

float frequency;               

#ifndef cbi
#define cbi(sfr, bit)(_SFR_BYTE(sfr)&=~_BV(bit)) 
#endif
#ifndef sbi
#define sbi(sfr, bit)(_SFR_BYTE(sfr)|=_BV(bit))
#endif

//edit this number
#define r_slope 200
char output[300];      
 int siz_e = 0;              
void setup()
{
  
  sbi(ADCSRA, ADPS2); // this for increase analogRead speed
  cbi(ADCSRA,ADPS1);
  cbi(ADCSRA,ADPS0);
  Serial.begin(115200);
  pinMode(A0,INPUT);
  Wire.begin();
  frequency = 91.1;                       //starting frequency
  radio.setFrequency(frequency);
  Serial.flush();
}
int prev = 0;
int count = 0;

uint16_t baud_check = 0;
uint16_t data = 0;
uint16_t bit_check = -1;

bool check_amp = false;
bool check_baud = false;

uint32_t baud_begin = 0;



bool one_time = true;

void loop()
{
  int tmp = analogRead(A0);//read from DAC
  //int tmp = analogRead(A2);//read from FM
  
  //Serial.println(tmp);
  if ( tmp > r_slope and prev < r_slope and !check_amp ) // check amplitude
  {
    //Serial.print("peak ");
    //Serial.println(tmp);
    check_amp = true; // is first max amplitude in that baud
    if ( !check_baud )
    {
      one_time = true;
      baud_begin = micros();
      bit_check++;
    }
  }

  if(tmp < r_slope and check_baud) {
   
    if (micros() - baud_begin > 41000) // full baud
    {
      //Serial.println(count); 
      uint16_t last = (((count - 10) / 10) & 3) << (bit_check * 2);  // shift data
      data |= last;                                                 // add two new bits in data
      baud_check++;
       
      
      if (baud_check == 5) // 8 bits
      {
          output[siz_e] = char(data);
          siz_e++;                     
        
        //data >>= 8;
        //Serial.print("receive ");
        //Serial.print(data,BIN);
        //if(data == '\n'){
          //Serial.println("back slash");
        //}
       // else
          //{
          // Serial.println(char(data));
          //}
        //Serial.println("---BAUD---");
        
        
        //Serial.flush();
        data = 0;
        baud_check = 0;
        bit_check = -1;
      }
      check_baud = false;
      count = 0;
    }
  }
  if (micros() - baud_begin > 50000 && one_time) {
    one_time = false;
    for(int i = 0 ;i <=siz_e;i++){
      
      if (output[i] == '\n'){ 
        Serial.print("");
      }
      else{
        Serial.print(output[i]);
      }
      Serial.flush();
      output[i] = NULL;
    }
    Serial.println("");
    
    data = 0;
    baud_check = 0;
    bit_check = -1;
    check_amp = false;
    check_baud = false;
    count = 0; }
  
  
  if(tmp <  r_slope and check_amp) {
    count++;
    check_baud = true;
    check_amp = false;
  }
  prev = tmp;
}
