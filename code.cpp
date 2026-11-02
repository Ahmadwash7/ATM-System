#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <cctype>
#include <limits>

using namespace std;

const string ClientsFile = "Clients.txt";

enum enMainMenu
{
    eQuickWithdraw = 1,
    eNormalWithdraw = 2,
    eDeposit = 3,
    eCheckBalance = 4,
    eLogout = 5
};

enum enQuickWithdraw
{
    e20 = 1,
    e50 = 2,
    e100 = 3,
    e200 = 4,
    e400 = 5,
    e600 = 6,
    e800 = 7,
    e1000 = 8,
    eExit = 9
};

struct stClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string PhoneNumber;
    double AccountBalance = 0;
    bool MarkForDelete = false;
};

int ReadNumber();

vector<string> SplitString(string S1, string Delim)
{
    vector<string> vString;
    
    short pos = 0;
    string sWord;
    
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos);
        if (sWord != "")
        {
            vString.push_back(sWord);
        }
        S1.erase(0, pos + Delim.length());
    }
    
    if (S1 != "")
    {
        vString.push_back(S1);
    }
    
    return vString;
}

stClient ConvertLinetoRecord(string Line, string Separator = "#//#")
{
    stClient Client;
    
    vector<string> vClient;
    
    vClient = SplitString(Line, Separator);
    
    if (vClient.size() != 5)
    {
        return Client;
    }
    
    Client.AccountNumber = vClient[0];
    Client.PinCode = vClient[1];
    Client.Name = vClient[2];
    Client.PhoneNumber = vClient[3];
    Client.AccountBalance = stod(vClient[4]);
    
    return Client;
}

vector<stClient> LoadClientsDataFromFile(string FileName)
{
    vector<stClient> vClient;
    
    fstream MyFile;
    
    MyFile.open(FileName, ios::in);
    
    if (MyFile.is_open())
    {
        string Line;
        stClient Client;
        
        while (getline(MyFile, Line))
        {
            Client = ConvertLinetoRecord(Line);
            vClient.push_back(Client);
        }
        
        MyFile.close();
    }
    
    return vClient;
}

string ConvertRecordToLine(stClient Client, string Seperator = "#//#")
{
    
    string stClientRecord = "";
    
    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.PhoneNumber + Seperator;
    stClientRecord += to_string(Client.AccountBalance);
    
    return stClientRecord;
}

