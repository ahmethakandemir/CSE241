#include <iostream>
#include <cstring>
#include <string>
using namespace std;


int main(){

    char ebrar[30] = "ebrarrr";
    char deneme[12] = "asdsad";
    char hakan[15];
    string other;
    

    strncpy(hakan,ebrar,3);
    // strncat(ebrar,hakan,5);

    // cout << hakan << endl;


    // cout << ebrar << endl;


    // getline(cin, other);
    // cout << other << endl;

    // other = cin.get();
    getline(cin, other);
    cin.putback(other[2]);

    other = cin.get();

    cout << other << endl;
    cout << other[3] << endl;



   // asdasdasdsad


    return 0;
}
