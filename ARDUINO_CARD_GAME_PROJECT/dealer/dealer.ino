/**
 * @author Teerapong Singthong <st.teerapong@gmail.com>
 */
#include <avr/pgmspace.h>
#include <LedControl.h>

const int numDevices = 4;       // number of MAX7219s used
long scrollDelay = 0;   // adjust scrolling speed

unsigned long bufferLong [14] = {0};

/*
  pin 10 - DataIn
  pin    9 - CLK
  pin  8 - CS
  VCC - 5V
  GND - GND
*/
LedControl lc = LedControl(10, 9, 8, numDevices);

const unsigned char scrollText[] PROGMEM = {" I LOVE YOU 3000 "};
const unsigned char pok_deng_text[] PROGMEM = {"POK DENG     "};
const unsigned char start_text[] PROGMEM = {"LET'S START     "};
const unsigned char redraw_text[] PROGMEM = {"REDRAW     "};
const unsigned char final_result[] PROGMEM = {"FINAL RESULT     "};

// GLOBAL VARIABLE FOR CALCULATING
#define data_pin 12
#define clk_pin 13
#define maxvalue 9223372036854775807 
 int card[3] = {0};
  int card_number = 2;
  int card_score = 0;
  bool card_pok = false;
  bool card_three_of_a_kind = false;
  bool card_straight = false;
  bool card_royal = false;
  
  int dealer_card[3] = {0};
  int dealer_card_number = 0;
  int dealer_card_score = 0;
  bool dealer_card_pok = false;
  bool dealer_card_three_of_a_kind = false;
  bool dealer_card_straight = false;
  bool dealer_card_royal = false;
  
  bool is_draw       = false;
  bool is_game_end   = false;
  bool is_show_card  = false;
  bool is_show_card_result = false;
  bool is_redraw = false;
  bool is_start = false;
  
// FUNCCTION PROTOTYPE
bool dealer_card_score_check ();
bool card_score_check ();
void decToBinary(int);
void sort_dealer_card();
void sort_card();
void show_card_summery();
void show_card();
int  win_or_lose ();
void show_game_result(int result);
void wait_for_command();
int  game_result = 0 ;

void setup() {
  Serial.begin(115200);
  for (int x = 0; x < numDevices; x++) {
    lc.shutdown(x, false);      //The MAX72XX is in power-saving mode on startup
    lc.setIntensity(x, 15);      // Set the brightness to default value
    lc.clearDisplay(x);         // and clear the display
  }
  pinMode(7,INPUT); // show card summery
  pinMode(6,INPUT); // show card
  pinMode(5,INPUT); // show_game_result (calculate win or lose)
  pinMode(4,INPUT); // redraw
  pinMode(3,INPUT); // end game
}

void wait_for_start(){
  scrollMessage(pok_deng_text);
}

void in_game(){
  
}

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
    
    String tmp_data ="";
    bool canRead = true; 
    while(tmp_data.length() < 6) {
      if(digitalRead(clk_pin) == 1 and canRead){
        canRead = false;
        tmp_data += String(digitalRead(data_pin));
//        timer = millis();
      }
      else if(digitalRead(clk_pin) == 0 and !canRead){
        canRead = true;
      }
    }
    int op = stringTOInt(tmp_data);
    int score = op & 0b001111;
    if ( (score == 0)||(score >= 14) ){
      op &= 0b11000;
      op |= 0b00010;
    }
    return op;
      
}

int timer_draw_card() {
    Serial.println("TIMER DRAW");
    String tmp_data ="";
    bool canRead = true; 
    int draw_time = millis();
    while(tmp_data.length() < 6) {
      if( millis() - draw_time > 1000){
        Serial.println("return 0");
        return 0;
      }
      if(digitalRead(clk_pin) == 1 and canRead){
        canRead = false;
        tmp_data += String(digitalRead(data_pin));
//        timer = millis();
      }
      else if(digitalRead(clk_pin) == 0 and !canRead){
        canRead = true;
      }
    }
    return stringTOInt(tmp_data);
}




void loop() {

    for( int i = 0 ; i < 3 ; i++ ){
      card[i] = 0;
      dealer_card[i] = 0;
    }
    card_number = 0;
    card_score = 0;
    card_pok = false;
    card_three_of_a_kind = false;
    card_straight = false;
    card_royal = false;
    
    dealer_card_number = 0;
    dealer_card_score = 0;
    dealer_card_pok = false;
    dealer_card_three_of_a_kind = false;
    dealer_card_straight = false;
    dealer_card_royal = false;
    
    is_draw       = false;
    is_game_end   = false;
    is_show_card  = true;
    is_show_card_result = false;
    is_redraw = false;
    is_start = false;
  
    scrollMessage(pok_deng_text);
    lc.clearDisplay(3);
    card[0] = draw_card();
    card[1] = draw_card();
    card_number = 2;
    scrollMessage(start_text);

    while( !is_redraw && !is_game_end ){
      wait_for_command();
  
      if (is_show_card_result){
  //      Serial.println( "SHOW CARD RESULT");
        show_card_summery();
        is_show_card_result = false;
      }
  
      if ( is_show_card ){
  //      Serial.println( "SHOW CARD");
        show_card();
        is_show_card = false;
      }
    }

    if ( is_redraw ) {
      lc.clearDisplay(3);
      card[2] = draw_card();
      card_number = 3;
      is_show_card = true;
      scrollMessage(redraw_text);
    }

//    scrollMessage(final_result);
//    Serial.println("DEALER 0");
//    dealer_card[0] = draw_card();
//    Serial.println("DEALER 1");
//    dealer_card[1] = draw_card();
//    Serial.println("DEALER 2");
//    dealer_card[2] = timer_draw_card();
//    if (dealer_card[2] == 0)
//      dealer_card_number = 2;
//    else
//      dealer_card_number = 3;
//    lc.clearDisplay(3);
//    sort_card();
//    sort_dealer_card();
//    dealer_card_score_check();

    Serial.println(card[0]);
    Serial.println(card[1]);
    Serial.println(card[2]);

    scrollMessage(final_result);
    is_show_card = true;
    game_result = win_or_lose ();
    while(!is_start){
      wait_for_command();
  
      if (is_show_card_result){
  //      Serial.println( "SHOW CARD RESULT");
        show_card_summery();
        is_show_card_result = false;
      }
  
      if ( is_show_card ){
  //      Serial.println( "SHOW CARD");
        show_card();
        is_show_card = false;
      }
      
    }
    is_start = false;
    
}


void wait_for_command(){
  
  if ( digitalRead(7) == HIGH && !is_show_card_result ){
      for( int i = 0 ; i < 4 ; i++ )
        lc.clearDisplay(i);
      is_show_card = false;
      is_show_card_result = true;
      is_game_end = false;
      is_redraw = false;
      is_start = false;
      sort_card();
      card_score_check();
//      Serial.println("READ 7");
      
    }else if ( digitalRead(6) == HIGH && !is_show_card ){
      for( int i = 0 ; i < 4 ; i++ )
        lc.clearDisplay(i);
      is_show_card = true;
      is_show_card_result = false;
      is_game_end = false;
      is_redraw = false;
      is_start = false;
      sort_card();
//      erial.println("READ 6");
      
    }else if ( digitalRead(5) == HIGH && !is_game_end ){
      for( int i = 0 ; i < 4 ; i++ )
        lc.clearDisplay(i);
      is_show_card = false;
      is_show_card_result = false;
      is_game_end = true;
      is_redraw = false;
      is_start = false;
      sort_card();
      card_score_check();
//      Serial.println("READ 5");
      
    }else if ( digitalRead(4) == HIGH && !is_redraw){
      for( int i = 0 ; i < 4 ; i++ )
        lc.clearDisplay(i);
        is_show_card = false;
        is_show_card_result = false;
        is_game_end = false;
        is_redraw = true;
        is_start = false;
//      Serial.println("READ 4");

    }else if ( digitalRead(3) == HIGH && !is_game_end ){
      for( int i = 0 ; i < 4 ; i++ )
        lc.clearDisplay(i);
        is_show_card = false;
        is_show_card_result = false;
        is_game_end = false;
        is_redraw = false;
        is_start = true;
//      Serial.println("READ 4");
    }
}

