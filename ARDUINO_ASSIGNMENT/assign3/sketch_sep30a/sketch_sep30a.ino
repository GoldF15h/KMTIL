#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

short state = 1;
int tape[200][2];

void setup()
{
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP); // note
  
  
  pinMode(9, OUTPUT); // ลำโพง
  
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP); //play rec
  
  Serial.begin(9600);
}

void play(){
  //Serial.println("play");
  if(digitalRead(2)==LOW){
    tone(9,NOTE_C4,10);
    //Serial.println("C4");
    //delay(200);
    
  } 
  if(digitalRead(3)==LOW){
    tone(9,NOTE_D4,10);
    //Serial.println("D4");
    //delay(200);
    
  } 
  if(digitalRead(4)==LOW){
    tone(9,NOTE_E4,10);
    //Serial.println("E4");
    //delay(200);
    
  } 
  if(digitalRead(5)==LOW){
    tone(9,NOTE_F4,10);
    //Serial.println("F4");
    //delay(200);
  } 
  
  if(digitalRead(6)==LOW){
    tone(9,NOTE_G4,10);
    //Serial.println("G4");
    //delay(200);
    
  } 
  if(digitalRead(7)==LOW){
    tone(9,NOTE_A4,10);
    //Serial.println("B4");
    //delay(200);
    
  } 
  if(digitalRead(8)==LOW){
    tone(9,NOTE_B4,10);
    //Serial.println("B4");
    //delay(200);
    
  }
}



