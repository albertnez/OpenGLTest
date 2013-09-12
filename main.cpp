#include "Game.hpp"

int main()
{
  Game myGame;
  if(myGame.init()) {
    myGame.run();
  }
  return 42;
}