void show_game_result(int result){
  int result_start_point = 0;
  switch (result){
    case -3 :
      result_start_point = 2;
      lc.setColumn( (26+result_start_point)/8 , (13-result_start_point)%8 , B00111110 ); // L
      lc.setColumn( (25+result_start_point)/8 , (14-result_start_point)%8 , B00000010 );
      lc.setColumn( (24+result_start_point)/8 , (15-result_start_point)%8 , B00000010 ); 
      lc.setColumn( (23+result_start_point)/8 , (16-result_start_point)%8 , B00000000 ); 
      lc.setColumn( (22+result_start_point)/8 , (17-result_start_point)%8 , B00111110 ); //O
      lc.setColumn( (21+result_start_point)/8 , (18-result_start_point)%8 , B00100010 ); 
      lc.setColumn( (20+result_start_point)/8 , (19-result_start_point)%8 , B00100010 ); 
      lc.setColumn( (19+result_start_point)/8 , (20-result_start_point)%8 , B00111110 );     
      lc.setColumn( (18+result_start_point)/8 , (21-result_start_point)%8 , B00000000 ); 
      lc.setColumn( (17+result_start_point)/8 , (22-result_start_point)%8 , B00111010 ); //S
      lc.setColumn( (16+result_start_point)/8 , (23-result_start_point)%8 , B00101010 );
      lc.setColumn( (15+result_start_point)/8 , (24-result_start_point)%8 , B00101110 ); 
      lc.setColumn( (14+result_start_point)/8 , (25-result_start_point)%8 , B00000000 ); 
      lc.setColumn( (13+result_start_point)/8 , (26-result_start_point)%8 , B00111110 ); // E 
      lc.setColumn( (12+result_start_point)/8 , (27-result_start_point)%8 , B00101010 ); 
      lc.setColumn( (11+result_start_point)/8 , (28-result_start_point)%8 , B00101010 ); 
      lc.setColumn( (10+result_start_point)/8 , (29-result_start_point)%8 , B00000000 ); // SPACE
      lc.setColumn( (9 +result_start_point)/8 , (30-result_start_point)%8 , B00000000 );
      lc.setColumn( (8 +result_start_point)/8 , (31-result_start_point)%8 , B00000000 ); 
      lc.setColumn( (7 +result_start_point)/8 , (32-result_start_point)%8 , B00110110 ); // X
      lc.setColumn( (6 +result_start_point)/8 , (33-result_start_point)%8 , B00001000 ); 
      lc.setColumn( (5 +result_start_point)/8 , (34-result_start_point)%8 , B00110110 ); 
      lc.setColumn( (4 +result_start_point)/8 , (35-result_start_point)%8 , B00000000 ); 
      lc.setColumn( (3 +result_start_point)/8 , (36-result_start_point)%8 , B00100010 ); // 2
      lc.setColumn( (2 +result_start_point)/8 , (37-result_start_point)%8 , B00101010 ); 
      lc.setColumn( (1 +result_start_point)/8 , (38-result_start_point)%8 , B00111110 ); 
      lc.setColumn( (0 +result_start_point)/8 , (39-result_start_point)%8 , B00000000 );
    break;
    
    case -2 :
      result_start_point = 2;
      lc.setColumn( (26+result_start_point)/8 , (13-result_start_point)%8 , B00111110 ); // L
      lc.setColumn( (25+result_start_point)/8 , (14-result_start_point)%8 , B00000010 );
      lc.setColumn( (24+result_start_point)/8 , (15-result_start_point)%8 , B00000010 ); 
      lc.setColumn( (23+result_start_point)/8 , (16-result_start_point)%8 , B00000000 ); 
      lc.setColumn( (22+result_start_point)/8 , (17-result_start_point)%8 , B00111110 ); //O
      lc.setColumn( (21+result_start_point)/8 , (18-result_start_point)%8 , B00100010 ); 
      lc.setColumn( (20+result_start_point)/8 , (19-result_start_point)%8 , B00100010 ); 
      lc.setColumn( (19+result_start_point)/8 , (20-result_start_point)%8 , B00111110 );     
      lc.setColumn( (18+result_start_point)/8 , (21-result_start_point)%8 , B00000000 ); 
      lc.setColumn( (17+result_start_point)/8 , (22-result_start_point)%8 , B00111010 ); //S
      lc.setColumn( (16+result_start_point)/8 , (23-result_start_point)%8 , B00101010 );
      lc.setColumn( (15+result_start_point)/8 , (24-result_start_point)%8 , B00101110 ); 
      lc.setColumn( (14+result_start_point)/8 , (25-result_start_point)%8 , B00000000 ); 
      lc.setColumn( (13+result_start_point)/8 , (26-result_start_point)%8 , B00111110 ); // E 
      lc.setColumn( (12+result_start_point)/8 , (27-result_start_point)%8 , B00101010 ); 
      lc.setColumn( (11+result_start_point)/8 , (28-result_start_point)%8 , B00101010 ); 
      lc.setColumn( (10+result_start_point)/8 , (29-result_start_point)%8 , B00000000 ); // SPACE
      lc.setColumn( (9 +result_start_point)/8 , (30-result_start_point)%8 , B00000000 );
      lc.setColumn( (8 +result_start_point)/8 , (31-result_start_point)%8 , B00000000 ); 
      lc.setColumn( (7 +result_start_point)/8 , (32-result_start_point)%8 , B00110110 ); // X
      lc.setColumn( (6 +result_start_point)/8 , (33-result_start_point)%8 , B00001000 ); 
      lc.setColumn( (5 +result_start_point)/8 , (34-result_start_point)%8 , B00110110 ); 
      lc.setColumn( (4 +result_start_point)/8 , (35-result_start_point)%8 , B00000000 ); 
      lc.setColumn( (3 +result_start_point)/8 , (36-result_start_point)%8 , B00101110 ); // 2
      lc.setColumn( (2 +result_start_point)/8 , (37-result_start_point)%8 , B00101010 ); 
      lc.setColumn( (1 +result_start_point)/8 , (38-result_start_point)%8 , B00111010 ); 
      lc.setColumn( (0 +result_start_point)/8 , (39-result_start_point)%8 , B00000000 );

    break;
    case -1 :
      result_start_point = 8;
      lc.setColumn( (15+result_start_point)/8 , (24-result_start_point)%8 , B00111110 ); // L
      lc.setColumn( (14+result_start_point)/8 , (25-result_start_point)%8 , B00000010 );
      lc.setColumn( (13+result_start_point)/8 , (26-result_start_point)%8 , B00000010 ); 
      lc.setColumn( (12+result_start_point)/8 , (27-result_start_point)%8 , B00000000 ); 
      lc.setColumn( (11+result_start_point)/8 , (28-result_start_point)%8 , B00111110 ); //O
      lc.setColumn( (10+result_start_point)/8 , (29-result_start_point)%8 , B00100010 ); 
      lc.setColumn( (9 +result_start_point)/8 , (30-result_start_point)%8 , B00100010 );
      lc.setColumn( (8 +result_start_point)/8 , (31-result_start_point)%8 , B00111110 );     
      lc.setColumn( (7 +result_start_point)/8 , (32-result_start_point)%8 , B00000000 ); 
      lc.setColumn( (6 +result_start_point)/8 , (33-result_start_point)%8 , B00111010 ); //S
      lc.setColumn( (5 +result_start_point)/8 , (34-result_start_point)%8 , B00101010 );
      lc.setColumn( (4 +result_start_point)/8 , (35-result_start_point)%8 , B00101110 ); 
      lc.setColumn( (3 +result_start_point)/8 , (36-result_start_point)%8 , B00000000 ); 
      lc.setColumn( (2 +result_start_point)/8 , (37-result_start_point)%8 , B00111110 ); // E 
      lc.setColumn( (1 +result_start_point)/8 , (38-result_start_point)%8 , B00101010 ); 
      lc.setColumn( (0 +result_start_point)/8 , (39-result_start_point)%8 , B00101010 ); 
      
    break;
    case 0 :
      result_start_point = 6;
      lc.setColumn( (19+result_start_point)/8 , (20-result_start_point)%8 , B00111110 ); // D
      lc.setColumn( (18+result_start_point)/8 , (21-result_start_point)%8 , B00100010 ); 
      lc.setColumn( (17+result_start_point)/8 , (22-result_start_point)%8 , B00010100 );
      lc.setColumn( (16+result_start_point)/8 , (23-result_start_point)%8 , B00001000 );
      lc.setColumn( (15+result_start_point)/8 , (24-result_start_point)%8 , B00000000 );
      lc.setColumn( (14+result_start_point)/8 , (25-result_start_point)%8 , B00111110 ); //R
      lc.setColumn( (13+result_start_point)/8 , (26-result_start_point)%8 , B00101000 );     
      lc.setColumn( (12+result_start_point)/8 , (27-result_start_point)%8 , B00101100 ); 
      lc.setColumn( (11+result_start_point)/8 , (28-result_start_point)%8 , B00010010 ); 
      lc.setColumn( (10+result_start_point)/8 , (29-result_start_point)%8 , B00000000 ); 
      lc.setColumn( (9 +result_start_point)/8 , (30-result_start_point)%8 , B00011110 ); //A
      lc.setColumn( (8 +result_start_point)/8 , (31-result_start_point)%8 , B00101000 ); 
      lc.setColumn( (7 +result_start_point)/8 , (32-result_start_point)%8 , B00101000 ); 
      lc.setColumn( (6 +result_start_point)/8 , (33-result_start_point)%8 , B00011110 ); 
      lc.setColumn( (5 +result_start_point)/8 , (34-result_start_point)%8 , B00000000 );
      lc.setColumn( (4 +result_start_point)/8 , (35-result_start_point)%8 , B00111100 ); // W
      lc.setColumn( (3 +result_start_point)/8 , (36-result_start_point)%8 , B00000010 ); 
      lc.setColumn( (2 +result_start_point)/8 , (37-result_start_point)%8 , B00011100 ); 
      lc.setColumn( (1 +result_start_point)/8 , (38-result_start_point)%8 , B00000010 ); 
      lc.setColumn( (0 +result_start_point)/8 , (39-result_start_point)%8 , B00111100 ); 
    break;
    case 1 :
      result_start_point = 9;
      lc.setColumn( (13+result_start_point)/8 , (26-result_start_point)%8 , B00111100 ); // W
      lc.setColumn( (12+result_start_point)/8 , (27-result_start_point)%8 , B00000010 ); 
      lc.setColumn( (11+result_start_point)/8 , (28-result_start_point)%8 , B00011100 ); 
      lc.setColumn( (10+result_start_point)/8 , (29-result_start_point)%8 , B00000010 ); 
      lc.setColumn( (9 +result_start_point)/8 , (30-result_start_point)%8 , B00111100 );     
      lc.setColumn( (8 +result_start_point)/8 , (31-result_start_point)%8 , B00000000 ); 
      lc.setColumn( (7 +result_start_point)/8 , (32-result_start_point)%8 , B00100010 ); // I
      lc.setColumn( (6 +result_start_point)/8 , (33-result_start_point)%8 , B00111110 );
      lc.setColumn( (5 +result_start_point)/8 , (34-result_start_point)%8 , B00100010 ); 
      lc.setColumn( (4 +result_start_point)/8 , (35-result_start_point)%8 , B00000000 ); 
      lc.setColumn( (3 +result_start_point)/8 , (36-result_start_point)%8 , B00111110 ); // N 
      lc.setColumn( (2 +result_start_point)/8 , (37-result_start_point)%8 , B00001000 ); 
      lc.setColumn( (1 +result_start_point)/8 , (38-result_start_point)%8 , B00000100 ); 
      lc.setColumn( (0 +result_start_point)/8 , (39-result_start_point)%8 , B00111110 ); 
      
    break;
    case 2 :
      result_start_point = 4;
      lc.setColumn( (23+result_start_point)/8 , (16-result_start_point)%8 , B00111100 ); // W
      lc.setColumn( (22+result_start_point)/8 , (17-result_start_point)%8 , B00000010 ); 
      lc.setColumn( (21+result_start_point)/8 , (18-result_start_point)%8 , B00011100 ); 
      lc.setColumn( (20+result_start_point)/8 , (19-result_start_point)%8 , B00000010 ); 
      lc.setColumn( (19+result_start_point)/8 , (20-result_start_point)%8 , B00111100 );     
      lc.setColumn( (18+result_start_point)/8 , (21-result_start_point)%8 , B00000000 ); 
      lc.setColumn( (17+result_start_point)/8 , (22-result_start_point)%8 , B00100010 ); // I
      lc.setColumn( (16+result_start_point)/8 , (23-result_start_point)%8 , B00111110 );
      lc.setColumn( (15+result_start_point)/8 , (24-result_start_point)%8 , B00100010 ); 
      lc.setColumn( (14+result_start_point)/8 , (25-result_start_point)%8 , B00000000 ); 
      lc.setColumn( (13+result_start_point)/8 , (26-result_start_point)%8 , B00111110 ); // N 
      lc.setColumn( (12+result_start_point)/8 , (27-result_start_point)%8 , B00001000 ); 
      lc.setColumn( (11+result_start_point)/8 , (28-result_start_point)%8 , B00000100 ); 
      lc.setColumn( (10+result_start_point)/8 , (29-result_start_point)%8 , B00111110 ); // SPACE
      lc.setColumn( (9 +result_start_point)/8 , (30-result_start_point)%8 , B00000000 );
      lc.setColumn( (8 +result_start_point)/8 , (31-result_start_point)%8 , B00000000 ); 
      lc.setColumn( (7 +result_start_point)/8 , (32-result_start_point)%8 , B00000000 ); 
      lc.setColumn( (6 +result_start_point)/8 , (33-result_start_point)%8 , B00110110 ); // X
      lc.setColumn( (5 +result_start_point)/8 , (34-result_start_point)%8 , B00001000 ); 
      lc.setColumn( (4 +result_start_point)/8 , (35-result_start_point)%8 , B00110110 ); 
      lc.setColumn( (3 +result_start_point)/8 , (36-result_start_point)%8 , B00000000 ); 
      lc.setColumn( (2 +result_start_point)/8 , (37-result_start_point)%8 , B00101110 ); // 2
      lc.setColumn( (1 +result_start_point)/8 , (38-result_start_point)%8 , B00101010 ); 
      lc.setColumn( (0 +result_start_point)/8 , (39-result_start_point)%8 , B00111010 );
    break;

    case 3:
      result_start_point = 4;
      lc.setColumn( (23+result_start_point)/8 , (16-result_start_point)%8 , B00111100 ); // W
      lc.setColumn( (22+result_start_point)/8 , (17-result_start_point)%8 , B00000010 ); 
      lc.setColumn( (21+result_start_point)/8 , (18-result_start_point)%8 , B00011100 ); 
      lc.setColumn( (20+result_start_point)/8 , (19-result_start_point)%8 , B00000010 ); 
      lc.setColumn( (19+result_start_point)/8 , (20-result_start_point)%8 , B00111100 );     
      lc.setColumn( (18+result_start_point)/8 , (21-result_start_point)%8 , B00000000 ); 
      lc.setColumn( (17+result_start_point)/8 , (22-result_start_point)%8 , B00100010 ); // I
      lc.setColumn( (16+result_start_point)/8 , (23-result_start_point)%8 , B00111110 );
      lc.setColumn( (15+result_start_point)/8 , (24-result_start_point)%8 , B00100010 ); 
      lc.setColumn( (14+result_start_point)/8 , (25-result_start_point)%8 , B00000000 ); 
      lc.setColumn( (13+result_start_point)/8 , (26-result_start_point)%8 , B00111110 ); // N 
      lc.setColumn( (12+result_start_point)/8 , (27-result_start_point)%8 , B00001000 ); 
      lc.setColumn( (11+result_start_point)/8 , (28-result_start_point)%8 , B00000100 ); 
      lc.setColumn( (10+result_start_point)/8 , (29-result_start_point)%8 , B00111110 ); // SPACE
      lc.setColumn( (9 +result_start_point)/8 , (30-result_start_point)%8 , B00000000 );
      lc.setColumn( (8 +result_start_point)/8 , (31-result_start_point)%8 , B00000000 ); 
      lc.setColumn( (7 +result_start_point)/8 , (32-result_start_point)%8 , B00000000 ); 
      lc.setColumn( (6 +result_start_point)/8 , (33-result_start_point)%8 , B00110110 ); // X
      lc.setColumn( (5 +result_start_point)/8 , (34-result_start_point)%8 , B00001000 ); 
      lc.setColumn( (4 +result_start_point)/8 , (35-result_start_point)%8 , B00110110 ); 
      lc.setColumn( (3 +result_start_point)/8 , (36-result_start_point)%8 , B00000000 ); 
      lc.setColumn( (2 +result_start_point)/8 , (37-result_start_point)%8 , B00100010 ); // 3
      lc.setColumn( (1 +result_start_point)/8 , (38-result_start_point)%8 , B00101010 ); 
      lc.setColumn( (0 +result_start_point)/8 , (39-result_start_point)%8 , B00111110 );
    break;
  }

}

