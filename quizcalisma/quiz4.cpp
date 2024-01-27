#include <iostream>
using namespace std;

class Digit
{
public:
    Digit();
    Digit(int a);
    friend ostream& operator<<(ostream& out, const Digit& d);
    //+ operator overload
    Digit operator++();
    Digit operator++(int a);
    int getNum() const { return num; }
private:
    int num;
};

Digit::Digit()
{
    num = 0;
}
Digit::Digit(int a) { num = a % 10; }
Digit Digit::operator++()
{
    Digit temp;
    temp.num = ++num % 10;
    return temp;
}
Digit Digit::operator++(int a)
{
    Digit temp(num);
    num = ++num % 10;
    return temp;
}

ostream& operator<<(ostream& out,const Digit& d)
{
    out << d.getNum();
    return out;
}

int operator+(Digit& d1, Digit& d2)
{
    return d1.getNum() + d2.getNum();
}

int main(){
    Digit d1(2), d2(2);
    cout << d1++ << endl;
    cout << ++d2 << endl;
    // cout << d1 + d2 << endl;
    return 0;
}
