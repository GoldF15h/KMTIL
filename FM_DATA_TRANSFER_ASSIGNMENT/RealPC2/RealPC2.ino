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
int output[300];
int siz_e = 0;

int sentFrameNumber = 0;
bool readingData = false;
bool waitForCommand = true;
bool canSend = false;
bool waitForAck = false;
bool dataSent = false;
bool resendAll = false;
bool lastFrame = false;
int receivedData[500];
int receivedDataSize = 0;
int frameNumber = 0;
int prev = 0;
int count = 0;

uint16_t baud_check = 0;
uint16_t data = 0;
uint16_t bit_check = -1;

bool check_amp = false;
bool check_baud = false;

uint32_t baud_begin = 0;

bool one_time = true;
void setup()
{
  sbi(ADCSRA, ADPS2); // this for increase analogRead speed
  cbi(ADCSRA, ADPS1);
  cbi(ADCSRA, ADPS0);
  Serial.begin(115200);
  pinMode(A0, INPUT);
  Wire.begin();
  frequency = 91.1;                       //starting frequency
  radio.setFrequency(frequency);
  Serial.flush();
}
void sendData() {
 
}
void sendAck() {

}

void receiveAck() {

}
void receiveCommand() {
  /*****************wait for command**********************/
  int tmp = analogRead(A0);//read from DAC


  //Serial.println(tmp);
  if ( tmp > r_slope and prev < r_slope and !check_amp ) // check amplitude
  {

    check_amp = true; // is first max amplitude in that baud
    if ( !check_baud )
    {
      one_time = true;
      baud_begin = micros();
      bit_check++;
    }
  }

  if (tmp < r_slope and check_baud) {

    if (micros() - baud_begin > 41000) // full baud
    {
      //Serial.println(count);
      uint16_t last = (((count - 10) / 10) & 3) << (bit_check * 2);  // shift data
      data |= last;                                                 // add two new bits in data
      baud_check++;


      if (baud_check == 7) // 8 bits
      {
        output[siz_e] = int(data);
        siz_e++;
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
    receivedDataSize = siz_e;
    for (int i = 0 ; i <= siz_e; i++) {
      output[i];
      receivedData[i] = output[i] & 0b11111111111111;
      output[i] = NULL;
    }

    


    data = 0;
    baud_check = 0;
    bit_check = -1;
    check_amp = false;
    check_baud = false;
    count = 0;
    siz_e = 0;
    
    for(int i = 0;i<receivedDataSize;i++){
      //decToBinary(receivedData[i]);
      
      Serial.println(receivedData[i]);
      int toBi = receivedData[i];
      Serial.println(toBi);
      int tmpArrOfBi[32] = {0};
      int arrOfBiCounter = 0;
      while ( toBi >= 0 ){
        Serial.println(toBi);
        tmpArrOfBi[arrOfBiCounter] = toBi % 2;
        toBi /= 2;
      }
      for ( int wtf = 14 ; wtf >= 0 ; wtf-- ){
        Serial.print(tmpArrOfBi[wtf]);
      }
      Serial.print("\n");
      
      receivedData[i] = 0;
      
    }
    receivedDataSize = 0;
  }


  if (tmp <  r_slope and check_amp) {
    count++;
    check_baud = true;
    check_amp = false;
  }
  prev = tmp;
}

void loop() {

  //decToBinary(511);

  if (waitForCommand) {
    receiveCommand();
    //Serial.print(".");   
    /****error check ***
      if no error -> waitForCommand = false , cansend = true

    ***error check ****/

  }
  if (waitForAck)
  {
    receiveAck();
    //Serial.print("."); 
    /****error check ***
       if frame type == 3(11 xx xxxxxxxxx)
          if ack number == frameNumber(xx 00,01 xxxxxxxxxx)
          if ack number == 3 -> resendAll(xx 11 xxxxxxxxxx)
      ->canSend == true


    ***error check ****/

  }
  if (canSend and !waitForCommand)
  {
    //Serial.print("."); 
  }

  //wait for command capture. capture1 capture2 capture3
  //frame design ! sentFramenumber data error !
  //send ack of command
  //send data
  //wait for ack of data

}
