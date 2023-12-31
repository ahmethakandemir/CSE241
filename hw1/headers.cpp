#ifndef HEADERS_H
#define HEADERS_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstring>

using namespace std;


class Piece{
public:
    friend class Board;
    Piece();
    Piece(int x, int y);
    Piece(char symbol, int x, int y);
    Piece(char symbol, int x, int y, int point);
    Piece(const Piece& other);
    double getPoint();
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
    void outSymbol();
    char getSymbol() const;
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
            inline bool getColor() const{return color;}
            static inline void setTurn(bool newturn){turn = newturn;}
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
    void savetoFile();
    void loadfromFile();


private:
    bool kingSafety(User p1,User p2);
    double * goodnessScore(User &p1white, User &p2black);
    struct LastMove;
    vector<vector<Piece>> board;
    Piece getPiece(int x, int y);
    void inputAndMove(User &p1, User &p2);
    bool inputValidity(string input, User &p1, User &p2);
    bool moveValidity(int x1, int y1, int x2, int y2);
    Board nextmove(User &p1, User &p2);
    bool isMate(User p1, User p2);

};



#endif