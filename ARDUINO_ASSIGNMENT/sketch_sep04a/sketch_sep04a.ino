  unsigned long presstimeR,presstimeG,presstimeY=99999999;
   void setup() {
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
  
    pinMode(10,INPUT_PULLUP);
    pinMode(11,INPUT);
    pinMode(12,INPUT);
    
  }
  
  void loop() {
  
  //    digitalWrite(2, LOW);
  //    digitalWrite(3, LOW);
  //    digitalWrite(4, LOW);
    //GREEN
      if(digitalRead(10)==LOW and digitalRead(4)==LOW ){
        while(digitalRead(10)==LOW) delay(1);
        if(digitalRead(2)==HIGH){
         digitalWrite(2,LOW); 
        }
        else{
          presstimeG = millis();
         digitalWrite(2, HIGH);
        }
         
      }
      if(millis()-presstimeG>3000){
        digitalWrite(2,LOW);
      }
      
      //RED
      if(digitalRead(12)==HIGH){
        while(digitalRead(12)==HIGH) delay(1);
        if(digitalRead(4)==HIGH){
          digitalWrite(4,LOW);
        }
        else{
          presstimeR = millis();
         digitalWrite(4, HIGH);
        }
      }
      if(millis()-presstimeR>3000){
        digitalWrite(4,LOW);
      }
    
    //YELLOW
    
    if(digitalRead(11)==LOW and digitalRead(4)==LOW and digitalRead(2)==LOW){
     digitalWrite(3,HIGH);
       presstimeY =millis();
      
    }
      if(millis()-presstimeY>500 and millis()-presstimeY<1000 ){
        digitalWrite(3,LOW);
  }
    if(millis()-presstimeY>=1000 and millis()-presstimeY<1500){
      digitalWrite(3,HIGH); 
    }
    if(millis()-presstimeY>=1500 and millis()-presstimeY<2000){
      digitalWrite(3,LOW); 
    }
    
    }
