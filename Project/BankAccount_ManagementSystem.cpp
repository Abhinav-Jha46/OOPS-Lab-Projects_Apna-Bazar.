// #include<iostream>
#include <bits/stdc++.h>
using namespace std;

class BankAccount
{
private:
    int Account_no;
    double Current_Balance;
    static int count; // count = total account;

public:
    BankAccount(int Account_no, double Current_Balance)
    {
        this->Account_no = Account_no;
        this->Current_Balance = Current_Balance;
        count++; // total account++;
    }

    static void displayTotal_Accounts()
    {
        cout << "Total no of accounts are : " << count << endl;
        return;
    }

    void display_AcNo_Bal()
    {
        cout << "Acc No : " << this->Account_no << "  " << "Balance in Rupees : " << this->Current_Balance << endl;
        return;
    }

    static void deposit(BankAccount &Account_no, double Amount)
    {
        Account_no.Current_Balance += Amount;
        cout << "\nBalance deposited , your current balance after deposit: " << Account_no.Current_Balance << endl;
    }

    static void Withdraw(BankAccount &AccountNo, double Amount)
    {
        if (AccountNo.Current_Balance >= Amount)
        {
            AccountNo.Current_Balance -= Amount;
            cout << "\nWithdrawl Complete! Current balance: " << AccountNo.Current_Balance << endl;
        }
        else
        {
            cout << "\nbalance in insufficient. you cant withdraw ! " << endl;
        }
    }
};

int BankAccount ::count;

int main()
{

    BankAccount account1(01, 500); // 500 = current balance
    account1.display_AcNo_Bal();
    BankAccount :: displayTotal_Accounts();

    // account1.deposit(account1, 100); // 500 + 100 = 600 = current balance after deposit of 100 rupees into bank account of acc no 1;
    BankAccount :: deposit(account1, 100);
    account1.display_AcNo_Bal();
    BankAccount :: displayTotal_Accounts();

    account1.Withdraw(account1, 200); // 600 - 200 = 400 = current balance after withdrawl of 200 rupees from bank account of acc no 1;
    account1.display_AcNo_Bal();      // if there were 700 in place of 200 then we cant withdraw the money!
    BankAccount ::displayTotal_Accounts();



    cout << endl;
    cout << endl;


    BankAccount account2(02, 1000); 
    account2.display_AcNo_Bal();
    BankAccount ::displayTotal_Accounts();

    account2.deposit(account2, 100); 
    account2.display_AcNo_Bal();
    BankAccount ::displayTotal_Accounts();

    account2.Withdraw(account2, 200); 
    account2.display_AcNo_Bal();     
    BankAccount ::displayTotal_Accounts();


    cout << endl;
    cout << endl;


    BankAccount account3(03,2000); 
    account3.display_AcNo_Bal();
    BankAccount ::displayTotal_Accounts();

    account3.deposit(account3, 100); 
    account3.display_AcNo_Bal();
    BankAccount ::displayTotal_Accounts();

    account3.Withdraw(account3, 200); 
    account3.display_AcNo_Bal();      
    BankAccount ::displayTotal_Accounts();

    return 0;
}