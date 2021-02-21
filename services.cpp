#include <iostream>
#include "services.h"
using namespace std;


/* -------- SERVICE CLASS METHODS -------- */


Service::Service(): fee(0){}


/*Constructor that sets the data to what is read from
 * the file. Used to reading the provider directory.*/
Service::Service(ifstream & in){

    getline(in, name, '|');
    in >> fee;
    in.ignore(100, '|');
    getline(in, code);
}


/*Writes to file. Type 1 means that it only writes the
 * name (member report). Any other type means that it
 * only writes the code and fee (provider reports).*/
void Service::write_report(ofstream & out, int type) const{

    if (type == 1)
        out << "\nService name: " << name << endl;
    else
        out << "\nService code: " << code
            << "\nService fee: " << fee << endl;
}


/*For testing*/
void Service::test(){

    code = "123456";
    name = "Therapy";
    fee = 150.00;
}


/*Used to display name for verification
 * when adding a service.*/
void Service::disp_name() const{

    cout << endl << name << endl;
}


/*Used to display fee when adding a service*/
void Service::disp_fee() const{

    cout << "\nFee for this service: $" << fee << endl;
}


/*Used for displaying the provider directory.*/
void Service::display() const{

    cout << "\nService: " << name
         << "\nCode: " << code;
    cout << "\nFee: $" << fee  << endl;
}


/*Used to generate the provider directory map 
 * and to compare because the map needs the 
 * code since that's what it's keyed on.*/
string Service::get_key() const{

    return code;
}


/*Used to keep a running total of a provider's 
 * fees for the week. It is called by the add_service
 * method of the provider class. It will also be
 * called by the data_center class when generating
 * reports in order to produce certain fee totals.*/
unsigned Service::get_fee() const{

    return fee;
}


/* -------- SERV_DATE CLASS METHODS -------- */


/*This constructor reads in the service date. It checks for valid
 * logical date responses and that a future date is not provided.
 * It is used to get the date before a service is selected in the
 * provider directory and before a Provider_service is made per
 * the program description. It is copied into the Provider_service.*/
Serv_date::Serv_date(){

    /*Get current time for range checking/that service date 
     * input is not in the future*/
    time_t now = time(0);
    /*Point to tm_struct in object*/
    tm * curr = localtime(&now);

    bool valid; //Used for do while conditions
    do
    {
        //Prompt and read for service month
        do
        {
            valid = true;
            cout << "\nPlease enter the month that the service was provided "
                 << "(ex. 1 for January): ";
            cin >> month;
            cin.clear();
            cin.ignore(100, '\n');
            if (month < 1 || month > 12)
            {
                cout << "\nInvalid input, must be within a range of 1 and 12. Try again.\n";
                valid = false;
            }

        }while(!valid);

        //Prompt and read for service day
        do
        {
            valid = true;
            cout << "\nPlease enter the day that the service was provided "
                 << "(ex. 1 for the 1st): ";
            cin >> day;
            cin.clear();
            cin.ignore(100, '\n');
            if (day < 1 || day > 31)
            {
                cout << "\nInvalid input, must be within the range of 1 and 31. Try again.\n";
                valid = false;
            }
        }while(!valid);

        //Prompt and read for service year
        do
        {
            valid = true;
            cout << "\nPlease enter the year that the service was provided: ";
            cin >> year;
            cin.clear();
            cin.ignore(100, '\n');
            //Check if year is valid
            if (year < 1980 || year > curr->tm_year + 1900)
            {
                cout << "\nInvalid input, must be within the range of 1980 and the current year"
                     << " Try again.\n";
                valid = false;
            }
        }while(!valid);

        /*This ugly thing checks if the service date that the user input
         * is not within the future. Just for funsies.*/
        if((curr->tm_year + 1900 == year && month > curr->tm_mon + 1) || 
            (curr->tm_year + 1900 == year && month == curr->tm_mon + 1 && day > curr->tm_mday))
        {
            valid = false;
            cout << "\nInvalid input, may not enter a future date. Try again.\n";
        }
        else
        {
            valid = true;
            cout << "\nYou entered:\n";
            display();
        }

    }while(!valid || !is_correct());
}


/*This constructor copies the Serv_date object that was
 * used to add the service date prior to everything else.
 * And it sends the service from the provider directory
 * to be copied by the Service CC. It is used when creating
 * a Provider_service.*/
Serv_date::Serv_date(const Service & curr_serv, const Serv_date & date): 
    Service(curr_serv), day(date.day), month(date.month), year(date.year){}


/*Constructor that sets the data to what is read from
 * the file.*/
Serv_date::Serv_date(ifstream & in): Service(in){
}


/*Writes to the service date to file in the
 * appropriate format.*/
void Serv_date::write_report(ofstream & out) const{

    out << "\nService date: ";
    if (month < 10)
        out << "0" << month;
    if (day < 10)
        out << "-0" << day;
    else
        out << "-" << day;
    out << "-" << year;
}


/*Used to add member services in the member service map in
 * order by date. It is called by the add_service method
 * of the Member class. Returns one once the service being
 * added is "less" than the current service in the map
 * which means that the correct position has been found.
 * Otherwise zero is returned and traversal continues.*/