int win_or_lose (){ // -3 LOSE_X3 -2 LOSE_X2 -1 LOSE 0 DRAW 1 WIN 2 WIN_X2 3 WIN_X3
  
  if ( dealer_card_three_of_a_kind || dealer_card_straight || dealer_card_royal ){
      if ( card_three_of_a_kind || card_straight || card_royal ){
        return 0;
      }else{
        if ( dealer_card_pok ){
          if( dealer_card_number == 2)
            return -2;
          if( dealer_card_number == 3)
            return -3;   
        }else
          return -1;
      }
  }

  if ( card_three_of_a_kind || card_straight || card_royal ){
    if ( dealer_card_three_of_a_kind || dealer_card_straight || dealer_card_royal ){
      return 0;
    }else{
      if ( card_pok ){
        if( card_number == 2 )
          return 2;
        if( card_number == 3 )
          return 3;
      }else
      return 1;
    }
  }
  
  if ( card_score%10 > dealer_card_score%10 ){
    if ( card_pok ){
      if ( card_number == 2 ){
        return 2;
      }
      if ( card_number == 3 ){
        return 3;
      }
    }else{
      return 1;
    }
  }

  if ( card_score%10 == dealer_card_score%10 )
    return 0;

  if ( card_score%10 < dealer_card_score%10 ){
   if ( dealer_card_pok ){
      if( dealer_card_number == 2)
        return -2;
      if( dealer_card_number == 3)
        return -3;   
    }else
      return -1;
  }
  
}

