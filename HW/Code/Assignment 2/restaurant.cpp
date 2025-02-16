#include "driver.hpp"
#include "restaurant.hpp"
#include "menu.hpp"
#include <iostream>
using namespace std;
//Constructor


/*********************************************************************
 ** Function: Constructor and distrcutors
 ** Description: Creates and initializes the object
 ** Parameters: Creates and destroys objects
 ** Pre-Conditions: 
 ** Post-Conditions: 
 *********************************************************************/
Restaurant::Restaurant() {
    Menu menu;
    orders = NULL;
    employees = NULL;
    num_orders = 0;
    num_days = 0;
    week = NULL;
    name = "NA";
    phone = "000-000-0000";
    address = "NA";
    num_employees = 0;

}


Restaurant::~Restaurant(){
    if(employees != NULL)
        delete [] this->employees;
    if(week != NULL)
        delete [] this->week;
    if(week != NULL)
        delete [] this->orders;
    
    employees = NULL;
    week = NULL;
}

/*********************************************************************
 ** Function: Accesors
 ** Description: Gives user access to private variables
 ** Parameters: Private class must exist
 ** Pre-Conditions:
 ** Post-Conditions:
 *********************************************************************/
// Accessors
void Restaurant::view_hours() const{
    for (int i = 0; i < 7; i++) {
        cout << week[i].day << ' ' <<  week[i].open_hour  << ' ' << week[i].close_hour << endl;
    }
}

void Restaurant::view_name() const { cout << name << endl;}
void Restaurant::view_address() const { cout << this->address << endl; }
void Restaurant::view_phone() const { cout << phone << endl; }
void Restaurant::view_num_employees() const { cout << this-> num_employees << endl; }
int Restaurant::return_num_employees() const { return this->num_employees;}
void Restaurant::view_employees() const {
    if (!employees) {
        for (int i = 0; i < this->num_employees; i++) {
            cout << employees[i].id << employees[i].first_name << employees[i].last_name << employees[i].password << endl;
        }
    }
}

void Restaurant::view_menu() const{
    menu.view_menu();
}


void Restaurant::search_by_cost(){
    string input ="", size = "";
    int price = 0;
    while(true){
        printf("What size are you looking for? (small, medium, large) \n");
        getline(cin, size);
        if(size == "small" || size == "medium" || size == "large")
            break;

        printf("Invalid input, lower case only\n");
    }
    while(true){
        printf("What is the max price you're looking for? \n");
        getline(cin, input);
        if(is_int(input)){
            price = get_int(input);
            break;
        }
    }
    //test
    // cout << "LET SEE IF THIS WORKS" << endl;
    Menu results;
    results = menu.search_pizza_by_cost(price, size);
    // cout << "I'm here! " << endl;
    results.view_menu();
    
    
    // menu.view_menu();
}

bool Restaurant::validate_login(Restaurant &r) const{
    string input = "";
    bool valid = false;
    do{
        printf("Username: \n");
        getline(cin, input);
        if(input == "Q" || input == "q")
            return false;
        for(int i =0; i < r.return_num_employees(); i++){
            if(employees[i].id == input){
                valid = true;
                break;
            }
        }
        
        printf("Please input a valid username. Q to quit\n");

    } while(!valid);
    valid = false;
    do{
        system("clear");
        printf("Password: \n");
        getline(cin, input);
        for(int i =0; i < r.return_num_employees(); i++){
            if(employees[i].password == input){
                valid = true;
                break;
            }

            printf("Please input a valid password\n");
        }
    } while(!valid);

    return true;
}


//Mutators

/*********************************************************************
 ** Function: Mutators
 ** Description: Mutate the function in certain way
 ** Parameters: Priavte variables must exit
 ** Pre-Conditions:
 ** Post-Conditions:
 *********************************************************************/
void Restaurant::set_name(string new_name) {name = new_name;}
void Restaurant::set_phone(string new_phone)  {phone = new_phone;}
void Restaurant::set_address(string new_add) {address = new_add;}
void Restaurant::set_num_days(int num) { num_days = num;}