vector<stClient> SaveClientDataToFile(string FileName, vector<stClient> vClient)
{
    fstream MyFile;
    
    MyFile.open(FileName, ios::out); // overwrite
    string DataLine;
    
    if (MyFile.is_open())
    {
        for (stClient C : vClient)
        {
            if (C.MarkForDelete == false)
            {
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return vClient;
}

bool LoginClientCheck(stClient &Client, vector<stClient> &vClient)
{
    for (stClient &C : vClient)
    {
        if (C.AccountNumber == Client.AccountNumber && C.PinCode == Client.PinCode)
        {
            Client = C;
            return true;
        }
    }
    return false;
}

void LoginScreen()
{
    cout << "===========================================" << endl;
    cout << "\t      Login" << endl;
    cout << "===========================================" << endl;
}

bool LoginUser(stClient &Client, vector<stClient> &vClient)
{
    while (true)
    {
        cout << "Enter Account Number: ";
        cin >> Client.AccountNumber;
        
        cout << "Enter Password: ";
        cin >> Client.PinCode;
        
        if (LoginClientCheck(Client, vClient))
        {
            return true;
        }
        else
        {
            system("clear");
            LoginScreen();
            cout << "Invalid Account Number/PinCode!" << endl;
        }
    }
    return false;
}

void ShowMainMenu()
{
    cout << "===========================================" << endl;
    cout << "\t     ATM Main Menu " << endl;
    cout << "===========================================" << endl;
    
    cout << "\t [1] Quick Withdraw." << endl;
    cout << "\t [2] Normal Withdraw." << endl;
    cout << "\t [3] Deposit." << endl;
    cout << "\t [4] Check Balances." << endl;
    cout << "\t [5] Logout." << endl;
    
    cout << "===========================================" << endl;
}

void showQuickWithdraw()
{
    cout << "===========================================\n";
    cout << "\t       Quick Withdarw\n";
    cout << "===========================================\n";
    
    cout << "\t[1] 20          [2] 50" << endl;
    cout << "\t[3] 100         [4] 200" << endl;
    cout << "\t[5] 400         [6] 600" << endl;
    cout << "\t[7] 800         [8] 1000" << endl;
    cout << "\t[9] Exit" << endl;
    cout << "===========================================\n";
}

short GetQuickWithdraw(enQuickWithdraw QuickWithdraw)
{
    short NumQuickWithdraw[8] = {20, 50, 100, 200, 400, 600, 800, 1000};

    return NumQuickWithdraw[QuickWithdraw - 1];
}

bool CheckAmountWithdraw(int Amount, stClient Client)
{
    if (Amount <= 0)
    {
        cout << "\nInvalid Withdraw Amount!" << endl;
        return false;
    }

    else if (Amount > Client.AccountBalance)
    {
        cout << "\nAmount Exceeds the balance, you can Withdraw up to : " << Client.AccountBalance << endl;
        return false;
    }

    return true;
}

enQuickWithdraw ReadQuickWithdraw()
{
    short Choice;

    do
    {
        cout << "Choose a Withdrawal Option [1 to 9]: ";
        Choice = ReadNumber();

    } while (Choice < 1 || Choice > 9);

    return (enQuickWithdraw)Choice;
}

bool QuickWithdrawTrans(stClient &Client, vector<stClient> &vClient)
{
    showQuickWithdraw();
    cout << "Your Balance is: " << Client.AccountBalance << endl;

    vClient = LoadClientsDataFromFile(ClientsFile);

    short ReadChoose = 0;

    enQuickWithdraw Choice = ReadQuickWithdraw();

    if (Choice == eExit)
    {
        return false;
    }

    ReadChoose = GetQuickWithdraw(Choice);

    if (!CheckAmountWithdraw(ReadChoose, Client))
    {
        return false;
    }

    char Answer;
    cout << "\nAre you sure you want to perform this transaction? (Y/N): ";
    cin >> Answer;

    if (toupper(Answer) != 'Y')
    {
        cout << "\nTransaction Cancelled." << endl;
        return false;
    }

    Client.AccountBalance -= ReadChoose;

    for (stClient &C : vClient)
    {
        if (C.AccountNumber == Client.AccountNumber)
        {
            C.AccountBalance = Client.AccountBalance;
            break;
        }
    }

    SaveClientDataToFile(ClientsFile, vClient);
    cout << "\nDone Successfully. Your New Balance [" << Client.AccountBalance << "]" << endl;

    return true;
}

void showNormalWithdrawScreen()
{
    cout << "===========================================\n";
    cout << "\t       Normal Withdraw\n";
    cout << "===========================================\n";
}

int NormalAmountCheck(stClient &Client)
{
    int Amount = 0;
    while(true)
    {
        cout << "\nEnter an Amount Multiple of 5's: ";
        cin >> Amount;
    
        if(Amount % 5 == 0 && CheckAmountWithdraw(Amount, Client))
        {
            return Amount;
        }
    }
}

bool NormalWithdrawTrans(stClient &Client, vector<stClient> &vClient)
{
    showNormalWithdrawScreen();
    vClient = LoadClientsDataFromFile(ClientsFile);
    
    int Amount = 0;
    Amount = NormalAmountCheck(Client);
    
    char Answer;
    cout << "\nAre you sure you want to perform this transaction? (Y/N): ";
    cin >> Answer;

    if (toupper(Answer) != 'Y')
    {
        cout << "\nTransaction Cancelled." << endl;
        return false;
    }

    Client.AccountBalance -= Amount;


    for (stClient &C : vClient)
    {
        if (C.AccountNumber == Client.AccountNumber)
        {
            C.AccountBalance = Client.AccountBalance;
            break;
        }
    }

    SaveClientDataToFile(ClientsFile, vClient);
    cout << "\nDone Successfully. Your New Balance [" << Client.AccountBalance << "]" << endl;

    return true;
}

void showDepositScreen()
{
    cout << "===========================================\n";
    cout << "\t       Deposit\n";
    cout << "===========================================\n";
}

int ReadDeposit()
{
    int Amount = 0;
    
    while(true)
    {
        cout << "Enter a Positive Deposit Amount: ";
        cin >> Amount; 

        if(Amount > 0)
        {
            return Amount;
        }
        cout << "\nInvalid Input, ";
    }

}

bool DepositTrans(stClient &Client, vector<stClient> &vClient)
{
    showDepositScreen();
    vClient = LoadClientsDataFromFile(ClientsFile);
    
    int Amount = ReadDeposit();
    
    char Answer;
    cout << "\nAre you sure you want to perform this transaction? (Y/N): ";
    cin >> Answer;

    if (toupper(Answer) != 'Y')
    {
        cout << "\nTransaction Cancelled." << endl;
        return false;
    }

    Client.AccountBalance += Amount;


    for (stClient &C : vClient)
    {
        if (C.AccountNumber == Client.AccountNumber)
        {
            C.AccountBalance = Client.AccountBalance;
            break;
        }
    }

    SaveClientDataToFile(ClientsFile, vClient);
    cout << "\nDone Successfully. Your New Balance [" << Client.AccountBalance << "]" << endl;

    return true;
}

void CheckBalance(stClient Client)
{
    cout << "===========================================\n";
    cout << "\t       Check Balance\n";
    cout << "===========================================\n";

    cout << "Your Balance is: " << Client.AccountBalance << endl;
}

int ReadNumber()
{
    int Number;

    while (!(cin >> Number))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\nInvalid input, please enter a number: ";
    }
    return Number;
}

enMainMenu ReadMainMenu(short &MenuList)
{
    do
    {
        cout << "Choose What do You want To Do [1 To 5]: ";
        MenuList = ReadNumber();

    } while (MenuList < 1 || MenuList > 5);

    return (enMainMenu)MenuList;
}

void GoBackToMenu()
{
    cout << "\nPress any key to go back to Menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();

    system("clear");
}

void Login();

void MainMenu(short &MenuList, stClient &Client)
{
    vector<stClient> vClient;

    do
    {
        system("clear");

        ShowMainMenu();
        ReadMainMenu(MenuList);

        switch (MenuList)
        {
            case eQuickWithdraw:
            {
                system("clear");
                QuickWithdrawTrans(Client, vClient);
                GoBackToMenu();
                break;
            }
    
            case eNormalWithdraw:
            {
                system("clear");    
                NormalWithdrawTrans(Client, vClient);
                GoBackToMenu();
                break;
            }
    
            case eDeposit:
            {
                system("clear");    
                DepositTrans(Client, vClient);
                GoBackToMenu();
                break;
            }
    
            case eCheckBalance:
            {
                system("clear");
                CheckBalance(Client);
                GoBackToMenu();
                break;
            }
    
            case eLogout:
            {
                Login();
            }
        }

    }while (MenuList != eLogout);
    
}

void Login()
{
    stClient Client;
    vector<stClient> vClient;
    vClient = LoadClientsDataFromFile(ClientsFile);

    system("clear");
    LoginScreen();

    if (LoginUser(Client, vClient))
    {
        short MenuList = 0;
        MainMenu(MenuList, Client);
    }
}

int main()
{
    Login();
}
