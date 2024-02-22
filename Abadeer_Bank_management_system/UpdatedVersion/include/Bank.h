#ifndef BANK_H
#define BANK_H
#include "Customer.h"
#include "Teller_Window.h"
#include <queue>
#include <windows.h>

using namespace std;

struct compareEventTime
{
    bool operator()(const Customer &lhs, const Customer &rhs) const
    {
        return lhs.arrivalTime > rhs.arrivalTime;
    }
};

class Bank
{
private:
    priority_queue<Customer, vector<Customer>, compareEventTime> MainQueue;
    int teller_num = 3;

public:
    int currentTime = 0;

    Teller_Window *tellers;

    int Teller_Total_time = 0;
    int Teller_Service_Time = 0;

    Bank()
    {
        tellers = new Teller_Window[teller_num];
        for (int i = 0; i < teller_num; ++i)
        {
            tellers[i].isAvailable = true;
            tellers[i].Teller_Number = i + 1;
            tellers[i].num_clients_served = 0;
            tellers[i].availableTime = 0;
            tellers[i].Total_Time_Served = 0;
        }
    }

    ~Bank()
    {
        delete[] tellers;
    }

    void add_Customers_MainQueue(Customer c)
    {
        MainQueue.push(c);
    }

    Teller_Window *Find_Next_Teller_Available()
    {
        Teller_Window *Next_Teller_Available = nullptr;
        int Earliest_Available_Time = INT_MAX;

        for (int i = 0; i < teller_num; i++)
        {
            if (tellers[i].availableTime < Earliest_Available_Time)
            {
                Next_Teller_Available = &tellers[i];
                Earliest_Available_Time = tellers[i].availableTime;
            }
        }

        return Next_Teller_Available;
    }

    void Serve()
    {
        while (!MainQueue.empty())
        {
            Customer Current_customer = MainQueue.top();
            currentTime = Current_customer.getArrivalTime();
            MainQueue.pop();

            bool served = false;
            for (int i = 0; i < teller_num; i++)
            {
                if (tellers[i].isAvailable)
                {
                    if(served==false)
                    {


                    Current_customer.setWaitingTime(0);
                    Current_customer.setEventTime(0 + Current_customer.getServiceTime());
                    Current_customer.Leaving_Time = Current_customer.getArrivalTime() + Current_customer.getWaitingTime() + Current_customer.getServiceTime(); // Corrected leaving time calculation

                    Display_Customer_Details(Current_customer, tellers[i]);

                    tellers[i].isAvailable = false;
                    tellers[i].availableTime = Current_customer.getEventTime();
                    tellers[i].num_clients_served++;

                    tellers[i].Total_Time_Served += Current_customer.getServiceTime();
                    Teller_Total_time += Current_customer.getServiceTime();
                    Teller_Service_Time += Current_customer.getWaitingTime();
                    served = true;
                    //not using break i used flag instead
                    }

                }
            }

            if (!served)
            {
                Teller_Window *nearestTeller = Find_Next_Teller_Available();
                // check if the  teller is not Null
                if (nearestTeller)
                {
                    nearestTeller->isAvailable = true;
                    nearestTeller->num_clients_served++;

                    Current_customer.setWaitingTime(nearestTeller->availableTime - Current_customer.getArrivalTime());
                    if (Current_customer.getWaitingTime() < 0)
                    {
                        Current_customer.setWaitingTime(-Current_customer.getWaitingTime());
                    }
                    Current_customer.setEventTime(Current_customer.getArrivalTime() + Current_customer.getWaitingTime() + Current_customer.getServiceTime());
                    Current_customer.Leaving_Time = Current_customer.getArrivalTime() + Current_customer.getWaitingTime() + Current_customer.getServiceTime(); // Corrected leaving time calculation

                    Display_Customer_Details(Current_customer, *nearestTeller);

                    Teller_Service_Time += Current_customer.getWaitingTime();
                    Teller_Total_time += Current_customer.getServiceTime();
                    nearestTeller->Total_Time_Served += Current_customer.getServiceTime();

                    nearestTeller->availableTime = Current_customer.getEventTime();
                    nearestTeller->isAvailable = false;
                }
            }
        }
    }

    // Function to set text color
    void SetColor(int color)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, color);
    }

    // Function to display customer details in a colored box
    // Function to display customer details in a colored box



    void Display_Customer_Details(Customer c, Teller_Window &t)
    {
        // Set text color to green
        SetColor(11);

        // Print customer details
        cout << "-------------------------------------------------------------------------------------------------------------------"<<endl<<endl;
        SetColor(14);
        cout <<"\t ID: "<<c.id
             <<" \n \n \tName: " << setw(30) << left << c.name
             <<"\tArrival Time: " << setw(23) << left << c.arrivalTime
             <<"\tWaiting Time: " << setw(23) << left << c.waitingTime
             <<"\n \tService Time: " << setw(23) << left << c.serviceTime
             <<"\tLeave Time: " << setw(25) << left << c.getEventTime()
             <<"\tServed at Teller: " << setw(20) << left << t.Teller_Number << endl;
        SetColor(11);



    }

    void Display_Teller_Details()
    {
        SetColor(11);
        cout << "-------------------------------------------------------------------------------------------------------------------" << endl << endl;
        cout << endl;


        for (int i = 0; i < teller_num; i++)
        {
            SetColor(12);
            cout << "\n \t \t \t \t \t \t Tellers Details : " << endl;
            SetColor(11);
            cout << "-------------------------------------------------------------------------------------------------------------------" << endl << endl;
            SetColor(14);
            cout << " \t   Teller Number : " << tellers[i].Teller_Number
                 << "\n \t Total Time served : " << tellers[i].Total_Time_Served
                 << "\n \t and he served : " << tellers[i].num_clients_served << " customers"
                 << "\n \t Average Service Time per Customer : " << (double)tellers[i].Total_Time_Served / tellers[i].num_clients_served
                 << endl;


        }
        SetColor(12);
        cout << "\n \t \t \t \t \t \t Some extra Statistics : " << endl;
        SetColor(11);
        cout << "-------------------------------------------------------------------------------------------------------------------" << endl << endl;
        SetColor(14);

        cout << endl;
        cout << "\tService and Waiting Details : " << endl;
        cout << " \n \t   Total Service Time is : " << Teller_Total_time
             << "\n \t and Total Waiting Time is : " << Teller_Service_Time << endl;
        SetColor(0);
    }


};

#endif // BANK_H
