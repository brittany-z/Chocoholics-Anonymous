#include <iostream>
#include "people.h"
using namespace std;


/* --------------- ADDRESS CLASS METHODS --------------- */


Address::Address(){};


/*Constructor that sets the data to what is read from
 * the file.*/
Address::Address(ifstream & in): Name(in){

    getline(in, street, '|');
    getline(in, city, '|');
    getline(in, state, '|');
    getline(in, zip, '|');
}


/*Writes to file. This will probably need to be
 * changed depending on file formatting.*/
void Address::write_file(ofstream & out) const{

    Name::write_file(out);
    out << street << '|'
        << city << '|'
        << state << '|'
        << zip << '|';
}


/*Writes to report*/
void Address::write_report(ofstream & out) const{

    Name::write_report(out);
    out << "\nStreet: " << street
        << "\nCity: " << city
        << "\nState: " << state
        << "\nZip: " << zip << endl;
}


/*Used to confirm that the user entered the correct
 * data.*/
void Address::display() const{

    cout << "\nStreet: " << street
         << "\nCity: " << city
         << "\nState: " << state
         << "\nZip: " << zip << endl;
}


/*This method is called when a manager wants to add
 * a person.*/
void Address::read(){

    Name::read();
    /*Misnomer, it is setting the address
     * in this case.*/
    change_address();

}


/*This method prompts and reads an address from the manager.
 * Called when a manager chooses to change someone's address
 * and in the read method to initialize the data when a
 * person is added.*/
void Address::change_address(){

     do
    {
        do
        {
            cout << "\nPlease enter the street address: ";
            getline(cin, street);
            //Check less than max
        }while (street.empty() || exceed_max(street.length(), STRT_MAX));

        do
        {
            cout << "\nPlease enter the city: ";
            getline(cin, city);
            //Check less than max
        }while (city.empty() || exceed_max(city.length(), CITY_MAX));

        do
        {
            cout << "\nPlease enter the state: ";
            getline(cin, state);
            /*This checks that the string is 2 chars long*/
        }while (state.empty() || !equal_max(state.length(), STATE_MAX));

        do
        {
            cout << "\nPlease enter the zip code: ";
            getline(cin, zip);
            /*This checks that the string is 5 chars long*/
        }while (zip.empty() || !equal_max(zip.length(), ZIP_MAX));

        //Make sure input is correct. If not, loop again.
        cout << "\nYou entered:";
        display();

    }while(!is_correct());

}


/*Used to update an address. Called in the data
 * center update method.*/
void Address::update(const Address & update_to){

    street = update_to.street;
    city = update_to.city;
    state = update_to.state;
    zip = update_to.zip;
}


//For testing, calls Name display
void Address::display_all() const
{
    Name::display();
    display();
}


/* -------------- PROVIDER CLASS METHODS ------------------ */


/*This is all that is needs to do because when
 * a provider is instantiated by the manager,
 * the provider list would be empty.*/
Provider::Provider(): num_consults(0), total_fees(0){}


/*Constructor that sets the data to what is read from
 * the file.*/
Provider::Provider(ifstream & in): Address(in), num_consults(0), total_fees(0){

}


/*Used to add a provider in the add_person method in the Data_center
 * class. It copies the Address object which contains the name
 * and address of the new provider.*/
Provider::Provider(const Address & to_add): Address(to_add), num_consults(0),
                    total_fees(0) {}


/*This method checks if the provider has provided any
 * services this week. It is called in the person_report
 * method in the Data_center class before a report is
 * generated.*/
bool Provider::check_week() const{

    for (auto it = serv_list.begin(); it != serv_list.end(); ++it)
    {
        if (it->Serv_date::check_week())
            return true;
    }
    return false;
}


/*Writes to file for generating a report.*/
void Provider::write_report(ofstream & out) const{
    
    Address::write_report(out);
    if (!serv_list.empty())
    {
        out << "\nServices provided this week:\n";
        for (auto it = serv_list.begin(); it != serv_list.end(); ++it)
        {
            /*Check if the service occured in the current
             * week*/
            if (it->Serv_date::check_week())
                it->write_report(out);
        }
        out << "\nTotal number of consulations this week: " << num_consults;
        out << "\nTotal fees to be paid for the week: $" << total_fees;
    }
}


