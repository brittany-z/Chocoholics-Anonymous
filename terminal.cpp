#include <iostream>
#include "terminal.h"
using namespace std;


/* -------- DATA_CENTER CLASS METHODS -------- */

Data_center::Data_center(){
}

void Data_center::write_file(){
}


int Data_center::check_valid(const string & input, bool set){
    return 0;
}


void Data_center::disp_map(int map_type){

    // maybe it->second.display();
    //second is the second thing in the pair
}


void Data_center::person_report(){
}


void Data_center::pull_EFT(){
}


void Data_center::sum_report(){
}


void Data_center::add_person(){

    /* 1. Instantiate user, this will cause the ripple affect of
     * constructors that read
     *
     * 2 call gen_num to generate user number catch string in temp
     *
     * 3. in while loop, call check valid, once check valid indicates
     * that the number is invalid (doesn't exist in map) then
     *
     * 4. add person to map by list_name.insert(make_pair(obj.get_key(), obj));
     * or list_name.insert(make_pair(temp, obj)); where temp is the num returned
     * by gen_num*/
}


void Data_center::remove(){

    //I think they have removal methods
}


void Data_center::update(){
}


void Data_center::add_service(){
}


/* -------- TERMINAL CLASS METHODS -------- */

Terminal::Terminal(){
}


Terminal::Terminal(const Data_center & link){
}


void Terminal::provider_menu(){
}


void Terminal::manager_menu(){
}


void Terminal::start_menu(){
}
