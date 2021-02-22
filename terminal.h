#ifndef TERMINAL_H
#define TERMINAL_H

#include <map>
#include <unordered_map>
#include "people.h"


// Data_center and Terminal Classes

class Data_center{

    public:
        Data_center();
        ~Data_center();
        void read_dir();
        void write_file();
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
        std::unordered_map<std::string, Provider> provider_list;
        std::unordered_map<std::string, Member> member_list;
        std::unordered_map<std::string, Name> manager_list;
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
    
    private:
        Data_center * data_link;
};
#endif
