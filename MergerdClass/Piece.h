#pragma once
#include <iostream>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Point.h"
using namespace std;

enum TypePiece
{
    ROOK = 1,
    KNIGHT = 2,
    BISHOP = 3,
    QUEEN = 4,
    KING = 5,
    PAWN = 6
};

class Piece
{
private:
    int color; // 1: white, -1: black
    TypePiece type;

public:
    Piece(int color, TypePiece type);
    virtual ~Piece();
    virtual vector<Point> canMove(Piece* board[8][8], Point start) = 0;
    int getColor();
    TypePiece getType();

    // Draw Piece
    sf::Texture texturePiece;
    sf::Sprite spritePiece;

    sf::Texture getTexturePiece();
    sf::Sprite getSpritePiece();

    virtual void initTexturePiece(int color) = 0;
    void setPosition(double x, double y);
    void initSpritePiece();
    void renderPiece(sf::RenderTarget& target);
    void transformSprite();
};

