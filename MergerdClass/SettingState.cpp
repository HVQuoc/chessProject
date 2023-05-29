#include "GameManager.h"
#include "WindowState.hpp"

SettingState::SettingState()
{
    changeMusicVol = 100; // per 200
    changeSoundVol = 100; // per 200
}

void SettingState::init(GameManager *gameMan)
{
    if (!this->font.loadFromFile("Asset/Pacifico.ttf"))
    {
        std::cout << "cannot load font in class setting" << std::endl;
    }

    // Title for changes
    bar1Title.setFont(this->font);
    bar2Title.setFont(this->font);
    bar1Title.setString("Music: ");
    bar2Title.setString("Sound: ");
    bar1Title.setCharacterSize(24);
    bar2Title.setCharacterSize(24);
    bar1Title.setFillColor(sf::Color(153, 98, 122, 255));
    bar2Title.setFillColor(sf::Color(153, 98, 122, 255));
    bar1Title.setOrigin(bar1Title.getLocalBounds().width/2,
                        bar1Title.getLocalBounds().height/2);
    bar2Title.setOrigin(bar2Title.getLocalBounds().width/2,
                        bar2Title.getLocalBounds().height/2);                 

    // 2 bar to change volume
    // behindBar[0].setBackgroundColor(sf::Color(255, 85, 163, 100));
    // behindBar[1].setBackgroundColor(sf::Color(255, 85, 163, 100));

    // behindBar[0].setSize(200, 10);
    // behindBar[1].setSize(200, 10);

    // int halfOfSizeWidth = behindBar[0].getSizeWidth()/2;
    // int halfOfSizeHeight = behindBar[1].getSizeHeight()/2;

    // behindBar[0].setPosition(250 + halfOfSizeWidth, 100 + halfOfSizeHeight);
    // behindBar[1].setPosition(250 + halfOfSizeWidth, 200 + halfOfSizeHeight);

    // frontBar[0].setBackgroundColor(sf::Color(255, 85, 163, 255));
    // frontBar[1].setBackgroundColor(sf::Color(255, 85, 163, 255));

    // frontBar[0].setSize(200, 10);
    // frontBar[1].setSize(200, 10);

    // frontBar[0].setPosition(250 + halfOfSizeWidth, 100 + halfOfSizeHeight);
    // frontBar[1].setPosition(250 + halfOfSizeWidth, 200 + halfOfSizeHeight);

    behindBar[0].setBackgroundColor(sf::Color(238, 129, 179, 100));
    behindBar[1].setBackgroundColor(sf::Color(238, 129, 179, 100));

    behindBar[0].setSize(200, 30);
    behindBar[1].setSize(200, 30);

    int halfOfSizeWidth = behindBar[0].getSizeWidth()/2;
    int halfOfSizeHeight = behindBar[1].getSizeHeight()/2;

    behindBar[0].setPosition(gameMan->getRenderWindow().getSize().x/2, 
                             gameMan->getRenderWindow().getSize().y/2 - halfOfSizeHeight);
    behindBar[1].setPosition(gameMan->getRenderWindow().getSize().x/2,
                             gameMan->getRenderWindow().getSize().y/2 - halfOfSizeHeight + 100);

    frontBar[0].setBackgroundColor(sf::Color(238, 129, 179, 255));
    frontBar[1].setBackgroundColor(sf::Color(238, 129, 179, 255));

    frontBar[0].setSize(200, 30);
    frontBar[1].setSize(200, 30);

    frontBar[0].setPosition(gameMan->getRenderWindow().getSize().x/2, 
                            gameMan->getRenderWindow().getSize().y/2 - halfOfSizeHeight);
    frontBar[1].setPosition(gameMan->getRenderWindow().getSize().x/2,
                            gameMan->getRenderWindow().getSize().y/2 - halfOfSizeHeight + 100);

    // set position for 2 title
    bar1Title.setPosition(gameMan->getRenderWindow().getSize().x/2 - halfOfSizeWidth - 50, 
                          gameMan->getRenderWindow().getSize().y/2 - halfOfSizeHeight);
    bar2Title.setPosition(gameMan->getRenderWindow().getSize().x/2 - halfOfSizeWidth - 50,
                          gameMan->getRenderWindow().getSize().y/2 - halfOfSizeHeight + 100);

    // back button
    backButton.setSize(60, 30);
    backButton.setBackgroundColor(sf::Color(238, 130, 238, 100));
    backButton.setTitle("Back");
    backButton.setFont(this->font);
    backButton.setTextColor(sf::Color::White);
    backButton.setTextSize(14);
    backButton.setPosition(gameMan->getRenderWindow().getSize().x/2,
                           gameMan->getRenderWindow().getSize().y - 100);

    // background
    this->background.setSize({(float)gameMan->getRenderWindow().getSize().x,
                             (float)gameMan->getRenderWindow().getSize().y});
    if (!this->bg_texture.loadFromFile("Asset/bg_setting.jpg")) {
        std::cout << "Fail to load setting background" << std::endl;
    }else{
        this->background.setTexture(&this->bg_texture);
    }
}

