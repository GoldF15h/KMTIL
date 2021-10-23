void setup() {
 Serial.begin(9600);
 pinMode(A0,INPUT);
}

void loop()
{
 //Sine Wave & Cosine Wave
 float i=0;
 for(i=0;i<=2;i+=0.1)
 {
    Serial.print(i);
    Serial.print(" ");
    if(i<1.0)
    Serial.print(0);
    else
    Serial.print(2);
    Serial.print(" ");
    if(i<1)
    Serial.println(2*i);
    else
    Serial.println(-2*i+4);
 
 
 delay(analogRead(A0)+1);
 }
}
