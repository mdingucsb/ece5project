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

#define VRX_PIN A0
#define VRY_PIN A1
#define SIZE 10

int xValue = 0;    // To store value of the X axis
int yValue = 0;    // To store value of the Y
String direction;  // stores the direction the joystick is in
char score[2];

bool gotapple = 0;  //if an apple was eaten on this cycle
bool goodapple = 0;

//pos 0 is x, pos 1 is y
short pos_snake[2];
short pos_apple[2];
short z = 0;
short length = 1;  // length of snake = score so no need for 2 variables

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

struct Segment {
  short x;
  short y;
  short expiration;  // Number of cycles remaining for this segment to be drawn
};
/*
int availableMemory() {
    // Use 1024 with ATmega168
    int size = 2048;
    byte *buf;
    while ((buf = (byte *) malloc(--size)) == NULL);
        free(buf);
    return size;
}
*/


Segment snake_segments[25];  // Maximum length of the snake
void endgame() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  // Display static text
  display.println("Game Over!");
  display.display(); 
  delay(1000);
  display.clearDisplay();
  pos_snake[0] = 5;
  pos_snake[0] = 5;
  length = 1;
  delay(3000);
}

void setup() {
  Serial.begin(9600);
  pinMode(VRX_PIN, INPUT);
  pinMode(VRY_PIN, INPUT);
  display.begin();
  Serial.print("setup");

  // initial positions
  pos_snake[0] = 6;
  pos_snake[1] = 6;
  pos_apple[0] = 5;
  pos_apple[1] = 9;


  if (!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }
  
  // draw welcome screen
  display.clearDisplay();
  display.display();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Hello, welcome to    Snake!");
  display.display();
  display.clearDisplay();
  delay(500);
  display.display();
}

void loop() {
  bool screenpixels[SIZE][SIZE];  // zeros matrix to store position of snake and border
  while(true) {
  for (int x = 0; x < 10; x++) {
    for (int y = 0; y < 10; y++) {
      screenpixels[x][y] = 0;
    }
  }

  // read analog X and Y analog values
  xValue = analogRead(VRX_PIN);
  yValue = analogRead(VRY_PIN);
  yValue = -1 * (yValue - 511) + 512;
  // down is up, left is left, up is down, right is left
  if (xValue < 406 && 213 < yValue < 813 && direction != "right") {
    direction = "left";
  } else if (xValue > 606 && 213 < yValue < 813 && direction != "left") {
    direction = "right";
  } else if (yValue < 413 && 206 < xValue < 806 && direction != "up") {
    direction = "down";
  } else if (yValue > 613 && 206 < xValue < 806 && direction != "down") {
    direction = "up";
  }

  //moving snake
  if (direction == "right") {
    pos_snake[0]++;
  }

  if (direction == "left") {
    pos_snake[0]--;
  }

  if (direction == "up") {
    pos_snake[1]--;
  }

  if (direction == "down") {
    pos_snake[1]++;
  }


  //check for collision w/ walls
  //needs to be updated for new size!!
  if (pos_snake[0] == -1 || pos_snake[0] == 10 || pos_snake[1] == -1 || pos_snake[1] == 10) {
    endgame();
  }
  
  // check for self collision
  for (int i = 1; i < length; i++)
  {
    if (pos_snake[0] == snake_segments[i].x && pos_snake[1] == snake_segments[i].y)
    {
      endgame();
    }
  }

  // check for collision w/ apple
  if (pos_snake[0] == pos_apple[0] && pos_snake[1] == pos_apple[1]) {
    //increment length and score by +1, randomize new apple position
    goodapple = 0;
    pos_apple[0] = random(1, 9);
    pos_apple[1] = random(1, 9);
    while(goodapple == 0) {
      if(pos_apple[0] == pos_snake[0] && pos_apple[1] == pos_snake[1]) {
        pos_apple[0] = random(1, 9);
        pos_apple[1] = random(1, 9);
        goodapple = 0;
      }
      else {
        goodapple = 1;
      }
      gotapple = 1;
    }
  }

  //scoreboard logic:
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


//sets the pixels where the snake is
  for (int i = 0; i < length; i++) {
    screenpixels[snake_segments[i].x][snake_segments[i].y] = true;
  }
  screenpixels[pos_apple[0]][pos_apple[1]] = 1;


  // Code to draw the display
  display.clearDisplay();

  
    // Draw border around the 50x50 grid
  
  for (int y = 10; y < 52; y++) {
    for (int x = 37; x < 79; x++) {
      // Draw pixel
      if (x == 37 || x == 78|| y == 10 || y == 51) {
        display.drawPixel(x, y, SSD1306_WHITE);
      }
    }
  }
  
// sets pixels that need to be drawn on the screen, specifically the snake
  for (int x = 0; x < SIZE*4; x++) {
    for (int y = 0; y < SIZE*4; y++) {
      if (screenpixels[x/4][y/4] == true) {
        display.drawPixel(x+38, y+11, SSD1306_WHITE);
        //delayMicroseconds(100);
      }
    }
  }


  
  //score = String(length - 1);
  itoa(length - 1, score, 10);
  // Draw the scoreboard
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor((SCREEN_WIDTH - 8 * 9 + 20) / 2, 0);  // Centered horizontally
  display.print("Score: ");
  display.print(score);
  display.display();

  delay(400);  // Adjust delay as needed

  
  //Serial.print(availableMemory());
  //Serial.print("\n");
  
  
}
}
