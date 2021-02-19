#ifndef UTILITIES_H
#define UTILITIES_H
#include <string>
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
#endif
