#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <string>

using namespace std;

class Customer
{
private:



public:
     int id;
    string name;
    int serviceTime;
    int arrivalTime;
    int Event_time;
    string Event_type;
    int waitingTime;
    int tellerId;
    bool served=false;
    bool hasVIP;
    int Leaving_Time;

    Customer ()
    {

    }
//    Customer(int ID, string name, int serviceTime, int arrivalTime)
//        : id(ID), name(name), serviceTime(serviceTime), arrivalTime(arrivalTime),
//          Event_time(arrivalTime), Event_type("Arriving"), waitingTime(0), tellerId(-1) {}
//


    Customer(int ID,string name, int arrivalTime, int serviceTime, bool vip)
    {
        this->id=ID;
        this->name = name;
        this->arrivalTime = arrivalTime;
        this->serviceTime = serviceTime;
        this->hasVIP = vip;

    }

    bool Is_Special()
    {
        return true;
    }

    int getId() const
    {
        return id;
    }

    string getName() const
    {
        return name;
    }

    int getServiceTime() const
    {
        return serviceTime;
    }

    int getArrivalTime() const
    {
        return arrivalTime;
    }

    int getEventTime() const
    {
        return Event_time;
    }

    void setEventTime(int time)
    {
        Event_time = time;
    }

    string getEventType() const
    {
        return Event_type;
    }

    void setEventType(string type)
    {
        Event_type = type;
    }

    int getWaitingTime() const
    {
        return waitingTime;
    }

    void setWaitingTime(int waitTime)
    {
        waitingTime = waitTime;
    }

    int getTellerId() const
    {
        return tellerId;
    }

    void setTellerId(int id)
    {
        tellerId = id;
    }

    void Set_arrivalTime(int t )
    {

        arrivalTime= t;

    }
    int Get_arrivalTime()
    {

        return arrivalTime;
    }

    void display() const
    {
        cout << "ID: " << id << ", Customer: " << name << ", Arrival Time: " << arrivalTime
             << ", Service Time: " << serviceTime << ", Waiting Time: " << waitingTime
             << ", Departure Time: " << Event_time << ", Teller ID: " << tellerId << endl;
    }
};

#endif // CUSTOMER_H
