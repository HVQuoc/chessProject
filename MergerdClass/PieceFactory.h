#pragma once
#include "Moves.h"

class Piece;
class PieceFactory
{
public:
    static Piece* createPiece(int value);
};