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
    const double getPoint();
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
            inline double const getScore() const{return score;}
            void setScore(double newscore){score = newscore;}
            static inline bool getTurn() {return turn;}
            static void changeTurn(){turn = !turn;}
            inline bool getColor() const{return color;}
        private:
            static bool turn;
            bool color;
            double score;
    };

    Board(Board& other);
    friend class Piece;
    Board();
    void printBoard(User p1,User p2);
    void initBoard();
    int modifyMove(char x);
    int game();
    Board operator =(const Board& other);


private:
    const bool kingSafety() const;
    double * goodnessScore(User &p1white, User &p2black);
    struct LastMove;
    vector<vector<Piece>> board;
    //void updateBoard();
    Piece getPiece(int x, int y);
    void inputAndMove(User &p1, User &p2);
    bool inputValidity(string input, User &p1, User &p2);
    bool moveValidity(int x1, int y1, int x2, int y2);
    Board nextmove(User &p1, User &p2);
    

};



#endif