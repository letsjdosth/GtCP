#include <iostream>
#include <cstdlib>

using namespace std;

class DayOfYear{
    public: //(c++ 문화적으로) 보통 application단 유저를 위해 public을 위로 올리나봄. 주석과 public을 바로 볼수있게
        void input();
        void output();
        void set(int newMonth, int newDay); //mutator(setter)
        void set(int newMOnth); //(overloading)
        int getMonthNumber(); //accessor(getter)
        int getDay();
    
    private:
        int month;
        int day;
};

int main(){
    DayOfYear today, bachBirthday;
    cout << "Enter today's date:\n";
    today.input();
    cout << "Today's date is ";
    today.output();
    cout << endl;

    bachBirthday.set(3, 21);
    cout << "J.S. Bach's birthday is ";
    bachBirthday.output();
    cout << endl;
    if(today.getMonthNumber() == bachBirthday.getMonthNumber() && today.getDay() == bachBirthday.getDay()){
        cout << "Happy Birthday Johann Sebastian!\n";
    } else {
        cout << "Happy Unbirthday Johann Sebastian!\n";
    }
    return 0;
}

void DayOfYear::set(int newMonth, int newDay){
    if((newMonth>=1) && (newMonth<=12))
        month = newMonth;
    else {
        cout << "Illegal month value! Program aborted.\n";
        exit(1);
    }
    if((newDay>=1) && (newDay)<=31)
        day = newDay;
    else {
        cout << "Illegal day value! Program aborted. \n";
        exit(1);
    }
}

void DayOfYear::set(int newMonth){
    if((newMonth>=1) && (newMonth<=12))
        month = newMonth;
    else {
        cout << "Illegal month value! Program aborted.\n";
        exit(1);
    }
    day=1;
}

int DayOfYear::getMonthNumber(){
    return month;
}

int DayOfYear::getDay(){
    return day;
}

void DayOfYear::input(){
    cout << "Enter the month as a number: ";
    cin >> month;
    cout << "Enter the day of the month: ";
    cin >> day;
    if((month<1) || (month>12) || (day<1) || (day>31)){
        cout << "Illegal date! Program aborted.\n";
        exit(1);
    }
}

void DayOfYear::output(){
    switch(month){
        case 1:
            cout << "Jenuary "; break;
        case 2:
            cout << "Fabruary "; break;
        case 3:
            cout << "March "; break;
        case 4:
            cout << "April "; break;
        case 5:
            cout << "May "; break;
        case 6:
            cout << "June "; break;
        case 7:
            cout << "July "; break;
        case 8:
            cout << "August "; break;
        case 9:
            cout << "September "; break;
        case 10:
            cout << "October "; break;
        case 11:
            cout << "November "; break;
        case 12:
            cout << "December "; break;
        default:
            cout << "Error in DayOfYear::output.";
    }
    cout << day;
}