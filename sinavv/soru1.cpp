#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class mystring{
public:
    int len;
    char *str;
    friend ofstream& operator<<(ofstream& out, const mystring& other);
    friend ifstream& operator>>(ifstream& in, mystring& other);
private:
};

class myint{
public:
    int *num;
private:
};

ofstream& operator<<(ofstream& out, const mystring& other){
    out << other.str;
    return out;
}
ifstream& operator>>(ifstream& in, mystring& other){
    in >> other.str;
    return in;
}



int main(){
    mystring s1;
    s1.str = new char[10];
    strcpy(s1.str, "Merhabafxdcnkml");

    ofstream dosya("deneme.txt");
    dosya << s1;
    dosya << " Dunya";
    dosya.close();

    ifstream dosya2("deneme.txt");

    dosya2 >> s1;

    cout << s1.str << endl;
    cout << "aha bu da aldim verdim str" << endl;

}