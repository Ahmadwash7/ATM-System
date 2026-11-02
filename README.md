# 🏧 ATM System

> A simple and interactive **C++ console application** that simulates an ATM machine, with client login, quick and normal withdrawals, deposits, balance checking, and persistent file storage.

This project was built to practice **problem solving, functions, structs, enums, file handling, vectors, input validation, and clean code organization** using C++.

---

## 🚀 What Can You Do?

After logging in, the main menu gives you access to:

| Option | Feature               | Description                                              |
| :----: | --------------------- | -------------------------------------------------------- |
|  ⚡ 1  | **Quick Withdraw**    | Withdraw a preset amount with a single choice            |
|  💵 2  | **Normal Withdraw**   | Withdraw any amount that is a multiple of 5              |
|  ➕ 3  | **Deposit**           | Add a positive amount to your account                    |
|  📊 4  | **Check Balance**     | Display your current balance                             |
|  🚪 5  | **Logout**            | Go back to the login screen for the next client          |

Every withdrawal and deposit asks for a **confirmation (Y/N)** before the balance is changed.

---

## 🔐 Login

The program starts with a login screen:

```text
===========================================
              Login
===========================================
Enter Account Number:
Enter Password:
```

Wrong credentials show `Invalid Account Number/PinCode!` and ask again until the login is correct.

---

## ⚡ Quick Withdraw

Selecting **[1] Quick Withdraw** opens a screen with preset amounts:

```text
===========================================
              Quick Withdraw
===========================================
    [1] 20          [2] 50
    [3] 100         [4] 200
    [5] 400         [6] 600
    [7] 800         [8] 1000
    [9] Exit
===========================================
```

* Your current balance is displayed before choosing.
* The amount is validated against your available balance.
* Choosing `9` takes you back without any transaction.

---

## 💵 Normal Withdraw & Deposit

* **Normal Withdraw** — enter any amount that is a **multiple of 5**. If it exceeds your balance, the program shows the maximum you can withdraw and asks again.
* **Deposit** — enter a **positive** amount to add to your balance.
* Both operations ask for confirmation, then save the new balance to the file immediately.

```text
Are you sure you want to perform this transaction? (Y/N): Y

Done Successfully. Your New Balance [5900]
```

---

## 💾 Data Persistence

The system uses a text file, so your data **doesn't disappear when the program closes**.

### `Clients.txt`

```text
AccountNumber#//#PinCode#//#Name#//#PhoneNumber#//#Balance
```

```text
A1201#//#1234#//#Ahmad Walid#//#+962771983925#//#6000.000000
B1202#//#5678#//#Farid Yasin#//#+962701981759#//#2000.000000
C1203#//#9101#//#Tariq Majd#//#+962790123456#//#50000.000000
```

> ⚠️ **Important:** `Clients.txt` must exist before the first run, otherwise nobody can log in. Lines that don't contain exactly 5 fields are treated as empty records.

---

## 👤 Client Information

Every client contains:

* 🔢 **Account Number**
* 🔐 **PIN Code**
* 👤 **Full Name**
* 📱 **Phone Number**
* 💰 **Account Balance**

---

## 🧠 What I Practiced

```text
C++
├── Functions
├── Structs
├── Enums
├── Vectors
├── Loops
├── Input Validation
├── File Handling
├── String Manipulation
├── Data Serialization
├── Login System
├── Banking Transactions (Withdraw / Deposit)
└── Menu-Driven Programs
```

I also practiced separating the program into smaller functions instead of putting everything inside `main()`.

---

## 🏗️ Code Structure

### Struct & Enums

```cpp
stClient          // a bank client
enMainMenu        // main menu options
enQuickWithdraw   // quick withdraw options
```

### File Handling

```cpp
LoadClientsDataFromFile()
SaveClientDataToFile()
```

### Data Conversion

```cpp
SplitString()
ConvertLinetoRecord()
ConvertRecordToLine()
```

### Login

```cpp
Login()
LoginUser()
LoginClientCheck()
LoginScreen()
```

### Transactions

```cpp
QuickWithdrawTrans()
NormalWithdrawTrans()
DepositTrans()
CheckBalance()
CheckAmountWithdraw()
```

### Menus & Input

```cpp
ShowMainMenu()      MainMenu()
showQuickWithdraw() ReadQuickWithdraw()
ReadMainMenu()      ReadNumber()
ReadDeposit()       GoBackToMenu()
```

---

## 🔄 How It Works

```text
Start
  ↓
Login Screen ──(wrong credentials)──→ try again
  ↓
Main Menu
  ↓
Choose an Operation
  ↓
Validate the Amount ──(invalid)──→ try again
  ↓
Confirm (Y/N)
  ↓
Update the Balance & Save to File
  ↓
Return to Main Menu
  ↓
Logout → back to Login Screen
```

---

## 🛠️ Technologies

* **C++11+**
* `iostream`
* `fstream`
* `vector`
* `string`
* `iomanip`
* `cctype`
* `limits`

---

## ▶️ Build & Run

### Linux / macOS

```bash
g++ code.cpp
./a.out
```

Run it from the same folder that contains `Clients.txt`.

### Windows

Replace every:

```cpp
system("clear");
```

with:

```cpp
system("cls");
```

---

## 📌 Current Improvements

Some improvements I plan to explore in the future:

* ✅ Better validation for non-numeric input in Normal Withdraw and Deposit
* 🔐 Hash/encrypt PINs instead of storing them as plain text
* 🚫 Lock the account after several failed login attempts
* 💵 Accept cents/decimals in amounts, not just whole numbers
* 🗂️ Split the project into separate header and source files
* 🎨 Improve the console interface
* 📊 Add more banking features (transaction history, transfers between accounts)

---

## 📚 Sample Data

### `Clients.txt`

```text
A1201#//#1234#//#Ahmad Walid#//#+962771983925#//#6000.000000
B1202#//#5678#//#Farid Yasin#//#+962701981759#//#2000.000000
C1203#//#9101#//#Tariq Majd#//#+962790123456#//#50000.000000
D1204#//#5635#//#Faris Ayman#//#+962793847083#//#6000.000000
E1205#//#4174#//#Khalid Amir#//#+962704012290#//#70000.000000
F1206#//#3364#//#Omar Raif#//#+962707914911#//#5000.000000
```

---

## 🎯 Project Goal

The main goal of this project was not just to build an ATM simulator, but to **strengthen my C++ problem-solving skills and learn how to structure a real console application** with login, validation, and file storage.

---

## ⭐ If You Like It

Feel free to explore the code, try the application, and check out the different features.

**More projects coming soon! 🚀**

---

### 👨‍💻 Built with C++

**Learning → Practicing → Building → Improving**
