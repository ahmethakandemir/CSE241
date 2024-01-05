#include <string>
#include <cstdlib>
#include <iostream>
#include "employee.h"


using std::string;
using std::cout;
namespace SavitchEmployees{

    Employee::Employee() : name('\0'), ssn('\0'), netPay(0){}
    Employee::Employee(const string& theName,const string& theSsn) : name(theName), ssn(theSsn), netPay(0){}
    string Employee::getName()const{return name;} 
    string Employee::getSsn()const{return ssn;} 
    double Employee::getNetPay()const{return netPay;}
    void Employee::setName(const string& newName){name = newName;}
    void Employee::setSsn(const string& newSsn){ssn = newSsn;}
    void Employee::setNetPay(double newNetPay){netPay = newNetPay;}
    void Employee::printCheck()const{
        cout << "bu class icin neyi print ediyon!!" << std::endl;
    }





}

