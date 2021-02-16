#include <iostream>
#include "services.h"
using namespace std;


/* -------- SERVICE CLASS METHODS -------- */


//For testing
Service::Service(){

    code = "123456";
    name = "Therapy";
    cost = 150.00;
}


/*Constructor that sets the data to what is read from
 * the file.*/
Service::Service(ifstream & in){
}


/*Writes to file*/
void Service::write_file(std::ofstream & out) const{
}


/*Used for displaying the provider directory. But cost should
 * not be displayed.*/
void Service::display() const{

    cout << "\nService: " << name
         << "\nCode: " << code;

    cout << "\ncost: $" << cost << endl; //remove this eventually
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
unsigned Service::get_cost() const{

    return cost;
}


/* -------- SERV_DATE CLASS METHODS -------- */


/*Constructor that sets the data to what is read from
 * the file.*/
Serv_date::Serv_date(ifstream & in): Service(in){
}


/*This constructor copies the Service object by sending it up tp
 * the copy constructor and it reads in the service date. It checks
 * for valid logical date responses and that a future date is not
 * provided.*/
Serv_date::Serv_date(const Service & curr_ser): Service(curr_ser){

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


/*Writes to file*/
void Serv_date::write_file(ofstream & out) const{
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


/*Checks if the service date is within the current week.*/
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
 * the provider directory, and the name object in
 * the current member object (from the member map) that 
 * the service was provided to. It also prompts and
 * reads for comments.*/
Provider_service::Provider_service(const Name & curr_mem, const Service & curr_ser): 
    Serv_date(curr_ser), mem_info(curr_mem){
    
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


/*Writes to file*/
void Provider_service::write_file(ofstream & out) const{
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


/*Writes to file*/
void Member_service::write_file(ofstream & out) const{
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

