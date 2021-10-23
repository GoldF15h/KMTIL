void setup() {
  Serial.begin(115200);
  pinMode(7,OUTPUT);// show card summery
  pinMode(6,OUTPUT);// show card
  pinMode(5,OUTPUT);// show_game_result (calculate win or lose)
  pinMode(4,OUTPUT);// redraw
  pinMode(3,OUTPUT);// restart game

}

char inp = "no input";

void loop() {
//  Serial.println("inp -> " + String(inp));
  
  if ( Serial.available() > 0){
//    Serial.println("reading");
    inp = Serial.read();
//    Serial.println(inp);
  }
    
    
  if ( inp == '7'){ 
    Serial.println("7");
    digitalWrite(7,HIGH);
    delay(100);
  }else if ( inp == '6'){
    Serial.println("6");
    digitalWrite(6,HIGH);
    delay(100);
  }else if ( inp == '5'){
    Serial.println("5");
    digitalWrite(5,HIGH);
    delay(100);
  }else if ( inp == '4'){
    Serial.println("4");
    digitalWrite(4,HIGH);
    delay(100);
  }else if ( inp == '3'){
    Serial.println("3");
    digitalWrite(3,HIGH);
    delay(100);
  }
 
  digitalWrite(7,LOW);
  digitalWrite(6,LOW);
  digitalWrite(5,LOW);
  digitalWrite(4,LOW);
  digitalWrite(3,LOW);
 
}
