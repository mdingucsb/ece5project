#define VRX_PIN  A0 // Arduino pin connected to VRX pin
#define VRY_PIN  A1 // Arduino pin connected to VRY pin

int xValue = 0; // To store value of the X axis
int yValue = 0; // To store value of the Y 
String direction;

void setup() {
  Serial.begin(9600) ;
}

void loop() {
  // read analog X and Y analog values
  xValue = analogRead(VRX_PIN);
  yValue = analogRead(VRY_PIN);
  yValue =  -1 * (yValue - 511) + 512;

  // print data to Serial Monitor on Arduino IDE
  Serial.print(" x = ");
  Serial.print(xValue);
  Serial.print(", y = ");
  Serial.println(yValue);

  // convert analog readings to direction
  if (xValue < 406 && 213 < yValue < 813)
  {
    direction = "left";
  }
  else if (xValue > 606 && 213 < yValue < 813)
  {
    direction = "right";
  }
  else if (yValue < 413 && 206 < xValue < 806)
  {
    direction = "down";
  }
  else if (yValue > 613 && 206 < xValue < 806)
  {
    direction = "up";
  }

  Serial.print("direction: ");
  Serial.print(direction);
  delay(200);
}
