/********************************************************************* 
 ** Program Filename: player.hpp
 ** Author: Braam Beresford
 ** Date: 05/13/18
 ** Description: Decleration of player class
 ** Input: N/A
 ** Output: Screen print
 *********************************************************************/
#ifndef PLAYER
#define PLAYER
#include "includes.hpp"

using namespace std;


/********************************************************************* 
 ** Function: Player class
 ** Description: Handles basic game data for player
 ** Parameters: N/A 
 ** Pre-Conditions: N/A
 ** Post-Conditions: N/A
 *********************************************************************/ 
class Player{
    private:
        string name;
        int balance;
        int num_properties;
	    int num_owned;
        

    public:
        Player();

        Player(const Player&);
        Player& operator=(const Player& copy);

        
        //Getters
        string get_name() const;
        int get_balance() const;
        int get_num_properties() const;
        int get_num_owned() const;

        //Setters

        void set_name(string name);
        void set_balance(int i);
        void change_balance(int i);
        void change_num_owned(int change); //Adds the difference



};




#endif