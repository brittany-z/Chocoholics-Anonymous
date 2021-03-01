#include <iostream>
#include "terminal.h"
#include <algorithm>
using namespace std;


/* -------- DATA_CENTER CLASS METHODS -------- */

Data_center::Data_center(): curr_provider(NULL), curr_member(NULL){}


Data_center::~Data_center(){
}


/*Reads all maps from the txt file. It returns 0 if
 * the reading or map creation failed, otherwise
 * it returns 1.*/
int Data_center::read_files(){
  
    /*Set for failure. This will occur if any of
     * the files do not exist or if any of the
     * maps were not successfully read in and
     * inserted*/
    int ret = 0;
    /*Holds the | flag at the beginning of
     * each line. Used to prime the pump.*/
    char flag;
    ifstream in;

    for (int i = 1; i < 5; ++i)
    {
        if (i == 1)
            in.open("members.txt");
        else if (i == 2)
            in.open("providers.txt");
        else if (i == 3)
            in.open("prov_dir.txt");
        else
            in.open("managers.txt");

        if (in.is_open())
        {
            /*Prime the pump*/
            in >> flag;
            while (in && !in.eof())
            {
                if (i == 1)
                {
                    /*Create temp to be added that invokes
                    * the constructor that reads the data*/
                    Member to_add(in);
                    //Insert into map
                    member_list.insert(make_pair(to_add.get_key(), to_add));
                }
                else if (i == 2)
                {
                    /*Create temp to be added that invokes
                    * the constructor that reads the data*/
                    Provider to_add(in);
                    //Insert into map
                    provider_list.insert(make_pair(to_add.get_key(), to_add));
                }
                else if (i == 3)
                {
                    /*Create temp to be added that invokes
                    * the constructor that reads the data*/
                    Service to_add(in);
                    //Insert into map
                    prov_dir.insert(make_pair(to_add.get_key(), to_add));
                }
                else
                {
                    /*Create temp to be added that invokes
                    * the constructor that reads the data*/
                    Name to_add(in);
                    //Insert into map
                    manager_list.insert(make_pair(to_add.get_key(), to_add));
                }
                in.ignore(100, '\n');
                //Prime the pump
                in >> flag;
            }
            in.close();
            in.clear();
        }
    }

    /*Check if any of the lists are empty, meaning that a file reading
     * or insertion failed. Doesn't matter which one failed because all of them are
     * needed."*/
    if (!member_list.empty() || !provider_list.empty() || !prov_dir.empty()
            || !manager_list.empty())
        ret = 1; //Files read and maps successfully created

    return ret;
}


void Data_center::write_file(){
}


/*Returns 0 for valid, -1 for invalid, -2 for valid but suspended,
 * and -3 if the map is empty*/
int Data_center::check_valid(const string & input){

    int ret = 0;
    switch(input[0])
    {
      case '1':
        {
          if(!member_list.empty())
          {
            unordered_map<string, Member>::iterator it;
            it = member_list.find(input);
            if (it == member_list.end())
                ret = -1; //Invalid
            else
            {
                if (it->second.check_susp())
                    ret = -2;//Valid but suspended
                else
                    curr_member = &(it->second);
            }
          }
          else
              ret = -3; //Map is empty
          break;
        }
      case '2':
        {
          if(!provider_list.empty())
          {
            unordered_map<string, Provider>::iterator it;
            it = provider_list.find(input);
            if(it == provider_list.end())
                ret = -1; //Invalid
            else
                curr_provider = &(it->second);
          }
          else
              ret = -3; //Map is empty
          break;
        }
      case '3':
        {
          if(!manager_list.empty())
          {
            if(!manager_list.count(input))
                ret = -1; //Invalid
          }
          else
              ret = -3; //Map is empty
          break;
        }
      default:
        ret = -1;
        break;
    }
    return ret;
}


/*This displays a map depending on the map_type. It only
 * displays the name and number of the people maps
 * because chris doesn't need to know more than that.*/
