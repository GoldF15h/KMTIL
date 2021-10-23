#define GoN  0
#define W8N  1
#define GoE  2
#define W8E  3
#define GoH  4
#define W8H1 5
#define W8H2 6
#define W8H3 7
#define W8H4 8

int current_state=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(3,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  pinMode(5,INPUT_PULLUP);

  pinMode(6 ,OUTPUT);
  pinMode(7 ,OUTPUT);
  pinMode(8 ,OUTPUT);
  pinMode(9 ,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);

  Serial.begin(9600);
}

struct state {

    int output;
    int wait_time;
    int next[8];
    
};
  // ไฟแดงแรก(N) R Y G ไฟแดงสอง(E) R Y G ไฟคน R G
  struct state st[9] = {
     B00110010 , 1000 ,{ GoN  , W8N  , W8N  , W8N  , GoN  , W8N  , W8N  , W8N  }  // ไฟ n ติด 0
    ,B01010010 , 500  ,{ GoE  , GoH  , GoE  , GoE  , GoN  , GoH  , GoE  , GoE  }  // ไฟ n ดับ 1
    ,B10000110 , 1000 ,{ GoE  , W8E  , GoE  , W8E  , W8E  , W8E  , W8E  , W8E  }  // ไฟ e ติด 2
    ,B10001010 , 500  ,{ GoH  , GoH  , GoE  , GoH  , GoN  , GoH  , GoN  , GoH  }  // ไฟ e ดับ 3
    ,B10010001 , 1000 ,{ GoH  , GoH  , W8H1 , W8H1 , W8H1 , W8H1 , W8H1 , W8H1 }  // ไฟ ค ติด 4
    ,B10010000 , 500  ,{ W8H2 , W8H2 , W8H2 , W8H2 , W8H2 , W8H2 , W8H2 , W8H2 }  // ไฟ ค ดับ 5
    ,B10010001 , 500  ,{ W8H3 , W8H3 , W8H3 , W8H3 , W8H3 , W8H3 , W8H3 , W8H3 }  // ไฟ ค ติด 6
    ,B10010000 , 500  ,{ W8H4 , W8H4 , W8H4 , W8H4 , W8H4 , W8H4 , W8H4 , W8H4 }  // ไฟ ค ดับ 7
    ,B10010001 , 500  ,{ GoN  , GoH  , GoE  , GoE  , GoN  , GoN  , GoN  , GoN  }  // ไฟ ค ติด 8
    };
 

void loop() {

  
  digitalWrite(6 , !( st[current_state].output & B10000000 ) );
  digitalWrite(7 , !( st[current_state].output & B01000000 ) );
  digitalWrite(8 , !( st[current_state].output & B00100000 ) );
  digitalWrite(9 , !( st[current_state].output & B00010000 ) );
  digitalWrite(10, !( st[current_state].output & B00001000 ) );
  digitalWrite(11, !( st[current_state].output & B00000100 ) );
  digitalWrite(12, !( st[current_state].output & B00000010 ) );
  digitalWrite(13, !( st[current_state].output & B00000001 ) );

  delay( st[ current_state ].wait_time );

  current_state = st[ current_state ].next[ (!digitalRead(3)*4) + (!digitalRead(4)*2) + (!digitalRead(5)*1) ];
  //Serial.print(current_state);

}
