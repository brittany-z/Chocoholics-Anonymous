#ifndef SERVICES_H
#define SERVICES_H
#include "name.h"


// Service, Serv_date, Provider_service, and Member_service Classes


/*Const for string length. 
 * size_t because that is what 
 * the string methods that
 * check length return.*/
const size_t COM_MAX = 100;


class Service{

    public:
        Service(); //For testing
        Service(std::ifstream & in);
        void write_file(std::ofstream & out) const;
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
        Serv_date(std::ifstream & in);
        Serv_date(const Service & curr_ser);
        void write_file(std::ofstream & out) const;
        int compare_date(const Serv_date & curr_serv) const;
        void display() const;
        bool check_week() const;

    protected:
        int month;
        int day;
        int year;
        /*I think this may not be needed because the check_week
         * function can do this.
        bool curr_week;*/
};


class Provider_service: public Serv_date{

    public:
        Provider_service(std::ifstream & in);
        Provider_service(const Name & curr_mem, const Service & curr_serv);
        void write_file(std::ofstream & out) const;
        void display_all() const; //For testing

    private:
        time_t received;
        Name mem_info;
        std::string comments;
};


class Member_service: public Serv_date{

    public:
        Member_service(std::ifstream & in);
        Member_service(const Name & curr_prov, const Provider_service & curr_serv);
        void write_file(std::ofstream & out) const;
        void display_all() const; //For testing

    private:
        std::string prov_name;
};
#endif
