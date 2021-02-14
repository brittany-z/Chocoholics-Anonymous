#include <iostream>
#include <random>
#include "name.h"
using namespace std;


/*Used to read in from the user since the only time
 * that we would instantiate an object that isn't
 * being read from file (use other constructor)
 * would be when the manager wants to add a person.*/
Name::Name(){

    do
    {
        cout << "\nPlease enter their full name: ";
        getline(cin, a_name);
        cout << "\nYou entered: " << a_name << endl;
    }while (a_name.empty() || exceed_max(a_name.length(), 
                NAME_MAX) || !is_correct());
}


/*Constructor that sets the data to what is read from
 * the file.*/
Name::Name(ifstream & in){
}


/*This generates an ID_num when a manager adds a user.
 * It is called in the Data_center add method so that
 * it can check if the generated number already exists.
 * It returns the number (string) generated so that the
 * find function can use it for comparison.*/
string Name::gen_num(char first_num){

    //Generating random number
    random_device obj;
    mt19937 gen(obj());
    uniform_int_distribution<> distr(100000000, 999999999);
    //Get random number
    unsigned temp = distr(gen);
    ID_num = to_string(temp); //Convert to string
    //Set the identifying first number of ID
    ID_num[0] = first_num;

    return ID_num;
}


void Name::write_file(ofstream & out) const{
}


/*Used to display lists of people.*/
void Name::display() const{

    cout << "\nName: " << a_name
         << "\nID number: " << ID_num << endl;
}


/*Used to generate the maps and compare because
 * the maps need the ID_num since that is what
 * they are keyed on.*/
string Name::get_key() const{

    return ID_num;
}


/*Used for the Member_service to copy the name of
 * the provider since that is all that it needs.*/
void Name::copy_name(string & prov_name) const{

    prov_name = a_name;
}
