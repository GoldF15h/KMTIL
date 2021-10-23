#define pinA0 0
#define pinA1 1
#define pinA2 2
#define x A0
#define y A1
#define z A2

float buffeR[3][10];
float buffeR2[3][10];
int pin[] = {pinA0, pinA1, pinA2};
int pos[3] = {0};
int pos2[3] = {0};
//347 338 417
int pointA = 268, pointB = 405 , pointC = 403;

void setup() {
  pinMode(pinA0,INPUT);
  pinMode(pinA1,INPUT); 
  pinMode(pinA2,INPUT);
  Serial.begin(9600);
  pinMode(7, INPUT_PULLUP);
}

int av (){

  delay(10);
  long sum = 0;
  for(int i=0;i<10;i++)
    sum+=analogRead(y);
  return round(sum / 10);
  
}

int Buffer(int axis)
{
  delay(10);
  buffeR[axis][pos[axis]] = analogRead(pin[axis]);
  pos[axis] = (pos[axis] + 1) % 10;
  long sum = 0;
  for (unsigned int i = 0; i < 10; i++)
  {
    sum += buffeR[axis][i];
  }
  return round(sum / 10);
}

int Buffer2(int axis, int value)
{
  delay(10);
  buffeR2[axis][pos2[axis]] = value;
  pos2[axis] = (pos2[axis] + 1) % 10;
  long sum2 = 0;
  for (unsigned int i = 0; i < 10; i++)
  {
    sum2 += buffeR2[axis][i];
  }
  return round(sum2 / 10);
}

void loop() {
 //Serial.print(analogRead(pinA0));
 //Serial.print(" ");
 Serial.print(analogRead(pinA1));
 Serial.print(" ");
 Serial.print(Buffer(pinA1));
 Serial.print(" ");
 //Serial.println(analogRead(pinA2));
 Serial.println(av());
 //Serial.println(Buffer(pinA1)-pointA);
  int aY = map(Buffer(pinA1)-pointB, -73, 74, -90, 90);
//   if(aX<-90) aX = -90;
// else if(aX>90) aX = 90;
  if(aY<-86) aY = -90;
  else if(aY>90) aY = 90;
// if(aZ<-90) aZ = -90;
//else if(aZ>90) aZ = 90;
// if(aX>-4&&aX<3) aX = 0;
  if(aY>=-5&&aY<4) aY = 0;
// if(aZ>-4&&aZ<3) aZ = 0;
//Serial.print("Y");
//Serial.println(aY);
//Serial.println(Buffer(pinA1)-pointB );
//Serial.print(Buffer2(0, Buffer(pinA0)-pointA));
//Serial.print(" ");
//Serial.println(Buffer2(1, Buffer(pinA1)-pointB));
//Serial.print(" ");
//Serial.print(Buffer2(2, Buffer(pinA2)-pointC));
//Serial.println(" ");
  delay(100);
  if (digitalRead(7) == LOW)
  {Serial.println("reset");
   pointA = Buffer(pinA0);
   pointB = Buffer(pinA1);
   pointC = Buffer(pinA2);
  }
}
