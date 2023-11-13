#include <iostream>



class deneme
{

public:
    deneme();
    deneme(int num);
    deneme add(deneme &other);
    deneme operator+(const deneme &other) const;
    void output() const;

private:
    int num;

};

deneme deneme::add(deneme &other)
{

    other.num += num;
    return other;
};
deneme::deneme(int num) : num(num) {}
deneme::deneme()
{
    num = 0;
}
deneme deneme::operator+(const deneme &other) const
{
    int result = num + other.num;
    return deneme(result);
}
void deneme::output() const {
    std::cout << "num: " << num << std::endl;
}



int main(){

    deneme a(3);
    a.output();
    decltype(a) b(2);

    deneme c;
    c = a + b;
    std::cout << "sum = ";
    c.output();

    

    return 0;
}
