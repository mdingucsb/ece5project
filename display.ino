#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64 

#define OLED_MOSI 11
#define OLED_CLK 13
#define OLED_DC 9
#define OLED_CS 6
#define OLED_RESET 4

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
  
  // Draw white square around the 50x50 grid
  for (int y = (SCREEN_HEIGHT - 53); y < (SCREEN_HEIGHT - 3); y++) {
    for (int x = (SCREEN_WIDTH - 52) / 2; x < (SCREEN_WIDTH + 52) / 2; x++) {
      // Draw the border
      if (x == (SCREEN_WIDTH - 52) / 2 || x == (SCREEN_WIDTH + 51) / 2 || y == (SCREEN_HEIGHT - 53) || y == (SCREEN_HEIGHT - 4)) {
        display.drawPixel(x, y, SSD1306_WHITE);
      }
      // Draw the 50x50 grid of randomly generated 1s and 0s
      else {
        int pixelValue = random(2); // Generate random 0 or 1
        display.drawPixel(x, y, pixelValue ? SSD1306_WHITE : SSD1306_BLACK);
      }
    }
  }
  
  // Display the message "Score: x" along the top center of the screen
  int score = random(100); // Generate a random score
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor((SCREEN_WIDTH - 8 * 9 + 20) / 2, 0); // Centered horizontally
  display.print("Score: ");
  display.print(score);
  
  display.display(); // Display the content in the buffer
  
  // Delay for some time before updating the display again
  delay(1000);
}
