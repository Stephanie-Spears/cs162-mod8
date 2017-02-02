/* The implementation file for class EntryList.

   Written by: Li Liang
   Date: 09/29/2009

   Sources: None
*/

#include "EntryList.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

/* Default constructor. It initializes the list to be empty.
*/
EntryList::EntryList()
{
	head = NULL;
	size = 0;
}

/* A constructor that initializes the list with data on the passed in file.
   in: fileName
*/
EntryList::EntryList(const char fileName[])
{
	head = NULL;
	size = 0;
	loadAddressBook(fileName);
}

/* Destructor. It releases the memory allocated for the linked list.
*/
EntryList::~EntryList()
{
	Node * curr = head;

	while(head != NULL)
	{
		curr = head->next;

		//delete the node pointed to by head. 
		//the destructor for the AddressEntry is invoked automatically
		delete head;	

		head = curr;
	}
}

/* This function reads the entries from the file and adds them to the list.
   in: fileName
*/
void EntryList::loadAddressBook(const char fileName[])
{
	ifstream		in;
	char			name[MAX_CHAR];
	char			email[MAX_CHAR];
	AddressEntry	anEntry;

	in.open (fileName);
	if(!in)
	{
		in.clear();
		cerr << endl << "Fail to open " << fileName << " for input!" << endl << endl;
		exit(1);
	}

	in.get(name, MAX_CHAR, ';');
	while (!in.eof())
	{
		in.get();							//remove field seperator ';'			
		in.get(email, MAX_CHAR, '\n');
		in.ignore(100, '\n');				//remove record seperator '\n'

		anEntry.setName(name);
		anEntry.setEmail(email);

		addEntry(anEntry);

		in.get(name, MAX_CHAR, ';');		//start the next record
	}
	in.close();
}

/* This function returns the size of the list.
   return: size
*/
int EntryList::getSize() const
{
	return size;
}

/* This function returns the AddressEntry object at the specified position through parameter
   in: index
   out: anEntry
   return: true if the entry exist, false if illegal index is passed in
*/
bool EntryList::get(int index, AddressEntry &anEntry) const
{
	char	name[MAX_CHAR];
	char	email[MAX_CHAR];

	if(index<0 || index>=size)
		return false;

	//traverse to the position
	int		i;
	Node *	curr = head;
	for(i=0; i<index; i++)
	{	
		curr = curr->next;
	}

	curr->data.getEmail(email);
	curr->data.getName(name);
	anEntry.setEmail (email);
	anEntry.setName(name);	
	return true;
}

/* This function searches the list for an entry with passed in name. 
   in: name
   out: match
   return: true if a match is found and match will be returned through parameter.
           false if a match can not be found and match contains garbage.
*/
bool EntryList::searchEntry(const char name[], AddressEntry &match) const
{
	Node *	curr;
	char	currentName[MAX_CHAR];
	char	currentEmail[MAX_CHAR];	

	for(curr=head; curr!=NULL; curr = curr->next)
	{
		curr->data.getName (currentName);
		curr->data.getEmail(currentEmail);
		if(strcmp(name, currentName) == 0)
		{
			match.setName(currentName);
			match.setEmail(currentEmail);
			break;
		}
	}
	if (!curr)
		return false;
	else
		return true;
}

/* This function prints all the entries to the standard output.
*/
void EntryList::printAll() const
{
	Node *	curr;
	char	name[MAX_CHAR];
	char	email[MAX_CHAR];

	cout << setw(NAME_COL_WIDTH) << "Name" << setw(EMAIL_COL_WIDTH) << "Email" << endl;
	for(curr=head; curr; curr=curr->next)
	{
		curr->data.getName(name);
		curr->data.getEmail (email);
		cout << setw(NAME_COL_WIDTH) << name << setw(EMAIL_COL_WIDTH) << email << endl;
	}
}

/* This function saves the list to the external file.
   in: fileName
*/
void EntryList::saveAddressBook(const char fileName[]) const
{
	ofstream		out;
	Node*			curr;
	char			name[MAX_CHAR];
	char			email[MAX_CHAR];

	out.open (fileName);
	if(!out)
	{
		out.clear();
		cerr << endl << "Fail to open " << fileName << " for output!" << endl << endl;
		exit(1);
	}

	for(curr=head; curr; curr=curr->next)
	{
		curr->data.getName(name);
		curr->data.getEmail(email);
		out << name << ';' << email << endl;
	}

	out.close();
}

/* This function adds a passed in entry to the list.
   in: anEntry
*/
void EntryList::addEntry(const AddressEntry &anEntry)
{
	addSorted(anEntry);
}

/* This function adds a passed in entry to the beginning of the list.
   in: anEntry
*/
void EntryList::addAtBeginning(const AddressEntry &anEntry)
{
	//create a new node to hold the data
	Node * newNode = new Node(anEntry);

	//insert the node at the beginning of the list
	newNode->next = head;
	head = newNode;

	size++;
}

/* This function appends a passed in entry to the end of the list.
   in: anEntry
*/
void EntryList::append(const AddressEntry &anEntry)
{
	//create a new node to hold the data
	Node * newNode = new Node(anEntry);

	//empty list?	
	if(!head)
		head = newNode;
	else
	{
		Node * curr = head;

		//traverse to the last node of the list
		while(curr->next)//note this is not while(curr)
		{
			curr = curr->next;
		}

		//link the newNode to the last node
		curr->next = newNode;
	}

	size++;
}

/* This function inserts a passed in entry at the right position 
   so that the list is sorted by name.
   in: anEntry
*/
void EntryList::addSorted(const AddressEntry &anEntry)
{
	char	name[MAX_CHAR];
	char	currName[MAX_CHAR];

	anEntry.getName (name);

	//create a new node to hold the data
	Node * newNode = new Node(anEntry);

	//if you prefer one line declaration: Node *prev, *curr;
	Node * prev = NULL;
	Node * curr = head;

	//traverse to find the position to insert
	while(curr)
	{
		curr->data.getName(currName);
		if(strcmp(name, currName) < 0)
			break;
		
		prev = curr;
		curr = curr->next;
	}

	//insert the newNode
	newNode->next = curr;

	//need to insert at the beginning
	if(!prev)
		head = newNode;
	else
		prev->next = newNode;

	size++;
}

