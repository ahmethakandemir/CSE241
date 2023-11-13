#include <iostream>

class Deneme
{
private:
    int num;
     
public:
    Deneme();    
    Deneme(int num);
    Deneme operator+(const Deneme &other) const;
    Deneme operator-(const Deneme &other) const;
    const Deneme operator=(const Deneme &other);
    friend std::ostream &operator<<(std::ostream &out, const Deneme &other);

    int getNum() const;
    void output() const;
};

Deneme::Deneme()
{
    num = 0;
}

Deneme::Deneme(int input)
{
    num = input;
}

int Deneme::getNum() const
{
    return num;
}

void Deneme::output() const
{
    std::cout << "num: " << num << std::endl;
}

Deneme Deneme::operator+(const Deneme &other) const
{
    Deneme c(num + other.num);
    return c;
}

Deneme operator+(int num, const Deneme &other)
{
    return Deneme(num + other.getNum());
}


Deneme Deneme::operator-(const Deneme &other) const
{
    Deneme c(num - other.num);
    return c;
}

const Deneme Deneme::operator=(const Deneme &other)
{
    num = other.num;
    return *this;
}

std::ostream &operator<<(std::ostream &out, const Deneme &other)
{
    out << other.getNum();
    return out;
}


int main()
{
    Deneme a(3);
    Deneme b(2);
    Deneme c;
    c = a + b;

    std::cout << "c = " << c << std::endl;

    int num = 11;
    Deneme d = c + num;
    std::cout << "d = " << d << std::endl;

    return 0;
}