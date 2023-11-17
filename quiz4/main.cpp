#include <iostream>
#include <fstream>

using namespace std;

class Digit
{
public:
    Digit() : num(0){};
    Digit(int d) : num(d){};
    friend ostream &operator<<(ostream &out, const Digit &d);
    friend Digit operator+(const int sayi, const Digit& d);
    Digit operator+(const Digit &other) const;
    Digit operator++();
    Digit operator++(int);
    
private:
    int num;
};

Digit Digit::operator+(const Digit &other) const
{
    Digit d(num + other.num);
    return d;
}

Digit operator+(const int sayi, const Digit& d)
{
    return Digit((sayi + d.num)%10);
}
Digit Digit::operator++(){
    return Digit((++num)%10);
}

Digit Digit::operator++(int){
    Digit t(num);
    (num++)%10;
    return t;
}
ostream& operator<<(ostream& out, const Digit &temp){
    out << (temp.num)%10 << endl;
    return out;
}
// ofstream& operator<<(ofstream& out, const Digit &temp){
//     out << temp.num << endl;
//     return out;
// }



int main()
{

    Digit d1, d2(12);
    const Digit d3(3);

    ofstream file("output.txt");
    file << d1 << d2;
    cout << ++d2;
    cout << d1++;
    cout << 1 + 2 + d1 + d3;
    file.close();

    return 0;
}