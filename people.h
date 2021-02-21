#include <list>
#include "services.h"


// Address, Provider, and Member Classes


/*Consts for string lengths. 
 * size_t because that is what 
 * the string methods that
 * check length return.*/
const size_t STRT_MAX = 25;
const size_t CITY_MAX = 14;
const size_t STATE_MAX = 2;
const size_t ZIP_MAX = 5;


class Address: public Name{

    public:
        Address();
        Address(std::ifstream & in);
        void write_file(std::ofstream & out) const;
        void write_report(std::ofstream & out) const;
        void display() const;
        void read();
        //For testing, calls Name display
        void display_all() const;

    protected:
        std::string street;
        std::string city;
        std::string state;
        std::string zip;
};


class Provider: public Address{

    public:
        Provider();
        Provider(std::ifstream & in);
        void write_report(std::ofstream & out) const;
        void write_rec_curr_DT(std::ofstream & out) const;
        void add_service(const Provider_service & to_add);
        //For testing. Displays all info in hierarchy.
        void display_all() const;

    private:
        unsigned short num_consults;
        float total_fees;
        std::list<Provider_service> serv_list;
};


class Member: public Address{

    public:
        Member();
        Member(char first_num);
        Member(std::ifstream & in);
        void write_report(std::ofstream & out) const;
        void add_service(const Member_service & to_add);
        bool check_susp() const;
        //For testing. Displays all info in hierarchy.
        void display_all() const;

    private:
        bool suspended;
        std::list<Member_service> serv_list;
};
