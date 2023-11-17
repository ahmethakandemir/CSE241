#include "headers.cpp"

Piece::Piece(){
    value = 0;
    x = 0;
    y = 0;
}

Piece::Piece(int x, int y) : x(x), y(y){
    value = 0;
    symbol = '.'; //empty space
    int point = 0;
}

Piece::Piece(int value, int x, int y) : value(value), x(x), y(y){
    setSymbol();
}

Piece::Piece(int value, int x, int y, int point) : value(value), x(x), y(y), point(point){
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

char Piece::getSymbol() const{
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
            symbol = 'K';
            break;
        case 6:
            symbol = 'Q';
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
            symbol = 'k';
            break;
        case 16:
            symbol = 'q';
            break;
        default:
            symbol = 'e';
            break;
    
    }

}

void Piece::outSymbol(){
    cout << symbol << endl;
}

int Board::modifyMove(char x){

    int intx;
    switch (x)
    {
    case 'a':
    case '1':
        intx = 1;
        break;
    case 'b':
    case '2':
        intx = 2;
        break;
    case 'c':
    case '3':
        intx = 3;
        break;  
    case 'd':
    case '4':
        intx = 4;
        break;
    case 'e':
    case '5':
        intx = 5;
        break;
    case 'f':
    case '6':
        intx = 6;
        break;
    case 'g':
    case '7':
        intx = 7;
        break;
    case 'h':
    case '8':
        intx = 8;
        break;
    
    default:
        cout << "Invalid input" << endl;
        break;
    }
    return intx;
}

Piece Piece::operator=(const Piece& other){
    value = other.value;
    x = other.x;
    y = other.y;
    symbol = other.symbol;
    point = other.point;
    return *this;
}

void Board::input(){
    cout << "Enter a move: " << endl;
    string input;
    getline(cin, input);
    while(!inputValidity(input)){
        cout << "Invalid input, try again: " << endl;
        getline(cin, input);
    }
    int x1, x2, y1, y2;
    y1 = modifyMove(input[0]);
    x1 = modifyMove(input[1]);
    y2 = modifyMove(input[2]);
    x2 = modifyMove(input[3]);

    //check if move is valid
    while(!moveValidity(x1, y1, x2, y2)){
        cout << "Invalid move, try again: " << endl;
        cout << "Enter a move: " << endl;
        getline(cin, input);
        while(!inputValidity(input)){
            cout << "Invalid input, try again: " << endl;
            getline(cin, input);
        }
        y1 = modifyMove(input[0]);
        x1 = modifyMove(input[1]);
        y2 = modifyMove(input[2]);
        x2 = modifyMove(input[3]);
    }

    board[x2][y2] = board[x1][y1];
    board[x1][y1] = Piece(x1, y1);

    printBoard();
}

bool Board::inputValidity(string input){

    string valid = "abcdefgh12345678";
    if(input.length() != 4){
        return false;
    }
    for(char c : input){
        if(valid.find(c) == string::npos){
            return false;
        }
    }
    if(isalpha(input[0]) && isdigit(input[1]) && isalpha(input[2]) && isdigit(input[3]  )){
        return true;
    }
    else{
        return false;
    }
    return true;
}

bool Board::moveValidity(int x1, int y1, int x2, int y2)
{
    //check if there is a piece at the source location
    if(board[x1][y1].getValue() == 0){
        return false;
    }

    


    return true;
}

int Board::game(){

    printBoard();
    while(true)
        input();




    return 0;

}   

Piece Board::getPiece(int x, int y){
    return board[x][y];
}

std::ostream& operator<<(std::ostream& out, const Piece& other)
{
    out << other.symbol;
    return out;
}

Board::Board(){
    initBoard();
}

void Board::printBoard(){
    for(int i = 8; i > 0; i--){
        cout << i << "  |  ";
        for(int j = 1; j < 9; j++){
            cout << board[i][j] << "  ";
        }
        cout << endl;
    }
    cout << "    -------------------------" <<endl;
    cout << "      a  b  c  d  e  f  g  h" << endl;
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
    board[1][1] = Piece(2, 1, 1, 5);
    board[1][2] = Piece(3, 2, 1, 3);
    board[1][3] = Piece(4, 3, 1, 3);
    board[1][4] = Piece(6, 4, 1, 9);
    board[1][5] = Piece(5, 5, 1, 999);
    board[1][6] = Piece(4, 6, 1, 3);
    board[1][7] = Piece(3, 7, 1, 3);
    board[1][8] = Piece(2, 8, 1, 5);
    //set up black pieces
    for(int i = 1; i < 9; i++){
        board[7][i] = Piece(11, i, 7);
    }
    board[8][1] = Piece(12, 1, 8, 5);
    board[8][2] = Piece(13, 2, 8, 3);
    board[8][3] = Piece(14, 3, 8, 3);
    board[8][4] = Piece(16, 4, 8, 9);
    board[8][5] = Piece(15, 5, 8, 999);
    board[8][6] = Piece(14, 6, 8, 3);
    board[8][7] = Piece(13, 7, 8, 3);
    board[8][8] = Piece(12, 8, 8, 5);
    //set up empty spaces
    for(int i = 3; i < 7; i++){
        for(int j = 1; j < 9; j++){
            board[i][j] = Piece(0, j, i);
        }
    }
}







int main(){

    
    // cout<< p2.getSymbol() << endl;
    Board newBoard;
    newBoard.game();
    

    return 0;
}