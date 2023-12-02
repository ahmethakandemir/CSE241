#include <iostream>
using namespace std;

class Rational{
public:
    Rational(int nume = 0, int denume = 1) : num(nume), denum(denume){};
    Rational(const Rational& other);
    void setter(int num, int denum);
    static void printCounter();
    friend ostream& operator<<(ostream& out,const Rational& other);
    bool operator!=(const Rational& other)const;
    bool operator==(const Rational& other)const;
    Rational operator++();
    Rational operator++(int);
    Rational operator--();
    Rational operator--(int);
    Rational operator-();
    Rational operator-(const Rational& other);
    Rational operator+(const Rational& other);
    Rational operator*(const Rational& other);
    Rational operator/(const Rational& other);
    Rational operator=(const Rational &other);

private : 
    static int counter;
    double num;
    double denum;
};

Rational::Rational(const Rational& other) : num(other.num), denum(other.denum) {
    counter++;
}

Rational Rational::operator=(const Rational &other){
    num = other.num;
    denum = other.denum;
    return *this;
}

Rational Rational::operator*(const Rational& other){

    num = num * other.num;
    denum = other.denum * denum;
    return *this;
}
Rational Rational::operator/(const Rational& other){

    num = num * other.denum;
    denum = other.num * denum;
    return *this;
}



Rational Rational::operator-(const Rational& other){
    int temp_num;
    int temp_denum;

    temp_num = num * other.denum;
    temp_denum = denum * other.denum;
    temp_num = temp_num - (other.num * denum);
    return Rational(temp_num,temp_denum);

}
Rational Rational::operator+(const Rational& other){
    int temp_num;
    int temp_denum;

    temp_num = num * other.denum;
    temp_denum = denum * other.denum;
    temp_num = temp_num + (other.num * denum);
    return Rational(temp_num,temp_denum);
}

Rational Rational::operator-(){
    num = -num;
    return *this;
}

Rational Rational::operator++(){
    num += denum;
    return *this;
}
Rational Rational::operator++(int){
    num += denum;
    return Rational(num - denum);
}
Rational Rational::operator--(){
    num -= denum;
    return *this;
}
Rational Rational::operator--(int){
    num -= denum;
    return Rational(num + denum);
}


bool Rational::operator!=(const Rational& other)const{
    return (num/denum != other.num/other.denum);
}
bool Rational::operator==(const Rational& other)const{
    return (num/denum == other.num/other.denum);
}


ostream &operator<<(ostream& out,const Rational& other){
    cout << other.num << "/" << other.denum << endl;
    return out;
}


void Rational::printCounter(){
    cout << counter << endl;
}


int Rational::counter = 0;

void Rational::setter(int nume, int denume){
    num = nume;
    denum = denume;
}



int main() {
    // Create two Rational objects
    Rational r1(3, 4);
    Rational r2(1, 2);
    cout << "r1 = " << r1;
    cout << "r2 = " << r2;
    // Test copy constructor
    Rational r3 = r1;

    // Test various operations
    Rational result;

    result = r1 + r2;
    cout << "r1 + r2 = " << r1 + r2;

    result = r1 - r2;
    cout << "r1 - r2 = " << result;

    result = r1 * r2;
    cout << "r1 * r2 = " << result;

    result = r1 / r2;
    cout << "r1 / r2 = " << result;

    cout << "Is r1 != r2? " << (r1 != r2) << endl;
    cout << "Is r1 == r2? " << (r1 == r2) << endl;

    cout << "Increment r1: " << ++r1;
    cout << "Post-increment r1: " << r1++;

    cout << "Decrement r2: " << --r2;
    cout << "Post-decrement r2: " << r2--;

    // Print the counter value
    Rational::printCounter();

    return 0;
}
