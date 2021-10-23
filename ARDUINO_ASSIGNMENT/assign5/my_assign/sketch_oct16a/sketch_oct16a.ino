#define x A0
#define y A1
#define z A2

void setup() {
  // put your setup code here, to run once:
  pinMode(x,INPUT);
  pinMode(y,INPUT);
  pinMode(z,INPUT);

  Serial.begin(9600);

  pinMode(7,INPUT_PULLUP);

}

int av_op (){

  int sum = 0;
  for(int i=0;i<20;i++){

    int op = map(av(1), -66, 66, -90, 90);
    
    sum += op;
  }

  return round(sum / 20);
    
  
    
 
  
}

int av (int inp){

    long sum=0;
    //Serial.print("av");
    switch(inp){
      case 0: 
              //Serial.print("x");
              for(int i=0;i<20;i++){ sum+=analogRead(x); }
      break;
      case 1: 
              //Serial.print("y");
              for(int i=0;i<20;i++){ sum+=analogRead(y); }
      break;
      case 2: 
              //Serial.print("z");
               for(int i=0;i<20;i++){ sum+=analogRead(z); }
      break;
    }

    return round( sum / 20 );
  
}

int  def_x = 337 
    ,def_y = 335
    ,def_z = 404
    ;

void loop() {

  delay(100);
  
  /*Serial.println(analogRead(x));
  Serial.print(' ');
  Serial.print(analogRead(y));
  Serial.print(' ');
  Serial.print(analogRead(z));
  Serial.print('\n');*/
  
  /*Serial.print(analogRead(x) - def_x);
  Serial.print(' ');
  Serial.print(analogRead(y) - def_y);
  Serial.print(' ');
  Serial.print(analogRead(z) - def_z);
  Serial.print('\n');*/
  
  /*Serial.print(analogRead(A0)-def_x);
  Serial.print(' ');
  Serial.print(av(0)-def_x);
  Serial.print(' ');*/
  
  int op = map(av(1)-def_y, -66, 66, -90, 90);
  if(op>90)
    op = 90;
  if(op<-90)
    op = -90;
  Serial.println(op);
  //Serial.println(analogRead(A1));
  //Serial.print('\n');

  if(digitalRead(7)==LOW){
    
    def_x = av(0);
    def_y = av(1);
    
    }
  
}
