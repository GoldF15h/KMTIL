#include<iostream>

using namespace std;

void decToBinary(int n);

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

void encode_vertical_1_even_counter(int* arr){
    int set_of_single_binary[10] = {1,2,4,8,16,32,64,128,256,512};
    arr[20] = 0;
    //decToBinary(arr[20]);
    for ( int bit_compare = 0 ; bit_compare < 10 ; bit_compare++ ){
        int counter = 0;
        //cout<<"------------------------------------------\n";
        for ( int number = 0 ; number < 20 ; number++ ){
            /*cout<<"number -> "<<arr[number]<<' '<<"bit -> "<< set_of_single_binary[bit_compare]<<" result -> "<<' '<<( arr[number] & set_of_single_binary[bit_compare] ) <<endl;
            decToBinary(arr[number]);
            decToBinary(set_of_single_binary[bit_compare]);
            decToBinary(arr[number] & set_of_single_binary[bit_compare]);*/
            if ( !(arr[number] & set_of_single_binary[bit_compare]) ){
                counter += 1;
                //cout<<"counter++++++++\n";
            }
            //cout<<"counter = "<<counter<<endl<<endl;
        }
        if( counter % 2 != 0 ){
            arr[20] |= set_of_single_binary[bit_compare];
        }
    }
}

bool decode_vertical_1_even_counter(int* arr){
    int set_of_single_binary[10] = {1,2,4,8,16,32,64,128,256,512};
    arr[20] = 0;
    //decToBinary(arr[20]);
    for ( int bit_compare = 0 ; bit_compare < 10 ; bit_compare++ ){
        int counter = 0;
        //cout<<bit_compare<<endl;
        //cout<<"------------------------------------------\n";
        for ( int number = 0 ; number < 21 ; number++ ){
            /*cout<<"number -> "<<arr[number]<<' '<<"bit -> "<< set_of_single_binary[bit_compare]<<" result -> "<<' '<<( arr[number] & set_of_single_binary[bit_compare] ) <<endl;
            decToBinary(arr[number]);
            decToBinary(set_of_single_binary[bit_compare]);
            decToBinary(arr[number] & set_of_single_binary[bit_compare]);*/
            if ( (arr[number] & set_of_single_binary[bit_compare]) ){
                counter += 1;
                //cout<<"counter++++++++\n";
            }
            //cout<<"counter = "<<counter<<endl<<endl;
        }
        //cout<<"before check counter "<<counter<<endl;
        if( counter % 2 != 0 ){
            //cout<<"false break!!!\n";
            return false;
        }
    }
    return true;
}

void paritiy_bits (int* arr){
    for( int i = 0 ; i < 20 ; i++ ){
        //cout<<arr[i]<<' ';
        //cout<<" Before -> ";
        //decToBinary(arr[i]);
        if( bits_1_even_counter(arr[i]) )
            arr[i] = arr[i] << 1 ;
        else
            arr[i] = ( arr[i] << 1 ) | 1 ;
        //cout<<"After -> ";
        //cout<<arr[i]<<" -> ";
        decToBinary(arr[i]);
    }
    encode_vertical_1_even_counter(arr);
    decToBinary(arr[20]);
}

bool error_checking_partity_bits (int* arr){
    for( int i = 0 ; i < 21 ; i++ ){
        if(!bits_1_even_counter(arr[i])){
            return false;
        }
    }
    if( !decode_vertical_1_even_counter(arr) ){
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
    for (int j = 9; j >= 0; j--)
        cout << binaryNum[j] <<' ';
    cout <<endl;
}



int main (){
    int arr_of_int[21];
    for(int i=0;i<20;i++){
        arr_of_int[i] = i+1;
        //cout<<arr_of_int[i]<<" -> ";
        //decToBinary(arr_of_int[i]);
    }
    //cout<<"debug "<<bits_1_even_counter(8)<<endl;
    //cout<<"test shift bits from 2 << 1 | 1"<<((2<<1)|1);
    /*for(int i=0;i<21;i++)
        cout<<arr_of_int[i]<<' ';
    cout<<endl;
    //all_plus_one(arr_of_int,21);
    for(int i=0;i<21;i++)
        cout<<arr_of_int[i]<<' ';
    cout<<endl;*/
    paritiy_bits(arr_of_int);
    //arr_of_int[20] = 511;
    arr_of_int[0] = 15;
    cout<<error_checking_partity_bits(arr_of_int);

    return 0;
}
