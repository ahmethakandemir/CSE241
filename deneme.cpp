#include <string>
#include <iostream>
#include <string>
using namespace std;

class Person{
protected:
    int age;
    std::string name;
public:
    Person():age(0),name('\0'){}
    Person(int theAge=0, string theName="\0"):age(theAge),name(theName){}
    string getName()const{return name;}
    int getAge()const{return age;}
    friend ostream& operator<<(ostream& out, const Person& other){
    cout<<other.getName()<<other.getAge();
    return out;}
    void nameSetter(std::string theName){name=theName;}
    void ageSetter(int theAge){age=theAge;}
};

class Student: public Person{
protected:
    double GPA;
public:
    Student():Person(),GPA(0){}
    Student(int theAge, string theName, double GPA):Person(theAge,theName),GPA(GPA){}
    friend ostream& operator<<(ostream& out,const Student& other){
    cout<<Person::getName()<<'\n';
    cout<<Person::getAge();
    cout<<"GPA is: "<<getGPA;
    return out;
}
    double getGPA()const{return GPA;}
    void setGPA(double other){GPA=other;}
};