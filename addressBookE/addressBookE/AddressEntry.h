/* The header file for class AddressEntry.

   Written by: Li Liang
   Date: 09/29/2009

   Sources: None
*/

#ifndef ADDRESS_ENTRY
#define ADDRESS_ENTRY

const int MAX_CHAR = 101;

class AddressEntry
{
public: 
	//constructors
	AddressEntry();
	AddressEntry(const char name[], const char email[]);

	//destructor
	~AddressEntry();

	//accessor functions
	void getName(char name[]) const;
	void getEmail(char email[]) const;
	void print() const;

	//mutator functions
	void setName(const char name[]);
	void setEmail(const char email[]);

private:
	char*	name;
	char*	email;
}; //don't forget this ';'

#endif