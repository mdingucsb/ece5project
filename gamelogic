#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define VRX_PIN  A0 // Arduino pin connected to VRX pin
#define VRY_PIN  A1 // Arduino pin connected to VRY pin

int joyx = 0; // To store current joystick values
int joyy = 0; 
String direction = "";  // stores the direction the joystick is in
int gotapple = 0; //if an apple was eaten on this cycle
void setup() {
  Serial.begin(9600) ;
}

void loop() {
  // read analog X and Y analog values
  joyx = analogRead(VRX_PIN);
  joyy = analogRead(VRY_PIN);
  //invert y value so it makes sense
  joyy =  -1 * (yValue - 511) + 512;


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

 
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1  // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


//game over function
  void endgame {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(RED);
    display.setCursor(0, 10);
    // Display static text
    display.println("Game Over!");
    display.display(); 
}
    //restart program
  }

  std::vector<int> pos_snake; // vectors to store position of snake and apple = [0] = x, [1] = y
  std::vector<int> pos_apple;
  //pos 0 is x, pos 1 is y
  pos_snake[0] = 25;
  pos_snake[1] = 25;
  pos_apple[0] = random(1, 48);
  pos_apple[1] = random(1, 48);

  int length  // length of snake = score so no need for 2 variables 
  int screenpixels[2499]; // zeros matrix to store position of snake and borders
}


//dimensions: 50x50 (for now)
void loop() {
  // put your main code here, to run repeatedly:

  while (true) {
    //moving snake
    
    if (direction == "right") {
      pos_snake[0]]++;
    }

    if (direction == "left") {
      pos_snake[0] -= 1;
    }

    if (direction == "up") {
      pos_snake[1]++;
    }

    if (direction == "down") {
      pos_snake[1] -= 1;
    }

    //check for collision w/ walls
    if (pos_snake[0] == 0 || pos_snake[0] == 50 || pos_snake[1] == 0 || pos_snake[1] == 50) {
        endgame;
    }
    
    //check for collision w/ apple
    if (pos_snake[0] == pos_apple[0] && pos_snake[1] == pos_apple[1]) {
      //increment length and score by +1, randomize new apple position
      length++;
      score++;
      pos_apple[0] = rand(1, 48);
      pos_apple[1] = rand(1, 48);
      gotapple = 1;
    }

    //scoreboard logic:

    if (gotapple = 1) {
      scoreboard++;
      length++;
      gotapple = 0;
    }


    //render game
    //snake.render
    //apple.render
    //scoreboard.render
    //clear old snake lengths
  }
}
}
