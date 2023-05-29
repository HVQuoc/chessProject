
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "WindowState.hpp"

class SettingState;
class MainMenu;

class GameManager {
private:
    // Video mode
    sf::RenderWindow window;
    
    // States
    WindowState* windowState;
    MainMenu* menu;
    SettingState* setting;
    Game* game;

    // Music
    sf::Music bg_music;
    sf::SoundBuffer selectionSoundBuffer;
    sf::Sound selectionSound;

    // Volume
    int bg_musicVol;
    int soundEffectVol;

public:
    ~GameManager();
    void initWindow();
    bool isWindowOpen();
    void setState(WindowState* state);
    WindowState* getMenuState();
    WindowState* getSettingState();
    WindowState* getGameState();
    WindowState* getCurrentState();
    sf::Sound& getSelectionSound();

    void clearScreen();
    void drawCurrentState();
    void displayState();

    sf::RenderWindow& getRenderWindow();

    // Music and sound
    void setBGMusicVol(int volume);
    void setSoundEffectVolVar(int volume);
};