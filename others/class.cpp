#include <iostream>
#include <string>

using namespace std;

class Common
{
public:
    int age;
    string name;
};

class Student : public Common
{
public:
    int studentClass;
};

class Teacher : public Common
{
public:
    string subject;
};

class TeachingAssistant : public Student, public Teacher
{
public:
    void displayTAInfo()
    {
        cout << "Teaching Assistant Name: " << Student::name << endl;
        cout << "Age: " << Student::age << " years" << endl;
        cout << "Teaching in Class: " << studentClass << endl;
        cout << "Teaching Subject: " << subject << endl;
    }
};
