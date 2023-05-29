#include "PieceFactory.h"
#include "WindowState.hpp"
#include "GameManager.h"

// Object
void Game::initBoard()
{
    this->board = new Board;
}

// Contructor, Destructor

Game::~Game()
{
    delete this->board;
}

// Accessors
bool Game::running(GameManager *gameMan)
{
    gameMan->getRenderWindow().isOpen() && this->board->endGame() == false;
}

// Functions

// override pure init function
void Game::init(GameManager *gameMan)
{
    this->initBoard();

    // setting basic infor for buttons
    homeBtn.setSize(32, 32);
    saveGameBtn.setSize(32, 32);
    undoBtn.setSize(32, 32);
    redoBtn.setSize(32, 32);

    //  - set position
    int halfOfLocalBounds = 16; // 32/2 : 'cause the buttons all have the same size
    homeBtn.setPosition(1140 + halfOfLocalBounds, 20 + halfOfLocalBounds);
    saveGameBtn.setPosition(1060 + halfOfLocalBounds, 20 + halfOfLocalBounds);
    undoBtn.setPosition(1060 + halfOfLocalBounds, 420 + halfOfLocalBounds);
    redoBtn.setPosition(1140 + halfOfLocalBounds, 420 + halfOfLocalBounds);


    // init and set texture for buttons
    if (!homeBtnTexture.loadFromFile("Picture/home-page.png")) {
        std::cout << "Load texture for home button fail" << std::endl;
    }else {
        homeBtn.setTexture(this->homeBtnTexture);
    }

    if (!saveGameBtnTexture.loadFromFile("Picture/save-file.png")) {
        std::cout << "Load texture for save game button fail" << std::endl;
    }else {
        saveGameBtn.setTexture(this->saveGameBtnTexture);
    }

    if (!undoBtnTexture.loadFromFile("Picture/undo.png")) {
        std::cout << "Load texture for home button fail" << std::endl;
    }else {
        undoBtn.setTexture(this->undoBtnTexture);
    }

    if (!redoBtnTexture.loadFromFile("Picture/redo.png")) {
        std::cout << "Load texture for home button fail" << std::endl;
    }else {
        redoBtn.setTexture(this->redoBtnTexture);
    }

    // load and set turn image
    turnImage.setSize({120, 120});
    //turnImage.setOrigin(turnImage.getLocalBounds().width/2, turnImage.getLocalBounds().height/2);
    turnImage.setPosition(1060, 240);
    if (!blackTurnTexture.loadFromFile("Picture/blackTurn.png") ||
        !whiteTurnTexture.loadFromFile("Picture/whiteTurn.png")) {
        std::cout << "Fail to load turn image texture" << std::endl;
    }else {
        turnImage.setTexture(&this->whiteTurnTexture);
    }

    // background: last load, first draw :v
    backgroundInGame.setSize({gameMan->getRenderWindow().getSize().x,
                             gameMan->getRenderWindow().getSize().y});
    if (!bgInGameTexture.loadFromFile("Picture/inGame_bg.jpg")) {
        std::cout << "Cannot load background in game" << std::endl;
    }else {
        backgroundInGame.setTexture(&bgInGameTexture);
    }
}

void Game::pollEvents(GameManager *gameMan)
{
    sf::Event ev;
    while (gameMan->getRenderWindow().pollEvent(ev))
    {
        switch (ev.type)
        {
        case sf::Event::Closed:
            gameMan->getRenderWindow().close();
            break;
        case sf::Event::MouseButtonPressed:
            if (ev.key.code == sf::Mouse::Left)
            {
                if (this->board->isTransform == true)
                {
                    this->board->transformPawn(this->mousePosView);
                }
                else
                {
                    this->board->savePointStart(this->mousePosView);
                }
            }
            if (this->homeBtn.isMouseOver(gameMan->getRenderWindow())) {
                gameMan->setState(gameMan->getMenuState());
            }
            break;
        case sf::Event::MouseButtonReleased:
            if (ev.key.code == sf::Mouse::Left)
            {
                this->board->Move(this->mousePosView);
            }
            break;
        default:
            break;
        }
    }
}

void Game::updateMousePosition(sf::RenderWindow &window)
{
    this->mousePosWindow = sf::Mouse::getPosition(window);
    this->mousePosView = window.mapPixelToCoords(this->mousePosWindow);
    // cout << this->mousePosView.x << " " << this->mousePosView.y << endl;
}

void Game::update(GameManager *gameMan)
{
    // check zoom window
    // if (gameMan->getRenderWindow().getSize().x != 1200 || gameMan->getRenderWindow().getSize().y != 800)
    //     this->board->isRender = true;
    // gay loi: moi lan click trong window thi moi render, con khong thi man hinh den xi

    this->updateMousePosition(gameMan->getRenderWindow());

    // this->pollEvents(); ??
    this->board->updateMove(this->mousePosView);
}

void Game::draw(GameManager *gameMan)
{
    // Draw background first
    gameMan->getRenderWindow().draw(this->backgroundInGame);

    // Draw
    this->board->renderBoard(gameMan->getRenderWindow());

    // Draw square direction
    this->board->renderSquareDirecitons(gameMan->getRenderWindow());

    // Draw buttons
    homeBtn.drawTo(gameMan->getRenderWindow());
    saveGameBtn.drawTo(gameMan->getRenderWindow());
    undoBtn.drawTo(gameMan->getRenderWindow());
    redoBtn.drawTo(gameMan->getRenderWindow());

    gameMan->getRenderWindow().draw(this->turnImage);
}
