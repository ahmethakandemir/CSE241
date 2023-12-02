#include "headers.cpp"


Piece::Piece(){
    symbol = '.';
    x = 0;
    y = 0;
    point = 0;
    isFirstMove = true;
}

Piece::Piece(int x, int y) : x(x), y(y){
    isFirstMove = true;
    symbol = '.'; //empty space
    int point = 0;
}

Piece::Piece(char symbol, int x, int y) : symbol(symbol), x(x), y(y){
    isFirstMove = true;
    point = 0;
}

Piece::Piece(char symbol, int x, int y, int point) : symbol(symbol), x(x), y(y), point(point){
    isFirstMove = true;
}

Board::User::User(bool color) : color(color){
    score = 39; //39 is the sum of all the pieces
}

bool Board::User::turn = true;

Piece::Piece(const Piece& other){
    x = other.x;
    y = other.y;
    symbol = other.symbol;
    point = other.point;
}

const char Piece::getSymbol()const{
    return symbol;
}

const int Piece::getPoint(){
    return point;
}

bool Piece::getColor(){
    if(isupper(getSymbol())){
        return true;
    }
    else{
        return false;
    }
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
    x = other.x;
    y = other.y;
    symbol = other.symbol;
    point = other.point;
    isFirstMove = other.isFirstMove;
    return *this;
}

struct Board::LastMove{
    int x1;
    int y1;
    int x2;
    int y2;
    char symbol;
}lastmove;

void Board::inputAndMove(){

    int x1, x2, y1, y2;
    

    cout << "Enter a move: " << endl;
    string input;
    getline(cin, input);
    while(!inputValidity(input)){
        cout << "Invalid input, try again: " << endl;
        getline(cin, input);
    }
    x1 = modifyMove(input[0]);
    y1 = modifyMove(input[1]);
    x2 = modifyMove(input[2]);
    y2 = modifyMove(input[3]);

    //check if move is valid
    while(!moveValidity(x1, y1, x2, y2)){
        cout << "Invalid move, try again: " << endl;
        cout << "Enter a move: " << endl;
        getline(cin, input);
        while(!inputValidity(input)){
            cout << "Invalid input, try again: " << endl;
            getline(cin, input);
        }
        x1 = modifyMove(input[0]);
        y1 = modifyMove(input[1]);
        x2 = modifyMove(input[2]);
        y2 = modifyMove(input[3]);
    }
    board[x1][y1].isFirstMove = false;
    lastmove.x1 = x1;
    lastmove.y1 = y1;
    lastmove.x2 = x2;
    lastmove.y2 = y2;
    lastmove.symbol = board[x1][y1].getSymbol();

    // cout << board[x1][y1].isFirstMove << endl;
    board[x2][y2] = board[x1][y1];
    board[x1][y1] = Piece(x1, y1);



    
}

