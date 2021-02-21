#include <iostream>
#include "terminal.h"
using namespace std;


/* -------- DATA_CENTER CLASS METHODS -------- */

Data_center::Data_center(): curr_provider(NULL), curr_member(NULL){
    read_dir();
}


Data_center::~Data_center(){
}


/*Reads provider directory*/
void Data_center::read_dir(){
    
    /*Holds flag ($) used to primp the pump.
     * I do this so that the read constructor
     * can read the all of the real data. I 
     * don't want this method to read any real 
     * data. Basically I don't want to prime 
     * the pump with real data so I use a flag
     * that separates the object data to 
     * be read. See text file for clarification.*/
    char flag;

    ifstream in;
    in.open("prov_dir.txt");

    if (in)
    {
        /*Prine the pump*/
        in >> flag;

        while (in && !in.eof())
        {
            in.ignore(100, '\n');

            /*Create temp to be added that invokes
             * the constructor that reads the data*/
            Service to_add(in);
            //Insert into map
            prov_dir.insert(make_pair(to_add.get_key(), to_add));

            /*Prime the pump*/
            in >> flag;
        }
        in.close();
        in.clear();
    }
    else
        cerr << "\nFile not found\n";
}

void Data_center::write_file(){
}


int Data_center::check_valid(const string & input, bool set){
    return 0;
}


void Data_center::disp_map(int map_type){

    if (map_type == 1)
        if(!member_list.empty())
            for(auto it = member_list.begin(); it != member_list.end(); ++it)
                it->second.Name::display();
        else
            cout << "\nMember list not found\n";
    if (map_type == 2)
        if(!provider_list.empty())
            for(auto it = provider_list.begin(); it != provider_list.end(); ++it)
                it->second.display_all();
        else
            cout << "\nProvider list not found\n";
    if (map_type == 3)
        if (!prov_dir.empty())
            for(auto it = prov_dir.begin(); it != prov_dir.end(); ++it)
                it->second.display();
        else
            cout << "\nProvider Directory not found\n";
    if (map_type == 4)
        if(!manager_list.empty())
            for(auto it = manager_list.begin(); it != manager_list.end(); ++it)
                cout << it->first << endl << it->second << endl;
        else
            cout << "\nManager list not found\n";
}


void Data_center::person_report(){
}


void Data_center::pull_EFT(){
}


void Data_center::sum_report(){
}


void Data_center::add_person(){

    /* 1. Instantiate user, this will cause the ripple affect of
     * constructors that read
     *
     * 2 call gen_num to generate user number catch string in temp
     *
     * 3. in while loop, call check valid, once check valid indicates
     * that the number is invalid (doesn't exist in map) then
     *
     * 4. add person to map by list_name.insert(make_pair(obj.get_key(), obj));
     * or list_name.insert(make_pair(temp, obj)); where temp is the num returned
     * by gen_num*/
}


void Data_center::remove(){

    //I think they have removal methods
}


void Data_center::update(){
}


/*This method adds a service to the people and writes
 * to "disk". It relies on the curr_provider and
 * curr_member pointers to be set. As well as permissions.*/
void Data_center::add_service(){

    if (permissions != '2')
    {
        cout << "\nNeed the appropriate permissions\n";
        return;
    }
    if (prov_dir.empty())
    {
        cout << "\nProvider Directory not found\n";
        return;
    }

    Serv_date date;
    map<string, Service>::iterator it;
    bool found;

    do
    {
        found = true;
        string code(read_num(2));
        it = prov_dir.find(code);
        if (it == prov_dir.end())
        {
            cout << "\nService code not found, try again\n";
            found = false;
        }
        else
            it->second.disp_name();
    }while(!found || !is_correct());

    Provider_service p_serv(*curr_member, it->second, date);
    Member_service m_serv(*curr_provider, p_serv);
    provider_list[curr_provider->get_key()].add_service(p_serv);
    member_list[curr_member->get_key()].add_service(m_serv);

    it->second.disp_fee();

    /*Write to "disk"*/
    ofstream out;
    
    /*The ios::app command appends to the file*/
    out.open("services.txt", ios::app);

    if (out)
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


/* -------- TERMINAL CLASS METHODS -------- */

Terminal::Terminal(Data_center & link){
    data_link = &link;
}


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
        cin.ignore(100, '\n');

        for(int i = 0; i < 100; ++i){
            cout << "\n";
        }

        if(choice >= 1 && choice <= 2){
            switch(choice){
                case 1:
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
        cin.ignore(100, '\n');

        for(int i = 0; i < 100; ++i){
            cout << "\n";
        }

        if(choice >= 1 && choice <= 5){
            switch(choice){
                case 1:
                    data_link->person_report(); 
                    break;
                case 2:
                    data_link->person_report();
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
        cin.ignore(100, '\n');

        for(int i = 0; i < 100; ++i){
            cout << "\n";
        }

        if(choice >= 1 && choice <= 3){
            switch(choice){
                case 1:
                    data_link->add_person();
                    break;
                case 2:
                    data_link->remove();
                    break;
                case 3:
                    data_link->update();
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
    bool set = 0;
   
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

    if(data_link->check_valid(ID_num, set) < 0){
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

    bool set = 0;
    int valid = link->check_valid(ID_num, set); // returns 0 for valid, -1 for invalid
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
