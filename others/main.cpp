#include <iostream>
#include <vector>

using namespace std; // Use the std namespace

class DayOfYear
{
public:
    DayOfYear(int monthValue, int dayValue)
    {
        month = monthValue;
        day = dayValue;
    }
    DayOfYear(int monthValue)
    {
        month = monthValue;
    }
    DayOfYear(){
        // intentionally blank
    };

    void input();
    void output();
    int getMonthNumber();
    int getDay();
    void set(int newMonth, int newDay);
    void set(int newMonth);

private:
    int month;
    int day;
};

class Birthday
{
public:
    Birthday(DayOfYear thisday)
    {
        today = thisday;
    }
    int getDay();
    int getMonth();
    void input();
    bool isBirthday();

private:
    DayOfYear today;
    int day;
    int month;
};

bool Birthday::isBirthday()
{
    if ((today.getMonthNumber() == getMonth()) && (today.getDay() == getDay()))
    {
        cout << "happy birthday" << endl;
        return true;
    }
    cout << "Happy unbirthday" << endl;
    return false;
}

int Birthday::getDay()
{
    return day;
}
int Birthday::getMonth()
{
    return month;
}
void Birthday::input()
{
    cout << "enter a month and day for birthday! " << endl;
    cin >> month >> day;
}

void DayOfYear::set(int newMonth, int newDay)
{
    month = newMonth;
    day = newDay;
}

void DayOfYear::set(int newMonth)
{
    month = newMonth;
}

void DayOfYear::input()
{
    cout << "enter a month and day! " << endl;
    cin >> month >> day;
}

void DayOfYear::output()
{
    cout << "month and day is: " << month << " " << day << endl;
}

int DayOfYear::getDay()
{
    return day;
}

int DayOfYear::getMonthNumber()
{
    return month;
}

int main()
{

    DayOfYear today;
    today.input();
    today.output();

    Birthday birth(today);
    birth.input();
    birth.isBirthday();

    return 0;
}
