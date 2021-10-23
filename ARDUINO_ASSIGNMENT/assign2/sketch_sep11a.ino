  unsigned long check_press;
  
  void setup()
  {
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);

    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);

    pinMode(11, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);

    pinMode(A3,INPUT_PULLUP);
    pinMode(A4,INPUT_PULLUP);  
    
    Serial.begin(9600);
  }

  void seven_print (int n){
    for(int i=0;i<9;i++){
    
      digitalWrite(i+2, !bitRead(n,i) );
      
    }
    
    /*for(int i=9;i>=0;i--){
      int k = bitRead(n,i);
      Serial.print( k );
      //delay(100);
      }
      Serial.print( "\n" );*/
    
  }

  void loop()
  {
    int my_print[10]= { 0,68,62,110,77,107,123,71,127,79 };
    int r = random();
    int bet = 1;
    int rand_re ;
    
    seven_print(my_print[bet]); 
    digitalWrite(13, 0); 
    digitalWrite(12, 0);
    digitalWrite(11, 0);
    
    while( digitalRead(A4)!=LOW ){
      
      if( digitalRead(A3)==LOW ){
      
        bet = bet + 1;
        if(bet == 7)
          bet = 1;
        delay(50);
        
      digitalWrite(13, 1);
      delay(100); 
      digitalWrite(12, 1);
      delay(100);
      digitalWrite(11, 1);
      delay(100);
    
    seven_print(my_print[bet]);       
      
      digitalWrite(13, 0); 
      digitalWrite(12, 0);
      digitalWrite(11, 0);
        
      }
      
    
      
      
        /*Serial.print(bet);
      Serial.print("\n");*/
    }
    delay(200);
    rand_re = random(1,7);
    /*Serial.print(rand_re);
    Serial.print("\n");*/
    check_press = millis();

    int run = 2;
    while( millis() - check_press <= 1500){

        if(run > 2)
          digitalWrite(run-1, 1);
        else
          digitalWrite(8, 1);
        digitalWrite(run, 0);
        run++;
        if(run == 9)
          run = 2;
        delay(100);
      
      if(millis() - check_press <= 500){
        digitalWrite(13, 1);
        continue;
      }
      if(millis() - check_press <= 1000){
        digitalWrite(13, 0);
        digitalWrite(12, 1);
        continue;
      }
      if(millis() - check_press <= 1500){
        digitalWrite(12, 0);
        digitalWrite(11, 1);
        continue;
      }
      
    }
    
    seven_print(0);
    
    digitalWrite(13, 0); 
    digitalWrite(12, 0);
    digitalWrite(11, 0);
    delay(500);
    
    if(bet == rand_re){
    digitalWrite(12,1);
    }
    else{
    digitalWrite(11,1);
    }

    seven_print(my_print[rand_re]);
    
    Serial.print(bet);
    Serial.print(" ");
    Serial.print(rand_re);
    Serial.print("\n");
    delay(2000);
            
  }