/*********************************************************************
 ** Function: Load data
 ** Description: Loads data for restuarant calss
 ** Parameters: Files must exist
 ** Pre-Conditions:
 ** Post-Conditions:
 *********************************************************************/
void Restaurant::load_data() {
    int num_days;
    fstream f;
    verify_file_open(f, REST_NAME); //opens and checks, re-prompts too
    getline(f, this->name);
    getline(f, this->phone);
    getline(f, this->address);

    f >> this->num_days;
    

    this->week = new hours[num_days];
    for (int i = 0; i < num_days; i++) {
        f >> week[i].day >> week[i].open_hour >> week[i].close_hour;
    }
    
    f.close();
   
    verify_file_open(f, EMP_NAME);
    this->num_employees = get_num_lines(f);
    employees = new employee [num_employees];
    get_employees(f);

    f.close();
     
    verify_file_open(f, ORD_NAME);
    this->num_orders = get_num_lines(f);
    this->orders = new order [this->num_orders*100];
    get_orders(f);
    
    f.close();
    
    menu.load_data(); 
}


/*********************************************************************
 ** Function: Change hours
 ** Description: Allows users to change hours
 ** Parameters: Hours file must exist
 ** Pre-Conditions:
 ** Post-Conditions:
 *********************************************************************/
void Restaurant::change_hours(){
    string input = "";
    int index = 0;
    this->view_hours();
    printf("What day would you like to change? ");
    getline(cin, input);
    index = verify_week_day(input);

    do{
    printf("What opening time would you like? ");
    getline(cin, input);
    }while(!is_int(input));
    week[index].open_hour = input;

    do{
    printf("What closing time would you like? ");
    getline(cin, input);
    }while(!is_int(input));
    week[index].close_hour = input;
}

/*********************************************************************
 ** Function: Place order
 ** Description: Allows user to palce orders
 ** Parameters: Pizza must exist
 ** Pre-Conditions:
 ** Post-Conditions:
 *********************************************************************/
void Restaurant::place_order(){
   string nums; 
   order temp;
   stringstream ss;
   ss << num_orders+1;
   ss>> nums;
   temp.order_num = nums;
   menu.place_order(temp);
   this->num_orders++;
   orders[num_orders - 1] = temp;
}

/*********************************************************************
 ** Function: Verify week day
 ** Description: Checks if the week day exists
 ** Parameters: Week days
 ** Pre-Conditions:
 ** Post-Conditions:
 *********************************************************************/
int Restaurant::verify_week_day(string input){
    while(true){
        for(int i =0; i < this->num_days; i++){
            if(this->week[i].day == input)
                return i;
        }
        printf("That is not a valid day of the week! Please re-enter it! ");
        cin >> input;
    }
}

/*********************************************************************
 ** Function: Save data
 ** Description: Saves for the restaurant class
 ** Parameters:
 ** Pre-Conditions:
 ** Post-Conditions:
 *********************************************************************/
void Restaurant::save_data(){
    fstream f;
    f.open(REST_NAME, fstream::out);
    f << name << '\n' << phone << '\n' << address << '\n' << num_days << endl;
    for(int i =0; i < num_days; i++){
        f << week[i].day << ' ' << week[i].open_hour << ' ' <<  week[i].close_hour << endl;
    }
    f.close();

    f.open(ORD_NAME, fstream::out);
    for(int i = 0; i < num_orders; i++){
        f << orders[i].order_num << ' ' << orders[i].customer_first << ' ' << orders[i].customer_last << ' ' << orders[i].credit_card;
        f << ' ' << orders[i].address << ' ' << orders[i].phone << ' ' << orders[i].pizza << ' ' << orders[i].size;
        f << ' ' << orders[i].quantity;
        if(i !=  num_orders-1)
            f<< endl;
    }
    f.close();
    f.open(MENU_NAME, fstream::out);
    menu.save_data(f);
    f.close();
    
}
/*********************************************************************
 ** Function: get_employees
 ** Description: Pulls employee data from file into struct
 ** Parameters: Requires already open file object
 ** Pre-Conditions: Requires already open file object
 ** Post-Conditions: Fills already created employee array;
 *********************************************************************/
