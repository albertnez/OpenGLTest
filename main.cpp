#include "Game.hpp"

int main()
{
    srand(time(NULL));
    Game myGame;
    if(myGame.init()) {
        myGame.run();
    }
	return 0;
}