void show_card(){
  int dok_start_point = 0 ;
  int number_start_point = 0;
  int number = 0;
  int dok = 0;
    
  for ( int i = 0 ; i < card_number ; i++ ){

    number = card[i]&0b001111;
    dok    = card[i]&0b110000;
    dok >>= 4;
    dok_start_point    = 0 + (i*11) ;
    number_start_point = 0 + (i*11) ;
//    Serial.println(dok);
    switch ( dok ){

      case 0: // จิก
        lc.setColumn( (4+dok_start_point)/8 , (35-dok_start_point)%8 , B00110000 ); 
        lc.setColumn( (3+dok_start_point)/8 , (36-dok_start_point)%8 , B11110000 ); 
        lc.setColumn( (2+dok_start_point)/8 , (37-dok_start_point)%8 , B11111000 ); 
        lc.setColumn( (1+dok_start_point)/8 , (38-dok_start_point)%8 , B11110000 ); 
        lc.setColumn( (0+dok_start_point)/8 , (39-dok_start_point)%8 , B00110000 );
      break;
      
      case 1: // ตัด
        lc.setColumn( (4+dok_start_point)/8 , (35-dok_start_point)%8 , B00100000 ); 
        lc.setColumn( (3+dok_start_point)/8 , (36-dok_start_point)%8 , B01110000 ); 
        lc.setColumn( (2+dok_start_point)/8 , (37-dok_start_point)%8 , B11111000 ); 
        lc.setColumn( (1+dok_start_point)/8 , (38-dok_start_point)%8 , B01110000 ); 
        lc.setColumn( (0+dok_start_point)/8 , (39-dok_start_point)%8 , B00100000 );
      break;
      
      case 2: // ใจ
        lc.setColumn( (4+dok_start_point)/8 , (35-dok_start_point)%8 , B01100000 ); 
        lc.setColumn( (3+dok_start_point)/8 , (36-dok_start_point)%8 , B11110000 ); 
        lc.setColumn( (2+dok_start_point)/8 , (37-dok_start_point)%8 , B01111000 ); 
        lc.setColumn( (1+dok_start_point)/8 , (38-dok_start_point)%8 , B11110000 ); 
        lc.setColumn( (0+dok_start_point)/8 , (39-dok_start_point)%8 , B01100000 );
      break;
      
      case 3: // โพธิ์
        lc.setColumn( (4+dok_start_point)/8 , (35-dok_start_point)%8 , B00110000 ); 
        lc.setColumn( (3+dok_start_point)/8 , (36-dok_start_point)%8 , B01110000 ); 
        lc.setColumn( (2+dok_start_point)/8 , (37-dok_start_point)%8 , B11111000 ); 
        lc.setColumn( (1+dok_start_point)/8 , (38-dok_start_point)%8 , B01110000 ); 
        lc.setColumn( (0+dok_start_point)/8 , (39-dok_start_point)%8 , B00110000 );
      break;
  
    }






    switch( number ){

      case 1 :
        lc.setColumn( (9+number_start_point)/8 , (30-number_start_point)%8 , B00000000 );
        lc.setColumn( (8+number_start_point)/8 , (31-number_start_point)%8 , B00000000 );
        lc.setColumn( (7+number_start_point)/8 , (32-number_start_point)%8 , B00001111 );
        lc.setColumn( (6+number_start_point)/8 , (33-number_start_point)%8 , B00010100 ); 
        lc.setColumn( (5+number_start_point)/8 , (34-number_start_point)%8 , B00001111 );  
      break;
      
      case 2 :
        lc.setColumn( (9+number_start_point)/8 , (30-number_start_point)%8 , B00000000 );
        lc.setColumn( (8+number_start_point)/8 , (31-number_start_point)%8 , B00000000 );
        lc.setColumn( (7+number_start_point)/8 , (32-number_start_point)%8 , B00001001 );
        lc.setColumn( (6+number_start_point)/8 , (33-number_start_point)%8 , B00010011 ); 
        lc.setColumn( (5+number_start_point)/8 , (34-number_start_point)%8 , B00001101 );
      break;
      
      case 3 :
        lc.setColumn( (9+number_start_point)/8 , (30-number_start_point)%8 , B00000000 );
        lc.setColumn( (8+number_start_point)/8 , (31-number_start_point)%8 , B00000000 );
        lc.setColumn( (7+number_start_point)/8 , (32-number_start_point)%8 , B00010001 );
        lc.setColumn( (6+number_start_point)/8 , (33-number_start_point)%8 , B00010101 ); 
        lc.setColumn( (5+number_start_point)/8 , (34-number_start_point)%8 , B00001010 );
      break;
      
      case 4 :
        lc.setColumn( (9+number_start_point)/8 , (30-number_start_point)%8 , B00000000 );
        lc.setColumn( (8+number_start_point)/8 , (31-number_start_point)%8 , B00000000 );
        lc.setColumn( (7+number_start_point)/8 , (32-number_start_point)%8 , B00011100 );
        lc.setColumn( (6+number_start_point)/8 , (33-number_start_point)%8 , B00000100 ); 
        lc.setColumn( (5+number_start_point)/8 , (34-number_start_point)%8 , B00011111 );
      break;
      
      case 5 :
        lc.setColumn( (9+number_start_point)/8 , (30-number_start_point)%8 , B00000000 );
        lc.setColumn( (8+number_start_point)/8 , (31-number_start_point)%8 , B00000000 );
        lc.setColumn( (7+number_start_point)/8 , (32-number_start_point)%8 , B00011101 );
        lc.setColumn( (6+number_start_point)/8 , (33-number_start_point)%8 , B00010101 ); 
        lc.setColumn( (5+number_start_point)/8 , (34-number_start_point)%8 , B00010111 );
      break;
      
      case 6 :
        lc.setColumn( (9+number_start_point)/8 , (30-number_start_point)%8 , B00000000 );
        lc.setColumn( (8+number_start_point)/8 , (31-number_start_point)%8 , B00000000 );
        lc.setColumn( (7+number_start_point)/8 , (32-number_start_point)%8 , B00011111 );
        lc.setColumn( (6+number_start_point)/8 , (33-number_start_point)%8 , B00010101 ); 
        lc.setColumn( (5+number_start_point)/8 , (34-number_start_point)%8 , B00010111 );
      break;

      case 7 :   
        lc.setColumn( (9+number_start_point)/8 , (30-number_start_point)%8 , B00000000 );
        lc.setColumn( (8+number_start_point)/8 , (31-number_start_point)%8 , B00000000 );
        lc.setColumn( (7+number_start_point)/8 , (32-number_start_point)%8 , B00010000 );
        lc.setColumn( (6+number_start_point)/8 , (33-number_start_point)%8 , B00010000 ); 
        lc.setColumn( (5+number_start_point)/8 , (34-number_start_point)%8 , B00011111 );
      break;
      
      case 8 :
        lc.setColumn( (9+number_start_point)/8 , (30-number_start_point)%8 , B00000000 );
        lc.setColumn( (8+number_start_point)/8 , (31-number_start_point)%8 , B00000000 );
        lc.setColumn( (7+number_start_point)/8 , (32-number_start_point)%8 , B00011111 );
        lc.setColumn( (6+number_start_point)/8 , (33-number_start_point)%8 , B00010101 ); 
        lc.setColumn( (5+number_start_point)/8 , (34-number_start_point)%8 , B00011111 );
      break;
      
      case 9 :
        lc.setColumn( (9+number_start_point)/8 , (30-number_start_point)%8 , B00000000 );
        lc.setColumn( (8+number_start_point)/8 , (31-number_start_point)%8 , B00000000 );
        lc.setColumn( (7+number_start_point)/8 , (32-number_start_point)%8 , B00011101 );
        lc.setColumn( (6+number_start_point)/8 , (33-number_start_point)%8 , B00010101 ); 
        lc.setColumn( (5+number_start_point)/8 , (34-number_start_point)%8 , B00011111 );
      break;
      
      case 10 :
        lc.setColumn( (9+number_start_point)/8 , (30-number_start_point)%8 , B00011111 );
        lc.setColumn( (8+number_start_point)/8 , (31-number_start_point)%8 , B00000000 );
        lc.setColumn( (7+number_start_point)/8 , (32-number_start_point)%8 , B00011111 );
        lc.setColumn( (6+number_start_point)/8 , (33-number_start_point)%8 , B00010001 ); 
        lc.setColumn( (5+number_start_point)/8 , (34-number_start_point)%8 , B00011111 );
      break;
      
      case 11 :
        lc.setColumn( (9+number_start_point)/8 , (30-number_start_point)%8 , B00000010 );
        lc.setColumn( (8+number_start_point)/8 , (31-number_start_point)%8 , B00010001 );
        lc.setColumn( (7+number_start_point)/8 , (32-number_start_point)%8 , B00011111 );
        lc.setColumn( (6+number_start_point)/8 , (33-number_start_point)%8 , B00010000 ); 
        lc.setColumn( (5+number_start_point)/8 , (34-number_start_point)%8 , B00000000 );
      break;
      
      case 12 :
        lc.setColumn( (9+number_start_point)/8 , (30-number_start_point)%8 , B00000000 );
        lc.setColumn( (8+number_start_point)/8 , (31-number_start_point)%8 , B00111110 );
        lc.setColumn( (7+number_start_point)/8 , (32-number_start_point)%8 , B00100010 );
        lc.setColumn( (6+number_start_point)/8 , (33-number_start_point)%8 , B00111110 ); 
        lc.setColumn( (5+number_start_point)/8 , (34-number_start_point)%8 , B00000001 );
      break;
      
      case 13 :
        lc.setColumn( (9+number_start_point)/8 , (30-number_start_point)%8 , B00000000 );
        lc.setColumn( (8+number_start_point)/8 , (31-number_start_point)%8 , B00111111 );
        lc.setColumn( (7+number_start_point)/8 , (32-number_start_point)%8 , B00001100 );
        lc.setColumn( (6+number_start_point)/8 , (33-number_start_point)%8 , B00010010 ); 
        lc.setColumn( (5+number_start_point)/8 , (34-number_start_point)%8 , B00100001 );
      break;
      
    }
    
  }
}

