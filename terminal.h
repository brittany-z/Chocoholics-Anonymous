#include <map>
#include <unordered_map>
#include "people.h"


// Data_center and Terminal Classes

class Data_center{

    public:
        Data_center();
        int validate(const std::string & input);
        void provider_menu(const std::string & num);
        void manager_menu(const std::string & num);
        void interactive_menu();

    private:
        char permissions;
        std::unordered_map<std::string, Provider> provider_list;
        std::unordered_map<std::string, Member> member_list;
        std::unordered_map<std::string, std::string> manager_list;
};

class Terminal{

    public:
        Terminal();
        Terminal(const Data_center & link);
        int validate(const std::string & input);
        void provider_menu(const std::string & num);
        void manager_menu(const std::string & num);
        void start_menu();
    
    private:
        Data_center * data_link;
        Provider * curr_provider;
        Member * curr_member;
        std::map<std::string, Service> prov_dir;
};
