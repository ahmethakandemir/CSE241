#ifndef HEADERS_H
#define HEADERS_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Piece{
public:
    friend class Board;
    Piece();
    Piece(int x, int y);
    Piece(char symbol, int x, int y);
    Piece(char symbol, int x, int y, int point);
    Piece(const Piece& other);
    const int getPoint();
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
    void outSymbol();
    const char getSymbol() const;
    friend ostream& operator<<(ostream& out, const Piece& other);
    Piece operator =(const Piece& other);
    bool getColor();
    

private:
    
    bool isUnderAttack;
    bool isFirstMove;
    double point;
    char symbol;
    int x;
    int y;
};


class Board{
public:
    class User{
        public:
            User(bool color);
            inline double getScore() const{return score;}
            void setScore(double newscore){score = newscore;}
            static inline bool getTurn() {return turn;}
            static void changeTurn(){turn = !turn;}
        private:
            static bool turn;
            bool color;
            double score;
    };
    friend class Piece;
    Board();
    void printBoard();
    void initBoard();
    int modifyMove(char x);
    int game();


private:
    void goodnessScore(User &p1white, User &p2black);
    struct LastMove;
    vector<vector<Piece>> board;
    //void updateBoard();
    Piece getPiece(int x, int y);
    void inputAndMove();
    bool inputValidity(string input);
    bool moveValidity(int x1, int y1, int x2, int y2);


};



#endif