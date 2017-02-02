/* The implementation file for class AddressEntry.

   Written by: Li Liang
   Date: 09/29/2009

   Sources: None
*/

#include "AddressEntry.h"
#include <iostream>
using namespace std;

/* Default constructor. It initializes the name and email to a default value.
*/
AddressEntry::AddressEntry()
{
	name = new char[strlen("no name")+1];
	strcpy(name, "no name");
	email = new char[strlen("no email")+1];
	strcpy(email, "no email");
}

/* Constructor. It initializes the name and email with the passed in value.
   in: name and email
*/
AddressEntry::AddressEntry(const char name[], const char email[])
{
	this->name = new char[strlen(name)+1];
	strcpy(this->name, name);	//this->name refers to the instance variable "name"
	this->email = new char[strlen(email)+1];
	strcpy(this->email, email); //this->email refers to the instance variable "email"
}

/* Destructor. It releases the dynamic char array allocated for name and email.
*/
AddressEntry::~AddressEntry()
{
	if(name != NULL)
		delete [] name;
	if(email != NULL)
		delete [] email;
}

/* This function returns the name of the entry through the parameter.
   out: name
*/
void AddressEntry::getName(char name[]) const
{
	strcpy(name, this->name);
}

/* This functions returns the email of the entry through the parameter.
   out: email
*/
void AddressEntry::getEmail(char email[]) const
{
	strcpy(email, this->email);
}

/* This function prints the state of the object to stdout.
*/
void AddressEntry::print() const
{
	cout << name << " -> " << email << endl;
}

/* This function sets the name to the passed in value.
   in: name
*/
void AddressEntry::setName(const char name[])
{
	if(this->name != NULL)
		delete [] this->name;
	this->name = new char[strlen(name)+1];
	strcpy(this->name, name);
}

/* This function sets the email to the passed in value.
   in: email
*/
void AddressEntry::setEmail(const char email[])
{
	if(this->email != NULL)
		delete [] this->email;
	this->email = new char[strlen(email)+1];
	strcpy(this->email, email);
}
