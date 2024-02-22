#include <iostream>
#include "Customer.h"
#include "Teller_v3.h"
#include "Bank.h"

using namespace std;

int main()
{

   cout<<" " <<endl;

   cout<<"\t \t \t \t \t  Welcome To The National Bank of ITI"<<endl<<endl;

   cout <<"########################################################################################################################"<<endl<<endl<<endl;

       Bank b1;

               int x = b1.Get_n_tellers();
    cout <<"\t  Number of Tellers is "<<x<<endl<<endl;
    Customer c1(1, "BEDO", 5, 5);       // Arrival Time: 5
    Customer c2(2, "BebO", 14, 6);       // Arrival Time: 6
    Customer c3(3, "abram", 6, 7);      // Arrival Time: 7
    Customer c4(4, "kero", 7, 8);       // Arrival Time: 8
    Customer c5(5, "Aya", 23, 9);        // Arrival Time: 9
    Customer c6(6, "sarah", 1, 10);     // Arrival Time: 10
    Customer c7(7, "Hanan", 7, 11);     // Arrival Time: 11
    Customer c8(8, "Zienb", 15, 12);    // Arrival Time: 12
    Customer c9(9, "Habiba", 6, 13);    // Arrival Time: 13
    Customer c10(10, "Mina", 4, 14);    // Arrival Time: 14


    c5.Is_Special();
    c7.Is_Special();
    c8.Is_Special();
    c10.Is_Special();


    b1.Add_Customers(c1);
    b1.Add_Customers(c2);
    b1.Add_Customers(c3);
    b1.Add_Customers(c4);
    b1.Add_Customers(c5);
    b1.Add_Customers(c6);
    b1.Add_Customers(c7);
    b1.Add_Customers(c8);
    b1.Add_Customers(c9);
    b1.Add_Customers(c10);

    b1.Start_Service();



    return 0;
}