/*This method adds a service to the provider's list of services.
 * Since the list is ordered by the time and date that it was
 * received by the data center, then the service is just added
 * to the end of the list.*/
int Provider::add_service(const Provider_service & to_add){

    /*Add at end of list since it is the latest service
     * received by the data center.*/
    serv_list.push_back(to_add);

    /*Add fee of service to total fees and increment
     * the total number of services if the service
     * occurred within the current week.*/
    if (to_add.Serv_date::check_week()) //Serv_date method
    {
        total_fees += to_add.get_fee(); //Service method
        ++num_consults;
    }
    if (serv_list.empty())
        return 0;
    return 1;
}


/*Used for testing to display all provider info.*/
void Provider::display_all() const{

    cout << "\nPERSONAL INFORMATION\n";
    Address::display_all();
    if (!serv_list.empty())
    {
        cout << "\nSERVICE LIST\n";
        for(auto it = serv_list.begin(); it != serv_list.end(); ++it)
            it->display_all();
    }
    else
        cout << "\nThis provider has not provided any services.\n";

    cout << "\nNumber of consultations this week: " << num_consults
         << "\nTotal fees for this week: $" << total_fees << endl;
}



/* ------------ MEMBER CLASS METHODS ---------------- */


/*This is all that is needs to do because when
 * a provider is instantiated by the manager,
 * the provider list would be empty.*/
Member::Member(): suspended(false){}


/*Constructor that set the data to what is read from
 * the file.*/
Member::Member(ifstream & in): Address(in){

    in >> suspended;
    in.ignore(100, '|');
}


/*Used to add a member in the add_person method in the Data_center
 * class. It copies the Address object which contains the name
 * and address of the new member.*/
Member::Member(const Address & to_add): Address(to_add), suspended(false) {}


void Member::write_file(ofstream & out) const{
    
    Address::write_file(out);
    if(suspended)
        out << "1" << '|';
    else
        out << "0" << '|';
}


/*This method checks if the member has provided any
 * services this week. It is called in the person_report
 * method in the Data_center class before a report is
 * generated.*/
bool Member::check_week() const{

    for (auto it = serv_list.begin(); it != serv_list.end(); ++it)
    {
        if (it->Serv_date::check_week())
            return true;
    }
    return false;
}



/*Writes to file for generating a report.*/
void Member::write_report(ofstream & out) const{

    Address::write_report(out);
    if (!serv_list.empty())
    {
        out << "\nServices received this week:\n";
        for (auto it = serv_list.begin(); it != serv_list.end(); ++it)
            /*Check if the service occured in the current
             * week*/
            if (it->Serv_date::check_week())
                it->write_report(out);
    }
}


/*This method inserts a member service into the member's 
 * service list in order by date.*/
int Member::add_service(const Member_service & to_add){

    /*If the list is empty then we insert at the
     * beginning of the list.*/
    if (serv_list.empty())
        serv_list.push_front(to_add);
    else
    {
        /*Used to stop traversal once insertion has
         * occured*/
        bool added = false;
        for (auto it = serv_list.begin(); it != serv_list.end() && !added; ++it)
        {
            /*Call the Serv_date method that checks if the service
             * to add is "less" than the current service in the
             * map. If so, then one is returned and the service
             * gets added in the current position and the rest
             * of the items are shifted down.*/
            if (it->compare_date(to_add))
            {
                added = true;
                serv_list.insert(it, to_add);
            }
        }
        /*This will occur if the service to add is "greater" than
         * all of the services in the map. It was never added
         * during traversal and so it gets added at the end.*/
        if (!added)
            serv_list.push_back(to_add);
    }
    if (serv_list.empty())
        return 0;
    return 1;
}


/*Checks if user is suspeded. Used when a member is
 * attempting to obtain services.*/
bool Member::check_susp() const{

    return suspended;
}


/*Used for testing to display all member info.*/
void Member::display_all() const{

    cout << "\nPERSONAL INFORMATION\n";
    Address::display_all();
    if (!serv_list.empty())
    {
        cout << "\nSERVICE LIST\n";
        for(auto it = serv_list.begin(); it != serv_list.end(); ++it)
            it->display_all();
    }
    else
        cout << "\nThis member has not received any services\n";

    if (suspended)
        cout << "\nMember is suspended\n";
    else
        cout << "\nMember NOT suspended\n";
}
