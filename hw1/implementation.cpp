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
    point = 0;
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

char Piece::getSymbol()const{
    return symbol;
}

double Piece::getPoint(){
    return point;
}

bool Piece::getColor(){
    if(isupper(getSymbol())){ //true is for white, false is for black
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

void Piece::outSymbol(){ // cout symbol
    cout << symbol << endl;
}

int Board::modifyMove(char x){ // converts char to int

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

Piece Piece::operator=(const Piece& other){ // = overload
    x = other.x;
    y = other.y;
    symbol = other.symbol;
    point = other.point;
    isFirstMove = other.isFirstMove;
    return *this;
}

bool Board::kingSafety(User p1,User p2) { // checks if king is under attack, it changes it isUnderAttack value
    goodnessScore(p1, p2);

    for(int i = 1; i <= 8; i++){
        for(int j = 1; j <= 8; j++){
            if(board[i][j].getSymbol() == 'K'){
                if(board[i][j].isUnderAttack == true){
                    // cout << "white king is under attack" << endl;
                    return false;
                }
            }
            else if(board[i][j].getSymbol() == 'k'){
                if(board[i][j].isUnderAttack == true){
                    // cout << "black king is under attack" << endl;
                    return false;
                }
            } 
        }
    }
    return true;
}

struct Board::LastMove{ // to keep the last move, used for enpassant but it didnt work
    int x1;
    int y1;
    int x2;
    int y2;
    char symbol;
}lastmove;

void Board::inputAndMove(User &p1, User &p2){

    int x1, x2, y1, y2;
    

    cout << "Enter a move: " << endl;
    string input;
    getline(cin, input);                         // getting input
    while(!inputValidity(input, p1, p2)){
    
        getline(cin, input);

        
    }
    x1 = modifyMove(input[0]);  // seperating input to chars
    y1 = modifyMove(input[1]);
    x2 = modifyMove(input[2]);
    y2 = modifyMove(input[3]);      

    //check if move is valid
    while(!moveValidity(x1, y1, x2, y2)){   // if move is not valid, reprompt for it
        cout << "Invalid move, try again: " << endl;
        cout << "Enter a move: " << endl;
        getline(cin, input);
        while(!inputValidity(input, p1, p2)){
            getline(cin, input);
        }
        x1 = modifyMove(input[0]);  // modifying inputs to ints
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

    board[x2][y2] = board[x1][y1];  // changing the board as the move
    board[x1][y1] = Piece(x1, y1);

}

void Board::savetoFile(){   // saving to file
    ofstream savefile;
    savefile.open("save.txt");
    for(int i = 1; i < 9; i++){
        for(int j = 1; j < 9; j++){
            savefile << board[i][j].getSymbol();
        }
    }
    savefile << User::getTurn();
    savefile.close();
    cout << "Game saved" << endl;
}

void Board::loadfromFile(){     // loading from file
    ifstream loadfile;
    loadfile.open("save.txt");
    if(!loadfile){      // if there is no file as save.txt
        cout << "No saved game" << endl;
        return;
    }
    string input;       
    getline(loadfile, input);
    if(!isalpha(input[0])){     //if there is file but there is format error
        cout << "No saved game" << endl;
        return;
    }
    if(input.length() != 65){   //there is file but there is format error
        cout << "There must have been an error while saving the game" << endl;
        return;
    }
    int counter = 0;
    for(int i = 1; i < 9; i++){
        for(int j = 1; j < 9; j++){
            board[i][j] = Piece(input[counter], i, j);
            counter++;
        }
    }
    if(input[counter] == '1'){  // setting the turn
        User::setTurn(true);
    }
    else{
        User::setTurn(false);
    }
    loadfile.close();
    cout << "Game loaded" << endl;
}

bool Board::inputValidity(string input, User &p1, User &p2){ //check the input is valid or not

    if(input == "quit"){            // if input is quit, exits
        cout << "...Exitted game..." << endl;
        exit(0);
    }
    if(input == "suggest"){         // suggests move
        if(User::getTurn() == true){
            nextmove(p1, p2);
        }
        else if(User::getTurn() == false){
            nextmove(p2, p1);
        }
        cout << "Enter a move: " << endl;
        return false;
    }
    if(input == "save"){            // saves to file
        savetoFile();
        cout << "Enter a move: " << endl;
        return false;
    }
    if(input == "load"){            // loads from this file
        loadfromFile();
        printBoard(p1,p2);
        cout << "Enter a move: " << endl;
        return false;
        
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
    if(isValid != 0){       // check if input is valid
        cout << "Invalid move, try again: " << endl;
        return false;
    }
    if(isalpha(input[0]) && isdigit(input[1]) && isalpha(input[2]) && isdigit(input[3]  )){
        return true;
    }
    else{
        cout << "Invalid move, try again: " << endl;
        return false;
    }
    
}

bool Board::moveValidity(int x1, int y1, int x2, int y2)    // input is valid but check if move is valid
{
    //check if there is a piece at the source location
    if(board[x1][y1].getSymbol() == '.'){
        return false;
    }
    //check if the piece is the right color
    if(User::getTurn() != board[x1][y1].getColor()){
        return false;
    }
    if((board[x2][y2].getSymbol() != '.') && (board[x1][y1].getColor() == board[x2][y2].getColor())){
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
        //for king
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

std::ostream& operator<<(std::ostream& out, const Piece& other) // << overload
{
    out << other.symbol;
    return out;
}

Board::Board(){
    initBoard();
}

void Board::printBoard(User p1, User p2){   // print board
    cout << "   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" <<endl;
    cout << "\n       White : "<< p1.getScore() << "  --  Black : " << p2.getScore() << endl; 
       
    cout << "   -----------------------------------" <<endl;

    for(int i = 8; i > 0; i--){
        cout << i << "  |  ";
        for(int j = 1; j < 9; j++){
            cout << board[j][i] << "   "; 
        }
        cout << "|  " << endl << "   |                                  |" << endl;
    }
    cout << "   -----------------------------------" <<endl;
    cout << "      a   b   c   d   e   f   g   h" << endl;

    if(User::getTurn() == true)
        cout << "White's Turn, ";
    else
        cout << "Black's Turn, ";

}

void Board::initBoard(){    //initializing board
    board.resize(9);
    for(int i = 1; i < 9; i++){
        board[i].resize(9);
    }
    for(int i = 1; i < 9; i++){
        board[i][2] = Piece('P', i, 2, 1);
    }
    board[1][1] = Piece('R', 1, 1, 5);
    board[2][1] = Piece('N', 2, 1, 3);
    board[3][1] = Piece('B', 3, 1, 3);
    board[4][1] = Piece('Q', 4, 1, 9);
    board[5][1] = Piece('K', 5, 1, 0);
    board[6][1] = Piece('B', 6, 1, 3);
    board[7][1] = Piece('N', 7, 1, 3);
    board[8][1] = Piece('R', 8, 1, 5);
    //set up black pieces
    for(int i = 1; i < 9; i++){
        board[i][7] = Piece('p', i, 7, 1);
    }
    board[1][8] = Piece('r', 1, 8, 5);
    board[2][8] = Piece('n', 2, 8, 3);
    board[3][8] = Piece('b', 3, 8, 3);
    board[4][8] = Piece('q', 4, 8, 9);
    board[5][8] = Piece('k', 5, 8, 0);
    board[6][8] = Piece('b', 6, 8, 3);
    board[7][8] = Piece('n', 7, 8, 3);
    board[8][8] = Piece('r', 8, 8, 5);
    for(int i = 3; i < 7; i++){
        for(int j = 1; j < 9; j++){
            board[j][i] = Piece('.', j, i);
        }
    }
}

double *Board::goodnessScore(User &p1white, User &p2black) // calculates goodness score
{

    double whiteScore = 0, blackScore = 0;
    for(int x1 = 1; x1 <= 8; x1++){
        for(int y1 = 1; y1 <= 8; y1++){
            board[x1][y1].isUnderAttack = false;    // initialize all pieces are not under attack
        }
    }

    for(int x1 = 1; x1 <= 8; x1++){
        for(int y1 = 1; y1 <= 8; y1++){
            for(int i = 1; i <= 8; i++){
                for (int k = 1; k <= 8; k++){
                    if(moveValidity(i,k,x1,y1)){
                        if(board[x1][y1].getSymbol() != '.'){ // if there is a piece at that location
                            board[x1][y1].isUnderAttack = true; // it is under attack
                        }
                    }
                    else{
                        board[x1][y1].isUnderAttack = false;
                    }
                }
            }
        }
    }
    User::changeTurn();
    for(int x1 = 1; x1 <= 8; x1++){
        for(int y1 = 1; y1 <= 8; y1++){
            for(int i = 1; i <= 8; i++){
                for (int k = 1; k <= 8; k++){
                    if(moveValidity(i,k,x1,y1)){
                        if(board[x1][y1].getSymbol() != '.'){   // if there is a piece at that location
                            board[x1][y1].isUnderAttack = true; // it is under attack
                        }
                    }
                    else{
                        board[x1][y1].isUnderAttack = false;    // it is not under attack
                    }
                }
            }
        }
    }
    User::changeTurn(); // change turn to other user to calculate other user's goodness score

    
    for(int x1 = 1; x1 <= 8; x1++){
        for(int y1 = 1; y1 <= 8; y1++){
            if((board[x1][y1].getColor() == true) && (board[x1][y1].getSymbol() != '.')){
                if(board[x1][y1].isUnderAttack == true){

                    whiteScore += (board[x1][y1].point / 2);
                }
                else if((board[x1][y1].isUnderAttack == false) && (board[x1][y1].getSymbol() != '.')){
                    whiteScore += board[x1][y1].point;
                }
            }
            else if((board[x1][y1].getColor() == false) && (board[x1][y1].getSymbol() != '.')){
                if(board[x1][y1].isUnderAttack == true){
                    blackScore += (board[x1][y1].point / 2);
                }
                else if((board[x1][y1].isUnderAttack == false) && (board[x1][y1].getSymbol() != '.')){
                    blackScore += board[x1][y1].point;
                    
                }
            }
        }
    }

    p1white.setScore(whiteScore);   // setting scores
    p2black.setScore(blackScore);
    double * score = new double[2]; // returning scores
    score[0] = whiteScore;
    score[1] = blackScore;
    return score;
}

Board::Board(Board& other){  // copy constructer
    board.resize(9);
    for(int i = 1; i < 9; i++){
        board[i].resize(9);
    }
    for(int i = 1; i < 9; i++){
        for(int j = 1; j < 9; j++){
            board[i][j] = other.board[i][j];
        }
    }
}

Board Board::operator=(const Board& other){ // = overload
    board.resize(9);
    for(int i = 1; i < 9; i++){
        board[i].resize(9);
    }
    for(int i = 1; i < 9; i++){
        for(int j = 1; j < 9; j++){
            board[i][j] = other.board[i][j];
        }
    }
    return *this;
}

Board Board::nextmove(User &p1, User &p2){ // calculates next move to suggest
    Board newBoard(*this);
    Board tempboard;
    double tempscore = -99;         // to find best move initialize the score at the lowest
    int tempx,tempy,tempx1,tempy1;
    for(int x1 = 1; x1 <= 8; x1++){
        for(int y1 = 1; y1 <= 8; y1++){
            for(int i = 1; i <= 8; i++){
                for (int k = 1; k <= 8; k++){
                    if(moveValidity(i,k,x1,y1) && kingSafety(p1,p2)){
                    newBoard.board[x1][y1] = newBoard.board[i][k];          // make a possible move for temp board
                    newBoard.board[i][k] = Piece(x1, y1);
                    if(p1.getColor() == true && newBoard.kingSafety(p1,p2) == true){ // the turn is white's and king is safe after the current possible move 
                        if((newBoard.goodnessScore(p1, p2)[0] - newBoard.goodnessScore(p1,p2)[1]) > tempscore ){    // save the move that has largest difference of scores
                            tempscore = newBoard.goodnessScore(p1, p2)[0] - newBoard.goodnessScore(p1,p2)[1];
                            tempboard = newBoard;
                            tempx = i;
                            tempy = k;
                            tempx1 = x1;
                            tempy1 = y1;
                        }
                    }
                    else if(p1.getColor() == false && newBoard.kingSafety(p1,p2) == true){ //  same as top but for black
                        if( ((newBoard.goodnessScore(p1, p2)[1] - newBoard.goodnessScore(p1,p2)[0]) > tempscore)){
                            tempscore = newBoard.goodnessScore(p1, p2)[1] - newBoard.goodnessScore(p1,p2)[0];
                            tempboard = newBoard;
                            tempx = i;
                            tempy = k;
                            tempx1 = x1;
                            tempy1 = y1;
                        }
                    }    

                    }
                    
                    newBoard = *this;   // reset the temp board
                }
            }
        }
    }



    cout << "Suggested move: " << endl;
    cout << char(tempx + 96) << tempy << char(tempx1+96) << tempy1 << endl; // print the suggested move
    return tempboard;

}

bool Board::isMate(User p1,User p2){    // check if it is checkmate or not
    Board tempboard(*this);
    for(int x1 = 1; x1 <= 8; x1++){
        for(int y1 = 1; y1 <= 8; y1++){
            for(int i = 1; i <= 8; i++){
                for (int k = 1; k <= 8; k++){
                    if(moveValidity(i,k,x1,y1)){
                        tempboard.board[x1][y1] = tempboard.board[i][k];
                        tempboard.board[i][k] = Piece(x1, y1);
                        if(tempboard.kingSafety(p1,p2)){
                            return false;
                        }
                    }
                    tempboard = *this;
                }
            }
        }
    }
    cout << "checkmate" << endl;
    exit(0);    // exit if checkmate
}

int Board::game(){  // the game loop 

    User p1white(false);
    User p2black(true);
    printBoard(p1white,p2black);

    while(true){
        if(kingSafety(p1white,p2black) == false){
            while (kingSafety(p1white,p2black) == false)
            {
                inputAndMove(p1white, p2black);
                
            }
            User::changeTurn();
        }
        else{
            inputAndMove(p1white, p2black);
            User::changeTurn();        
            isMate(p1white,p2black);
        }
        
        printBoard(p1white,p2black);
        isMate(p1white,p2black);
        
    
    }
    return 0;
}   
