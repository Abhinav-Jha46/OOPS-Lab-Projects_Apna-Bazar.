#include <iostream>
#include <windows.h>
#include <fstream>
#include <sstream>
using namespace std;

class Login
{

private:
    string user_name;
    string pass_word;

public:
    // constructor
    Login()
    {
        // initail values ;
        user_name = "";
        pass_word = "";
    }

    // setting the name of user in private;
    void set_userName(string user_name)
    {
        this->user_name = user_name;
        return;
    }

    // setting the user password in private;
    void set_Password(string pass_word)
    {
        this->pass_word = pass_word;
        return;
    }

    // getting user_name from private;
    string get_userName()
    {
        return user_name;
    }

    // gettign user password from private;
    string get_Password()
    {
        return pass_word;
    }
};

void Register(Login &user_u)
{
    string userName, password;
    
    cout << "Enter user name: ";
    getline(cin, userName);
    user_u.set_userName(userName);

    cout << "Enter password: ";
    getline(cin, password);
    user_u.set_Password(password);

    ofstream writeFile("loginFile.txt", ios::app);
    if (!writeFile)
    {
        cout << "Error: Unable to open file for writing!" << endl;
        return;
    }

    writeFile << user_u.get_userName() << ":" << user_u.get_Password() << endl;
    writeFile.close();

    cout << "\033[1;32m" << "User Registered Successfully!" << "\033[0m" << endl;
    Sleep(2000);
    system("cls");
}

void login(Login &user_u)
{
    string verify_userName, verify_password;
    cout << "Enter user name to verify: ";
    getline(cin, verify_userName);

    cout << "Enter user password to verify: ";
    getline(cin, verify_password);

    ifstream readFile("loginFile.txt");
    if (!readFile)
    {
        cout << "Error: Unable to open file for reading!" << endl;
        return;
    }

    string line;
    bool found = false;

    while (getline(readFile, line))
    {
        size_t delimiter_pos = line.find(':');
        if (delimiter_pos == string::npos) continue; // Skip invalid lines

        string stored_userName = line.substr(0, delimiter_pos);
        string stored_password = line.substr(delimiter_pos + 1);

        if (verify_userName == stored_userName && verify_password == stored_password)
        {
            found = true;
            break;
        }
    }
    readFile.close();

    if (found)
    {
        cout << "Please wait";
        for (int i = 0; i < 3; i++)
        {
            cout << ".";
            Sleep(800);
        }
        system("cls");
        cout << "\033[1;32m" << "Welcome back!" << "\033[0m" << endl;
    }
    else
    {
        cout << "\033[1;31m" << "Incorrect Username or Password. Please try again!" << "\033[0m" << endl;
    }
    Sleep(2000);
    system("cls");
}

int main()
{
    Login user;
    bool flag = true;

    while (flag)
    {
        int user_input;

        cout << "\033[1;32m" << "\t********** Welcome to Registration Login Form **********" << "\033[0m" << endl;
        cout << "Choose an option:" << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;

        cin >> user_input;
        cin.ignore(); // To consume the trailing newline from input buffer

        switch (user_input)
        {
        case 1:
            Register(user);
            break;
        case 2:
            login(user);
            break;
        case 3:
            cout << "You quit!" << endl;
            flag = false;
            break;
        default:
            cout << "Invalid input. Please try again";
            for(int i = 0; i < 3; i++)
            {
                cout << ".";
                Sleep(1000);
            }
            system("cls");
        }
    }
    return 0;
}
