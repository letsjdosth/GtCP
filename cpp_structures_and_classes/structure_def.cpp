#include <iostream>

using namespace std;

struct CDAccountV1{
    double balance;
    double interestRate;
    int term; // months until maturity
}; //<- ;를 찍어줘야한다...

void getData(CDAccountV1& theAccount);

int main(){
    CDAccountV1 account;
    getData(account);

    double rateFraction, interest;
    rateFraction = account.interestRate/100.0;
    interest = account.balance * (rateFraction * (account.term / 12.0));
    account.balance = account.balance + interest;

    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);
    cout << "When your CD matures in "
        << account.term << " months,\n"
        << "It will have a balance of $"
        << account.balance << endl;
    
    return 0;
}

void getData(CDAccountV1& theAccount){
    cout << "Enter account balance : $";
    cin >> theAccount.balance;
    cout << "Enter account interest rate: ";
    cin >> theAccount.interestRate;
    cout << "Enter the number of months until maturity: ";
    cin >> theAccount.term;
}