/* This program continues to demonstrate how to program a linked list.

   Written by: Li Liang
   Date: 09/29/2009

   Sources: None
*/

//memory leak detection tool headers
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>                 
#include <cctype>

#include "AddressEntry.h"
#include "EntryList.h"
#include "InputTools.h"

using namespace std;     

//user-interface related functions
void displayMenu();
char readInCommand();
void processCommand(char command, EntryList& list);
void readInEntry(AddressEntry& anEntry);
void readInName(char name[]);

int main ()
{
	//enable memory leak detection tools
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	char			command;
	char			fileName[] = "addressBook.txt";
	EntryList		list(fileName);

	displayMenu();
	command = readInCommand();
	while (command != 'q')
	{
		processCommand(command, list);
		displayMenu();
		command = readInCommand();
	}

	list.saveAddressBook(fileName);	
    
    return 0;
}

/* This function displays the main menu. */
void displayMenu()
{
	cout << endl << "Welcome to Easy Addressbook!" << endl << endl;
	cout << "\ta: add an entry" << endl
		<< "\tl: list all the entries" << endl
		<< "\ts: search address by name" << endl
		<< "\tq: exit this program" << endl << endl;
}

/* This function reads in user's command.
   return: the command in lower case
*/
char readInCommand()
{
	char	cmd;

	cmd = readChar("Please enter the command (a,l,s or q): ");

	return tolower(cmd);
}

/* This function processes the command passed in.
   in: command
   in/out: list and listSize
*/
void processCommand(char command, EntryList& list)
{
	AddressEntry	entry;
	char			name[MAX_CHAR];
	char			email[MAX_CHAR];

	switch (command)
	{
	case 'a': readInEntry(entry);
		      list.addEntry(entry);
			break;

	case 'l': list.printAll();
			break;

	case 's': readInName(name);
			  if(list.searchEntry(name, entry))
			  {
				  entry.getEmail(email);
				  cout << endl << "The email address for " << name << ": " << email << endl;
			  }
			  else
				  cout << endl << "The email address for " << name << " doesn't exist." << endl;
			break;

	default: cout << endl << "Illegal Command!" << endl;
			break;
	}
}
	
/* This function reads in an address entry.
   out: anEntry
*/
void readInEntry(AddressEntry& anEntry)
{
	char	name[MAX_CHAR];
	char	email[MAX_CHAR];

	//read in name and email
	readString("Please enter the name: ", name, MAX_CHAR);
	readString("Please enter the email: ", email, MAX_CHAR);

	//populate the passed in object
	anEntry.setName(name);
	anEntry.setEmail(email);
}

/* This function reads in name.
   out: name
*/
void readInName(char name[])
{
	readString("Please enter the name you want to search: ", name, MAX_CHAR);
}

