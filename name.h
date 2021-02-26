#ifndef NAME_H
#define NAME_H

#include <fstream>
#include "utilities.h"


/*Consts for string lengths. 
 * size_t because that is what 
 * the string methods that
 * check length return.*/
const size_t NUM_MAX = 9;
const size_t N_MAX = 25;



class Name{
    
    public:
        Name();
        //Reads from file
        Name(std::ifstream & in);
        //Generates ID_num for added person
        std::string gen_num(char first_num);
        /*Prompts and reads from user*/
        void read();
        //Writes to file
        void write_file(std::ofstream & out) const;
        void write_report(std::ofstream & out) const;
        void display() const; 
        //Gets key (ID_num) for map operations
        std::string get_key() const;
        //Gets name for filename of reports
        std::string get_name() const;
        //Copies name for Member_service
        void copy_name(std::string & prov_name) const;

    protected:
        std::string a_name;
        std::string ID_num;
};
#endif
