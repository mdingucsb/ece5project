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



short length = 0; // length of snake = score so no need for 2 variables 

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

void endgame() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  // Display static text
  display.println("Game Over!");
  display.display(); 
  delay(1000);
}

void setup() {
  pos_snake[0] = 25;
  pos_snake[1] = 25;
  pos_apple[0] = random(1, 48);
  pos_apple[1] = random(1, 48);
  Serial.begin(2000000);
  pinMode(LEFT_PIN, INPUT);
  pinMode(UP_PIN, INPUT);
  pinMode(DOWN_PIN, INPUT);
  pinMode(RIGHT_PIN, INPUT);

  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

display.clearDisplay();
display.display();
display.setTextSize(1);
display.setTextColor(SSD1306_WHITE);
display.setCursor(0, 0);
display.println(", welcome to    Snake!");
display.display();
delay(3000);
display.clearDisplay();
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
  Serial.print(" test");
  // put your main code here, to run repeatedly:
bool screenpixels[50][50]; // zeros matrix to store position of snake and borders

  // read digital values
  LEFT = 0;
  UP = 0;
  DOWN = 0;
  RIGHT = 0;
Serial.print("1");
  LEFT = digitalRead(LEFT_PIN);
  UP = digitalRead(UP_PIN);
  DOWN = digitalRead(DOWN_PIN);
  RIGHT = digitalRead(RIGHT_PIN);
Serial.print("2");
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
  Serial.print("I'm not an infinite loop!");
for (int i = 0; i < 50; i++){
  for (int j = 0; j < 50; j++)  {
    screenpixels[i][j] = 0;
  }
}
Serial.print("Promise?");
    //moving snake
    Serial.print("3");
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
Serial.print("4");
    //check for collision w/ walls
    if (pos_snake[0] == 0 || pos_snake[0] == 50 || pos_snake[1] == 0 || pos_snake[1] == 50) {
      endgame();
    }
    Serial.print("5");
    // check for collision w/ apple
    if (pos_snake[0] == pos_apple[0] && pos_snake[1] == pos_apple[1]) {
      //increment length and score by +1, randomize new apple position
      length += 1;
      pos_apple[0] = random(1, 48);
      pos_apple[1] = random(1, 48);
      gotapple = 1;
    }

    //scoreboard logic:
Serial.print("6");
    if (gotapple == 1) {
      length++;
      gotapple = 0;
    }
    
    Serial.print("7");
    screenpixels[pos_snake[0]][pos_snake[1]] = 1;
    screenpixels[5][10] = 1;
     // Code to draw the display
    display.clearDisplay();
    Serial.print("xyz");
    Serial.print("8");
    for (int y = 0; y < 50; y++) {
      for (int x = 0; x < 50; x++) {
        if (screenpixels[x][y] == 1) {
          display.drawPixel(x, y, SSD1306_WHITE);
          Serial.print(x);
          Serial.print("x");
        }
        Serial.print(y);
        Serial.print("y");
      }
    }
    
Serial.print("9");
    // Draw the apple
    display.drawPixel(pos_apple[0], pos_apple[1], SSD1306_WHITE);

    // Draw the scoreboard
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor((SCREEN_WIDTH - 8 * 9 + 20) / 2, 0); // Centered horizontally
    display.print("Score: ");
    display.print(direction);
    Serial.print("10");
    display.display();
    delay(100); // Adjust delay as needed
    Serial.print("Failure");
   // pos_snake[0] = pos_snake[0] + 1;
    
}
// https://chat.openai.com/share/5f2291bf-cfdc-4ef8-9362-eb733d17ea70
