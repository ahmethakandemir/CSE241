#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;
class MyStr{
    public:
        MyStr (const MyStr& str);
        MyStr (const char* str);
        MyStr();

        int length()const;
        MyStr operator =(const MyStr& str2);
        MyStr operator +=(const MyStr& str2);
        ~MyStr();
        friend ostream& operator<<(ostream& outputstream, const MyStr& str);
    private:
        char *ptr;

};

MyStr::MyStr(const MyStr& str){
    if(str.ptr==nullptr)ptr=nullptr;
    else{
        delete[] ptr;
        ptr = new char [str.length()+1]; //for null 
        strcpy(ptr,str.ptr);
    }
};

MyStr::MyStr(const char* str){
    if(str==nullptr)ptr=nullptr;
    else {
        int length2 = strlen(str);
        ptr = new char [length2+1];
        strcpy(ptr,str);
    }
}

MyStr::MyStr(){
    ptr = new char [1];
    ptr[0]='\0';
}

 int MyStr:: length()const{
    return strlen(ptr);  
};

MyStr MyStr:: operator =(const MyStr& str2){
    if(str2.ptr==nullptr)ptr=nullptr;
    else{
        delete [] ptr;
        ptr = new char [str2.length()+1];
        strcpy(ptr,str2.ptr);
    }
    return *this;
}

MyStr MyStr::operator+=(const MyStr& str2){
    if(str2.ptr==nullptr){
        return *this;
    }
    else{
        char temp[length()];
        strcpy(temp,ptr);
        int lengthpre = length();
        delete[] ptr;
        ptr = new char [lengthpre+str2.length()+1];
        strcpy(ptr,temp);
        strcat(ptr, str2.ptr);
        return *this;
    }
}
ostream& operator<<(ostream& outputstream, const MyStr& str) {
    outputstream << str.ptr;
    return outputstream;
}
MyStr:: ~MyStr(){
    delete [] ptr;
    ptr=nullptr;
}

int main(){
    // MyStr s1("hakan"), s2("sample text");
    // cout<<s1.length()<<endl;
    // cout<<s2.length()<<endl;
    // //s1=s2;
    // // s1+=s2;
    // // MyStr s3(s1);
    // cout<<s1<<endl;
    // // cout<<s3<<endl;
    // cout<<s1.length()<<endl;
    return 0;
}