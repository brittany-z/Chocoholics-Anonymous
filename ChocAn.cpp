#include "terminal.h"
#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;


int main(){

    //Uncomment the following block to test provider's service 
    //list (FYI cannot test both provider service list and member 
    //service list at the same time)

    /*cout << "\n##TESTING PROVIDER SERVICE LIST##"
         << "\nYOU WILL ENTER ONE PROVIDER AND TWO MEMBERS."
         << "\nA SERVICE WILL BE ADDED TO THE LIST FOR EACH"
         << "\nMEMBER\n";

    cout << "\nPlease enter a provider info:\n";
    Provider p;
    p.read();
    p.gen_num('1');
    p.display_all();

    //Just use the same service from "directory"
    Service serv;
    serv.set_test();

    cout << "\nFIRST MEMBER\n";
    Member m;
    m.read();
    m.gen_num('2');
    m.display_all();
    Serv_date date1;
    date1.read();
    Provider_service p_serv(m,serv, date1);
    p_serv.read_comm();

    cout << "\nSECOND MEMBER\n";
    Member m2;
    m2.read();
    m2.gen_num('2');
    m2.display_all();
    Serv_date date2;
    date2.read();
    Provider_service p_serv2(m2,serv, date2);
    p_serv2.read_comm();


    p.add_service(p_serv);
    p.add_service(p_serv2);

    cout << "\nPROVIDER SERVICE INFO AND SERVICE LIST\n";
    p.display_all();*/
    
    //###############################################################

    //Uncomment the following block to test member's service 
    //list (FYI cannot test both provider service list and member 
    //service list at the same time)


    /*cout << "\n##TESTING MEMBER SERVICE LIST##"
         << "\n##MAKE SURE THAT IT ADDS IN ORDER BY DATE##\n";

    cout << "\nPlease enter a provider info:\n";
    Provider p;
    p.read();
    p.gen_num('1');
    p.display_all();

    cout << "\nPlease enter a member info:\n";
    Member m;
    m.read();
    m.gen_num('2');
    m.display_all();
   
    //Just use the same service from "directory"
    Service serv;
    serv.set_test();

    cout << "\nYOU WILL ENTER THREE SERVICES AS IF YOU ARE A PROVIDER,\n"
         << "FOR THE SAME MEMBER\n";
    
    //Create provider services that get copied into member
    //services objects that will be added to the member's
    //list of services

    cout << "\nFIRST SERVICE\n";
    Serv_date date1;
    date1.read();
    Provider_service p_serv1(m,serv, date1);
    p_serv1.read_comm();
    Member_service m_serv1(p,p_serv1);

    cout << "\nSECOND SERVICE\n";
    Serv_date date2;
    date2.read();
    Provider_service p_serv2(m,serv, date2);
    p_serv2.read_comm();
    Member_service m_serv2(p,p_serv2);
    
    cout << "\nTHIRD SERVICE\n";
    Serv_date date3;
    date3.read();
    Provider_service p_serv3(m,serv, date3);
    p_serv3.read_comm();
    Member_service m_serv3(p,p_serv3);

    m.add_service(m_serv1);
    m.add_service(m_serv2);
    m.add_service(m_serv3);

    cout << "\nMEMBER SERVICE INFO AND SERVICE LIST\n";
    m.display_all();*/


    //###############################################################

    //Uncomment the following block to test the Terminal and Data_center
    //class functionality.

    /*Data_center testCenter;
    Terminal testTerminal(testCenter);

    testTerminal.start_menu();*/

    return 0;
}

