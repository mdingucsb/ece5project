#define LEFT_PIN  2
#define UP_PIN 3
#define DOWN_PIN 4
#define RIGHT_PIN 5

int LEFT = 0;
int UP = 0;
int DOWN = 0;
int RIGHT = 0;

String direction;

void setup() {
  Serial.begin(9600);
  pinMode(LEFT_PIN, INPUT);
  pinMode(UP_PIN, INPUT);
  pinMode(DOWN_PIN, INPUT);
  pinMode(RIGHT_PIN, INPUT);
}

void loop() {
  // read digital values
  LEFT = 0;
  UP = 0;
  DOWN = 0;
  RIGHT = 0;

  LEFT = digitalRead(LEFT_PIN);
  UP = digitalRead(UP_PIN);
  DOWN = digitalRead(DOWN_PIN);
  RIGHT = digitalRead(RIGHT_PIN);

  // print data to Serial Monitor on Arduino IDE
  /*
  Serial.print(" LEFT = ");
  Serial.print(LEFT);
  Serial.print(", UP = ");
  Serial.println(UP);
  Serial.print(", DOWN = ");
  Serial.println(DOWN);
  Serial.print(", RIGHT = ");
  Serial.println(RIGHT);
  */
  

  if (LEFT == 1)
  {
    direction = "left";
  }
  else if (UP == 1)
  {
    direction = "up";
  }
  else if (DOWN == 1)
  {
    direction = "down";
  }
  else if (RIGHT == 1)
  {
    direction = "right";
  }

  Serial.print("direction2: ");
  Serial.print(direction);
  Serial.print('\n');
  delay(200);
}
