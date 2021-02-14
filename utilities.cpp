#include "utilities.h"
#include <iostream>
#include <cctype>
using namespace std;


/*Consts for the person number max and
 * service code max. Not entirely
 * necessary other than for clarity.
 * size_t because that is what the
 * string methods that check length
 * return.*/
const size_t ID_MAX = 9;
const size_t CODE_MAX = 6;


/*This function simply asks the user if their input
 * is correct and returns true if it is and false
 * otherwise. It is used so that the user has a
 * chance fix any mistakes with their input.
 * It is called within any while loops where the
 * user is asked for input.*/
bool is_correct()
{
    char response;
    do
    {
        cout << "\nIs this correct? Please enter Y/N: ";
        cin >> response;
        cin.clear();
        cin.ignore(100, '\n');
        response = toupper(response);

    }while(response != 'Y' && response != 'N');

    if (response == 'Y')
        return true;
    return false;
}



/*This method simply asks the user if they would like
 * to perform an operation again. It may be useful 
 * so that the user doesn't have to return to the
 * menu in order to do the same thing again. It
 * returns true if they would like to repeat and
 * false otherwise.*/
bool again()
{
    char response;
    do
    {
        cout << "\nWould you like to perform this operation again?"
             << " Please enter Y/N: ";
        cin >> response;
        cin.clear();
        cin.ignore(100, '\n');
        response = toupper(response);

    }while(response != 'Y' && response != 'N');

    if (response == 'Y')
        return true;
    return false;
}



/*This function checks if a string exceeds the designated 
 * maximum length. It is necessary because string length 
 * cannot be restricted. This way, we can restrict the length 
 * and inform the user. It returns false if the string length 
 * is within a valid range, and true if exceeds the max 
 * length. It takes the length of the string and its max 
 * length.*/
bool exceed_max(size_t str_len, size_t max)
{
    if (str_len <= max)
        return false;
    cout << "\nCannot exceed " << max << " characters, please try again.\n";
    return true;
}


/*This function checks if a string is equal to the necessary
 * length. This is used for input that must be a certain
 * length such as state (ex. OR) and zip. Input like that
 * doesn't make sense to be less than or greater than a 
 * certain length. It returns true if it the correct length 
 * that it should be and false if it isn't. It takes the length
 * of the string and its max length.*/
bool equal_max(size_t str_len, size_t max)
{
    if (str_len == max)
        return true;
    cout << endl << max << " characters required, please try again.\n";
    return false;
}


/*This function prompts and reads for either a user number 
 * or a service code. This is useful since we have to prompt 
 * for this information in different circumstances and we 
 * don't want to repeat code. And both situations 
 * basically do the same thing but with a different prompt. 
 * It takes an identifying int that is used to indicate which
 * type of data we are reading. 1 for a user number and 2 
 * for a service code. It returns a copy of the string that 
 * was read in.*/
string read_num(int type)
{
    size_t max = 0;
    string temp;
    do
    {
        if (type == 1)
        {
            cout << "\nPlease enter user number: ";
            max = ID_MAX;
        }
        else if (type == 2)
        {
            cout << "\nPlease enter service code: ";
            max = CODE_MAX;
        }
        cin >> temp;
        cin.ignore(100, '\n');
        
        cout << "\nYou entered: " << temp << endl;
        /*Call the function that makes sure that the
         * string is the designated size since it
         * shouldn't be greater or less.*/
    }while(!equal_max(temp.length(), max) || !is_correct());

    return temp;
}