void Data_center::disp_map(int map_type){

    switch (map_type)
    {
        case 1:
            {
                if(!member_list.empty())
                    for(auto it = member_list.begin(); it != member_list.end(); ++it)
                        it->second.Name::display();
                        //it->second.display_all(); //If you want to disp all info
                else
                    cout << "\nNo members stored\n";
                break;
            }
        case 2:
            {
                if(!provider_list.empty())
                    for(auto it = provider_list.begin(); it != provider_list.end(); ++it)
                        it->second.Name::display();
                        //it->second.display_all(); //If you want to disp all info
                else
                    cout << "\nNo providers stored\n";
                break;
            }
        case 3:
            {
                if (!prov_dir.empty())
                    for(auto it = prov_dir.begin(); it != prov_dir.end(); ++it)
                        it->second.display();
                else
                    cout << "\nProvider Directory not found\n";
                break;
            }
        case 4:
            {
                if(!manager_list.empty())
                    for(auto it = manager_list.begin(); it != manager_list.end(); ++it)
                        it->second.display();
                else
                    cout << "\nNo managers stored\n";
                break;
            }
        default: cerr << "\nInvalid map type\n";
            break;
    }
}


/*Used to write a provider or member report. It
 * is passed the person's ID_num. It returns 0
 * if the person has not received or provided
 * any services this week (no report generated)
 * or if the number doesn't match any number in
 * the system, -1 if the ID number provided is
 * not a valid number (doesn't start with the
 * proper identifier), and 1 if a report was
 * successfully generated. Really only need to
 * account for 0 or 1 because check_valid should
 * be called first which would handle erroneous
 * input.*/
int Data_center::person_report(const string & num) {

    switch(num[0])
    {
        case '1':
            {   
                if (member_list.count(num))
                {
                    //Check if they received services this week
                    if (!member_list[num].check_week())
                        return 0;
                }
                else
                    return 0;
            }
            break;
        case '2':
            {
                if (provider_list.count(num))
                {
                    //Check if they provided services this week
                    if (!provider_list[num].check_week())
                        return 0;
                }
                else
                    return 0;
            }
            break;
        default:
            return -1; //First char isn't 1 or 2
            break;
    }
    
    /*Start the file name off with the current date*/
    string filename(get_curr_date());

    /*Get the name of the person*/
    string name;
    if (num[0] == '1')
        name = member_list[num].get_name();
    else
        name = provider_list[num].get_name();

    /*Remove spaces in the name*/
    name.erase(std::remove(name.begin(), name.end(), ' '), name.end());

    /*Append the name to the file name (the current date)*/
    filename += name + ".txt";
    
    ofstream out;
    out.open(filename.c_str());
    if (out.is_open())
    {
        if (num[0] == '1')
            member_list[num].write_report(out);
        else
            provider_list[num].write_report(out);

        out.close();
        out.clear();
    }
    return 1;
}


void Data_center::pull_EFT(){
}


void Data_center::sum_report(){
}


/*This takes and address object which is all of the info needed
 * for a person. Type is the type of person we are adding.
 * This returns 1 if the person was added successfully and
 * 0 otherwise (meaning that the type is not 1 for member
 * or 2 for provider).*/
int Data_center::add_person(const Address & to_add, int type){

    int ret = 1;

    switch(type)
    {
        case 1:
            {
                Member new_mem(to_add);
                new_mem.gen_num('1'); 
                while(member_list.count(new_mem.get_key()))
                  new_mem.gen_num('1');
                member_list.insert(make_pair(new_mem.get_key(), new_mem));
            }
            break;
        case 2:
            {
                Provider new_prov(to_add);
                new_prov.gen_num('2');
                while(provider_list.count(new_prov.get_key()))
                    new_prov.gen_num('2');
                provider_list.insert(make_pair(new_prov.get_key(), new_prov));
            }
            break;
        default:
            ret = 0;
    }
    return ret;
}


/*This takes the ID number of the provider or
 * member that is to be removed. It returns
 * 1 if the person exists and has been removed,
 * 0 if the person does not exist or the map
 * is empty, and -1 if the number is not a
 * provider or member number.*/
int Data_center::remove(const string & num){

    int ret = 0;

    switch(num[0])
    {
        case '1':
            if (member_list.erase(num))
                ret = 1;
            break;
        case '2':
            if (provider_list.erase(num))
                ret = 1;
            break;
        default:
            ret = -1;
            break;
    }
    return ret;
}