void show_card_summery(){
//  Serial.println("in show");
  int score_start_point = 2;
  int pok_start_point = 13;
  int kind_start_point = 22;
  
  for ( int i = 0 ; i < card_number ; i++){
    
    int number = card_score%10;

    if ( card_three_of_a_kind ){// DISPLAY KIND OF CARD
        lc.setColumn( (7+kind_start_point)/8 , (32-kind_start_point)%8 , B00000000 );
        lc.setColumn( (6+kind_start_point)/8 , (33-kind_start_point)%8 , B00000000 ); 
        lc.setColumn( (5+kind_start_point)/8 , (34-kind_start_point)%8 , B01000000 ); 
        lc.setColumn( (4+kind_start_point)/8 , (35-kind_start_point)%8 , B01000000 ); 
        lc.setColumn( (3+kind_start_point)/8 , (36-kind_start_point)%8 , B01111110 ); 
        lc.setColumn( (2+kind_start_point)/8 , (37-kind_start_point)%8 , B01000000 ); 
        lc.setColumn( (1+kind_start_point)/8 , (38-kind_start_point)%8 , B01000000 ); 
        lc.setColumn( (0+kind_start_point)/8 , (39-kind_start_point)%8 , B00000000 );
    }else if ( card_straight ){
        lc.setColumn( (7+kind_start_point)/8 , (32-kind_start_point)%8 , B00000000 );
        lc.setColumn( (6+kind_start_point)/8 , (33-kind_start_point)%8 , B00000000 ); 
        lc.setColumn( (5+kind_start_point)/8 , (34-kind_start_point)%8 , B01111110 ); 
        lc.setColumn( (4+kind_start_point)/8 , (35-kind_start_point)%8 , B01001000 ); 
        lc.setColumn( (3+kind_start_point)/8 , (36-kind_start_point)%8 , B01001100 ); 
        lc.setColumn( (2+kind_start_point)/8 , (37-kind_start_point)%8 , B00110010 ); 
        lc.setColumn( (1+kind_start_point)/8 , (38-kind_start_point)%8 , B00000000 ); 
        lc.setColumn( (0+kind_start_point)/8 , (39-kind_start_point)%8 , B00000000 );
    }else if ( card_royal ){
        lc.setColumn( (7+kind_start_point)/8 , (32-kind_start_point)%8 , B00000000 );
        lc.setColumn( (6+kind_start_point)/8 , (33-kind_start_point)%8 , B00000000 ); 
        lc.setColumn( (5+kind_start_point)/8 , (34-kind_start_point)%8 , B01111110 ); 
        lc.setColumn( (4+kind_start_point)/8 , (35-kind_start_point)%8 , B01001000 ); 
        lc.setColumn( (3+kind_start_point)/8 , (36-kind_start_point)%8 , B01001000 ); 
        lc.setColumn( (2+kind_start_point)/8 , (37-kind_start_point)%8 , B01000000 ); 
        lc.setColumn( (1+kind_start_point)/8 , (38-kind_start_point)%8 , B00000000 ); 
        lc.setColumn( (0+kind_start_point)/8 , (39-kind_start_point)%8 , B00000000 );
    }else if ( card_pok ){
        lc.setColumn( (7+kind_start_point)/8 , (32-kind_start_point)%8 , B00000000 );
        lc.setColumn( (6+kind_start_point)/8 , (33-kind_start_point)%8 , B00000000 ); 
        lc.setColumn( (5+kind_start_point)/8 , (34-kind_start_point)%8 , B01111110 ); 
        lc.setColumn( (4+kind_start_point)/8 , (35-kind_start_point)%8 , B01001000 ); 
        lc.setColumn( (3+kind_start_point)/8 , (36-kind_start_point)%8 , B01001000 ); 
        lc.setColumn( (2+kind_start_point)/8 , (37-kind_start_point)%8 , B00110000 ); 
        lc.setColumn( (1+kind_start_point)/8 , (38-kind_start_point)%8 , B00000000 ); 
        lc.setColumn( (0+kind_start_point)/8 , (39-kind_start_point)%8 , B00000000 );
    }else{
        lc.setColumn( (7+kind_start_point)/8 , (32-kind_start_point)%8 , B00000000 );
        lc.setColumn( (6+kind_start_point)/8 , (33-kind_start_point)%8 , B00000000 ); 
        lc.setColumn( (5+kind_start_point)/8 , (34-kind_start_point)%8 , B01111110 ); 
        lc.setColumn( (4+kind_start_point)/8 , (35-kind_start_point)%8 , B00010000 ); 
        lc.setColumn( (3+kind_start_point)/8 , (36-kind_start_point)%8 , B00001000 ); 
        lc.setColumn( (2+kind_start_point)/8 , (37-kind_start_point)%8 , B01111110 ); 
        lc.setColumn( (1+kind_start_point)/8 , (38-kind_start_point)%8 , B00000000 ); 
        lc.setColumn( (0+kind_start_point)/8 , (39-kind_start_point)%8 , B00000000 );
    }




    if ( card_pok ){// DISPLAY POKNUMBER
        if ( card_number == 2 ){
          lc.setColumn( (7+pok_start_point)/8 , (32-pok_start_point)%8 , B00000000 );
          lc.setColumn( (6+pok_start_point)/8 , (33-pok_start_point)%8 , B00001000 ); 
          lc.setColumn( (5+pok_start_point)/8 , (34-pok_start_point)%8 , B00011100 ); 
          lc.setColumn( (4+pok_start_point)/8 , (35-pok_start_point)%8 , B00001000 ); 
          lc.setColumn( (3+pok_start_point)/8 , (36-pok_start_point)%8 , B01100010 ); 
          lc.setColumn( (2+pok_start_point)/8 , (37-pok_start_point)%8 , B01000110 ); 
          lc.setColumn( (1+pok_start_point)/8 , (38-pok_start_point)%8 , B01001010 ); 
          lc.setColumn( (0+pok_start_point)/8 , (39-pok_start_point)%8 , B01110010 );
        }else if ( card_number == 3){         
          lc.setColumn( (7+pok_start_point)/8 , (32-pok_start_point)%8 , B00000000 );
          lc.setColumn( (6+pok_start_point)/8 , (33-pok_start_point)%8 , B00001000 ); 
          lc.setColumn( (5+pok_start_point)/8 , (34-pok_start_point)%8 , B00011100 ); 
          lc.setColumn( (4+pok_start_point)/8 , (35-pok_start_point)%8 , B00001000 ); 
          lc.setColumn( (3+pok_start_point)/8 , (36-pok_start_point)%8 , B01000010 ); 
          lc.setColumn( (2+pok_start_point)/8 , (37-pok_start_point)%8 , B01001010 ); 
          lc.setColumn( (1+pok_start_point)/8 , (38-pok_start_point)%8 , B01001010 ); 
          lc.setColumn( (0+pok_start_point)/8 , (39-pok_start_point)%8 , B01111110 );
        }
    }else{
        lc.setColumn( (7+pok_start_point)/8 , (32-pok_start_point)%8 , B00000000 );
        lc.setColumn( (6+pok_start_point)/8 , (33-pok_start_point)%8 , B00001000 ); 
        lc.setColumn( (5+pok_start_point)/8 , (34-pok_start_point)%8 , B00001000 ); 
        lc.setColumn( (4+pok_start_point)/8 , (35-pok_start_point)%8 , B00001000 ); 
        lc.setColumn( (3+pok_start_point)/8 , (36-pok_start_point)%8 , B00001000 ); 
        lc.setColumn( (2+pok_start_point)/8 , (37-pok_start_point)%8 , B00001000 ); 
        lc.setColumn( (1+pok_start_point)/8 , (38-pok_start_point)%8 , B00001000 ); 
        lc.setColumn( (0+pok_start_point)/8 , (39-pok_start_point)%8 , B00000000 );
    }



    
    switch (number){// DISPLAY THE SCORE
      
      case 0:
          lc.setColumn( (7+score_start_point)/8 , (32-score_start_point)%8 , B00000000 );
          lc.setColumn( (6+score_start_point)/8 , (33-score_start_point)%8 , B00000000 ); 
          lc.setColumn( (5+score_start_point)/8 , (34-score_start_point)%8 , B01111110 ); 
          lc.setColumn( (4+score_start_point)/8 , (35-score_start_point)%8 , B01000010 ); 
          lc.setColumn( (3+score_start_point)/8 , (36-score_start_point)%8 , B01000010 ); 
          lc.setColumn( (2+score_start_point)/8 , (37-score_start_point)%8 , B01111110 ); 
          lc.setColumn( (1+score_start_point)/8 , (38-score_start_point)%8 , B00000000 ); 
          lc.setColumn( (0+score_start_point)/8 , (39-score_start_point)%8 , B00000000 );
      break;
      
      case 1:
          lc.setColumn( (7+score_start_point)/8 , (32-score_start_point)%8 , B00000000 );
          lc.setColumn( (6+score_start_point)/8 , (33-score_start_point)%8 , B00000000 ); 
          lc.setColumn( (5+score_start_point)/8 , (34-score_start_point)%8 , B00010000 ); 
          lc.setColumn( (4+score_start_point)/8 , (35-score_start_point)%8 , B00100000 ); 
          lc.setColumn( (3+score_start_point)/8 , (36-score_start_point)%8 , B01111110 ); 
          lc.setColumn( (2+score_start_point)/8 , (37-score_start_point)%8 , B00000000 ); 
          lc.setColumn( (1+score_start_point)/8 , (38-score_start_point)%8 , B00000000 ); 
          lc.setColumn( (0+score_start_point)/8 , (39-score_start_point)%8 , B00000000 );
      break;

      case 2 : 
          lc.setColumn( (7+score_start_point)/8 , (32-score_start_point)%8 , B00000000 );
          lc.setColumn( (6+score_start_point)/8 , (33-score_start_point)%8 , B00000000 ); 
          lc.setColumn( (5+score_start_point)/8 , (34-score_start_point)%8 , B01100010 ); 
          lc.setColumn( (4+score_start_point)/8 , (35-score_start_point)%8 , B01000110 ); 
          lc.setColumn( (3+score_start_point)/8 , (36-score_start_point)%8 , B01001010 ); 
          lc.setColumn( (2+score_start_point)/8 , (37-score_start_point)%8 , B01110010 ); 
          lc.setColumn( (1+score_start_point)/8 , (38-score_start_point)%8 , B00000000 ); 
          lc.setColumn( (0+score_start_point)/8 , (39-score_start_point)%8 , B00000000 );
      break;
      
      case 3 : 
          lc.setColumn( (7+score_start_point)/8 , (32-score_start_point)%8 , B00000000 );
          lc.setColumn( (6+score_start_point)/8 , (33-score_start_point)%8 , B00000000 ); 
          lc.setColumn( (5+score_start_point)/8 , (34-score_start_point)%8 , B01000010 ); 
          lc.setColumn( (4+score_start_point)/8 , (35-score_start_point)%8 , B01001010 ); 
          lc.setColumn( (3+score_start_point)/8 , (36-score_start_point)%8 , B01001010 ); 
          lc.setColumn( (2+score_start_point)/8 , (37-score_start_point)%8 , B01111110 ); 
          lc.setColumn( (1+score_start_point)/8 , (38-score_start_point)%8 , B00000000 ); 
          lc.setColumn( (0+score_start_point)/8 , (39-score_start_point)%8 , B00000000 );
      break;
      
      case 4 : 
          lc.setColumn( (7+score_start_point)/8 , (32-score_start_point)%8 , B00000000 );
          lc.setColumn( (6+score_start_point)/8 , (33-score_start_point)%8 , B00000000 ); 
          lc.setColumn( (5+score_start_point)/8 , (34-score_start_point)%8 , B01111000 ); 
          lc.setColumn( (4+score_start_point)/8 , (35-score_start_point)%8 , B00001000 ); 
          lc.setColumn( (3+score_start_point)/8 , (36-score_start_point)%8 , B01111110 ); 
          lc.setColumn( (2+score_start_point)/8 , (37-score_start_point)%8 , B00001000 ); 
          lc.setColumn( (1+score_start_point)/8 , (38-score_start_point)%8 , B00000000 ); 
          lc.setColumn( (0+score_start_point)/8 , (39-score_start_point)%8 , B00000000 );
      break;
      
      case 5 : 
          lc.setColumn( (7+score_start_point)/8 , (32-score_start_point)%8 , B00000000 );
          lc.setColumn( (6+score_start_point)/8 , (33-score_start_point)%8 , B00000000 ); 
          lc.setColumn( (5+score_start_point)/8 , (34-score_start_point)%8 , B01111010 ); 
          lc.setColumn( (4+score_start_point)/8 , (35-score_start_point)%8 , B01001010 ); 
          lc.setColumn( (3+score_start_point)/8 , (36-score_start_point)%8 , B01001010 ); 
          lc.setColumn( (2+score_start_point)/8 , (37-score_start_point)%8 , B01001110 ); 
          lc.setColumn( (1+score_start_point)/8 , (38-score_start_point)%8 , B00000000 ); 
          lc.setColumn( (0+score_start_point)/8 , (39-score_start_point)%8 , B00000000 );
      break;
      
      case 6 : 
          lc.setColumn( (7+score_start_point)/8 , (32-score_start_point)%8 , B00000000 );
          lc.setColumn( (6+score_start_point)/8 , (33-score_start_point)%8 , B00000000 ); 
          lc.setColumn( (5+score_start_point)/8 , (34-score_start_point)%8 , B01111110 ); 
          lc.setColumn( (4+score_start_point)/8 , (35-score_start_point)%8 , B01001010 ); 
          lc.setColumn( (3+score_start_point)/8 , (36-score_start_point)%8 , B01001010 ); 
          lc.setColumn( (2+score_start_point)/8 , (37-score_start_point)%8 , B01001110 ); 
          lc.setColumn( (1+score_start_point)/8 , (38-score_start_point)%8 , B00000000 ); 
          lc.setColumn( (0+score_start_point)/8 , (39-score_start_point)%8 , B00000000 );
      break;
      
      case 7 : 
          lc.setColumn( (7+score_start_point)/8 , (32-score_start_point)%8 , B00000000 );
          lc.setColumn( (6+score_start_point)/8 , (33-score_start_point)%8 , B00000000 ); 
          lc.setColumn( (5+score_start_point)/8 , (34-score_start_point)%8 , B01100000 ); 
          lc.setColumn( (4+score_start_point)/8 , (35-score_start_point)%8 , B01001110 ); 
          lc.setColumn( (3+score_start_point)/8 , (36-score_start_point)%8 , B01010000 ); 
          lc.setColumn( (2+score_start_point)/8 , (37-score_start_point)%8 , B01100000 ); 
          lc.setColumn( (1+score_start_point)/8 , (38-score_start_point)%8 , B00000000 ); 
          lc.setColumn( (0+score_start_point)/8 , (39-score_start_point)%8 , B00000000 );
      break;

      case 8 : 
          lc.setColumn( (7+score_start_point)/8 , (32-score_start_point)%8 , B00000000 );
          lc.setColumn( (6+score_start_point)/8 , (33-score_start_point)%8 , B00000000 ); 
          lc.setColumn( (5+score_start_point)/8 , (34-score_start_point)%8 , B01111110 ); 
          lc.setColumn( (4+score_start_point)/8 , (35-score_start_point)%8 , B01001010 ); 
          lc.setColumn( (3+score_start_point)/8 , (36-score_start_point)%8 , B01001010); 
          lc.setColumn( (2+score_start_point)/8 , (37-score_start_point)%8 , B01111110 ); 
          lc.setColumn( (1+score_start_point)/8 , (38-score_start_point)%8 , B00000000 ); 
          lc.setColumn( (0+score_start_point)/8 , (39-score_start_point)%8 , B00000000 );
      break;

      case 9 : 
          lc.setColumn( (7+score_start_point)/8 , (32-score_start_point)%8 , B00000000 );
          lc.setColumn( (6+score_start_point)/8 , (33-score_start_point)%8 , B00000000 ); 
          lc.setColumn( (5+score_start_point)/8 , (34-score_start_point)%8 , B01111010 ); 
          lc.setColumn( (4+score_start_point)/8 , (35-score_start_point)%8 , B01001010 ); 
          lc.setColumn( (3+score_start_point)/8 , (36-score_start_point)%8 , B01001010); 
          lc.setColumn( (2+score_start_point)/8 , (37-score_start_point)%8 , B01111110 ); 
          lc.setColumn( (1+score_start_point)/8 , (38-score_start_point)%8 , B00000000 ); 
          lc.setColumn( (0+score_start_point)/8 , (39-score_start_point)%8 , B00000000 );
      break;
    }
    
  }
  
}

