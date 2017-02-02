/* The header file for class EntryList.

   Written by: Li Liang
   Date: 09/29/2009

   Sources: None
*/
#ifndef ENTRY_LIST
#define ENTRY_LIST

#include "AddressEntry.h"
#include <iostream>
using namespace std;

const int NAME_COL_WIDTH = 30;
const int EMAIL_COL_WIDTH = 40;

class EntryList
{
public: 
	//constructors
	EntryList();
	EntryList(const char fileName[]);

	//destructor
	~EntryList();

	//accessor functions
	bool get(int index, AddressEntry& anEntry) const;
	bool searchEntry(const char name[], AddressEntry& match) const;
	int getSize() const;
	void printAll() const;
	void saveAddressBook(const char fileName[]) const;

	//mutator functions
	void addEntry(const AddressEntry& anEntry);

	void addAtBeginning(const AddressEntry& anEntry);
	void append(const AddressEntry& anEntry);
	void addSorted(const AddressEntry& anEntry);

	void loadAddressBook(const char fileName[]);
	
	
private:
	struct Node
	{
		AddressEntry	data;
		Node *			next;

		Node(const AddressEntry& aData)
		{
			char	email[MAX_CHAR];
			char 	name[MAX_CHAR];

			aData.getEmail (email);
			aData.getName(name);
			data.setEmail(email);
			data.setName(name);
			next = NULL;
		}
	};

	Node *	head;
	int		size;
};

#endif