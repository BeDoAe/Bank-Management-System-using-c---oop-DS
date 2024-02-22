#ifndef PRIORITYCUSTOMER_H
#define PRIORITYCUSTOMER_H

#include <iostream>
#include <string>

using namespace std;


class PiorityCustomer
{
public:
    PiorityCustomer(int id, string p, string Name)
    {
        priority_Cus_ID = id;
        priority = p;
        name = Name;
    }

    void Display()
    {
        cout << "Special Customer of ID " << priority_Cus_ID << " of Name is " << name << " of priority Type as " << priority << std::endl;
    }

protected:

private:
    string name;
    int priority_Cus_ID;
    string priority;
};

#endif // PRIORITYCUSTOMER_H
