// Customer.h
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <string>

using namespace std;

class Customer {
public:
    int id;
    string name;
    int serviceTime;
    int arrivalTime;
    int Event_time;
    string Event_type;
    int waitingTime;



    Customer(int ID, string name, int serviceTime, int arrivalTime)
        : id(ID), name(name), serviceTime(serviceTime), arrivalTime(arrivalTime),
          Event_time(arrivalTime), Event_type("Arriving"), waitingTime(0) {}





     bool Is_Special()
     {

         return true;
     }

    int getId() const {
        return id;
    }

    string getName() const {
        return name;
    }

    int getServiceTime() const {
        return serviceTime;
    }

    int getArrivalTime() const {
        return arrivalTime;
    }

    int getWaitingTime() const {
        return waitingTime;
    }

    void setWaitingTime(int waitTime) {
        waitingTime = waitTime;
    }

    void display(int d) const {

        cout << "ID:" << id << " Customer:\t" << name << "\t Arrival Time:  "<< arrivalTime << "\t Serving Time:"<<serviceTime<<" \t Waiting Time: " <<waitingTime<<"\t Departure Time: "<<d<<endl;
    }
};

#endif
