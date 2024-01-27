#include <iostream>
#include <string>

using namespace std;

class DayOfYear
{
public:
    DayOfYear(int monthValue, int dayValue){}
    DayOfYear();
    void input(){
        cout << "enter a month and day! " << endl;
        cin >> day >> month;
    }
    void output();


    int getMonthNumber(){
        return month;
    }
    int getDay(){
        return day;
    }
private:
    int month = 1;
    int day = 1;
};

void DayOfYear::output(){
    cout << "day and month is: " << day << " " << month << endl;
}



class Holiday{
public:
    Holiday();
    Holiday(int month, int day, bool enforcement);
    void output()
    {
        if (parkingEnforcement)
            cout << "bugun tatill" << endl;
        else
            cout << "bugun tatil degil" << endl;
    }

private:
    DayOfYear date;
    bool parkingEnforcement;
};

Holiday::Holiday(int month, int day, bool enforcement) : date(month, day), parkingEnforcement(enforcement) {}
Holiday::Holiday()
{
}
