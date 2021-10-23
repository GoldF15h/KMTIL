#include<Wire.h>
#include <TEA5767Radio.h>
#include<Adafruit_MCP4725.h>
#include<Adafruit_ADS1015.h>

TEA5767Radio radio = TEA5767Radio();

float frequency;

#ifndef cbi
#define cbi(sfr, bit)(_SFR_BYTE(sfr)&=~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit)(_SFR_BYTE(sfr)|=_BV(bit))
#endif

#define defaultFreq 8000
#define f0 275
#define f1 635
#define f2 1125
#define f3 1825

int delay0, delay1, delay2, delay3;
#define r_slope 280

const uint16_t S_DAC[4] = {1000, 2000, 1000, 0};  // 10 bits input
Adafruit_MCP4725 dac;

void setup()
{
  dac.begin(0x60);
  sbi(ADCSRA, ADPS2); // this for increase analogRead speed
  cbi(ADCSRA, ADPS1);
  cbi(ADCSRA, ADPS0);
  delay0 = (1000000 / f0 - 1000000 / defaultFreq) / 4;
  delay1 = (1000000 / f1 - 1000000 / defaultFreq) / 4;
  delay2 = (1000000 / f2 - 1000000 / defaultFreq) / 4;
  delay3 = (1000000 / f3 - 1000000 / defaultFreq) / 4;
  Serial.begin(115200);
  pinMode(A0, INPUT);
  Wire.begin();
  frequency = 91.1;                       //starting frequency
  radio.setFrequency(frequency);
  Serial.flush();
}


uint32_t timer = 0;
bool one_time = true;
bool check_amp = false;
bool check_baud = false;
bool canSend = true;
bool canReceive = false;
bool received = false;
bool stateToggle = true;


int output[30];
int prev = 0;
int count = 0;
int inData[300];
int ackRespond = 0;
int ackFrame[14] = {0};
int frameNumber = 0;
int dataFromCamera;
int siz_e = 0;
int receivedData[30] = {0};
int receivedDataSize = 0;

uint32_t baud_begin = 0;
uint16_t baud_check = 0;
uint16_t data = 0;
uint16_t bit_check = -1;

String readFromSerial ;
String Data;

void clearSignal ();
bool bits_1_even_counter (int inp);
void makeArrayOfDataFrame(int* arrayOfData, int siz_e);
void encode_vertical_1_even_counter(int* arr, int len_arr);
bool decode_vertical_1_even_counter(int* arr, int len_arr);
void makeArrayOfDataFrame(int* arrayOfData, int siz_e);
void decToBinary(int n);
void paritiy_bits (int* arr, int len_arr);
bool error_checking_partity_bits (int* arr, int len_arr);
void send_14_bits_of_data (int send_data);

