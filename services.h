#include "name.h"


// Service, Serv_date, Provider_service, and Member_service Classes

class Service{

    public:
        Service();
        Service(std::ifstream & in);
        void display() const;
        std::string get_key() const;
        unsigned get_cost() const;

    protected:
        std::string name;
        float cost;
        std::string code;
};


class Serv_date: public Service{

    public:
        Serv_date();
        Serv_date(const Service & curr_ser);
        void write_file(std::ofstream & out);
        int compare_date(const Serv_date & a_date) const;
        void display() const;
        bool check_week() const;

    protected:
        int month;
        int day;
        int year;
        bool curr_week;
};


class Provider_service: public Serv_date{

    public:
        Provider_service();
        Provider_service(const Name & a_name, const Service & a_ser);
        void write_file(std::ofstream & out);

    private:
        time_t received;
        Name mem_info;
        std::string comments;
};


class Member_service: public Serv_date{

    public:
        Member_service();
        Member_service(const Name & a_name, const Provider_service & a_ser);
        void write_file(std::ofstream & out);

    private:
        std::string prov_name;
};
