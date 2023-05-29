#include <iostream>
#include "GameManager.h"
#include <SFML/Graphics/CircleShape.hpp>

int main() {
    
    GameManager game;
    game.initWindow();

    while (game.isWindowOpen()) {
        game.clearScreen();
        game.getCurrentState()->pollEvents(&game);
        game.getCurrentState()->update(&game);
        game.drawCurrentState();
        game.displayState();
    } 

    /* sf::RenderWindow* window;
    window->create(sf::VideoMode(640, 320), "ChessGame");
    MainMenu menu;
    menu.init(window);
    while (window->isOpen()) {
        menu.pollEvents(window);
        window->clear();
        menu.draw(window);
        window->display();
    } */

    std::cout << "End program" << std::endl;
    return 0;
}


