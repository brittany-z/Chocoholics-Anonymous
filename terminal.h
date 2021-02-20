#ifndef TERMINAL_H
#define TERMINAL_H

#include <map>
#include <unordered_map>
#include "people.h"


// Data_center and Terminal Classes

class Data_center{

    public:
        Data_center();
        void write_file();
        //set is a flag to know if we need to set the pointers and permissions
        //or not, I was thinking about maybe using this method as a search as
        //well as a setter. Because a search method would do the same thing
        //other than setting the pointers and permissions.
        int check_valid(const std::string & input, bool set); 
        void disp_map(int map_type);
        void person_report();
        void pull_EFT();
        void sum_report();
        void add_person();
        void remove(); 
        void update();
        void add_service();

    private:
        char permissions;
        std::unordered_map<std::string, Provider> provider_list;
        std::unordered_map<std::string, Member> member_list;
        std::unordered_map<std::string, std::string> manager_list;
        std::map<std::string, Service> prov_dir;
        Provider * curr_provider;
        Member * curr_member;
};

class Terminal{

    public:
        Terminal(Data_center & link);
        void provider_menu();
        void manager_menu();
        void start_menu();
        void interactive_mode();
        //int validate(const Data_center * link, string & ID_num);
    
    private:
        Data_center * data_link;
};
#endif
