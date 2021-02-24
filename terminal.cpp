#include <iostream>
#include "terminal.h"
using namespace std;


/* -------- DATA_CENTER CLASS METHODS -------- */

Data_center::Data_center(): curr_provider(NULL), curr_member(NULL){
    
    for (int i = 1; i < 5; ++i)
        read_file(i);
}


Data_center::~Data_center(){
}


/*Reads in any map from the txt file.*/
void Data_center::read_file(int type){
   
    /*Holds the | flag at the beginning of
     * each line. Used to prime the pump.*/
    char flag;
    ifstream in;
    if (type == 1)
        in.open("members.txt");
    else if (type == 2)
        in.open("providers.txt");
    else if (type == 3)
        in.open("prov_dir.txt");
    else
        in.open("managers.txt");

    if (in.is_open())
    {
        /*Prine the pump*/
        in >> flag;

        while (in && !in.eof())
        {
            if (type == 1)
            {
                /*Create temp to be added that invokes
                * the constructor that reads the data*/
                Member to_add(in);
                //Insert into map
                member_list.insert(make_pair(to_add.get_key(), to_add));
            }
            else if (type == 2)
            {
                /*Create temp to be added that invokes
                * the constructor that reads the data*/
                Provider to_add(in);
                //Insert into map
                provider_list.insert(make_pair(to_add.get_key(), to_add));
            }
            else if (type == 3)
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
            /*Prime the pump*/
            in >> flag;
        }
        in.close();
        in.clear();
    }
    else
        cerr << "\nFile not found\n";
}


//Or a destructor can do this
void Data_center::write_file(){
}


/*Returns 0 for valid, -1 for invalid, -2 for suspended*/
int Data_center::check_valid(const string & input, bool set){
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
                if(set) 
                    curr_member = &(it->second);
            }
          }
          else
              cout << "\nNo members stored\n";
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
              cout << "\nNo providers stored\n";
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
              cout << "\nNo managers stored\n";
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
                else
                    cout << "\nNo members stored\n";
                break;
            }
        case 2:
            {
                if(!provider_list.empty())
                    for(auto it = provider_list.begin(); it != provider_list.end(); ++it)
                        it->second.Name::display();
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


void Data_center::person_report(){
}


void Data_center::pull_EFT(){
}


void Data_center::sum_report(){
}


void Data_center::add_person(){
    int choice = -1;
    do{
        cout << "Here are your options:\n\n"
             << "\t(1)  Add a new Member\n"
             << "\t(2)  Add a new Provider\n"
             << "\t(3)  Exit\n\n"
             << "Please enter the number corresponding to your selection: ";

        cin >> choice;
        cin.clear();
        cin.ignore(100, '\n');

        for(int i = 0; i < 100; ++i){
            cout << "\n";
        }

        switch(choice)
        {
          case 1:
            {
                Member new_member;
                new_member.gen_num(choice);
                while(member_list.count(new_member.get_key()))
                  new_member.gen_num(choice);
                member_list.insert(make_pair(new_member.get_key(), new_member));
                break;
            }
          case 2:
            {
                Provider new_provider;
                new_provider.gen_num(choice);
                while(provider_list.count(new_provider.get_key()))
                  new_provider.gen_num(choice);
                provider_list.insert(make_pair(new_provider.get_key(), new_provider));
                break;
            }
          case 3:
            break;
          default:
            cout << "Error: Invalid selection. Please try again.\n\n";
            break;
        }
    }while(choice < 1 || choice > 3);
}


void Data_center::remove(){
    string input;
         
    int choice = -1;
    do{
        cout << "Here are your options:\n\n"
             << "\t(1)  Remove a Member\n"
             << "\t(2)  Remove a Provider\n"
             << "\t(3)  Display Members\n"
             << "\t(4)  Display providers\n"
             << "\t(5)  Exit\n\n"
             << "Please enter the number corresponding to your selection: ";
        cin >> choice;
        cin.clear();
        cin.ignore(100, '\n');


        for(int i = 0; i < 100; ++i){
            cout << "\n";
        }

        if (choice == 1 || choice == 2)
            input = read_num(3);

        switch(choice)
        {
          case 1:
            {
                if (!member_list.empty())
                {
                    if(!member_list.erase(input))
                        cout << "Error: Invalid ID. Please try again.\n\n";
                    else
                        cout << "Member with ID [" << input << "] erased.\n\n"; 
                }
                else
                    cout << "\nNo members stored\n";
                break;
            }
          case 2:
            {
                if (!provider_list.empty())
                {
                    if(!provider_list.erase(input))
                        cout << "Error: Invalid ID. Please try again.\n\n";
                    else
                        cout << "Provider with ID [" << input << "] erased.\n\n";
                }
                else
                    cout << "\nNo providers found\n";
                break;
            }
          case 3:
            disp_map(1);
            break;
          case 4:
            disp_map(2);
            break;
          case 5:
            break;
          default:
            cout << "Error: Invalid selection. Please try again.\n\n";
            break;
        }
    }while(choice != 5);

}


void Data_center::update(){
    string input;           
    int choice = -1;

    do{
        cout << "Here are your options:\n\n"
             << "\t(1)  Update a Member\n"
             << "\t(2)  Update a Provider\n"
             << "\t(3)  Display members\n"
             << "\t(4)  Display providers\n"
             << "\t(5)  Exit\n\n"
             << "Please enter the number corresponding to your selection: ";
        cin >> choice;
        cin.clear();
        cin.ignore(100, '\n');


        for(int i = 0; i < 100; ++i){
            cout << "\n";
        }
        if (choice == 1 || choice == 2)
            input = read_num(3);

        switch(choice)
        {
          case 1:
            {
                unordered_map<string, Member>::iterator temp;
                if (!member_list.empty())
                {
                    temp = member_list.find(input);
                    if(temp != member_list.end())
                        temp->second.read();
                    else
                        cout << "Error: Invalid selection. Please try again.\n\n";
                }
                else
                    cout << "\nNo members stored\n";
                break;
            }
          case 2:
            {
                unordered_map<string, Provider>::iterator temp;
                if (!provider_list.empty())
                {
                    temp = provider_list.find(input);
                    if(temp != provider_list.end())
                        temp->second.read();
                    else
                        cout << "Error: Invalid selection. Please try again.\n\n";
                }
                else
                    cout << "\nNo providers stored\n";
                break;
            }
          case 3:
            disp_map(1);
            break;
          case 4:
            disp_map(2);
            break;
          case 5:
            break;
          default:
            cout << "Error: Invalid selection. Please try again.\n\n";
            break;
        }
    }while(choice != 5);
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


/* -------- TERMINAL CLASS METHODS -------- */

Terminal::Terminal(Data_center & link){
    data_link = &link;
}


/*Need to call check valid for member ID for adding service
 * (where set is true) per assignment description. Add service 
 * will not work without this.*/
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
        cin.clear();
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


/*Need member check-in option per assignment description*/
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