int Serv_date::compare_date(const Serv_date & to_add) const{
  
    /*If date of service being added is "greater" than the 
     * current service in the map, then zero is returned and 
     * we continue traversing.*/
    /*This is really ugly but I thought that one long if
     * statement would be even uglier.*/
    if (to_add.year > this->year)
        return 0;
    if (to_add.year == this->year && to_add.month > this->month)
        return 0;
    if (to_add.year == this->year && to_add.month == this->month 
            && to_add.day > this->day)
        return 0;
    /*If the date of the service being added is "less" than the
     * current service in the map, then one is returned and
     * the service gets added before it.*/
    return 1;
}


/*Used to make sure that the user entered the
 * desired data and for testing.*/
void Serv_date::display() const{

    cout << "\nMonth: " << month
         << "\nDay: " << day
         << "\nYear: " << year << endl;
}


/*Checks if the service date is within the current week.
 * Returns true if it is and false if not.*/
bool Serv_date::check_week() const{

    /*Get current date*/
    time_t now = time(0);
    /*Point to tm_struct in object*/
    tm * curr = localtime(&now);

    /*Check if the service month and year are the current
     * month and year*/
    if(curr->tm_year + 1900 == year && curr->tm_mon + 1 == month)
    {
        /*Get the difference of the current day and service day
         * and then check if the difference is within the number
         * of days since sunday (tm_wday) to see if the service
         * occurred within the current week.*/
        int diff = curr->tm_mday - day;
        if (diff >= 0 && diff <= curr->tm_wday)
            return true;
    }
    return false;
}


/* -------- PROVIDER_SERVICE CLASS METHODS -------- */


/*Constructor that sets the data to what is read from
 * the file.*/
Provider_service::Provider_service(ifstream & in): Serv_date(in){
}


/*Constructor that is used to create a provider service.
 * It copies the service chosen by the provider from
 * the provider directory,the name object in the current 
 * member object (from the member map) that the service 
 * was provided to, and the service date. All by passing
 * objects to constructors. It also prompts and reads 
 * for comments.*/
Provider_service::Provider_service(const Name & curr_mem, 
        const Service & curr_ser, const Serv_date & date): 
        Serv_date(curr_ser, date), mem_info(curr_mem){
    
    char response;
    do
    {
        cout << "\nWould you like to add comments? Y/N: ";
        cin >> response;
        cin.clear();
        cin.ignore(100, '\n');
        response = toupper(response);

    }while(response != 'Y' && response != 'N');

    if (response == 'Y')
    {
        do
        {
            cout << "\nPlease enter any comments:\n";
            getline(cin, comments);
            //Make sure it's less than max
        }while (comments.empty() || exceed_max(comments.length(), COM_MAX));
    }
    
    //Set the time and date that the data was received by the data center
    received = time(0);
}


/*Writes to file. Used for generating provider reports.*/
void Provider_service::write_report(ofstream & out) const{

    Serv_date::write_report(out);

    tm * recv = localtime(&received);

    out << "\nReceived date and time: ";
    if (recv->tm_mon + 1 < 10)
        out << "0" << recv->tm_mon + 1;
    else
        out << recv->tm_mon + 1;
    
    if (recv->tm_mday < 10)
        out << "-0" << recv->tm_mday;
    else
        out << "-" << recv->tm_mday;

    out << "-" << recv->tm_year + 1900 << " ";

    if (recv->tm_hour < 10)
        out << "0" << recv->tm_hour;
    else
        out << ":" << recv->tm_hour;
    if (recv->tm_min + 1 < 0)
        out << ":0" << recv->tm_min + 1;
    else
        out << ":" << recv->tm_min + 1;
    if (recv->tm_sec < 10)
        out << ":0" << recv->tm_sec << endl;
    else
        out  << ":" << recv->tm_sec << endl;

    mem_info.write_report(out);
    Service::write_report(out, 2);
}


/*Only writes to service disk*/
void Provider_service::write_comm(ofstream & out) const{

    if (!comments.empty())
        out << "\nComments: " << comments << endl;
}


//For testing
void Provider_service::display_all() const
{
    cout << "\nMember info:";
    mem_info.display();
    cout << "\nService info:";
    Service::display();
    cout << "\nService date:";
    Serv_date::display();
    cout << "\nDate received: " << ctime(&received);
    cout << "\nComments:\n" << comments << endl;
}



/* -------- MEMBER_SERVICE CLASS METHODS -------- */


/*Constructor that sets the data to what is read from
 * the file.*/
Member_service::Member_service(ifstream & in): Serv_date(in){
}


/*This constructor copies the necessary data from a 
 * provider service because a provider service has 
 * all of the information that a member service needs.*/
Member_service::Member_service(const Name & curr_prov, 
        const Provider_service & curr_serv): Serv_date(curr_serv){

    //Copy just the provider name
    curr_prov.copy_name(prov_name);
}


/*Writes to file. Used for generating member reports.*/
void Member_service::write_report(ofstream & out) const{

    Serv_date::write_report(out);
    out << "\nProvider name: " << prov_name;
    Service::write_report(out, 1);
}


//For testing
void Member_service::display_all() const
{
    cout << "\nService info:";
    Service::display();
    cout << "\nService date:";
    Serv_date::display();
    cout << "\nProvider name: " << prov_name << endl;
}

