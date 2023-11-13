#include <iostream>
#include <cstring>

using namespace std;

int main(){

    char ebrar[] = "ebrarinyanaklari";
    char deneme[12] = "asdasdsad";
    char hakan[1];
    

    cout << sizeof(hakan) << endl;
    // strcpy(hakan,ebrar);
    strcpy(hakan, ebrar);

    cout << hakan << endl;


    return 0;
}

