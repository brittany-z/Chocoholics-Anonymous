#include <iostream>
#include "people.h"
using namespace std;


/* -------- ADDRESS CLASS METHODS -------- */

Address::Address(){
}


Address::Address(char first_num){
}


Address::Address(ifstream & in){
}


void Address::write_file(ofstream & out) const{
}


void Address::display() const{
}


void Address::read(){
}


/* -------- PROVIDER CLASS METHODS -------- */

Provider::Provider(){
}


Provider::Provider(char first_num){
}


Provider::Provider(ifstream & in){
}


void Provider::write_file(ofstream & out){
}


void Provider::add_service(const Provider_service & to_add){
}


/* -------- MEMBER CLASS METHODS -------- */

Member::Member(){
}


Member::Member(char first_num){
}


Member::Member(ifstream & in){
}


void Member::write_file(ofstream & out){
}


void Member::add_service(const Member_service & to_add){
}
