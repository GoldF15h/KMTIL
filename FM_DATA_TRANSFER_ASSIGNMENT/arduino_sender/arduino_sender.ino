  
#include<Wire.h>
#include<Adafruit_MCP4725.h>
#include<Adafruit_ADS1015.h>

#define defaultFreq 1700
#define f0 500
#define f1 800
#define f2 1100
#define f3 1400
int delay0, delay1, delay2, delay3;

const uint16_t S_DAC[4] = {1000, 2000, 1000, 0};  // 10 bits input
Adafruit_MCP4725 dac;

void setup()
{
  dac.begin(0x64);//A2
  delay0 = (1000000 / f0 - 1000000 / defaultFreq) / 4;
  delay1 = (1000000 / f1 - 1000000 / defaultFreq) / 4;
  delay2 = (1000000 / f2 - 1000000 / defaultFreq) / 4;
  delay3 = (1000000 / f3 - 1000000 / defaultFreq) / 4;
  Serial.begin(115200);
  Serial.flush();
}

bool bits_1_even_counter (int inp){
    int counter = 0;
    while ( inp > 0 ){
        if( inp % 2 != 0 ){
            //cout<<"1";
            counter += 1;
        }else {
            //cout<<"0";
        }
        inp /= 2;
    }
    //cout<<endl;
    if( counter %2 == 0 ){
        return true;
    }else{
        return false;
    }
}

void encode_vertical_1_even_counter(int* arr,int len_arr){
    int set_of_single_binary[10] = {1,2,4,8,16,32,64,128,256,512};
    arr[len_arr-1] = 0;
    //decToBinary(arr[20]);
    for ( int bit_compare = 0 ; bit_compare < 10 ; bit_compare++ ){
        int counter = 0;
        //cout<<"------------------------------------------\n";
        Serial.println("change number******************************************************");
        for ( int number = 0 ; number < len_arr-1 ; number++ ){
            /*cout<<"number -> "<<arr[number]<<' '<<"bit -> "<< set_of_single_binary[bit_compare]<<" result -> "<<' '<<( arr[number] & set_of_single_binary[bit_compare] ) <<endl;
            decToBinary(arr[number]);
            decToBinary(set_of_single_binary[bit_compare]);
            decToBinary(arr[number] & set_of_single_binary[bit_compare]);*/
            Serial.print("----------------------------");Serial.println(arr[number]);
            decToBinary(arr[number]);
            decToBinary(set_of_single_binary[bit_compare]);
            decToBinary((arr[number] & set_of_single_binary[bit_compare]));
            if ( (arr[number] & set_of_single_binary[bit_compare]) != 0){
                counter += 1;
                Serial.println("counter+++");
                //cout<<"counter++++++++\n";
            }
            //cout<<"counter = "<<counter<<endl<<endl;
        }
        Serial.print("XXXXXXXXXX COUNTER -> ");Serial.print(counter);Serial.print(" counter % 2 -> ");Serial.println(counter%2);
        Serial.print("before -> ");decToBinary(arr[len_arr-1]);
        if( counter % 2 != 0 ){
            arr[len_arr-1] |= set_of_single_binary[bit_compare];
        }
        Serial.print("after  -> ");decToBinary(arr[len_arr-1]);
    }
}

bool decode_vertical_1_even_counter(int* arr,int len_arr){
    int set_of_single_binary[10] = {1,2,4,8,16,32,64,128,256,512};
    //arr[20] = 0;
    //decToBinary(arr[20]);
    for ( int bit_compare = 0 ; bit_compare < 10 ; bit_compare++ ){
        int counter = 0;
        //cout<<bit_compare<<endl;
        //cout<<"------------------------------------------\n";
        for ( int number = 0 ; number < len_arr ; number++ ){
            /*cout<<"number -> "<<arr[number]<<' '<<"bit -> "<< set_of_single_binary[bit_compare]<<" result -> "<<' '<<( arr[number] & set_of_single_binary[bit_compare] ) <<endl;
            decToBinary(arr[number]);
            decToBinary(set_of_single_binary[bit_compare]);
            decToBinary(arr[number] & set_of_single_binary[bit_compare]);*/
           //Serial.print("----------------------------");Serial.println(arr[number]);
              //decToBinary(arr[number]);
              //decToBinary(set_of_single_binary[bit_compare]);
            if ( (arr[number] & set_of_single_binary[bit_compare]) ){
                counter += 1;
                //Serial.println(arr[number]);
                //Serial.println("counter+++");
                //cout<<"counter++++++++\n";
            }
            //cout<<"counter = "<<counter<<endl<<endl;
        }
        //cout<<"before check counter "<<counter<<endl;
        //Serial.print("before check counter : ");Serial.println(counter);
        if( counter % 2 != 0 ){
            //Serial.println("false break");
            return false;
        }
    }
    return true;
}

