#ifndef UTILITIES_H
#define UTILITIES_H
#include <string>
#include <fstream>
// Put your handy dandy utility function prototypes here.


//Asks if input is correct
bool is_correct();
//Asks if they would like to do something again
bool again();
//Checks if a string exceeds the max length
bool exceed_max(size_t str_len, size_t max);
//Checks if a string is the necessary length
bool equal_max(size_t str_len, size_t max);
//Prompts and reads for a user number or a
//service code depending on the int type
std::string read_num(int type);
/*Returns a string of the current date*/
std::string get_curr_date();
//Writes the current date end time for the service file
void write_curr_DT(std::ofstream & out);
void remove_files();

#endif
