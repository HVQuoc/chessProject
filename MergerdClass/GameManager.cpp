#include "GameManager.h"

GameManager::~GameManager() {
    delete this->menu;
    delete this->setting;
    delete this->game;
}

void GameManager::initWindow() {

    this->window.create(sf::VideoMode(1200, 800), "ChessGame");
    this->window.setFramerateLimit(90);
    
    // Creat and load 4 states
    this->menu = new MainMenu;
    this->menu->init(this);

    this->setting = new SettingState;
    this->setting->init(this);

    this->game = new Game;
    this->game->init(this);

    this->windowState = this->menu;

    // Load background music
    if (!this->bg_music.openFromFile("Asset/bg_music.ogg")) {
        std::cout << "Cannot load audio" << std::endl; 
    }else {
        bg_music.setVolume(50);
        bg_music.play();
        bg_music.setLoop(true);
    }
}

bool GameManager::isWindowOpen() {
    return this->window.isOpen();
}

void GameManager::setState(WindowState* state) {
    this->windowState = state;
}

WindowState* GameManager::getMenuState() {
    return this->menu;
}

WindowState* GameManager::getSettingState() {
    return this->setting;
}

WindowState* GameManager::getGameState() {
    return this->game;
}

WindowState* GameManager::getCurrentState() {
    return this->windowState;
}

sf::Sound& GameManager::getSelectionSound() {
    return this->selectionSound;
}

void GameManager::clearScreen() {
    this->window.clear();
}

void GameManager::drawCurrentState() {
    //this->windowState->pollEvents(this); ??
    this->windowState->draw(this);
}

void GameManager::displayState() {
    this->window.display();
}

sf::RenderWindow& GameManager::getRenderWindow() {
    return this->window;
}

void GameManager::setBGMusicVol(int volume) {
    this->bg_musicVol = volume;
    this->bg_music.setVolume(volume);
}

void GameManager::setSoundEffectVolVar(int volume) {
    this->soundEffectVol = volume;
    this->selectionSound.setVolume(volume);
}


