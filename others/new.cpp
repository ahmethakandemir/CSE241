#include <iostream>
#include <iomanip>
#include <vector>
#include "ders.cpp"

int addRef(int* a, int* b) {
    int swap = *a;
    *a = *b;
    *b = swap;
    
    return *a + *b;
}

int add(int &a, int &b) {    // EN IYISI BU BASKA KULLANAN TOP
    int swap = a;
    a = b;
    b = swap;
    
    return a + b;
}
int addres(int a, int b) {
    int swap = a;
    a = b;
    b = swap;
    
    return a + b;
}

int sum(int a, int b) {
    return a + b;
}

int main(){
using namespace std;  // Use the std namespace

int a;
int b;

a = 15;

b = 10;

// cout << "call by reference by using pointer: " << setw(20) << addRef(&a, &b) << "   a = " << a << "   b = " << b << endl;
 
// cout << "call by reference by using only address: "  << setw(15) << add(a, b) << "   a = " << a << "   b = " << b << endl;   //EN IYISI BU BASKA KULLANAN TOP

//cout <<"call by value: "  << setw(41) << addres(a, b) << "   a = " << a << "   b = " << b << endl;


vector<int> numbers;

// vector<int> numbers2;
// numbers2.assign(3, 5);


for (int i = 10; i <= 50; i += 10) {
    numbers.push_back(i);
}
// numbers.push_back(35);

//cout << "vector size is: " << numbers.size() << endl;
//cout << "max vector size is: " << numbers.max_size() << endl;

// numbers.resize(3);

//cout << "vector size is: " << numbers.size() << endl;

//numbers.erase(numbers.end() - 1); // 1,2,3,4,5
// numbers.pop_back();

//numbers.insert(numbers.begin() + 3, 35);

//numbers.swap(numbers2);

// cout << numbers.front() << endl;
// cout << numbers.back() << endl;
// cout << numbers.at(3) << endl;


// cout << "-----------" << endl << "1. Numbers" << endl << "-----------" << endl;
// for (int i : numbers) {
//     cout << i << endl;
// }

// cout << "-----------" << endl << "2. Numbers" << endl << "-----------" << endl;
// for (int i : numbers2) {
//     cout << i << endl;
// }



// DayOfYear today(2,3);

// cout << today.getDay() << endl;

// today.input();

// today.output();



    // Create a DayOfYear object
    DayOfYear myDate(3, 15);

    // Display the initial date
    cout << "Initial Date: ";
    myDate.output();

    // Input a new date
    myDate.input();

    // Display the updated date
    cout << "Updated Date: ";
    myDate.output();

    // Create a Holiday object
    Holiday myHoliday(12, 25, false);

    // Check if it's a holiday
    cout << "Is it a holiday? ";
    myHoliday.output();







return 0;




}
