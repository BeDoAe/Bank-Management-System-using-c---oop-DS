// Teller_v3.h
#ifndef TELLER_V3_H
#define TELLER_V3_H

#include "Customer.h"

#include <string>
using namespace std;

class Teller_v3 {
private:
    int id;
    bool isAvailable;
    int finishTime; // Time by which the current customer will finish

public:
    Teller_v3 ()
    {

    }
    Teller_v3(int id) : id(id), isAvailable(true), finishTime(0) {}

    bool isTellerAvailable() const {
        return isAvailable;
    }

    void setBusy(int currentTime, int serviceTime) {
        isAvailable = false;
        finishTime = currentTime + serviceTime;
    }

    void setAvailable() {
        isAvailable = true;
    }

    int getFinishTime() const {
        return finishTime;
    }
};

#endif // TELLER_V3_H
