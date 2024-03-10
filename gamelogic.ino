#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <string.h>
#include <Vector.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64 

#define OLED_MOSI 11
#define OLED_CLK 13
#define OLED_DC 9
#define OLED_CS 6
#define OLED_RESET 7

#define VRX_PIN  A0 // Arduino pin connected to VRX pin
#define VRY_PIN  A1 // Arduino pin connected to VRY pin
#define LEFT_PIN  2
#define UP_PIN 3
#define DOWN_PIN 4
#define RIGHT_PIN 5

int LEFT = 0;
int UP = 0;
int DOWN = 0;
int RIGHT = 0;
String direction; // stores the direction the joystick is in

bool gotapple = 0; //if an apple was eaten on this cycle

//pos 0 is x, pos 1 is y
short pos_snake[2];
short pos_apple[2];
short z = 0;
short length = 5; // length of snake = score so no need for 2 variables 

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
struct Segment {
  short x;
  short y;
  short expiration; // Number of cycles remaining for this segment to be drawn
};
Segment snake_segments[25]; // Maximum length of the snake

void setup() {

  Serial.begin(9600);
  pinMode(LEFT_PIN, INPUT);
  pinMode(UP_PIN, INPUT);
  pinMode(DOWN_PIN, INPUT);
  pinMode(RIGHT_PIN, INPUT);
  display.begin();

  // initial positions
  pos_snake[0] = 5;
  pos_snake[1] = 5;
  pos_apple[0] = 5;
  pos_apple[1] = 9;
  
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.display();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Hello, welcome to    Snake!");
  display.display();
  display.clearDisplay();
  delay(1500);
  display.display();
  Serial.print("hello world");

  // Draw border around the 50x50 grid
  for (int y = (SCREEN_HEIGHT - 53); y < (SCREEN_HEIGHT - 3); y++) {
    for (int x = (SCREEN_WIDTH - 52) / 2; x < (SCREEN_WIDTH + 52) / 2; x++) {
      // Draw pixel
      if (x == (SCREEN_WIDTH - 52) / 2 || x == (SCREEN_WIDTH + 51) / 2 || y == (SCREEN_HEIGHT - 53) || y == (SCREEN_HEIGHT - 4)) {
        display.drawPixel(x, y, SSD1306_WHITE);

      }
    }
  }

  //draw the scoreboard
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor((SCREEN_WIDTH - 8 * 9 + 20) / 2, 0); // Centered horizontally
  display.print("Score: ");
  //display.print(direction);
  display.display();
}

//dimensions: 50x50 (for now)
void loop() {
  //Serial.print(" test");
  // put your main code here, to run repeatedly:
  bool screenpixels[10][10]; // zeros matrix to store position of snake and borders

  // read digital values
  LEFT = 0;
  UP = 0;
  DOWN = 0;
  RIGHT = 0;

  LEFT = digitalRead(LEFT_PIN);
  UP = digitalRead(UP_PIN);
  DOWN = digitalRead(DOWN_PIN);
  RIGHT = digitalRead(RIGHT_PIN);

    if (LEFT == 1)  {
    direction = "left";
  }
  else if (UP == 1)  {
    direction = "up";
  }
  else if (DOWN == 1)  {
    direction = "down";
  }
  else if (RIGHT == 1)  {
    direction = "right";
  }
  // Serial.print("I'm not an infinite loop!");
  for (int i = 0; i < 10; i++){
    for (int j = 0; j < 10; j++)  {
      screenpixels[i][j] = 0;
    
    }
  }
  //Serial.print("Promise?");
    //moving snake
    //Serial.print("3");
    if (direction == "right") {
      pos_snake[0]++;
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
    //needs to be updated for new size!!
    if (pos_snake[0] == 0 || pos_snake[0] == 50 || pos_snake[1] == 0 || pos_snake[1] == 50) {
      endgame();
    }
    //Serial.print("5");
    // check for collision w/ apple
    if (pos_snake[0] == pos_apple[0] && pos_snake[1] == pos_apple[1]) {
      //increment length and score by +1, randomize new apple position
      Serial.print("YUM");
      //length += 1;
      pos_apple[0] = random(1, 9);
      pos_apple[1] = random(1, 9);
      //gotapple = 1;
    }

    //scoreboard logic:
    gotapple = 1;
    if (gotapple == 1) {
      length++;
      gotapple = 0;
    }

    
      for (int i = length - 1; i > 0; i--) {
        snake_segments[i] = snake_segments[i - 1];
      }
      snake_segments[0].x = pos_snake[0];
      snake_segments[0].y = pos_snake[1];
      snake_segments[0].expiration = length;
    
    
    //Serial.print("7");
     for (int i = 0; i < length; i++) {
    screenpixels[snake_segments[i].x][snake_segments[i].y] = true;
  }
     // Code to draw the display
    display.clearDisplay();


    for (int x = 0; x < 10; x++) {
      for (int y = 0; y < 10; y++) {
        if (screenpixels[x][y] == true) {
          display.drawPixel(x, y, SSD1306_WHITE);
          //delayMicroseconds(100);
        }
      }
    }
    
  //Serial.print("9");
    // Draw the apple
    display.drawPixel(pos_apple[0], pos_apple[1], SSD1306_WHITE);

    // Draw the scoreboard
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor((SCREEN_WIDTH - 8 * 9 + 20) / 2, 0); // Centered horizontally
    display.print("Score: ");
    //Serial.print("10");
    display.display();
    delay(100); // Adjust delay as needed
    //Serial.print("Failure");
    pos_snake[1] = pos_snake[1] + 1;
    
    pos_apple[0] = pos_apple[0] + random(-2, 3);
    //pos_apple[1] = pos_apple[1] + 1;
    
}

void endgame() {
  /*display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  // Display static text
  display.println("Game Over!");
  display.display(); 
  delay(1000);*/
}
// https://chat.openai.com/share/5f2291bf-cfdc-4ef8-9362-eb733d17ea70
