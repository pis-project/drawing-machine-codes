/*     Simple Stepper Motor Control Exaple Code
 *      
 *  by Dejan Nedelkovski, www.HowToMechatronics.com
 *  
 */

// defines pins numbers
const int XstepPin = 3; 
const int XdirPin = 4; 
const int YstepPin = 6; 
const int YdirPin = 7;

const int XJoyPin = A0;
const int YJoyPin = A1;
const int SWPin = 2;
const int unit = 200;

int arrayX[10] = {1, 4, 2, 1, 8, 12, 50, 12, 1, 0}, arrayY[10]={20, 10, 15, 2, 0, 70, 20, 1, 90, 0};
int t=0;
int x=0,y=0,xp,yp;
float dx,dy, magn=0;

void moveX(float deltaX)
{
  if (deltaX==0);
  else{
  if(deltaX<0){
    digitalWrite(XdirPin,LOW); // Enables the motor to move in a particular direction
    //Serial.println("LOW");
  }
  else if(deltaX>0){
    digitalWrite(XdirPin,HIGH); // Enables the motor to move in a particular direction
    //Serial.println("HIGH");
  }
  //delay(5000);
  // Moves Stepper Motor
  float t = abs(deltaX)*unit;
  for(int x = 0; x < int(t); x++) {
    digitalWrite(XstepPin,HIGH); 
    delayMicroseconds(500); 
    digitalWrite(XstepPin,LOW); 
    delayMicroseconds(500); 
  }
  }
}

void moveY(float deltaY)
{
  if (deltaY==0);
  else{
  if(deltaY<0){
    digitalWrite(YdirPin,LOW); // Enables the motor to move in a particular direction
  }
  else if(deltaY>0){
    digitalWrite(YdirPin,HIGH); // Enables the motor to move in a particular direction
  }
  // Makes 200 pulses for making one full cycle rotation
  float t = abs(deltaY)*unit;
  for(int x = 0; x < int(t); x++) {
    digitalWrite(YstepPin,HIGH); 
    delayMicroseconds(500); 
    digitalWrite(YstepPin,LOW); 
    delayMicroseconds(500);
  }
  }
}


void changeX(){
  //x = arrayX[t];
  x = analogRead(XJoyPin);
}
void changeY(){
  //y = arrayY[t];
  y = analogRead(YJoyPin);
}
 
void setup() {
  // Sets the two pins as Outputs
  Serial.begin(9600);
  pinMode(XstepPin,OUTPUT); 
  pinMode(XdirPin,OUTPUT);
  pinMode(YstepPin,OUTPUT); 
  pinMode(YdirPin,OUTPUT);
  pinMode(SWPin, INPUT);
  digitalWrite(SWPin, HIGH);
}
void loop() {
  xp=x;//Previous X
  yp=y;
  //changeX();
  //changeY();
  x = analogRead(XJoyPin);
  y = analogRead(YJoyPin);
  //Serial.println(String(x)+' '+String(y));
  Serial.print(String(x)+'\n');
  Serial.print(String(y)+'\n');
  //t = t+1;
  //if(t>9) delay(10000);
  dx=x-514;
  dy=y-524;
  if(abs(dx)<=50) dx=0;
  if(abs(dy)<=50) dy=0;
  magn=sqrt(pow(dx,2)+pow(dy,2));
  if(magn!=0){
    dx=dx/magn;
    dy=dy/magn;
  }
  //Serial.println(dx, dy);
  //Serial.println(dy);
  moveX(dx); 
  moveY(dy);
  //delay(1000);
}