void Restaurant::get_employees(fstream &f) {
    for (int i = 0; i < num_employees; i++)
        f >> employees[i].id >> employees[i].first_name >> employees[i].last_name >> employees[i].password;
}
/*********************************************************************
 ** Function: View orders
 ** Description:
 ** Parameters:
 ** Pre-Conditions:
 ** Post-Conditions:
 *********************************************************************/
void Restaurant::view_orders(){
    for(int i =0; i < this->num_orders; i++){
        cout << orders[i].order_num << " " << orders[i].customer_first << " " << orders[i].customer_last << " ";
        cout << orders[i].credit_card << " " << orders[i].address << " " << orders[i].pizza << " " << orders[i].size;
        cout << " " << orders[i].quantity;
        putchar('\n');
    }    
}

void Restaurant::remove_orders(){
    string input ="";
    printf("What order NUMBER would you like to remove? ");
    getline(cin, input);
    for(int i = 0; i < this->num_orders; i++){
        if(orders[i].order_num == input){
            for(int j = i; j < this->num_orders; j++){
		        if(j+1 == this-> num_orders){
			        continue;
                    }
		        else
			        orders[j] = orders[j+1];
                }
	            // pizzas[this->num_pizzas-1] = NULL;
	        this->num_orders--;
        }
    }
}

void Restaurant::get_orders(fstream &f){
    for(int i =0; i < this-> num_orders; i++){
        f >> orders[i].order_num >> orders[i].customer_first >> orders[i].customer_last;
        f >> orders[i].credit_card >> orders[i].address >> orders[i].phone;
        f >> orders[i].pizza >> orders[i].size >> orders[i].quantity;
    }
}

void Restaurant::search_by_ingredients(){
    Menu results;
    results.create_array(100);

    string input = "";
    int num_ingredients_to_ei = 1;
    string * sort_ingredients;
    bool continue_searching = true;
    
    while(continue_searching){
        results.view_menu();
        printf("Would you like to include (I), exclude (E), display results/exit (Q) ");
        getline(cin, input);

        if(input == "e" || input == "E"){
            printf("How many ingredients would you like to exclude? ");
            getline(cin, input);
            num_ingredients_to_ei = get_int(input);
            sort_ingredients = new string[num_ingredients_to_ei];
            for(int i = 0; i < num_ingredients_to_ei; i++){
                printf("Ingredient: ");
                getline(cin, sort_ingredients[i]);
                for(int j = 0; j < sort_ingredients[i].length(); j++)
                    if(sort_ingredients[i][j]== ' ')
                        sort_ingredients[i][j] = '_';
            };

            menu.search_pizza_by_ingredients_to_exclude(results, sort_ingredients, num_ingredients_to_ei);
        }


        else if(input == "i" || input == "I"){
            printf("How many ingredients would you like to include?  ");
            
            getline(cin, input);
            num_ingredients_to_ei = get_int(input);
            sort_ingredients = new string[num_ingredients_to_ei];

            for(int i = 0; i < num_ingredients_to_ei; i++){
                printf("Ingredient: ");
                getline(cin, sort_ingredients[i]);
                for(int j = 0; j < sort_ingredients[i].length(); j++)
                    if(sort_ingredients[i][j]== ' ')
                        sort_ingredients[i][j] = '_';
            };

            menu.search_pizza_by_ingredients_to_include(results, sort_ingredients, num_ingredients_to_ei);
            delete [] sort_ingredients;
        
        }

        else if(input == "q" || input == "Q")
        continue_searching = false;

    }

    
    // menu.view_menu();
    results.view_menu();

    printf("Would you like to order off the results? Y/N ");
    getline(cin, input);
    if(input == "y" || input == "Y")
        this->place_order();
}

void Restaurant::add_item_to_menu(){
    menu.add_item_to_menu();

}

void Restaurant::remove_iterm_from_menu(){
    menu.remove_iterm_from_menu();
}