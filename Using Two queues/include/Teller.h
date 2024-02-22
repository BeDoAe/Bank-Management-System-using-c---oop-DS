#ifndef TELLER_H
#define TELLER_H

#include <iostream>
#include <string>
using namespace std;

class Teller {
public:
    Teller(int Teller_nmber) {
        Number_of_Tellers = Teller_nmber;
    }

    bool isAvailable() {
        return Number_of_Tellers > 0;
    }

    void Display() {
        cout << "Number of Tellers are  " << Number_of_Tellers << endl;
    }

        int Number_of_Tellers;

protected:


private:
};

#endif // TELLER_H
