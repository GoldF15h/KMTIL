#include<iostream>
#include<stdio.h>
bool decode_vertical_1_even_counter(int*, int  );
int main(){
    int arr[3] = {255,254,253};
    printf(decode_vertical_1_even_counter(arr,3));

}
bool decode_vertical_1_even_counter(int* arr, int len_arr) {
  int set_of_single_binary[10] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};
  //Serial.println("vertical check");
  for ( int bit_compare = 0 ; bit_compare < 10 ; bit_compare++ ) {
    int counter = 0;
   // Serial.println("--------------------------------");
    for ( int number = 0 ; number < len_arr ; number++ ) {
     // Serial.println(arr[number]);
      if ( (arr[number] & set_of_single_binary[bit_compare]) ) {
        counter += 1;
      }
    }
    if ( counter % 2 != 0 ) {
      //Serial.println("false break");
      return false;
    }
  }
  //255  -> 11 11 11 11
  //254  -> 11 11 11 10
  //253  -> 11 11 11 01
  //Serial.println("true");
  return true;
}
