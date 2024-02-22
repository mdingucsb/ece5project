#include <vector>


void setup() {
  // put your setup code here, to run once:

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

  while(true) {
    //moving snake
    if(joystick is up) {
      position_snake[1]++;
    }

    if(joystick is down) {
      position_snake[1] -= 1;
    }

    if(joystick is right) {
      position_snake[0]++;
    }

    if(joystick is left) {
      position_snake[0] -= 1;
    }

    //check for collision

    if(collides with wall) {
      if(position_snake[0] == 0 || position_snake[0] == 50 || position_snake[1] == 0 || position_snake[1] == 50) {
        endgame;
      }
    }

    if(position_snake[0] == position_apple[0] && position_snake[1] == position_apple[1]) {
      //increment length and score by +1, randomize new apple position
      length++
      score++
      position_apple[0] = rand(1, 48);
      position_apple[1] = rand(1, 48);
    }

    //update scoreboard logic

    if(touched apple) {
      score++;
    }
    //render board

  }
}