/*This takes an Address object which is what the address
 * will be updated to. It also takes the user's ID number.
 * It checks if the person exists and if so updates their
 * address. It returns 1 if they exist and if it has been
 * updated, -1 if the number is not a provider or member
 * number, and 0 if the map is empty or the number wasn't
 * found. These returns are really just for unit testing.
 * We can call check_valid before calling this to check
 * for everything as well so that the menu doesn't have to
 * deal with all of these returns.*/
int Data_center::update(const string & num, const Address & update_to){

    int ret = 0;

        switch(num[0])
        {
          case '1':
            {
                if (member_list.count(num))
                {
                    member_list[num].update(update_to);
                    ret = 1;
                }
            }
            break;
          case '2':
            {
                if (provider_list.count(num))
                {
                    provider_list[num].update(update_to);
                    ret = 1;
                }
                break;
            }
          default:
            ret = -1;
            break;
        }
        return ret;
}





/*This method adds a service to the people and writes
 * to "disk". It relies on the curr_provider and
 * curr_member pointers to be set.*/
void Data_center::add_service(){

    if (prov_dir.empty())
    {
        cerr << "\nProvider Directory not found\n";
        return;
    }
   
    /*This shouldn't happen because suspension
     * should be checked prior to calling this
     * method.*/
    if (!curr_member)
    {
        cout << "\nMember is suspended\n";
        return;
    }

    /*Service date gets read first*/
    Serv_date date;
    date.read();

    map<string, Service>::iterator it;
    bool found;
    /*Here we find the service in the provider
     * directory.*/
    do
    {
        found = true;
        /*Read in the service code*/
        string code(read_num(2));
        /*Attempt to find the service*/
        it = prov_dir.find(code);
        if (it == prov_dir.end()) //Not found
        {
            cout << "\nService code not found, try again\n";
            found = false;
        }
        else
            it->second.disp_name(); //Display the serv name
    }while(!found || !is_correct());

    /*Create the provider service by calling the constructor
     * that takes a member, a service, and a serv_date and
     * copies the necessary info*/
    Provider_service p_serv(*curr_member, it->second, date);
    /*Read in the comments*/
    p_serv.read_comm();
    /*Copy it into a member service object*/
    Member_service m_serv(*curr_provider, p_serv);
    /*Insert it into provider's service list*/
    provider_list[curr_provider->get_key()].add_service(p_serv);
    /*Insert it into member's service list*/
    member_list[curr_member->get_key()].add_service(m_serv);

    /*Display the service fee*/
    it->second.disp_fee();

    /*Write to "disk"*/
    ofstream out;
    
    /*The ios::app command appends to the file*/
    out.open("services.txt", ios::app);

    if (out.is_open())
    {
        write_curr_DT(out);
        p_serv.Serv_date::write_report(out);
        out << "\nProvider number: " << curr_provider->get_key()
            << "\nMember number: " << curr_member->get_key()
            << "\nService code: " << p_serv.get_key();
        p_serv.write_comm(out);

        out.close();
        out.clear();
    }
}


void Data_center::set_serv_test(){

    Member_service temp;
    temp.set_test();
    member_list["128461839"].add_service(temp);
}


/* -------- TERMINAL CLASS METHODS -------- */

Terminal::Terminal(Data_center & link){
    data_link = &link;
}


/*CANNOT ADD SERVICES IF THE MEMBER IS SUSPENDED*/
void Terminal::provider_menu(){

    // Clear screen
    for(int i = 0; i < 100; ++i){
        cout << "\n";
    }
    
    cout << "Welcome to the Provider Menu.\n\n";
    int choice = 0;

    do{
        cout << "Here are your options:\n\n"
             << "\t(1)  Input a Service\n"
             << "\t(2)  Request Provider Directory\n"
             << "\t(3)  Exit\n"
             << "Please enter the number corresponding to your selection: ";

        cin >> choice;
        cin.clear();
        cin.ignore(100, '\n');

        for(int i = 0; i < 100; ++i){
            cout << "\n";
        }

        if(choice >= 1 && choice <= 2){
            switch(choice){
                case 1:
                    /*Make sure member is not suspended*/
                    data_link->add_service();
                    break;
                case 2:
                    data_link->disp_map(3);
                    break;
            }
        }

        else if(choice != 3){
            cout << "Error: Invalid selection. Please try again.\n\n";
        }

    }while(choice != 3);
    
    return;
}


