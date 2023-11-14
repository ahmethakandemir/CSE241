#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Piece{
public:
    Piece();
    Piece(int value, int x, int y);
    Piece(int value, int x, int y, int point);
    const int getValue();
    int getX();
    int getY();
    char getSymbol();
    void setX(int x);
    void setY(int y);
    void outSymbol();
    char getSymbol() const;
    friend ostream& operator<<(ostream& out, const Piece& other);

private:
    int point;
    int value;
    void setSymbol();
    char symbol;
    int x;
    int y;
};


class Board{
public:
    friend Piece;
    Board();
    void printBoard();
    void initBoard();
    // void movePiece(int x1, int y1, int x2, int y2);

private:
    vector<vector<Piece>> board;

};


