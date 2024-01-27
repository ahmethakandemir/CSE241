#include <iostream>
#include <cstring>

class MyStr{
public:
    MyStr();
    MyStr(const char* input);
    MyStr(const MyStr& other);
    MyStr operator+(const MyStr&);
    bool operator<(const MyStr&)const;
    bool operator>(const MyStr &) const;
    MyStr operator=(const MyStr&);
    bool operator==(const MyStr &other) const ;
    friend std::ostream& operator<<(std::ostream& out,const MyStr& other);
    char* getStr();
    int getLength() const;
    ~MyStr();
private:
    char* str = nullptr;    
};

std::ostream &operator<<(std::ostream &out, const MyStr &other){

    std::cout << other.str << std::endl;
    return out;
}

MyStr::MyStr(const MyStr &other)
{
    if(other.str != nullptr){
        str = new char[other.getLength() + 1];
        strcpy(str,other.str);
    }
    else{
        str = nullptr;
    }
}

char *MyStr::getStr()
{
    return str;
}

MyStr::~MyStr(){
    delete[] str;
    str = nullptr;
}

MyStr MyStr::operator+(const MyStr &other)
{
    char* temp = new char[getLength() + other.getLength() + 1];
    strcpy(temp,str);
    strcat(temp,other.str);
    return MyStr(temp);
}

bool MyStr::operator<(const MyStr &other) const
{
    return getLength() < other.getLength();
}



bool MyStr::operator>(const MyStr &other) const
{
    return getLength() > other.getLength();
}

MyStr::MyStr() {
    // Delete existing 'str' if it's not nullptr
    if (str != nullptr) {
        delete[] str;
        str = nullptr;  // Set to nullptr after deleting
    }

    // Allocate new memory for 'str'
    str = new char[1];
    str[0] = '\0';
}

MyStr::MyStr(const char* input){
    delete[] str;
    int length = strlen(input);
    char *a = new char[length + 1];
    strcpy(a,input);

    str = a;
}
int MyStr::getLength() const { return strlen(str); }

bool MyStr::operator==(const MyStr &other) const
{
    return (strcmp(str,other.str) == 0);

}

MyStr MyStr::operator=(const MyStr& other) {
    if (this != &other) {
        delete[] str;

        // Check if other.str is not nullptr before copying
        if (other.str != nullptr) {
            str = new char[other.getLength() + 1];
            strcpy(str, other.str);
        } else {
            str = nullptr;  // Set to nullptr if other.str is nullptr
        }
    }
    return *this;
}


int main() {
    // Create MyStr objects
    MyStr a("asd");               // Default constructor
    MyStr b("deneme");     // Constructor with char* input

    // Display initial strings
    std::cout << "Initial strings:" << std::endl;
    std::cout << "a: " << a.getStr() << std::endl;
    std::cout << "b: " << b.getStr() << std::endl;

    // Concatenate strings using operator+
    MyStr c = a + b;
    std::cout << "\nAfter concatenation (c = a + b):" << std::endl;
    std::cout << "a: " << a.getStr() << std::endl;
    std::cout << "b: " << b.getStr() << std::endl;
    std::cout << "c: " << c.getStr() << std::endl;

    // Compare string lengths using operators < and >
    std::cout << "\nString length comparisons:" << std::endl;
    std::cout << "a < b: " << (a < b) << std::endl;
    std::cout << "a > b: " << (a > b) << std::endl;
    std::cout << "a == b: " << (a == b) << std::endl;

    std::cout << "b: " << b.getStr() << std::endl;
    // Assignment using operator=
    MyStr d;
    d = b;
    std::cout << "\nAfter assignment (d = b):" << std::endl;
    std::cout << "d: " << d.getStr() << std::endl;

    std::cout << "\n<< operation overload" << std::endl;
    std::cout << "a = " << a;
    std::cout << "b = " << b;
    std::cout << "c = " << c;
    

    return 0;
}