void SettingState::pollEvents(GameManager *gameMan)
{
    sf::Event ev;
    while (gameMan->getRenderWindow().pollEvent(ev))
    {
        if (ev.type == sf::Event::Closed)
        {
            gameMan->getRenderWindow().close();
        }

        if (ev.type == sf::Event::MouseButtonPressed) {
            if (behindBar[0].isMouseOver(gameMan->getRenderWindow()))
            {
                this->changeMusicVol = sf::Mouse::getPosition(gameMan->getRenderWindow()).x - behindBar[0].getPositionX() + behindBar[0].getSizeWidth() / 2;
                gameMan->getSelectionSound().play();
                update(gameMan);
                gameMan->setBGMusicVol(this->changeMusicVol/2);
            }
            if (behindBar[1].isMouseOver(gameMan->getRenderWindow()))
            {
                this->changeSoundVol = sf::Mouse::getPosition(gameMan->getRenderWindow()).x - behindBar[1].getPositionX() + behindBar[1].getSizeWidth() / 2;
                gameMan->getSelectionSound().play();
                update(gameMan);
                gameMan->setSoundEffectVolVar(this->changeSoundVol/2);
            }
            if (this->backButton.isMouseOver(gameMan->getRenderWindow())) {
                gameMan->getSelectionSound().play();
                gameMan->setState(gameMan->getMenuState());
                gameMan->clearScreen();
                std::cout << "Back to menu" << std::endl;
                return;
            }
        }
    }

    if (this->backButton.isMouseOver(gameMan->getRenderWindow())) {
        this->backButton.setBackgroundColor(sf::Color(238, 130, 238, 200));
    }else {
        this->backButton.setBackgroundColor(sf::Color(238, 130, 238, 100));
    }
}

void SettingState::update(GameManager *gameMan)
{   
    // std::cout << "update" << std::endl;
    if (this->changeMusicVol > -1)
    {
        frontBar[0].setSize(changeMusicVol, frontBar[0].getSizeHeight());
        frontBar[0].setPosition(behindBar[0].getPositionX() - behindBar[0].getSizeWidth() / 2 + changeMusicVol / 2,
                                frontBar[0].getPositionY());
    }

    if (this->changeSoundVol > -1 && this->changeSoundVol < 200)
    {
        frontBar[1].setSize(changeSoundVol, frontBar[1].getSizeHeight());
        frontBar[1].setPosition(behindBar[1].getPositionX() - behindBar[1].getSizeWidth() / 2 + changeSoundVol / 2,
                                frontBar[1].getPositionY());
    }
}

void SettingState::draw(GameManager *gameMan)
{
    // std::cout << "draw" << std::endl;
    gameMan->getRenderWindow().draw(this->background);

    gameMan->getRenderWindow().draw(bar1Title);
    gameMan->getRenderWindow().draw(bar2Title);

    this->behindBar[0].drawTo(gameMan->getRenderWindow());
    this->behindBar[1].drawTo(gameMan->getRenderWindow());

    this->frontBar[0].drawTo(gameMan->getRenderWindow());
    this->frontBar[1].drawTo(gameMan->getRenderWindow());

    this->backButton.drawTo(gameMan->getRenderWindow());
}


/* void initFrontBarDebug()
{
    behindBar[0].setBackgroundColor(sf::Color::Yellow);
    behindBar[1].setBackgroundColor(sf::Color::Yellow);

    behindBar[0].setSize(200, 10);
    behindBar[1].setSize(200, 10);

    behindBar[0].setPosition(250 + 100, 100 + 5);
    behindBar[1].setPosition(250 + 100, 200 + 5);

    frontBar[0].setBackgroundColor(sf::Color::Green);
    frontBar[1].setBackgroundColor(sf::Color::Green);

    frontBar[0].setSize(200, 10);
    frontBar[1].setSize(200, 10);

    frontBar[0].setPosition(250 + 100, 100 + 5);
    frontBar[1].setPosition(250 + 100, 200 + 5);
}

void debugFrontBar(sf::RenderWindow &window)
{
    if (behindBar[0].isMouseOver(window))
    {
        this->changeMusicVol = sf::Mouse::getPosition(window).x - behindBar[0].getPositionX() + behindBar[0].getSizeWidth()/2;
        std::cout << "CMV " << changeMusicVol << std::endl;
        sf::Event ev;
        while (window.pollEvent(ev))
        {
            if (ev.type == sf::Event::MouseButtonPressed)
            {
                update(window);
            }
        }
    }

    if (behindBar[1].isMouseOver(window))
    {
        this->changeSoundVol = sf::Mouse::getPosition(window).x - behindBar[1].getPositionX() + behindBar[1].getSizeWidth()/2;
        std::cout << "CSVooooo " << changeSoundVol << std::endl;
        sf::Event ev;
        while (window.pollEvent(ev))
        {
            if (ev.type == sf::Event::MouseButtonPressed)
            {
                update(window);
            }
        }
    }

    window.clear();
    behindBar[0].drawTo(window);
    behindBar[1].drawTo(window);
    frontBar[0].drawTo(window);
    frontBar[1].drawTo(window);
    window.display();
} */
