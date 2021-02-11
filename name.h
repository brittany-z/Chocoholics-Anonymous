#include <string>
#include <fstream>
#include "utilities.h"


class Name{
    
    public:
        Name();
        Name(std::ifstream & in);
        std::string gen_num(char first_num);
        void write_file(std::ofstream & out) const;
        void display() const; 
        bool compare_num(const std::string & num) const;
        std::string get_key() const;
        void copy_name(std::string & prov_name) const;

    protected:
        std::string a_name;
        std::string ID_num;
};
