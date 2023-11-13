#include <iostream>

using namespace std;

class Digit{
public:
    int num;
    Digit(int a);
    Digit();
    void inc();
    void add(Digit a);
    void output();
};

Digit::Digit(int a){
    num = a;
}

Digit::Digit(){
    num = 0;
}

void Digit::add(Digit a){
    num += a.num;
}

void Digit::output(){
    cout << num << endl;
}
void Digit::inc(){
    num++;
    if(num == 10)
        num = 0;
}

    int main()
{
    Digit d1,d2(9);
    d1.output();
    d2.output();
    d1.inc();
    d2.inc();
    d1.output();
    d2.output();
    d1.add(d2);
    d1.output();

}