#include <list>
#include "services.h"


// Address, Provider, and Member Classes

class Address: public Name{

    public:
        Address();
        Address(char first_num);
        Address(std::ifstream & in);
        void write_file(std::ofstream & out) const;
        void display() const;
        void read();

    protected:
        std::string street;
        std::string city;
        std::string state;
        std::string zip;
};


class Provider: public Address{

    public:
        Provider();
        Provider(char first_num);
        Provider(std::ifstream & in);
        void write_file(std::ofstream & out);
        void add_service(const Provider_service & to_add);

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
        void write_file(std::ofstream & out);
        void add_service(const Member_service & to_add);

    private:
        bool suspended;
        std::list<Member_service> serv_list;
};
