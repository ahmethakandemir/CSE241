#include <cstring>
#include <iostream>

using namespace std;

class MyStr{
public:
    MyStr(){
        str = new char[1];
        str[0] = '\0';
    }

    MyStr(const char* input){

        str = new char[length() + 1];
        strcpy(str,input);
    
    }
    friend ostream& operator<<(ostream& out, const MyStr& other){
        out << other.str;
        return out;
    }
    MyStr(MyStr& other){
        delete[] str;
        if(other.str == nullptr){
            str = nullptr;
        }
        else{
        str = new char[other.length() + 1];
        strcpy(str,other.str);
        }
    }



    int length() const {
        if(str == nullptr){
            return 0;
        }
        else{
            return strlen(str);
        }
    }

    MyStr operator+=(const MyStr& other){
    if(other.str == nullptr){
        return *this;
    }
    else{
        char* temp = new char[length() + 1];
        strncpy(temp,str,length());
        delete[] str;
        str = new char[strlen(temp) + other.length() + 1];
        strncpy(str,temp,strlen(temp) + 1);
        strcat(str,other.str);
        return *this;
    }
}

    MyStr operator=(const MyStr& other){
        delete[] str;
        if(other.str == nullptr){
            str = nullptr;
        }
        else{
            str = new char[other.length() + 1];
            strcpy(str,other.str);
        }
        return *this;
    }


    ~MyStr(){
        delete[] str;
    }


private:
    char *str = nullptr;


};


int main(){

    MyStr s1,s2("sample text");
    cout << s2.length() << endl;
    for(int i = 0; i < s2.length(); ++i){
        s1 += s2;
    }
    s2 = s1;
    MyStr s3(s2);

    MyStr* s4 = new MyStr(s3);

    cout <<"s4 length "<< *(s4) << endl;

    cout << s1.length() << endl;
    cout << s2.length() << endl;
    cout << s3.length() << endl;
    
    return 0;
}



