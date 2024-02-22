// Bank.h
#ifndef BANK_H
#define BANK_H

#include "Teller_v3.h"
#include "Customer.h"
#include <queue>
#include <iostream>

using namespace std;
struct compareEventTime {
    bool operator()( Customer& lhs,  Customer& rhs) const {
        // Check if either lhs or rhs is special
        bool lhs_special = lhs.Is_Special();
        bool rhs_special = rhs.Is_Special();

        // Check if arrival times are equal
        if (lhs.Event_time == rhs.Event_time) {
            // If both are special or both are regular, prioritize by arrival time
            if (lhs_special == rhs_special) {
                return lhs.Event_time > rhs.Event_time;
            } else {
                // Special customers are served before regular customers
                return lhs_special;
            }
        } else {
            // Serve the one with the earlier arrival time
            return lhs.Event_time > rhs.Event_time;
        }
    }
};



class Bank {
private:
    priority_queue<Customer, vector<Customer>, compareEventTime> MainQueue;
    queue<Customer> WaitingQueue;
    int num_of_Tellers = 3;
    int currentTime = 0;

public:

    // n of tellers is
    int Get_n_tellers()
    {
        return num_of_Tellers;
    }
    void Add_Customers(Customer& customer) {
        MainQueue.push(customer);
    }

    void Add_customer_waitingQueue(Customer& customer) {
        WaitingQueue.push(customer);
    }

    void Start_Service() {
        while (!MainQueue.empty()) {
            Customer current_Customer = MainQueue.top();
            currentTime = current_Customer.Event_time;
            MainQueue.pop();

            if (current_Customer.Event_type == "Arriving") {
                if (num_of_Tellers != 0) {
                    current_Customer.setWaitingTime(0);
                    int w = current_Customer.getWaitingTime();
                    current_Customer.waitingTime = currentTime - current_Customer.Event_time;
                    current_Customer.Event_time = currentTime + current_Customer.serviceTime;
                                        int d = current_Customer.Event_time;

//
//                    cout << "ID " << current_Customer.id << " Customer: " << current_Customer.name
//                         << " arrived at " << current_Customer.arrivalTime << " waited for " << current_Customer.waitingTime
//                         << " and Left at time of: " << current_Customer.Event_time << endl;

current_Customer.display(d);

                    current_Customer.Event_type = "Leaving";
                    Add_Customers(current_Customer);
                    num_of_Tellers--;
                } else {
                    Add_customer_waitingQueue(current_Customer);
                }
            } else if (current_Customer.Event_type == "Leaving") {
                if (!WaitingQueue.empty()) {
                    Customer current_Customer = WaitingQueue.front();
                    WaitingQueue.pop();

                    int arrived = current_Customer.Event_time;
                    current_Customer.waitingTime = currentTime - current_Customer.Event_time;
                    current_Customer.Event_time = currentTime + current_Customer.serviceTime;
                    int d = current_Customer.Event_time;
//
//                    cout << "ID " << current_Customer.id << " Customer: " << current_Customer.name
//                         << " arrived at " << arrived << " waited for " << current_Customer.waitingTime
//                         << " and Left at time of: " << current_Customer.Event_time << endl;

current_Customer.display(d);


                    current_Customer.Event_type = "Leaving";
                    Add_Customers(current_Customer);
                } else {
                    num_of_Tellers++;
                }
            }
        }
    }
};

#endif // BANK_H