void sort_card(){
  
  for( int i = 0 ; i < card_number ; i ++ ){
    for( int j = i ; j < card_number ; j++ ){
      if ( card[i] > card[j]){
        int tmp = card[i];
        card[i] = card[j];
        card[j] = tmp;
      }
    }
  }
  
}

void sort_dealer_card(){
  
  for( int i = 0 ; i < dealer_card_number ; i ++ ){
    for( int j = i ; j < dealer_card_number ; j++ ){
      if ( dealer_card[i] > dealer_card[j]){
        int tmp = dealer_card[i];
        dealer_card[i] = dealer_card[j];
        dealer_card[j] = tmp;
      }
    }
  }
  
}


bool card_score_check (){
//    cout<<"PLAYER CHECK\n";
    int tmp_score = 0; 
    if ( card_number > 0 ){

        for( int i = 0 ; i < card_number ; i++ ){ // COUNT THE SCORE'
            if ( (0b001111&card[i]) < 10 )
              tmp_score += (0b001111&card[i]);
        }

        if ( card_number == 2 ){  // IF IT'S TWO CARD
            if( (card[0]&0b110000) == (card[1]&0b110000) ){
                card_pok = true;
            }else
                card_pok = false;

        }else if ( card_number == 3 ){ // IF TI'S THREE CARD

            for ( int i = 0 ; i < 3 ; i ++ ){ // SORT WITH BUBBLE SORT
                for (int j = i ; j < 3 ; j ++){
                    if ( card[i] > card[j]  ){
                        int tmp = card[i];
                        card[i] = card[j];
                        card[j] = tmp;
                    }
                }
            }

            if ( (card[0]&0b001111) == (card[1]&0b001111) && (card[1]&0b001111) == (card[2]&0b001111) ){ // FIND THE THREE OF A KIND
                card_three_of_a_kind = true;
            }else
                card_three_of_a_kind = false;

            if ( ( card[0] + 1 == card[1] && card[1] + 1 == card[2] ) ){ // FIND THE STRIGHT
                card_straight = true;
            }else
                card_straight = false;

            if ( ( (card[0]&0b001111) > 10 ) && ( (card[1]&0b001111) > 10) && ((card[2]&0b001111) > 10 ) ){ // FIND THE ROYAL
                card_royal = true;
            }else
                card_royal = false;

            if ( ( (card[0]&0b110000) == (card[1]&0b110000) ) && ( (card[1]&0b110000) == (card[2]&0b110000) ) ){ // FIND POK
                card_pok = true;
            }else
                card_pok = false;

        }
    }
//    printf("CARD \n");for(int i = 0 ; i < 3 ; i++ )decToBinary(card[i]);
//    cout<<"SCORE -> "<<tmp_score<<endl<<"POK -> "<<card_pok<<endl<<"THREE OF A KIND -> "<<card_three_of_a_kind<<endl<<"STRIGHT -> "<<card_straight<<endl<<"ROYAL -> "<<card_royal<<endl;
  card_score = tmp_score;
}

