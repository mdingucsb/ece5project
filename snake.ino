#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define VRX_PIN  A0 // Arduino pin connected to VRX pin
#define VRY_PIN  A1 // Arduino pin connected to VRY pin

int joyx = 0; // To store value of the X axis
int joyy = 0; // To store value of the Y axis

void setup() {
  Serial.begin(9600) ;
}

void loop() {
  // read analog X and Y analog values
  joyx = analogRead(VRX_PIN);
  joyy = analogRead(VRY_PIN);
  //invert y value so it makes sense
  joyy =  -1 * (yValue - 511) + 512;

}
/* left is -x = 0
right is +x = 1023
up is -y = 0
down is +y = 1023
center is 500 -> 450 550 */

void setup() {
  // put your setup code here, to run once:

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// read analog X and Y analog values
  xValue = analogRead(VRX_PIN);
  yValue = analogRead(VRY_PIN);
  yValue =  -1 * (yValue - 511) + 512;

  // print data to Serial Monitor on Arduino IDE
  Serial.print("x = ");
  Serial.print(xValue);
  Serial.print(", y = ");
  Serial.println(yValue);
  delay(200);
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1  // Reset pin # (or -1 if sharing Arduino reset pin)
  Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);



  void endgame {
    //draw GAME OVER
    //restart program
  }

  std::vector<int> position_snake;
  std::vector<int> position_apple;
  //pos 0 is x, pos 1 is y
  position_snake[0] = 25;
  position_snake[1] = 25;
  position_apple[0] = random(1, 48);
  position_apple[1] = random(1, 48);

  int length 
  int score
  int screenpixels[2499];
}


//dimensions: 50x50 (for now)
void loop() {
  // put your main code here, to run repeatedly:

  while (true) {
    //moving snake


    if (joystick is up) {
      position_snake[1]++;
    }

    if (joystick is down) {
      position_snake[1] -= 1;
    }

    if (joystick is right) {
      position_snake[0]++;
    }

    if (joystick is left) {
      position_snake[0] -= 1;
    }

    //check for collision

    if (collides with wall) {
      if (position_snake[0] == 0 || position_snake[0] == 50 || position_snake[1] == 0 || position_snake[1] == 50) {
        endgame;
      }
    }

    if (position_snake[0] == position_apple[0] && position_snake[1] == position_apple[1]) {
      //increment length and score by +1, randomize new apple position
      length++ score++ position_apple[0] = rand(1, 48);
      position_apple[1] = rand(1, 48);
    }

    //update scoreboard logic

    if (touched apple) {
      score++;
    }
    //render board
  }
}
