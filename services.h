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
        Service(); 
        Service(std::ifstream & in);
        void write_report(std::ofstream & out, int type) const;
        void set_test();
        void disp_name() const;
        void disp_fee() const;
        void display() const;
        std::string get_key() const;
        unsigned get_fee() const;

    protected:
        std::string name;
        float fee;
        std::string code;
};


class Serv_date: public Service{

    public:
        Serv_date();
        Serv_date(const Service & curr_serv, const Serv_date & date); 
        Serv_date(std::ifstream & in);
        Serv_date(const Service & curr_ser);
        void read();
        void write_report(std::ofstream & out) const;
        int compare_date(const Serv_date & curr_serv) const;
        void display() const;
        bool check_week() const;
        void set_test();

    protected:
        int month;
        int day;
        int year;
};


class Provider_service: public Serv_date{

    public:
        Provider_service();
        Provider_service(std::ifstream & in);
        Provider_service(const Name & curr_mem, const Service & curr_serv,
                const Serv_date & date);
        void read_comm();
        void write_report(std::ofstream & out) const;
        void write_comm(std::ofstream & out) const;
        void display_all() const; //For testing

    private:
        time_t received;
        Name mem_info;
        std::string comments;
};


class Member_service: public Serv_date{

    public:
        Member_service();
        Member_service(std::ifstream & in);
        Member_service(const Name & curr_prov, const Provider_service & curr_serv);
        void write_report(std::ofstream & out) const;
        void display_all() const; //For testing
        void set_test();

    private:
        std::string prov_name;
};
#endif