bool dealer_card_score_check (){
//    cout<<"\n\nDEALER CHECK \n";
    int tmp_score = 0;
    if ( dealer_card_number > 0 ){

        for( int i = 0 ; i < dealer_card_number ; i++ ){ // COUNT THE SCORE
            if( (0b001111&dealer_card[i]) < 10 )
              tmp_score += (0b001111&dealer_card[i]);
        }

        if ( dealer_card_number == 2 ){  // IF IT'S TWO DEALER_CARD
            if( (dealer_card[0]&0b110000) == (dealer_card[1]&0b110000) ){
                dealer_card_pok = true;
            }else
                dealer_card_pok = false;

        }else if ( dealer_card_number == 3 ){ // IF TI'S THREE DEALER_CARD

            for ( int i = 0 ; i < 3 ; i ++ ){ // SORT WITH BUBBLE SORT
                for (int j = i ; j < 3 ; j ++){
                    if ( dealer_card[i] > dealer_card[j]  ){
                        int tmp = dealer_card[i];
                        dealer_card[i] = dealer_card[j];
                        dealer_card[j] = tmp;
                    }
                }
            }

            if ( (dealer_card[0]&0b001111) == (dealer_card[1]&0b001111) && (dealer_card[1]&0b001111) == (dealer_card[2]&0b001111) ){ // FIND THE THREE OF A KIND
                dealer_card_three_of_a_kind = true;
            }else
                dealer_card_three_of_a_kind = false;

            if ( ( dealer_card[0] + 1 == dealer_card[1] && dealer_card[1] + 1 == dealer_card[2] ) ){ // FIND THE STRIGHT
                dealer_card_straight = true;
            }else
                dealer_card_straight = false;

            if ( ( (dealer_card[0]&0b001111) > 10 ) && ( (dealer_card[1]&0b001111) > 10) && ((dealer_card[2]&0b001111) > 10 ) ){ // FIND THE ROYAL
                dealer_card_royal = true;
            }else
                dealer_card_royal = false;

            if ( ( (dealer_card[0]&0b110000) == (dealer_card[1]&0b110000) ) && ( (dealer_card[1]&0b110000) == (dealer_card[2]&0b110000) ) ){ // FIND POK
                dealer_card_pok = true;
            }else
                dealer_card_pok = false;

        }
    }
//    printf("DEALER_CARD \n");for(int i = 0 ; i < 3 ; i++ )decToBinary(dealer_card[i]);
//    cout<<"SCORE -> "<<tmp_score<<endl<<"POK -> "<<dealer_card_pok<<endl<<"THREE OF A KIND -> "<<dealer_card_three_of_a_kind<<endl<<"STRIGHT -> "<<dealer_card_straight<<endl<<"ROYAL -> "<<dealer_card_royal<<endl;
  dealer_card_score = tmp_score;
}



/**
 * Define Set of Characters
 */
