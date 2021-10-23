#define data_pin 11
#define clk_pin 13
#define maxvalue 9223372036854775807 
boolean canRead = true;
String tmp_data = "";
int card_count=0;
int count = 0;
int real_card = 0;
bool alreadyFirstDeal = false;
int card[3];
int dealercard[3];
unsigned long long timer = maxvalue;

int myPow(int b, int d){
  int n = 1;
  for(int i = 0; i < d; i++){
    n *= b;
  }
  return n;
}

int stringTOInt(String s){
  int n = 0;
  for(int i = 0 ; i < s.length(); i++){
     n += myPow(2, i) * (s[s.length() - 1 - i] - '0');
  }
  return n;
}

int draw_card() {

    while(tmp_data.length() < 6) {
      if(digitalRead(clk_pin) == 1 and canRead){
        canRead = false;
        tmp_data += String(digitalRead(data_pin));
        timer = millis();
      }
      else if(digitalRead(clk_pin) == 0 and !canRead){
        canRead = true;
      }
    }
    return stringTOInt(tmp_data);
}



int getDealerCard()
{
  while(tmp_data.length() < 6) {
      if(digitalRead(clk_pin) == 1 and canRead){
        canRead = false;
        tmp_data += String(digitalRead(data_pin));
        timer = millis();
      }
      else if(digitalRead(clk_pin) == 0 and !canRead){
        canRead = true;
      }
    }
    return stringTOInt(tmp_data);
}

void inGame_Dealer()
{
// open menu display
// call draw_card x2 ---> store card x2
// if reqeust more card 
// {call draw_card ----> store card} 
// else
//{wait }
  
  
}

void inGame_Player()
{
//
//  wait for card
  
}

void loop(){
  
}
