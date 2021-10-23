#define clkOut 13
#define dataOut 11
#define randomNumber A1
#define randomSuit A2

int suit;
int number;
String card = "";
void setup() {
  // put your setup code here, to run once:
  pinMode(clkOut,OUTPUT);
  pinMode(dataOut,OUTPUT);
  pinMode(randomNumber,INPUT);
  pinMode(randomSuit,INPUT);
  Serial.begin(500000);
 }

void loop() {
  suit = analogRead(randomSuit) % 4;
  number = (analogRead(randomNumber) % 13)+1;

  switch(suit){
    case 0:card += "00";break;
    case 1:card += "01";break;
    case 2:card += "10";break;
    case 3:card += "11";break;
  }
  
  switch(number){
    case 1:card += "0001";break;
    case 2:card += "0010";break;
    case 3:card += "0011";break;
    case 4:card += "0100";break;
    case 5:card += "0101";break;
    case 6:card += "0110";break;
    case 7:card += "0111";break;
    case 8:card += "1000";break;
    case 9:card += "1001";break;
    case 10:card += "1010";break;
    case 11:card += "1011";break;
    case 12:card += "1100";break;
    case 13:card += "1101";break;
  }
  Serial.println(card);
  for(int i = 0; i < 6; i++)
  {
   
    
    if(card[i] == '1')
      digitalWrite(dataOut,HIGH);
      
    else
      digitalWrite(dataOut,LOW);
      
   digitalWrite(clkOut,HIGH);
   delay(1);
    digitalWrite(clkOut,LOW);
    delay(1);
    
  }
  
  card = "";
  
  // put your main code here, to run repeatedly:

}
