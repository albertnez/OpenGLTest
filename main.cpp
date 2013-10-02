#include "Game.hpp"
#include "Scene.hpp"

int main()
{
    srand(time(NULL));
	Game myGame;


    if(myGame.init()) {
		myGame.setScene(new Scene(myGame));
        myGame.run();
    }
	return 0;
}

