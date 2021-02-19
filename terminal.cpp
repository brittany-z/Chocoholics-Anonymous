#include <iostream>
#include "terminal.h"
using namespace std;


/* -------- DATA_CENTER CLASS METHODS -------- */

Data_center::Data_center(){
}

void Data_center::write_file(){
}


int Data_center::check_valid(const string & input, bool set){
    return 0;
}


void Data_center::disp_map(int map_type){

    // maybe it->second.display();
    //second is the second thing in the pair
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


void Data_center::add_service(){
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
    
    cout << "Welcome to the Manager Menu.\n\n";
    int choice = 0;

    do{
        cout << "Here are your options:\n\n"
             << "\t(1)  Input a Service\n"
             << "\t(2)  Request Provider Directory\n"
             << "\t(3)  Exit\n\n"
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
                    data_link->disp_map(4);
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
