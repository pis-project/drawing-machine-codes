import processing.serial.*;

int prev_mouseX, prev_mouseY;
int dX, dY;
float magn;
float inkX, inkY,prev_inkX,prev_inkY;
boolean turn=false;
boolean done;
Serial myPort;
void setup(){
  size(500,500);
  dX=dY=0;
  magn=0;
  inkX=inkY=prev_inkX=prev_inkY=250;

  frameRate(50);
  background(255);
  done = false;
  String portName = Serial.list()[1];
  myPort = new Serial(this, portName, 9600);
}

void draw(){
  strokeWeight(0.5);
  circle(inkX,inkY,0.1);
  
  strokeWeight(2);
  line(prev_inkX,prev_inkY,inkX,inkY);
  strokeWeight(0.5);
  fill(255,0,0);
  circle(inkX,inkY,0.5);
  prev_inkX=inkX;
  prev_inkY=inkY;
  magn=sqrt(pow(dX,2)+pow(dY,2));
  if(magn!=0){
    inkX=inkX+dX/magn;
    inkY=inkY+dY/magn;
  }
  /*if(mousePressed){
    strokeWeight(0.5);
    circle(mouseX, mouseY, 0.1);
    strokeWeight(2);
    line(prev_mouseX, prev_mouseY, mouseX, mouseY);
    prev_mouseX = mouseX;
    prev_mouseY = mouseY;
  }
  prev_mouseX = mouseX;
  prev_mouseY = mouseY;
  */
  if(keyPressed){
    if(key=='d') {
      saveFrame("hey.jpg");  
    }
  }
}
void serialEvent(Serial myPort){
  String input = myPort.readStringUntil('\n');
  if(input!=null){
    input=trim(input);
    if(!turn){
      dX = (int(input)-516);
      if(abs(dX)<=20) dX=0;
      turn=!turn;
    }
    else {
      dY = (int(input)-504);
      if(abs(dY)<=20) dY=0;
      turn=!turn;
    }
    println(turn, input);
  }
  
}
