//#include <iostream>
//#include <fstream>
//#include <iomanip>
//#include "Customer.h"
//#include "Teller.h"
//#include "Bank.h"
//#include <windows.h>
//
//// Function to set text color
//void SetColor(int color) {
//    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//    SetConsoleTextAttribute(hConsole, color);
//}
//
//using namespace std;
//
//int main()
//{
//    SetColor(12);
//    cout << "\t \t \t \t \t  Welcome To The National Bank of ITI" << endl << endl;
//    SetColor(11);
//    cout << "########################################################################################################################" << endl << endl << endl;
//
//    SetColor(12);
//    cout << "\t \t \t \t \t \t  Customer Details" << endl;
//
//    // Open the input file
//    ifstream inputFile("customer_Details.txt");
//
//    if (!inputFile.is_open())
//    {
//        cerr << "Error: Unable to open input file!" << endl;
//        return 1;
//    }
//
//    Bank b1;
//
//    int id, arrivalTime, serviceTime;
//    string name;
//
//    // Read data from the file and add customers to the bank
//    while (inputFile >> id >> name >> arrivalTime >> serviceTime)
//    {
//        Customer customer(id, name, arrivalTime, serviceTime);
//        b1.add_Customers_MainQueue(customer);
//    }
//
//    // Close the input file
//    inputFile.close();
//
//    // Start bank service
//    b1.Serve();
//
//    b1.Display_Teller_Details();
//
//    return 0;
//}
////////////////////////////
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Customer.h"
#include "Teller.h"
#include "Bank.h"
#include <windows.h> // Include the Windows Console API header

// Function to set text color
void SetColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

using namespace std;

int main()
{
    SetColor(12);
    cout << "\t \t \t \t \t  Welcome To The National Bank of ITI" << endl << endl;
    SetColor(11);
    cout << "########################################################################################################################" << endl << endl << endl;

    SetColor(12);
    cout << "\t \t \t \t \t \t  Customer Details" << endl;

    // Open the input file
    ifstream inputFile("customer_Details.txt");

    if (!inputFile.is_open())
    {
        cerr << "Error: Unable to open input file!" << endl;
        return 1;
    }

    Bank b1;

    int id, arrivalTime, serviceTime;
    string name;
    bool hasVIP;

    // Read data from the file and add customers to the bank
    while (inputFile >> id >> name >> arrivalTime >> serviceTime >> hasVIP)
    {
        Customer customer(id, name, arrivalTime, serviceTime, hasVIP);
        b1.add_Customers_MainQueue(customer);
    }

    // Close the input file
    inputFile.close();

    // Start bank service
    b1.Serve();

    b1.Display_Teller_Details();

    return 0;
}
