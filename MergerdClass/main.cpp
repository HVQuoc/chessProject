
#include "WindowState.hpp"
#include "GameManager.h"

int main()
{
    //Game game;

    // while ()
    // {
    //     // Update
    //     game.update();
    //     // Render
    //     game.render();
    // }

    GameManager game;
    game.initWindow();

    while (game.isWindowOpen()) {
        game.clearScreen();
        game.getCurrentState()->pollEvents(&game);
        game.getCurrentState()->update(&game);
        game.drawCurrentState();
        game.displayState();
    } 

}