#ifndef BANK_H
#define BANK_H

#include "Customer.h"
#include "Teller.h"
#include <deque>
#include <iostream>
#include <algorithm> // for std::sort
#include <windows.h>

class Bank
{
private:
    std::deque<Customer> MainQueue;
    int currentTime = 0;
    int teller_num = 3;
    Teller *tellers;
    int Teller_Total_time = 0;
    int Teller_Service_Time = 0;

public:
    Bank()
    {
        currentTime = 0; // Initialize currentTime
        tellers = new Teller[teller_num];
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
        MainQueue.push_back(c);
    }

    // Sort the MainQueue based on customer arrival time
    void Sort_Customers_By_Arrival()
    {
        std::sort(MainQueue.begin(), MainQueue.end(), [](const Customer &a, const Customer &b)
                  {
                      return a.getArrivalTime() < b.getArrivalTime();
                  });
    }

    Teller *Find_Next_Teller_Available()
    {
        Teller *Next_Teller_Available = nullptr;
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

    int Find_Special_Customer()
    {
        int NextTellerIndex = 0;
        int TellerMinAvailabilityTime = tellers[0].availableTime;

        // Find the earliest available time among all tellers
        for (int i = 0; i < teller_num; i++)
        {
            if (tellers[i].availableTime < TellerMinAvailabilityTime)
            {
                TellerMinAvailabilityTime = tellers[i].availableTime;
                NextTellerIndex = i;
            }
        }

        // Check customers whose arrival time is before or at the same time as the earliest available time of any teller
        for (int i = 0; i < MainQueue.size(); i++)
        {
            Customer c = MainQueue[i];
            // If the customer is special and arrived before or at the same time as the earliest available time of any teller
            if (c.hasVIP && c.getArrivalTime() <= TellerMinAvailabilityTime)
            {
                return i; // Return the index of the special customer
            }
        }

        return -1; // No special customer found under the specified conditions
    }
void Serve() {
    Sort_Customers_By_Arrival(); // Sort the customers by arrival time

    // Iterate over the main queue until it's empty
    while (!MainQueue.empty()) {
        bool served = false;

        // Iterate over the tellers to find an available one
        for (int i = 0; i < teller_num; i++) {
            if (tellers[i].isAvailable) {
                if (served == false) {
                    // Serve the first customer in the queue with the available teller
                    Customer currentCustomer = MainQueue.front();
                    MainQueue.pop_front();

                    // Update customer's waiting time and event time
                    currentCustomer.setWaitingTime(0);
                    currentCustomer.setEventTime(currentCustomer.getArrivalTime() + currentCustomer.getServiceTime());
                    currentCustomer.Leaving_Time = currentCustomer.getArrivalTime() + currentCustomer.getWaitingTime() + currentCustomer.getServiceTime();

                    // Display customer details and update teller status
                    Display_Customer_Details(currentCustomer, tellers[i]);
                    tellers[i].isAvailable = false;
                    tellers[i].availableTime = currentCustomer.getEventTime();
                    tellers[i].num_clients_served++;

                    // Update total service and waiting time
                    tellers[i].Total_Time_Served += currentCustomer.getServiceTime();
                    Teller_Total_time += currentCustomer.getServiceTime();
                    Teller_Service_Time += currentCustomer.getWaitingTime();

                    served = true;
                }
            }
        }

        // If all tellers are busy, check for customers whose arrival time is close to the available time of a teller
        if (!served) {
            for (int i = 0; i < MainQueue.size(); i++) {
                if (served == false) {
                    Customer currentCustomer = MainQueue[i];
                    Teller *nearestTeller = Find_Next_Teller_Available();

                    // Check if there's a special customer and prioritize serving them first
                    int specialIndex = Find_Special_Customer();
                    if (specialIndex != -1 && nearestTeller && currentCustomer.getArrivalTime() <= nearestTeller->availableTime) {
                        currentCustomer = MainQueue[specialIndex];
                        MainQueue.erase(MainQueue.begin() + specialIndex);
                    } else if (!nearestTeller || currentCustomer.getArrivalTime() > nearestTeller->availableTime) {
                        break; // No available teller or no customer arrival time close to the available time of the teller
                    } else {
                        MainQueue.erase(MainQueue.begin() + i);
                    }

                    // Update customer's waiting time and event time
                    currentCustomer.setWaitingTime(nearestTeller->availableTime - currentCustomer.getArrivalTime());
                    if (currentCustomer.getWaitingTime() < 0) {
                        currentCustomer.setWaitingTime(0);
                    }
                    currentCustomer.setEventTime(currentCustomer.getArrivalTime() + currentCustomer.getWaitingTime() + currentCustomer.getServiceTime());
                    currentCustomer.Leaving_Time = currentCustomer.getArrivalTime() + currentCustomer.getWaitingTime() + currentCustomer.getServiceTime();

                    // Display customer details and update teller status
                    Display_Customer_Details(currentCustomer, *nearestTeller);
                    Teller_Service_Time += currentCustomer.getWaitingTime();
                    Teller_Total_time += currentCustomer.getServiceTime();
                    nearestTeller->Total_Time_Served += currentCustomer.getServiceTime();
                    nearestTeller->availableTime = currentCustomer.getEventTime();
                    nearestTeller->isAvailable = false;

                    served = true;
                }
            }
        }
    }
}

    void Display_Customer_Details(Customer c, Teller &t)
    {
        SetColor(11); // Set text color to cyan
        std::cout << "-------------------------------------------------------------------------------------------------------------------" << std::endl;
        SetColor(14); // Set text color to yellow
        std::cout << "\t ID: "
                  << c.id << "\t \t \t \t has VIP: "
                  << c.hasVIP << "\n \t Name "
                  << c.name << "\t \t \t \t Arrival Time: "
                  << c.arrivalTime << "\n \t Waiting Time: "
                  << c.waitingTime << "\t \t Service Time: "
                  << c.serviceTime << "\t \t \t  Leave Time: "
                  << c.getEventTime() << "\n \tServed at Teller: "
                  << t.Teller_Number << std::endl;
    }

    void Display_Teller_Details()
    {
        SetColor(11); // Set text color to cyan
        std::cout << "-------------------------------------------------------------------------------------------------------------------" << std::endl;
        for (int i = 0; i < teller_num; i++)
        {
            SetColor(12);
            std::cout << "\n \t \t \t \t \t \t Tellers Details : " << std::endl;
            SetColor(11);
            std::cout << "-------------------------------------------------------------------------------------------------------------------" << std::endl
                      << std::endl;
            SetColor(14);
            std::cout << "\n \tTeller Number: " << tellers[i].Teller_Number
                      << "\n \tTotal Time Served: " << tellers[i].Total_Time_Served
                      << "\n \tNumber of Customers Served: " << tellers[i].num_clients_served
                      << "\n \tAverage Service Time per Customer: " << (double)tellers[i].Total_Time_Served / tellers[i].num_clients_served << std::endl;
        }

        SetColor(11); // Set text color to cyan
        std::cout << "-------------------------------------------------------------------------------------------------------------------" << std::endl;
        std::cout << "\n \tService and Waiting Details:" << std::endl;
        std::cout << "\n \tTotal Service Time: " << Teller_Total_time << "\tTotal Waiting Time: " << Teller_Service_Time << std::endl;
    }

    // Function to set text color
    void SetColor(int color)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, color);
    }
};

#endif // BANK_H
