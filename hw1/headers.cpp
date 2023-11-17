#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Piece{
public:
    friend class Board;
    Piece();
    Piece(int x, int y);
    Piece(int value, int x, int y);
    Piece(int value, int x, int y, int point);
    const int getValue();
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
    void outSymbol();
    char getSymbol() const;
    friend ostream& operator<<(ostream& out, const Piece& other);
    Piece operator =(const Piece& other);
    void move(int x, int y);

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
    friend class Piece;
    Board();
    void printBoard();
    void initBoard();
    int modifyMove(char x);
    int game();

private:
    vector<vector<Piece>> board;
    void updateBoard();
    Piece getPiece(int x, int y);
    void input();
    bool inputValidity(string input);
    bool moveValidity(int x1, int y1, int x2, int y2);


};