void Terminal::manager_menu(){

    // Clear screen
    for(int i = 0; i < 100; ++i){
        cout << "\n";
    }
    
    cout << "Welcome to the Manager Menu.\n\n";
    int choice = 0;

    do{
        cout << "Here are your options:\n\n"
             << "\t(1)  Run Member Report\n"
             << "\t(2)  Run Provider Report\n"
             << "\t(3)  Run Summary Report\n"
             << "\t(4)  Pull EFT Data\n"
             << "\t(5)  Run Interactive Mode\n"
             << "\t(6)  Exit\n\n"
             << "Please enter the number corresponding to your selection: ";

        cin >> choice;
        cin.clear();
        cin.ignore(100, '\n');

        for(int i = 0; i < 100; ++i){
            cout << "\n";
        }

        if(choice >= 1 && choice <= 5){
            switch(choice){
                case 1:
                    //data_link->person_report(); 
                    break;
                case 2:
                    //data_link->person_report();
                    break;
                case 3:
                    data_link->sum_report();
                    break;
                case 4:
                    data_link->pull_EFT();
                    break;
                case 5:
                    interactive_mode();
                    break;
            }
        }

        else if(choice != 6){
            cout << "Error: Invalid selection. Please try again.\n\n";
        }

    }while(choice != 6);
    
    return;
}


void Terminal::interactive_mode(){

    // Clear screen
    for(int i = 0; i < 100; ++i){
        cout << "\n";
    }
    
    cout << "Welcome to Interactive Mode.\n\n";
    int choice = 0;

    do{
        cout << "Here are your options:\n\n"
             << "\t(1)  Add a new Provider or Member\n"
             << "\t(2)  Remove an existing Provider or Member\n"
             << "\t(3)  Update existing Provider or Member records\n"
             << "\t(4)  Exit\n\n"
             << "Please enter the number corresponding to your selection: ";

        cin >> choice;
        cin.clear();
        cin.ignore(100, '\n');

        for(int i = 0; i < 100; ++i){
            cout << "\n";
        }

        if(choice >= 1 && choice <= 3){
            switch(choice){
                case 1:
                    //data_link->add_person();
                    break;
                case 2:
                    //data_link->remove();
                    break;
                case 3:
                    //data_link->update();
                    break;
            }
        }

        else if(choice != 4){
            cout << "Error: Invalid selection. Please try again.\n\n";
        }

    }while(choice != 4);
    
    return;
}


void Terminal::start_menu(){

    // Clear screen
    for(int i = 0; i < 100; ++i){
        cout << "\n";
    }

    cout << "Welcome to the Chocoholics Anonymous terminal.\n\n";

    string ID_num(read_num(1));
    char first_num = ID_num[0];
   
    // Checking if the user is not a Provider nor a Manager.
    if(first_num != '2' && first_num != '3'){
        for(int i = 0; i < 100; ++i){
            cout << "\n";
        }

        cout << "You do not have permission to access this terminal.\n"
             << "Terminal booting down.\n\n";

        return;
    }

    //validate(data_link, ID_num);

    if(data_link->check_valid(ID_num) < 0){
        // More to do here, depends on what messages/options
        // check_valid provides on the Data_center side.
        return;
    }

    if(first_num == '3'){ // Manager
        manager_menu();
    }

    else{
        provider_menu();
    }


    return;
}

/* Some stuff written in case Data_center doesn't handle the error messages.
int Terminal::validate(const Data_center * link, string & ID_num){

    int valid = link->check_valid(ID_num); // returns 0 for valid, -1 for invalid
    char response;

    while(valid == -1){
        cout << "Error: Invalid user ID number.\n"
             << "The user ID number entered was not found in the ChocAn Data Center.\n"
             << "Would you like to try again? (Y/N): ";
        cin >> response;
        cin.ignore(100, '\n');
        response = toupper(response);

        if(response == 'N'){
          return 0;
        }

        ID_num = read_num(1);

        valid = link->check_valid(ID_num, set);
    }

    return 1;
}

*/
