#include "headers.cpp"

Piece::Piece(){
    value = 0;
    x = 0;
    y = 0;
}

Piece::Piece(int value, int x, int y) : value(value), x(x), y(y){
    setSymbol();
}

const int Piece::getValue(){
    return value;
}

int Piece::getX(){
    return x;
}

int Piece::getY(){
    return y;
}

void Piece::setX(int xval){
    x = xval;
}

void Piece::setY(int yval){
    y = yval;
}

char Piece::getSymbol(){
    return symbol;
}

void Piece::setSymbol(){
    //switch case for chess Piece  
    switch(value){
        case 0:
            symbol = '.'; //empty space
            break;
        case 1:
            symbol = 'P';
            break;
        case 2:
            symbol = 'R';
            break;
        case 3:
            symbol = 'N';
            break;
        case 4:
            symbol = 'B';
            break;
        case 5:
            symbol = 'Q';
            break;
        case 6:
            symbol = 'K';
            break;
        //black Piece starting from 11 to avoid confusion
        case 11:
            symbol = 'p';
            break;
        case 12:
            symbol = 'r';
            break;
        case 13:
            symbol = 'n';
            break;
        case 14:   
            symbol = 'b';
            break;
        case 15:
            symbol = 'q';
            break;
        case 16:
            symbol = 'k';
            break;
        default:
            symbol = 'e';
            break;
    
    
    
    }

}

void Piece::outSymbol(){
    cout << symbol << endl;
}

std::ostream& operator<<(std::ostream& out, const Piece& other)
{
    out << other.symbol;
    return out;
}

Board::Board(){
    initBoard();
    printBoard();
}

void Board::printBoard(){
    for(int i = 8; i > 0; i--){
        for(int j = 8; j > 0; j--){
            cout << board[i][j] << "  ";
        }
        cout << endl;
    }
}

void Board::initBoard(){
    board.resize(9);
    for(int i = 1; i < 9; i++){
        board[i].resize(9);
    }
    //set up white pieces
    for(int i = 1; i < 9; i++){
        board[2][i] = Piece(1, i, 2);
    }
    board[1][1] = Piece(2, 1, 1);
    board[1][2] = Piece(3, 2, 1);
    board[1][3] = Piece(4, 3, 1);
    board[1][4] = Piece(5, 4, 1);
    board[1][5] = Piece(6, 5, 1);
    board[1][6] = Piece(4, 6, 1);
    board[1][7] = Piece(3, 7, 1);
    board[1][8] = Piece(2, 8, 1);
    //set up black pieces
    for(int i = 1; i < 9; i++){
        board[7][i] = Piece(11, i, 7);
    }
    board[8][1] = Piece(12, 1, 8);
    board[8][2] = Piece(13, 2, 8);
    board[8][3] = Piece(14, 3, 8);
    board[8][4] = Piece(15, 4, 8);
    board[8][5] = Piece(16, 5, 8);
    board[8][6] = Piece(14, 6, 8);
    board[8][7] = Piece(13, 7, 8);
    board[8][8] = Piece(12, 8, 8);
    //set up empty spaces
    for(int i = 3; i < 7; i++){
        for(int j = 1; j < 9; j++){
            board[i][j] = Piece(0, j, i);
        }
    }
}


int main(){

    // cout << p2 << endl;
    // cout<< p2.getSymbol() << endl;
    Board newBoard;
    // newBoard.printBoard();



    return 0;
}