const unsigned char font5x7 [] PROGMEM = {      // Numeric Font Matrix (Arranged as 7x font data + 1x kerning data)
  B00000000,  //Space (Char 0x20)
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  6,

  B10000000,  //!
  B10000000,
  B10000000,
  B10000000,
  B00000000,
  B00000000,
  B10000000,
  2,

  B10100000,  //"
  B10100000,
  B10100000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  4,

  B01010000,  //#
  B01010000,
  B11111000,
  B01010000,
  B11111000,
  B01010000,
  B01010000,
  6,

  B00100000,  //$
  B01111000,
  B10100000,
  B01110000,
  B00101000,
  B11110000,
  B00100000,
  6,

  B11000000,  //%
  B11001000,
  B00010000,
  B00100000,
  B01000000,
  B10011000,
  B00011000,
  6,

  B01100000,  //&
  B10010000,
  B10100000,
  B01000000,
  B10101000,
  B10010000,
  B01101000,
  6,

  B11000000,  //'
  B01000000,
  B10000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  3,

  B00100000,  //(
  B01000000,
  B10000000,
  B10000000,
  B10000000,
  B01000000,
  B00100000,
  4,

  B10000000,  //)
  B01000000,
  B00100000,
  B00100000,
  B00100000,
  B01000000,
  B10000000,
  4,

  B00000000,  //*
  B00100000,
  B10101000,
  B01110000,
  B10101000,
  B00100000,
  B00000000,
  6,

  B00000000,  //+
  B00100000,
  B00100000,
  B11111000,
  B00100000,
  B00100000,
  B00000000,
  6,

  B00000000,  //,
  B00000000,
  B00000000,
  B00000000,
  B11000000,
  B01000000,
  B10000000,
  3,

  B00000000,  //-
  B00000000,
  B11111000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  6,

  B00000000,  //.
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B11000000,
  B11000000,
  3,

  B00000000,  ///
  B00001000,
  B00010000,
  B00100000,
  B01000000,
  B10000000,
  B00000000,
  6,

  B01110000,  //0
  B10001000,
  B10011000,
  B10101000,
  B11001000,
  B10001000,
  B01110000,
  6,

  B01000000,  //1
  B11000000,
  B01000000,
  B01000000,
  B01000000,
  B01000000,
  B11100000,
  4,

  B01110000,  //2
  B10001000,
  B00001000,
  B00010000,
  B00100000,
  B01000000,
  B11111000,
  6,

  B11111000,  //3
  B00010000,
  B00100000,
  B00010000,
  B00001000,
  B10001000,
  B01110000,
  6,

  B00010000,  //4
  B00110000,
  B01010000,
  B10010000,
  B11111000,
  B00010000,
  B00010000,
  6,

  B11111000,  //5
  B10000000,
  B11110000,
  B00001000,
  B00001000,
  B10001000,
  B01110000,
  6,

  B00110000,  //6
  B01000000,
  B10000000,
  B11110000,
  B10001000,
  B10001000,
  B01110000,
  6,

  B11111000,  //7
  B10001000,
  B00001000,
  B00010000,
  B00100000,
  B00100000,
  B00100000,
  6,

  B01110000,  //8
  B10001000,
  B10001000,
  B01110000,
  B10001000,
  B10001000,
  B01110000,
  6,

  B01110000,  //9
  B10001000,
  B10001000,
  B01111000,
  B00001000,
  B00010000,
  B01100000,
  6,

  B00000000,  //:
  B11000000,
  B11000000,
  B00000000,
  B11000000,
  B11000000,
  B00000000,
  3,

  B00000000,  //;
  B11000000,
  B11000000,
  B00000000,
  B11000000,
  B01000000,
  B10000000,
  3,

  B00010000,  //<
  B00100000,
  B01000000,
  B10000000,
  B01000000,
  B00100000,
  B00010000,
  5,

  B00000000,  //=
  B00000000,
  B11111000,
  B00000000,
  B11111000,
  B00000000,
  B00000000,
  6,

  B10000000,  //>
  B01000000,
  B00100000,
  B00010000,
  B00100000,
  B01000000,
  B10000000,
  5,

  B01110000,  //?
  B10001000,
  B00001000,
  B00010000,
  B00100000,
  B00000000,
  B00100000,
  6,

  B01110000,  //@
  B10001000,
  B00001000,
  B01101000,
  B10101000,
  B10101000,
  B01110000,
  6,

  B01110000,  //A
  B10001000,
  B10001000,
  B10001000,
  B11111000,
  B10001000,
  B10001000,
  6,

  B11110000,  //B
  B10001000,
  B10001000,
  B11110000,
  B10001000,
  B10001000,
  B11110000,
  6,

  B01110000,  //C
  B10001000,
  B10000000,
  B10000000,
  B10000000,
  B10001000,
  B01110000,
  6,

  B11100000,  //D
  B10010000,
  B10001000,
  B10001000,
  B10001000,
  B10010000,
  B11100000,
  6,

  B11111000,  //E
  B10000000,
  B10000000,
  B11110000,
  B10000000,
  B10000000,
  B11111000,
  6,

  B11111000,  //F
  B10000000,
  B10000000,
  B11110000,
  B10000000,
  B10000000,
  B10000000,
  6,

  B01110000,  //G
  B10001000,
  B10000000,
  B10111000,
  B10001000,
  B10001000,
  B01111000,
  6,

  B10001000,  //H
  B10001000,
  B10001000,
  B11111000,
  B10001000,
  B10001000,
  B10001000,
  6,

  B11100000,  //I
  B01000000,
  B01000000,
  B01000000,
  B01000000,
  B01000000,
  B11100000,
  4,

  B00111000,  //J
  B00010000,
  B00010000,
  B00010000,
  B00010000,
  B10010000,
  B01100000,
  6,

  B10001000,  //K
  B10010000,
  B10100000,
  B11000000,
  B10100000,
  B10010000,
  B10001000,
  6,

  B10000000,  //L
  B10000000,
  B10000000,
  B10000000,
  B10000000,
  B10000000,
  B11111000,
  6,

  B10001000,  //M
  B11011000,
  B10101000,
  B10101000,
  B10001000,
  B10001000,
  B10001000,
  6,

  B10001000,  //N
  B10001000,
  B11001000,
  B10101000,
  B10011000,
  B10001000,
  B10001000,
  6,

  B01110000,  //O
  B10001000,
  B10001000,
  B10001000,
  B10001000,
  B10001000,
  B01110000,
  6,

  B11110000,  //P
  B10001000,
  B10001000,
  B11110000,
  B10000000,
  B10000000,
  B10000000,
  6,

  B01110000,  //Q
  B10001000,
  B10001000,
  B10001000,
  B10101000,
  B10010000,
  B01101000,
  6,

  B11110000,  //R
  B10001000,
  B10001000,
  B11110000,
  B10100000,
  B10010000,
  B10001000,
  6,

  B01111000,  //S
  B10000000,
  B10000000,
  B01110000,
  B00001000,
  B00001000,
  B11110000,
  6,

  B11111000,  //T
  B00100000,
  B00100000,
  B00100000,
  B00100000,
  B00100000,
  B00100000,
  6,

  B10001000,  //U
  B10001000,
  B10001000,
  B10001000,
  B10001000,
  B10001000,
  B01110000,
  6,

  B10001000,  //V
  B10001000,
  B10001000,
  B10001000,
  B10001000,
  B01010000,
  B00100000,
  6,

  B10001000,  //W
  B10001000,
  B10001000,
  B10101000,
  B10101000,
  B10101000,
  B01010000,
  6,

  B10001000,  //X
  B10001000,
  B01010000,
  B00100000,
  B01010000,
  B10001000,
  B10001000,
  6,

  B10001000,  //Y
  B10001000,
  B10001000,
  B01010000,
  B00100000,
  B00100000,
  B00100000,
  6,

  B11111000,  //Z
  B00001000,
  B00010000,
  B00100000,
  B01000000,
  B10000000,
  B11111000,
  6,

  B11100000,  //[
  B10000000,
  B10000000,
  B10000000,
  B10000000,
  B10000000,
  B11100000,
  4,

  B00000000,  //(Backward Slash)
  B10000000,
  B01000000,
  B00100000,
  B00010000,
  B00001000,
  B00000000,
  6,

  B11100000,  //]
  B00100000,
  B00100000,
  B00100000,
  B00100000,
  B00100000,
  B11100000,
  4,

  B00100000,  //^
  B01010000,
  B10001000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  6,

  B00000000,  //_
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B11111000,
  6,

  B10000000,  //`
  B01000000,
  B00100000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  4,

  B00000000,  //a
  B00000000,
  B01110000,
  B00001000,
  B01111000,
  B10001000,
  B01111000,
  6,

  B10000000,  //b
  B10000000,
  B10110000,
  B11001000,
  B10001000,
  B10001000,
  B11110000,
  6,

  B00000000,  //c
  B00000000,
  B01110000,
  B10001000,
  B10000000,
  B10001000,
  B01110000,
  6,

  B00001000,  //d
  B00001000,
  B01101000,
  B10011000,
  B10001000,
  B10001000,
  B01111000,
  6,

  B00000000,  //e
  B00000000,
  B01110000,
  B10001000,
  B11111000,
  B10000000,
  B01110000,
  6,

  B00110000,  //f
  B01001000,
  B01000000,
  B11100000,
  B01000000,
  B01000000,
  B01000000,
  6,

  B00000000,  //g
  B01111000,
  B10001000,
  B10001000,
  B01111000,
  B00001000,
  B01110000,
  6,

  B10000000,  //h
  B10000000,
  B10110000,
  B11001000,
  B10001000,
  B10001000,
  B10001000,
  6,

  B01000000,  //i
  B00000000,
  B11000000,
  B01000000,
  B01000000,
  B01000000,
  B11100000,
  4,

  B00010000,  //j
  B00000000,
  B00110000,
  B00010000,
  B00010000,
  B10010000,
  B01100000,
  5,

  B10000000,  //k
  B10000000,
  B10010000,
  B10100000,
  B11000000,
  B10100000,
  B10010000,
  5,

  B11000000,  //l
  B01000000,
  B01000000,
  B01000000,
  B01000000,
  B01000000,
  B11100000,
  4,

  B00000000,  //m
  B00000000,
  B11010000,
  B10101000,
  B10101000,
  B10001000,
  B10001000,
  6,

  B00000000,  //n
  B00000000,
  B10110000,
  B11001000,
  B10001000,
  B10001000,
  B10001000,
  6,

  B00000000,  //o
  B00000000,
  B01110000,
  B10001000,
  B10001000,
  B10001000,
  B01110000,
  6,

  B00000000,  //p
  B00000000,
  B11110000,
  B10001000,
  B11110000,
  B10000000,
  B10000000,
  6,

  B00000000,  //q
  B00000000,
  B01101000,
  B10011000,
  B01111000,
  B00001000,
  B00001000,
  6,

  B00000000,  //r
  B00000000,
  B10110000,
  B11001000,
  B10000000,
  B10000000,
  B10000000,
  6,

  B00000000,  //s
  B00000000,
  B01110000,
  B10000000,
  B01110000,
  B00001000,
  B11110000,
  6,

  B01000000,  //t
  B01000000,
  B11100000,
  B01000000,
  B01000000,
  B01001000,
  B00110000,
  6,

  B00000000,  //u
  B00000000,
  B10001000,
  B10001000,
  B10001000,
  B10011000,
  B01101000,
  6,

  B00000000,  //v
  B00000000,
  B10001000,
  B10001000,
  B10001000,
  B01010000,
  B00100000,
  6,

  B00000000,  //w
  B00000000,
  B10001000,
  B10101000,
  B10101000,
  B10101000,
  B01010000,
  6,

  B00000000,  //x
  B00000000,
  B10001000,
  B01010000,
  B00100000,
  B01010000,
  B10001000,
  6,

  B00000000,  //y
  B00000000,
  B10001000,
  B10001000,
  B01111000,
  B00001000,
  B01110000,
  6,

  B00000000,  //z
  B00000000,
  B11111000,
  B00010000,
  B00100000,
  B01000000,
  B11111000,
  6,

  B00100000,  //{
  B01000000,
  B01000000,
  B10000000,
  B01000000,
  B01000000,
  B00100000,
  4,

  B10000000,  //|
  B10000000,
  B10000000,
  B10000000,
  B10000000,
  B10000000,
  B10000000,
  2,

  B10000000,  //}
  B01000000,
  B01000000,
  B00100000,
  B01000000,
  B01000000,
  B10000000,
  4,

  B00000000,  //~
  B00000000,
  B00000000,
  B01101000,
  B10010000,
  B00000000,
  B00000000,
  6,

  B01100000,  // (Char 0x7F)
  B10010000,
  B10010000,
  B01100000,
  B00000000,
  B00000000,
  B00000000,
  5

};


void scrollFont() {
  for (int counter = 0x20; counter < 0x80; counter++) {
    loadBufferLong(counter);
    delay(500);
  }
}


// Scroll Message
void scrollMessage(const unsigned char * messageString) {
  int counter = 0;
  int myChar = 0;
  do {
    // read back a char
    myChar =  pgm_read_byte_near(messageString + counter);
    if (myChar != 0) {
      loadBufferLong(myChar);
    }
    counter++;
  }
  while (myChar != 0);
}

// Load character into scroll buffer
void loadBufferLong(int ascii) {
  if (ascii >= 0x20 && ascii <= 0xff) {
    for (int a = 0; a < 7; a++) {               // Loop 7 times for a 5x7 font
      unsigned long c = pgm_read_byte_near(font5x7 + ((ascii - 0x20) * 8) + a);     // Index into character table to get row data
      unsigned long x = bufferLong [a * 2];   // Load current scroll buffer
      x = x | c;                              // OR the new character onto end of current
      bufferLong [a * 2] = x;                 // Store in buffer
    }
    byte count = pgm_read_byte_near(font5x7 + ((ascii - 0x20) * 8) + 7);    // Index into character table for kerning data
    for (byte x = 0; x < count; x++) {
      rotateBufferLong();
      printBufferLong();
      delay(scrollDelay);
    }
  }
}

// Rotate the buffer
void rotateBufferLong() {
  for (int a = 0; a < 7; a++) {             // Loop 7 times for a 5x7 font
    unsigned long x = bufferLong [a * 2];   // Get low buffer entry
    byte b = bitRead(x, 31);                // Copy high order bit that gets lost in rotation
    x = x << 1;                             // Rotate left one bit
    bufferLong [a * 2] = x;                 // Store new low buffer
    x = bufferLong [a * 2 + 1];             // Get high buffer entry
    x = x << 1;                             // Rotate left one bit
    bitWrite(x, 0, b);                      // Store saved bit
    bufferLong [a * 2 + 1] = x;             // Store new high buffer
  }
}

// Display Buffer on LED matrix
void printBufferLong() {
  for (int a = 0; a < 7; a++) {             // Loop 7 times for a 5x7 font
    unsigned long x = bufferLong [a * 2 + 1]; // Get high buffer entry
    byte y = x;                             // Mask off first character
    lc.setRow(3, a, y);                     // Send row to relevent MAX7219 chip
    x = bufferLong [a * 2];                 // Get low buffer entry
    y = (x >> 24);                          // Mask off second character
    lc.setRow(2, a, y);                     // Send row to relevent MAX7219 chip
    y = (x >> 16);                          // Mask off third character
    lc.setRow(1, a, y);                     // Send row to relevent MAX7219 chip
    y = (x >> 8);                           // Mask off forth character
    lc.setRow(0, a, y);                     // Send row to relevent MAX7219 chip
  }
}
