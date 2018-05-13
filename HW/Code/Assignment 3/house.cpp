#include "house.hpp"

using namespace std;

House::House(){
	this->value = ((rand()%500)+100)*100;
	this->type = HOUSE;
	Tenant t(PERSON);
	this->num_tenants = 1;
	this->t.set_budget((rand()%500) + 100);
}


House::~House(){
}


Tenant& House::get_tenant(int index){
	return t;
}


void House::remove_tenant(int index){
	t.set_rent(0);

	this->num_tenants = 0;
	this->t.set_name("No tenant");
}