void record (){
  int i=0;
  int bt_press = 0;
  int blank_time = millis();
  for(int j=0;j<200;j++){
    tape[j][0] = 0 ;
    tape[j][1] = 0 ;
  }
 
  while(state == -1){

    // start bt 2
    
    if(digitalRead(2)==LOW ){

        bt_press = millis();
        //tone(9,NOTE_C4,10);

        tape[i][0] = -1;
        tape[i][1] = bt_press - blank_time;  
        Serial.print(i);Serial.print(" ");Serial.print(tape[i][0]);Serial.print(" ");Serial.println(tape[i][1]);
        i++;

        while(digitalRead(2)==LOW)play();
      
        tape[i][0] = NOTE_C4;
        tape[i][1] = millis() - bt_press;
        blank_time = millis();
        Serial.print(i);Serial.print(" ");Serial.print(tape[i][0]);Serial.print(" ");Serial.println(tape[i][1]);
        i++;

    }
    // end bt 2

    // start bt 3
    if(digitalRead(3)==LOW ){

        bt_press=millis();
        //tone(9,NOTE_D4,10);
        
        tape[i][0] = -1;
        tape[i][1] = bt_press - blank_time;  
        Serial.print(i);Serial.print(" ");Serial.print(tape[i][0]);Serial.print(" ");Serial.println(tape[i][1]);
        i++;

        while(digitalRead(3)==LOW)play();
        
        tape[i][0] = NOTE_D4;
        tape[i][1] = millis() - bt_press;
        blank_time = millis();
        Serial.print(i);Serial.print(" ");Serial.print(tape[i][0]);Serial.print(" ");Serial.println(tape[i][1]);
        i++;
      
    }
    // end bt 3

    // start bt 4
    if(digitalRead(4)==LOW){
      
        bt_press=millis();
        //tone(9,NOTE_E4,10);
        
        tape[i][0] = -1;
        tape[i][1] = bt_press - blank_time;  
        Serial.print(i);Serial.print(" ");Serial.print(tape[i][0]);Serial.print(" ");Serial.println(tape[i][1]);
        i++;

        while(digitalRead(4)==LOW)play();
        
        tape[i][0] = NOTE_E4;
        tape[i][1] = millis() - bt_press;
        blank_time = millis();
        Serial.print(i);Serial.print(" ");Serial.print(tape[i][0]);Serial.print(" ");Serial.println(tape[i][1]);
        i++;
      
    }
    // end bt 4

      // start bt 5
    if(digitalRead(5)==LOW){
      
        bt_press=millis();
        //tone(9,NOTE_F4,10);
       
        tape[i][0] = -1;
        tape[i][1] = bt_press - blank_time;  
        Serial.print(i);Serial.print(" ");Serial.print(tape[i][0]);Serial.print(" ");Serial.println(tape[i][1]);
        i++;

        while(digitalRead(5)==LOW)play();
        
        tape[i][0] = NOTE_F4;
        tape[i][1] = millis() - bt_press;
        blank_time = millis();
        Serial.print(i);Serial.print(" ");Serial.print(tape[i][0]);Serial.print(" ");Serial.println(tape[i][1]);
        i++;
      
    }
    // end bt 5


    // start bt 6
    if(digitalRead(6)==LOW){
      
      
        bt_press=millis();
        //tone(9,NOTE_G4,10);
        
        tape[i][0] = -1;
        tape[i][1] = bt_press - blank_time;  
        Serial.print(i);Serial.print(" ");Serial.print(tape[i][0]);Serial.print(" ");Serial.println(tape[i][1]);
        i++;

        while(digitalRead(6)==LOW)play();
        
        tape[i][0] = NOTE_G4;
        tape[i][1] = millis() - bt_press;
        blank_time = millis();
        Serial.print(i);Serial.print(" ");Serial.print(tape[i][0]);Serial.print(" ");Serial.println(tape[i][1]);
        i++;
      
    }
    // end bt 6

    // start bt 7
    if(digitalRead(7)==LOW){
  
      
        bt_press=millis();
        //tone(9,NOTE_A4,10);
      

        tape[i][0] = -1;
        tape[i][1] = bt_press - blank_time;  
        Serial.print(i);Serial.print(" ");Serial.print(tape[i][0]);Serial.print(" ");Serial.println(tape[i][1]);
        i++;

        while(digitalRead(7)==LOW)play();
        
        tape[i][0] = NOTE_A4;
        tape[i][1] = millis() - bt_press;
        blank_time = millis();
        Serial.print(i);Serial.print(" ");Serial.print(tape[i][0]);Serial.print(" ");Serial.println(tape[i][1]);
        i++;
      
    }
    // end bt 7
    // start bt 8
    if(digitalRead(8)==LOW ){
      
        bt_press=millis();
        //tone(9,NOTE_B4,10);

        tape[i][0] = -1;
        tape[i][1] = bt_press - blank_time;  
        Serial.print(i);Serial.print(" ");Serial.print(tape[i][0]);Serial.print(" ");Serial.println(tape[i][1]);
        i++;

        while(digitalRead(8)==LOW)play();
        
        tape[i][0] = NOTE_B4;
        tape[i][1] = millis() - bt_press;
        blank_time = millis();
        Serial.print(i);Serial.print(" ");Serial.print(tape[i][0]);Serial.print(" ");Serial.println(tape[i][1]);
        i++;
      
    }
    // end bt 8
    // ending check
    if(digitalRead(11)==LOW){
    
        while(digitalRead(11)==LOW) 
          delay(1);
        state = 1;
        Serial.println("RECORD = 0");
      
    }
    
  }
  
}

void play_tape (){
    int i=1;
    Serial.println("START REPLAY");
    while(tape[i][0] != 0){

        if(tape[i][0] == -1 && tape[i][1]>=0)
          delay(tape[i][1]+100);
        else{
          tone(9,tape[i][0],tape[i][1]+50 );
          
        }
        Serial.print(i);Serial.print(" ");Serial.print(tape[i][0]);Serial.print(" ");Serial.println(tape[i][1]);
        i++;
      
    }
    state = 1;
}

void loop()
{
  //tone(9,NOTE_C4,100);
  
  if(digitalRead(11)==LOW){
   
    while(!digitalRead(11)) delay(10);
    state=-1;
    
  }

  if(digitalRead(12)==LOW){
   
    while(!digitalRead(12)) delay(10);
    state=0;
    
  }

  if(state==0){
    Serial.println("Play_tape"); 
    play_tape();
    
  }
  
  if(state==1){
    
    Serial.print("P"); 
    play();
  }
    
  if(state==-1){
    
    Serial.println("\nRECORD = 1");
    record();
    
  }
  
}