bool Board::inputValidity(string input){

    if(input == "q"){
        cout << "...Exitted game..." << endl;
        exit(0);
    }

    string valid = "abcdefgh12345678";
    if(input.length() != 4){
        return false;
    }
    int isValid = 4;
    for(char c : input){
        for(char v : valid){
            if(c == v){
                isValid--;
                break;
            }
        }
    }
    if(isValid != 0){
        return false;
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
    if(board[x1][y1].getSymbol() == '.'){
        return false;
    }
    //check if the piece is the right color
    if(User::getTurn() != board[x1][y1].getColor()){
        return false;
    }
    switch(board[x1][y1].getSymbol()){
        // for white pawns
        case 'P':
            if(x1 == x2 && y2 == y1 + 1 && board[x2][y2].getSymbol() == '.'){
                return true;
            }
            else if (x1 == x2 && y2 == y1 + 2 && board[x2][y2].getSymbol() == '.' && board[x2][y2 - 1].getSymbol() == '.' && board[x1][y1].isFirstMove)
            {   
                return true;
            }
            else if((x2 == x1 + 1 || x2 == x1 - 1) && y2 == y1 + 1 && board[x2][y2].getSymbol() != '.'){
                return true;
            }
            // else if statement for en passant
            else if((x1 == x2 + 1 || x1 == x2 - 1) && y2 == y1 + 1 && (x1 == lastmove.x2 + 1 || x1 == lastmove.x2 - 1) && y1 == lastmove.y2 && lastmove.symbol == 'p'){
                board[lastmove.x2][lastmove.y2] = Piece(lastmove.x2, lastmove.y2);
                //////////////////////////////////////////////////////////////////////pawn captured dont forget this
                return true;
            }
            else{
                return false;
            }
            break;
        // for black pawns
        case 'p':
            if(x1 == x2 && y2 == y1 - 1 && board[x2][y2].getSymbol() == '.'){
                return true;
            }
            else if (x1 == x2 && y2 == y1 - 2 && board[x2][y2].getSymbol() == '.' && board[x2][y2 + 1].getSymbol() == '.' && board[x1][y1].isFirstMove)
            {
                return true;
            }
            else if((x2 == x1 + 1 || x2 == x1 - 1) && y2 == y1 - 1 && board[x2][y2].getSymbol() != '.'){
                return true;
            }
            // enpassant code just like for white pawns
            else if((x1 == x2 + 1 || x1 == x2 - 1) && y2 == y1 - 1 && (x1 == lastmove.x2 + 1 || x1 == lastmove.x2 - 1) && y1 == lastmove.y2 && lastmove.symbol == 'P'){
                board[lastmove.x2][lastmove.y2] = Piece(lastmove.x2, lastmove.y2);
                //////////////////////////////////////////////////////////////////////pawn captured dont forget this
                return true;
            }
            else{
                return false;
            }
            break;
        // for rooks
        case 'R':
        case 'r':
            if(x1 == x2 && y1 != y2){
                if(y1 < y2){
                    for(int i = y1 + 1; i < y2; i++){
                        if(board[x1][i].getSymbol() != '.'){
                            return false;
                        }
                    }
                    return true;
                }
                else{
                    for(int i = y1 - 1; i > y2; i--){
                        if(board[x1][i].getSymbol() != '.'){
                            return false;
                        }
                    }
                    return true;
                }
            }
            else if(y1 == y2 && x1 != x2){
                if(x1 < x2){
                    for(int i = x1 + 1; i < x2; i++){
                        if(board[i][y1].getSymbol() != '.'){
                            return false;
                        }
                    }
                    return true;
                }
                else{
                    for(int i = x1 - 1; i > x2; i--){
                        if(board[i][y1].getSymbol() != '.'){
                            return false;
                        }
                    }
                    return true;
                }
            }
            else{
                return false;
            }
            break;
        // for knights
        case 'N':
        case 'n':
            if((x2 == x1 + 1 || x2 == x1 - 1) && (y2 == y1 + 2 || y2 == y1 - 2)){
                return true;
            }
            else if((x2 == x1 + 2 || x2 == x1 - 2) && (y2 == y1 + 1 || y2 == y1 - 1)){
                return true;
            }
            else{
                return false;
            }
            break;
        // for bishops
        case 'B':
        case 'b':
            if(abs(x2 - x1) == abs(y2 - y1)){
                if(x1 < x2 && y1 < y2){
                    for(int i = 1; i < abs(x2 - x1); i++){
                        if(board[x1 + i][y1 + i].getSymbol() != '.'){
                            return false;
                        }
                    }
                    return true;
                }
                else if(x1 < x2 && y1 > y2){
                    for(int i = 1; i < abs(x2 - x1); i++){
                        if(board[x1 + i][y1 - i].getSymbol() != '.'){
                            return false;
                        }
                    }
                    return true;
                }
                else if(x1 > x2 && y1 < y2){
                    for(int i = 1; i < abs(x2 - x1); i++){
                        if(board[x1 - i][y1 + i].getSymbol() != '.'){
                            return false;
                        }
                    }
                    return true;
                }
                else if(x1 > x2 && y1 > y2){
                    for(int i = 1; i < abs(x2 - x1); i++){
                        if(board[x1 - i][y1 - i].getSymbol() != '.'){
                            return false;
                        }
                    }
                    return true;
                }
            }
            else{
                return false;
            }
            break;
        // for queens
        case 'Q':
        case 'q':
            if(x1 == x2 && y1 != y2){
                if(y1 < y2){
                    for(int i = y1 + 1; i < y2; i++){
                        if(board[x1][i].getSymbol() != '.'){
                            return false;
                        }
                    }
                    return true;
                }
                else{
                    for(int i = y1 - 1; i > y2; i--){
                        if(board[x1][i].getSymbol() != '.'){
                            return false;
                        }
                    }
                    return true;
                }
            }
            else if(y1 == y2 && x1 != x2){
                if(x1 < x2){
                    for(int i = x1 + 1; i < x2; i++){
                        if(board[i][y1].getSymbol() != '.'){
                            return false;
                        }
                    }
                    return true;
                }
                else{
                    for(int i = x1 - 1; i > x2; i--){
                        if(board[i][y1].getSymbol() != '.'){
                            return false;
                        }
                    }
                    return true;
                }
            }
            else if(abs(x2 - x1) == abs(y2 - y1)){
                if(x1 < x2 && y1 < y2){
                    for(int i = 1; i < abs(x2 - x1); i++){
                        if(board[x1 + i][y1 + i].getSymbol() != '.'){
                            return false;
                        }
                    }
                    return true;
                }
                else if(x1 < x2 && y1 > y2){
                    for(int i = 1; i < abs(x2 - x1); i++){
                        if(board[x1 + i][y1 - i].getSymbol() != '.'){
                            return false;
                        }
                    }
                    return true;
                }
                else if(x1 > x2 && y1 < y2){
                    for(int i = 1; i < abs(x2 - x1); i++){
                        if(board[x1 - i][y1 + i].getSymbol() != '.'){
                            return false;
                        }
                    }
                    return true;
                }
                else if(x1 > x2 && y1 > y2){
                    for(int i = 1; i < abs(x2 - x1); i++){
                        if(board[x1 - i][y1 - i].getSymbol() != '.'){
                            return false;
                        }
                    }
                    return true;
                }
                else{
                    return false;
                }
        case 'K':
        case 'k':
            if((x2 == x1 + 1 || x2 == x1 - 1) && (y2 == y1 + 1 || y2 == y1 - 1)){
                return true;
            }
            else if(x1 == x2 && (y2 == y1 + 1 || y2 == y1 - 1)){
                return true;
            }
            else if(y1 == y2 && (x2 == x1 + 1 || x2 == x1 - 1)){
                return true;
            }
            else{
                return false;
            }
            break;
            }
        default:
            return false;
            break;
    }




    return true;
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

    //cout << board[6][8] << endl;
    cout << "   -----------------------------------" <<endl;

    for(int i = 8; i > 0; i--){
        cout << i << "  |  ";
        for(int j = 1; j < 9; j++){
            cout << board[j][i] << "   "; //<<board[j][i].getX()<<board[j][i].getY()
        }
        cout << "|  " << endl << "   |                                  |" << endl;
    }
    cout << "   -----------------------------------" <<endl;
    cout << "      a   b   c   d   e   f   g   h" << endl;

    // print out last move
    //cout << "Last move: " << lastmove.symbol << " " << lastmove.x1 << " " << lastmove.y1 << " " << lastmove.x2 << " " << lastmove.y2 << endl;
    //print current move
    if(User::getTurn() == true)
        cout << "White's Turn, ";
    else
        cout << "Black's Turn, ";

}

void Board::initBoard(){
    board.resize(9);
    for(int i = 1; i < 9; i++){
        board[i].resize(9);
    }
    //set up white pieces
    for(int i = 1; i < 9; i++){
        board[i][2] = Piece('P', i, 2);
    }
    board[1][1] = Piece('R', 1, 1, 5);
    board[2][1] = Piece('N', 2, 1, 3);
    board[3][1] = Piece('B', 3, 1, 3);
    board[4][1] = Piece('Q', 4, 1, 9);
    board[5][1] = Piece('K', 5, 1, 999);
    board[6][1] = Piece('B', 6, 1, 3);
    board[7][1] = Piece('N', 7, 1, 3);
    board[8][1] = Piece('R', 8, 1, 5);
    //set up black pieces
    for(int i = 1; i < 9; i++){
        board[i][7] = Piece('p', i, 7);
    }
    board[1][8] = Piece('r', 1, 8, 5);
    board[2][8] = Piece('n', 2, 8, 3);
    board[3][8] = Piece('b', 3, 8, 3);
    board[4][8] = Piece('q', 4, 8, 9);
    board[5][8] = Piece('k', 5, 8, 999);
    board[6][8] = Piece('b', 6, 8, 3);
    board[7][8] = Piece('n', 7, 8, 3);
    board[8][8] = Piece('r', 8, 8, 5);
    //set up empty spaces
    for(int i = 3; i < 7; i++){
        for(int j = 1; j < 9; j++){
            board[j][i] = Piece('.', j, i);
        }
    }
}

void Board::goodnessScore(User &p1white, User &p2black){

    double whiteScore = 0, blackScore = 0;

    for(int x1 = 1; x1 <= 8; x1++){
        for(int y1 = 1; y1 <= 8; y1++){
            for(int i = 1; i <= 8; i++){
                for (int k = 1; k <= 8; k++){
                    if(board[x1][y1].isUnderAttack == false){
                        if(moveValidity(i,k,x1,y1) == true){
                            board[x1][y1].isUnderAttack = true;
                            if(board[x1][y1].getColor() == true)
                                whiteScore += (board[x1][y1].point / 2);
                            else if (board[x1][y1].getColor() == false){
                                blackScore += (board[x1][y1].point / 2);
                            }
                        }
                    }
                }
            }
        }
    }

    p1white.setScore(whiteScore);
    p2black.setScore(blackScore);
}

int Board::game(){

    printBoard();
    User p1white(false);
    User p2black(true);

    while(true){
        inputAndMove();
        User::changeTurn();
        goodnessScore(p1white, p2black);
        printBoard();
        cout << "\nwhite : "<< p1white.getScore() << "  --  black : " << p2black.getScore() << endl; 



    }
    return 0;

}   


int main(){

    
    // cout<< p2.getSymbol() << endl;
    Board newBoard;
    newBoard.game();
    

    return 0;
}