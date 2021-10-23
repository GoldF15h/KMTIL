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

void paritiy_bits (int* arr){



    for( int i = 0 ; i < 20 ; i++ ){

        cout<<arr[i];
        cout<<" Before -> ";
        decToBinary(arr[i]);
        if( bits_1_even_counter(arr[i]) )
            arr[i] = arr[i] << 1 ;
        else
            arr[i] = ( arr[i] << 1 ) | 1 ;
        cout<<"After -> ";
        decToBinary(arr[i]);
        cout<<"---------------------------"<<endl;

    }

}

void decToBinary(int n)
{
    // array to store binary number
    int binaryNum[32];

    // counter for binary array
    int i = 0;
    while (n > 0) {

        // storing remainder in binary array
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }

    // printing binary array in reverse order
    for (int j = i - 1; j >= 0; j--)
        cout << binaryNum[j];
    cout <<endl;
}

void all_plus_one (int *arr,int size_of_arr){

    for(int i=0 ; i< size_of_arr ;i++)
        arr[i]++;

}

int main (){

    int arr_of_int[21];
    for(int i=0;i<21;i++){
        arr_of_int[i] = i+1;
    }
    cout<<"debug "<<bits_1_even_counter(8)<<endl;
    //cout<<"test shift bits from 2 << 1 | 1"<<((2<<1)|1);
    /*for(int i=0;i<21;i++)
        cout<<arr_of_int[i]<<' ';
    cout<<endl;
    //all_plus_one(arr_of_int,21);
    for(int i=0;i<21;i++)
        cout<<arr_of_int[i]<<' ';
    cout<<endl;*/
    arr_of_int[0] |= 15;
    paritiy_bits(arr_of_int);


    return 0;

}
