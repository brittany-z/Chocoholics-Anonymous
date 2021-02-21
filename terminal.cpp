#include <iostream>
#include "terminal.h"
using namespace std;


/* -------- DATA_CENTER CLASS METHODS -------- */

Data_center::Data_center(): curr_provider(NULL), curr_member(NULL), permissions('2') {}


Data_center::~Data_center(){
}


/*Reads provider directory*/
void Data_center::read_dir(){
    
    /*Holds flag used to primp the pump*/
    char flag;

    ifstream in;
    in.open("prov_dir.txt");

    if (in)
    {
        /*Prine the pump*/
        in >> flag;

        while (in && !in.eof())
        {
            in.ignore(100, '\n');

            Service to_add(in);
            prov_dir.insert(make_pair(to_add.get_key(), to_add));

            /*Prime the pump*/
            in >> flag;
        }
        in.close();
        in.clear();
    }
    else
        cerr << "\nFile not found\n";
}

void Data_center::write_file(){
}


int Data_center::check_valid(const string & input, bool set){
    return 0;
}


void Data_center::disp_map(int map_type){

    if (map_type == 1)
        if(!member_list.empty())
            for(auto it = member_list.begin(); it != member_list.end(); ++it)
                it->second.Name::display();
        else
            cout << "\nMember list not found\n";
    if (map_type == 2)
        if(!provider_list.empty())
            for(auto it = provider_list.begin(); it != provider_list.end(); ++it)
                it->second.display_all();
        else
            cout << "\nProvider list not found\n";
    if (map_type == 3)
        if (!prov_dir.empty())
            for(auto it = prov_dir.begin(); it != prov_dir.end(); ++it)
                it->second.display();
        else
            cout << "\nProvider Directory not found\n";
    if (map_type == 4)
        if(!manager_list.empty())
            for(auto it = manager_list.begin(); it != manager_list.end(); ++it)
                cout << it->first << endl << it->second << endl;
        else
            cout << "\nManager list not found\n";
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


/*This method adds a service to the people and writes
 * to "disk". It relies on the curr_provider and
 * curr_member pointers to be set.*/
void Data_center::add_service(){

    if (permissions != '2')
    {
        cout << "\nNeed the appropriate permissions\n";
        return;
    }
    if (prov_dir.empty())
    {
        cout << "\nProvider Directory not found\n";
        return;
    }

    Serv_date date;
    map<string, Service>::iterator it;
    bool found;

    do
    {
        found = true;
        string code(read_num(2));
        it = prov_dir.find(code);
        if (it == prov_dir.end())
        {
            cout << "\nService code not found, try again\n";
            found = false;
        }
        else
            it->second.disp_name();
    }while(!found || !is_correct());

    Provider_service p_serv(*curr_member, it->second, date);
    Member_service m_serv(*curr_provider, p_serv);
    provider_list[curr_provider->get_key()].add_service(p_serv);
    member_list[curr_member->get_key()].add_service(m_serv);

    it->second.disp_fee();

    ofstream out;
     
    out.open("services.txt", ios::app);

    if (out)
    {
        write_curr_DT(out);
        p_serv.Serv_date::write_report(out);
        out << "\nProvider number: " << curr_provider->get_key()
            << "\nMember number: " << curr_member->get_key()
            << "\nService code: " << p_serv.get_key();
        p_serv.write_comm(out);

        out.close();
        out.clear();
    }
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