void paritiy_bits (int* arr,int len_arr){
    for( int i = 0 ; i < len_arr-1 ; i++ ){
        if( bits_1_even_counter(arr[i]) )
            arr[i] = arr[i] << 1 ;
        else
            arr[i] = ( arr[i] << 1 ) | 1 ;
        //decToBinary(arr[i]);
    }
    encode_vertical_1_even_counter(arr,len_arr);
    //decToBinary(arr[20]);
}

bool error_checking_partity_bits (int* arr,int len_arr){
    for( int i = 0 ; i < len_arr ; i++ ){
        if(!bits_1_even_counter(arr[i])){
            return false;
        }
    }
    if( !decode_vertical_1_even_counter(arr,len_arr) ){
        return false;
    }
    return true;
}

void decToBinary(int n)
{
    // array to store binary number
    int binaryNum[32]={0};
    // counter for binary array
    int i = 0;
    while (n > 0) {
        // storing remainder in binary array
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }
    // printing binary array in reverse order
    for (int j = 9; j >= 0; j--){
        Serial.print( (binaryNum[j] ) );
        Serial.print(' ');
    }
    Serial.println(' ');
}

void send_10_bits_of_data (int send_data){ // this function need to sent int
  Serial.print("----------------------------\n");
  Serial.print("in send function");
  Serial.println(send_data);
  for (int k = 7; k > 0; k -= 2) //send 10 bits from LSB tp MSB
      {
      int tmp = send_data & 3;
      int useDelay,cyc;  
        if(tmp == 0)
        {
          //Serial.println("00");
          cyc =5;
          useDelay = delay0;   
        }
        else if(tmp == 1)
        {
          //Serial.println("01");
          cyc = 8;
          useDelay = delay1;  
        }
        else if(tmp == 2)
        {
          //Serial.println("10");
          cyc = 11;
          useDelay = delay2; 
        }
        else
        {
          //Serial.println("11");
          cyc = 14;
          useDelay = delay3;  
        }
        for (int sl=0;sl<cyc;sl++)
        {
          for (int s=0;s<4;s++) //4 sample/cycle
          {
            dac.setVoltage(S_DAC[s], false);//modify amplitude
            //Serial.println(S_DAC[s]);
            delayMicroseconds(useDelay);
            
          }
        }
        //delayMicroseconds(500);
        //delay(1);
        send_data>>=2;
        
        dac.setVoltage(0, false);
        
      }
  
}

int inData[300];
bool one_time = true;

void loop()
{
 /* if(one_time){
    one_time = !one_time;
    int len_arr = 18;
    int arr_of_int[len_arr];
    for(int i=0;i<len_arr-1;i++){
        arr_of_int[i] = i+1;
    }   
    paritiy_bits(arr_of_int,len_arr);

    //Serial.println(arr_of_int[i]);
    //arr_of_int[0] = 0b0000000111;
    //arr_of_int[1] = 0b0000000111;
    Serial.println("FINAL RESULT");
    for(int i=0;i<len_arr;i++)
      decToBinary(arr_of_int[i]);
    Serial.print("ERROR CHECK -> ");Serial.println(error_checking_partity_bits(arr_of_int,len_arr));
    
    Serial.println("END");
  }*/
  
  
  if (Serial.available() > 0)
  {
    int counter = 0;
    String inp = Serial.readString();
    //for(int i = 0 ; i < inp.length() ; i++ ){Serial.print(inp[i]); Serial.println("*");}
    /*String _[inp.length()]; 
    for(int i = 0 ; i < inp.length() ; i++ ){Serial.print(inp[i]); Serial.println("*");}
    String slide_inp[60];
    while( inp.length() % 5 != 0 ){
      inp += '\n';
    }
    Serial.print("fill up the string -> "); Serial.println(inp);
    Serial.println("---------------------------");
    //int data_combo = 0;
    for( int i = 0 ; i < inp.length() / 5 ; i ++ ){

      for( int j = 0 ; j < 5 ; i ++ ){

        slide_inp[i] =   
        
      }
      
    }*/
    inp = '\n'+inp;
    for(int i=0;i<inp.length();i++)
    {
      inData[i] = int(inp[i]); // cast char to int 
    }
    for (int i=0;i<inp.length()-1;i++) // send data
    {
      send_10_bits_of_data(inData[i]);
    }
    dac.setVoltage(0, false);
  }
  
}
