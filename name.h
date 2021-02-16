#include <fstream>
#include "utilities.h"


/*Consts for string lengths. 
 * size_t because that is what 
 * the string methods that
 * check length return.*/
const size_t NAME_MAX = 25;
const size_t NUM_MAX = 9;


class Name{
    
    public:
        //Reads from user
        Name();
        //Reads from file
        Name(std::ifstream & in);
        //Generates ID_num for added person
        std::string gen_num(char first_num);
        //Writes to file
        void write_file(std::ofstream & out) const;
        void display() const; 
        //Gets key (ID_num) for map operations
        std::string get_key() const;
        //Copies name for Member_service
        void copy_name(std::string & prov_name) const;

    protected:
        std::string a_name;
        std::string ID_num;
};
