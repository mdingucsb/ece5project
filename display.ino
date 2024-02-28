#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64 

#define OLED_MOSI 11
#define OLED_CLK 13
#define OLED_DC 9
#define OLED_CS 6
#define OLED_RESET 7

#define VRX_PIN  A0 // Arduino pin connected to VRX pin
#define VRY_PIN  A1 // Arduino pin connected to VRY pin

int xValue = 0; // To store value of the X axis
int yValue = 0; // To store value of the Y 
String direction;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

void setup() {
  Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Clear the display buffer
  display.clearDisplay();

  // Display text
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Hello, SSD1309!");
  display.display(); // Display the content in the buffer

  // Delay for visualization
  delay(1000);
}

void loop() {
  // Clear the display buffer
  display.clearDisplay();

  xValue = analogRead(VRX_PIN);
  yValue = analogRead(VRY_PIN);
  yValue =  -1 * (yValue - 511) + 512;

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

  // Draw white square around the 50x50 grid
  for (int y = (SCREEN_HEIGHT - 53); y < (SCREEN_HEIGHT - 3); y++) {
    for (int x = (SCREEN_WIDTH - 52) / 2; x < (SCREEN_WIDTH + 52) / 2; x++) {
      // Draw the border
      if (x == (SCREEN_WIDTH - 52) / 2 || x == (SCREEN_WIDTH + 51) / 2 || y == (SCREEN_HEIGHT - 53) || y == (SCREEN_HEIGHT - 4)) {
        display.drawPixel(x, y, SSD1306_WHITE);
      }
      // replace with game data
      else {
        int pixelValue = random(2); // Generate random 0 or 1
        display.drawPixel(x, y, pixelValue ? SSD1306_WHITE : SSD1306_BLACK);
      }
    }
  }
  
  // replace with game score data
  int score = random(100); // Generate a random score
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor((SCREEN_WIDTH - 8 * 9 + 20) / 2, 0); // Centered horizontally
  display.print("Score: ");
  // display.print(score);
  display.print(direction);
  
  display.display(); // Display the content in the buffer
  
  // Delay for some time before updating the display again
  delay(1000);
}
