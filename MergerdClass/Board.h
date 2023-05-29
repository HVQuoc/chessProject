#pragma once
#include <SFML/Audio.hpp>
#include "Queen.h"
#include "Knight.h"
#include "Pawn.h"
#include "King.h"
#include "Bishop.h"
#include "Rook.h"
#include "Moves.h"

class Board
{
public:
    Piece* board[8][8];
    int turn;
    int win; // 1: White win, -1: Black win
    vector<Moves> beforeMoves;
    vector<Moves> afterMoves;

    // Draw board
    void initTextureBoard();
    void initSpriteBoard();
    sf::Texture textureBoard;
    sf::Sprite spriteBoard;

    //Graphic
    bool isTransform;
    bool isRender;
    bool isMove;
    Point start;
    Point end;

    // sound
    sf::Sound choosePieceSound;
    sf::SoundBuffer choosePieceSound_buffer;
    sf::Sound movePieceSound;
    sf::SoundBuffer movePS_buffer;
    sf::Sound eatOtherPieceSound;
    sf::SoundBuffer eatOtherPieceSound_buffer;
    sf::Sound winGameSound;
    sf::SoundBuffer winGameSound_buffer;
    sf::Sound beInCheckSound;
    sf::SoundBuffer beInCheckSound_buffer;

    // Square direction
    sf::CircleShape squareDirection;
    vector<sf::CircleShape> squareDirections;

public:
    Board();
    void initBoard();
    bool canMoveInBoard(vector<Point> listValidMoves, Point end);
    bool endGame();
    void clearBoard();
    Piece*& Get(Point a);

    bool checkmate(int color);
    vector<Point> canLosePiece(int color);
    ~Board();

    // Draw board
    void renderBoard(sf::RenderTarget& target);

    // Graphics
    void transformPawn(sf::Vector2f mousePosView);
    void savePointStart(sf::Vector2f mousePosView);
    Point getPositionPiece(sf::Vector2f mousePosView);
    void Move(sf::Vector2f mousePosView);
    void updateMove(sf::Vector2f mousePosView);

    // square Direction
    void initSquareDirection();
    void createSquareDirections(vector<Point> listValidMoves);
    void renderSquareDirecitons(sf::RenderTarget& target);

    void initSound();
};
