#include <SFML/Window/Event.hpp>
#include <iostream>
#include "GameManager.h"
#include "WindowState.hpp"

MainMenu::MainMenu()
{
}

void MainMenu::pollEvents(GameManager* gameMan)
{   
    sf::Event ev;
    while (gameMan->getRenderWindow().pollEvent(ev))
    {
        if (ev.type == sf::Event::Closed)
        {
            gameMan->getRenderWindow().close();
        }else if (ev.type == sf::Event::MouseButtonPressed) {
            switch (this->currentChoice) {
            case 0:
                std::cout << "Open board to play game" << std::endl;
                gameMan->getSelectionSound().play();
                gameMan->clearScreen();
                gameMan->setState(gameMan->getGameState());
                break;
            case 1:
                std::cout << "Load game" << std::endl;
                gameMan->getSelectionSound().play();
                break;
            case 2:
                std::cout << "Setting" << std::endl;
                gameMan->getSelectionSound().play();
                gameMan->clearScreen();
                gameMan->setState(gameMan->getSettingState());
                return;
            case 3:
                std::cout << "Exit" << std::endl;
                gameMan->getSelectionSound().play();
                exit(2);
                break;
            default:
                break;
            }
        }
    }

    // live mouse
    for (int i = 0; i < this->numberOfButtons; ++i) {
        if (button[i].isMouseOver(gameMan->getRenderWindow())) {
            currentChoice = i;
            update(gameMan);
            break;
        }
        currentChoice = -1;
    }

}

void MainMenu::init(GameManager* gameMan)
{

    // Load sound effect
    sf::SoundBuffer soundBuffer;
    if (!this->soundBuffer.loadFromFile("Asset/selectionSound.wav")) {
        std::cout << "Can not load file sound effect in class MainMenu" << std::endl;
    }else {
        gameMan->getSelectionSound().setBuffer(this->soundBuffer);
    }

    // Game title
    this->currentChoice = 0;
    if (!this->font.loadFromFile("Asset/Pacifico.ttf"))
    {
    }
    this->background.setSize(sf::Vector2f(gameMan->getRenderWindow().getSize().x, 
                                          gameMan->getRenderWindow().getSize().y));
    this->bg_texture.loadFromFile("Asset/bg_image.jpg");
    this->background.setTexture(&this->bg_texture);

    this->gameTitle.setString("Chess Game");
    this->gameTitle.setFont(this->font);
    this->gameTitle.setFillColor(sf::Color::Magenta);
    this->gameTitle.setOrigin(this->gameTitle.getLocalBounds().width / 2,
                              this->gameTitle.getLocalBounds().height / 2);
    this->gameTitle.setPosition(gameMan->getRenderWindow().getSize().x / 2, 
                                gameMan->getRenderWindow().getSize().y / 2 - 100);

    // Option buttons
    button[0].setTitle("Play");
    button[1].setTitle("Game data");
    button[2].setTitle("Setting");
    button[3].setTitle("Exit");

    this->numberOfButtons = 4;
    for (int i = 0; i < numberOfButtons; ++i)
    {
        button[i].setSize(150, 30);
        button[i].setBackgroundColor(sf::Color(0, 0, 0, 0));
        button[i].setTextColor(sf::Color::White);
        button[i].setFont(this->font);
        button[i].setTextSize(20);
        button[i].setPosition(gameMan->getRenderWindow().getSize().x / 2,
                              gameMan->getRenderWindow().getSize().y / 2 - 30 + 45 * i);
    }
    
}

void MainMenu::draw(GameManager* gameMan)
{
    update(gameMan);
    gameMan->getRenderWindow().draw(this->background);
    gameMan->getRenderWindow().draw(this->gameTitle);
    for (int i = 0; i < this->numberOfButtons; ++i)
    {
        button[i].drawTo(gameMan->getRenderWindow());
    }
}

void MainMenu::update(GameManager* gameMan)
{

    for (int i = 0; i < this->numberOfButtons; ++i)
    {
        button[i].setTextSize(20);
        button[i].setTextColor(sf::Color::White);
        if (i == currentChoice)
        {
            button[i].setTextSize(25);
            button[i].setTextColor(sf::Color::Green);
        }
    }
}

/* void MainMenu::debug() {

    // solution: set the size of the rectangleShape for Button.button (i forgot :<)

    this->renderWindow.create(sf::VideoMode(640, 360), "ChessGameMenu");
    Button btn1("Button", {100, 100}, 20, sf::Color::Yellow, sf::Color::Blue);
    btn1.drawTo(renderWindow);

    while(renderWindow.isOpen()) {
        renderWindow.clear();
        processInput();
        btn1.drawTo(renderWindow);
        renderWindow.display();
    }
} */

/* void MainMenu::debugIsMouseOverOfButton()
{

    // solution: forgot to give the function
    mouse.getPostion the parameter 'window'

    this->renderWindow.create(sf::VideoMode(640, 360), "ChessGameMenu");
    Button btn1("Button", {60, 30}, 12, sf::Color::Blue, sf::Color::White);
    btn1.setPosition(100, 100);

    sf::Event ev;
    while (renderWindow.isOpen())
    {
        while (renderWindow.pollEvent(ev))
        {
            if (ev.type == sf::Event::Closed) {
                renderWindow.close();
            }

            if (ev.type == sf::Event::MouseMoved)
            {
                if (btn1.isMouseOver(renderWindow))
                {
                    std::cout << "Huhu bugs :<" << std::endl;
                }
            }

            if (ev.type == sf::Event::MouseButtonPressed) {
                std::cout << "Press ne" << std::endl;
            }
        }


        std::cout << sf::Mouse::getPosition().x << " " << sf::Mouse::getPosition().y << std::endl;

        renderWindow.clear();
        processInput();
        btn1.drawTo(renderWindow);
        renderWindow.display();
    }
} */
