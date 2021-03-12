#include "terminal.h"
#include <iostream>
using namespace std;


int main(){

    Data_center ChocAn;
    ChocAn.read_files();
    Terminal term(ChocAn);
    term.start_menu();

    ChocAn.write_file(); //Only if you want to save all changes (so save the txts)
    
    return 0;
}
