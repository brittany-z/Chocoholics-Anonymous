#include <iostream>
#include "services.h"
using namespace std;


/* -------- SERVICE CLASS METHODS -------- */

Service::Service(){
}


Service::Service(ifstream & in){
}


void Service::display() const{
}


string Service::get_key() const{
    return "null";
}


unsigned Service::get_cost() const{
    return 0;
}


/* -------- SERV_DATE CLASS METHODS -------- */

Serv_date::Serv_date(){
}


Serv_date::Serv_date(const Service & curr_ser){
}


void Serv_date::write_file(ofstream & out){
}


int Serv_date::compare_date(const Serv_date & a_date) const{
    return 0;
}


void Serv_date::display() const{
}


bool Serv_date::check_week() const{
    return 0;
}


/* -------- PROVIDER_SERVICE CLASS METHODS -------- */

Provider_service::Provider_service(){
}


Provider_service::Provider_service(const Name & a_name, const Service & a_ser){
}


void Provider_service::write_file(ofstream & out){
}


/* -------- MEMBER_SERVICE CLASS METHODS -------- */

Member_service::Member_service(){
}


Member_service::Member_service(const Name & a_name, const Provider_service & a_ser){
}


void Member_service::write_file(ofstream & out){
}