void receiveAck () {
  int tmp = analogRead(A0);//read from DAC
  //  Serial.println( "SIZE = ");
  //  Serial.flush();

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

    if (micros() - baud_begin > 40000) // full baud
    {
      //Serial.println(count);
      int last = (((count - 10) / 10) & 3) << (bit_check * 2);  // shift data
      data |= last;                                                 // add two new bits in data
      baud_check++;


      if (baud_check == 7) // 8 bits
      {
        //Serial.println("FULL FRAME");
        received = true;
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

  if (micros() - baud_begin > 60000 and received) {

    one_time = false;
    receivedDataSize = siz_e;
    //Serial.println("-------------------- ACK -----------------------");
    for (int i = 0 ; i < siz_e; i++) {
      //Serial.println(output[i]);
      //output[i] &= 0b11111111111111;
      receivedData[i] = output[i];
      output[i] = 0;
    }

    data = 0;
    baud_check = 0;
    bit_check = -1;
    check_amp = false;
    check_baud = false;
    count = 0;
    siz_e = 0;
    stateToggle = true;

    receivedDataSize = 0;
    //send_14_bits_of_data(16383);
    received = false;
  }


  if (tmp <  r_slope and check_amp) {
    count++;
    check_baud = true;
    check_amp = false;
  }
  prev = tmp;
}

void receiveData() {
  /*****************wait for command**********************/
  int tmp = analogRead(A0);//read from DAC
  //  Serial.println( "SIZE = ");
  //  Serial.flush();

  //Serial.println(tmp);
  if ( tmp > r_slope and prev < r_slope and !check_amp ) // check amplitude
  {

    check_amp = true; // is first max amplitude in that baud
    if ( !check_baud )
    {
      one_time = true;
      baud_begin = micros();
      received = false;
      bit_check++;
    }
  }

  if (tmp < r_slope and check_baud) {

    if (micros() - baud_begin > 40000) // full baud
    {
      //Serial.println(count);
      int last = (((count - 10) / 10) & 3) << (bit_check * 2);  // shift data
      data |= last;                                                 // add two new bits in data
      baud_check++;


      if (baud_check == 7) // 8 bits
      {
        received = true;
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

  if (micros() - baud_begin > 60000 and received) {

    one_time = false;
    receivedDataSize = siz_e;
    Serial.println("-------------------------------------------");
    for (int i = 0 ; i < siz_e; i++) {
      //Serial.println(output[i]);
      //output[i] &= 0b11111111111111;
      receivedData[i] = output[i];
      output[i] = 0;
    }

    data = 0;
    baud_check = 0;
    bit_check = -1;
    check_amp = false;
    check_baud = false;
    count = 0;
    siz_e = 0;
    canReceive = false;
    canSend = true;
    stateToggle = true;

    for (int i = 0; i < receivedDataSize; i++) {
      decToBinary(receivedData[i]);
      //Serial.println(receivedData[i]);
      
    }
    receivedDataSize = 0;
    //send_14_bits_of_data(16383);
  received = false;
  }


  if (tmp <  r_slope and check_amp) {
    count++;
    check_baud = true;
    check_amp = false;
  }
  prev = tmp;
}

void loop() {
 
  if(stateToggle){
  if (canSend) {
    Serial.println("Sender");
  }
  if (canReceive) {
    Serial.println("Receiver");
  }
  stateToggle = false;
  }
  if (Serial.available() && canSend) {
    canSend = false;
    canReceive = true;
    stateToggle = true;


    readFromSerial = Serial.readString();
    Serial.println(readFromSerial);

    int dataLen = readFromSerial.length() - 1; // remove "\n"
    int sendFrame[ dataLen + 1 ] = {};
    for ( int i = 0 ; i < dataLen ; i++ ) {
      sendFrame[i] = int(readFromSerial[i]);
    }

    
    makeArrayOfDataFrame(sendFrame, dataLen + 1);
    paritiy_bits( sendFrame , dataLen + 1);
    
    clearSignal();

    int i = 0 ;

    for ( int _ ; _ < dataLen + 1 ; _ ++ ){
      decToBinary(sendFrame[_]);
    }

    //sendFrame[4] = 0b01000001000101; 
    while ( i < dataLen + 1 ) {
      Serial.print("SENDING -> ");decToBinary(sendFrame[i]);
      send_14_bits_of_data(sendFrame[i]);
      
      receivedData[0] = 0;
      //Serial.print("WAIT FOR ACK");
      uint32_t resendTimer = millis();
      while( receivedData[0] == 0){
       //Serial.print('.');
        receiveAck();
        if ( receivedData[0] != 0 ){
//          Serial.print("RECIVED ACK i%2 -> " + String(i%2) + " ACK MOD -> " + String(((receivedData[0] >> 10)&3)) + " ack -> ");decToBinary(receivedData[0]);
          Serial.print("RECIVED ACK -> ");decToBinary(receivedData[0]);
          if ( ((receivedData[0] >> 10)&15) == 15){
            Serial.println("IT\'S NACK RESEND ALL");
            i = -1;
            receivedData[0] = 0;
            resendTimer = millis();
          }else
          if ( ((receivedData[0] >> 10)&3) == (i%2) ){
            Serial.println("RESEND");
            Serial.print("SENDING -> ");decToBinary(sendFrame[i]);
            send_14_bits_of_data(sendFrame[i]); // resend
            receivedData[0] = 0;
            resendTimer = millis();
          }
        
        }

        if (millis() - resendTimer > 2500){
          Serial.println("TIMEOUT RESEND");
          Serial.print("SENDING -> ");decToBinary(sendFrame[i]);
          send_14_bits_of_data(sendFrame[i]); // resend
          resendTimer = millis();
          receivedData[0] = 0;
        }
        
      }
      //Serial.println("\nRECIVE ACK " + String(receivedData[0]));
      i++;
    }

    clearSignal();

    timer = millis();
  }
  if (canReceive) {
    receiveData();
  }
}

bool bits_1_even_counter (int inp) {
  int counter = 0;
  while ( inp > 0 ) {
    if ( inp % 2 != 0 ) {
      counter += 1;
    } else {
    }
    inp /= 2;
  }
  if ( counter % 2 == 0 ) {
    return true;
  } else {
    return false;
  }
}

void encode_vertical_1_even_counter(int* arr, int len_arr) {
  int set_of_single_binary[10] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};
  arr[len_arr - 1] = 0;
  for ( int bit_compare = 0 ; bit_compare < 10 ; bit_compare++ ) {
    int counter = 0;
    for ( int number = 0 ; number < len_arr - 1 ; number++ ) {
      if ( (arr[number] & set_of_single_binary[bit_compare]) != 0) {
        counter += 1;
      }
    }
    if ( counter % 2 != 0 ) {
      arr[len_arr - 1] |= set_of_single_binary[bit_compare];
    }
  }
}

void clearSignal () {

  int useDelay, cyc;
  cyc = 10;
  useDelay = delay0;
  for (int sl = 0; sl < cyc; sl++)
  {
    for (int s = 0; s < 4; s++) //4 sample/cycle
    {
      dac.setVoltage(100, false);//modify amplitude
      //Serial.println(S_DAC[s]);
      delayMicroseconds(useDelay);

    }
  }
}

void decToBinary(int n)
{
  int binaryNum[32] = {0}; int i = 0;
  while (n > 0) {
    binaryNum[i] = n % 2;
    n = n / 2;
    i++;
  }
  for (int j = 13; j >= 0; j--) {
    Serial.print( (binaryNum[j] ) );
    Serial.print(' ');
  } Serial.println(' ');
}

void makeArrayOfDataFrame(int* arrayOfData, int siz_e)
{

  int number = 0;
  for (int i = 0; i < siz_e; i++)
  {
    arrayOfData[i] &= 0b00001111111111                                                                                                                                                                                ;
    if (number == 0)
    {
      if (i == siz_e - 1) {
        arrayOfData[i] |= 0b01000000000000;
      }
      else {
        arrayOfData[i] |= 0b00000000000000;
      }
    }
    else {
      if (i == siz_e - 1) {
        arrayOfData[i] |= 0b01010000000000;
      }
      else {
        arrayOfData[i] |= 0b00010000000000;
      }
    }
    number = (number + 1) % 2;
  }

}

void paritiy_bits (int* arr, int len_arr) {
  for ( int i = 0 ; i < len_arr - 1 ; i++ ) {
    if ( bits_1_even_counter(arr[i]) )
      arr[i] = arr[i] << 1 ;
    else
      arr[i] = ( arr[i] << 1 ) | 1 ;
  }
  encode_vertical_1_even_counter(arr, len_arr);
}

void send_14_bits_of_data (int send_data) { // this function need to sent int
  for (int k = 13; k > 0; k -= 2) //send 10 bits from LSB tp MSB
  {
    int tmp = send_data & 3;
    int useDelay, cyc;
    if (tmp == 0)
    {
      // Serial.println("00");
      cyc = 10;
      useDelay = delay0;
    }
    else if (tmp == 1)
    {
      //Serial.println("01");
      cyc = 20;
      useDelay = delay1;
    }
    else if (tmp == 2)
    {
      //Serial.println("10");
      cyc = 30;
      useDelay = delay2;
    }
    else
    {
      //Serial.println("11");
      cyc = 40;
      useDelay = delay3;
    }
    for (int sl = 0; sl < cyc; sl++)
    {
      for (int s = 0; s < 4; s++) //4 sample/cycle
      {
        dac.setVoltage(S_DAC[s], false);//modify amplitude
        //Serial.println(S_DAC[s]);
        delayMicroseconds(useDelay);

      }
    }
    //delayMicroseconds(500);
    delay(1);
    send_data >>= 2;

    dac.setVoltage(0, false);

  }

}
