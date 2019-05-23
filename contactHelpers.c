#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

// This source file needs to "know about" the SYSTEM string library functions.
// HINT: The library name is string.h.
//       #include the string.h header file on the next line:
#include <string.h>


// ----------------------------------------------------------
// Include your contactHelpers header file on the next line:
#include "contactHelpers.h"



// ----------------------------------------------------------
// define MAXCONTACTS for sizing contacts array (5):
#define MAXCONTACTS 5


//------------------------------------------------------
// Function Definitions
//------------------------------------------------------

// +-------------------------------------------------+
// | NOTE:  Copy/Paste your Assignment-2 Milestone-3 |
// |        function definitions below...            |
// +-------------------------------------------------+

// clearKeyboard
void clearKeyboard(void)
{
	while (getchar() != '\n'); // empty execution code block on purpose
}

// pause:
void pause(void)
{
	printf("(Press Enter to Continue)");
	clearKeyboard();
}

// getInt:
int getInt(void)
{
	char NL = 'x';
	int Value;

	do {
		scanf("%d%c", &Value, &NL);
		if (NL != '\n') {
			clearKeyboard();
			printf("*** INVALID INTEGER *** <Please enter an integer>: ");
		}
	} while (NL != '\n');
	return Value;
}

// getIntInRange:
int getIntInRange(int min, int max)
{
	int value = getInt();
	while (value < min || value > max) {
		printf("*** OUT OF RANGE *** <Enter a number between %d and %d>: ", min, max);
		value = getInt();
	}
	return value;
}

// yes:
int yes(void)
{
	char x = '\0';
	char answer;
	int number = 0;
	do {
		scanf("%c%c", &answer, &x);
		if (x != '\n') {
			clearKeyboard();
			number = 0;
			printf("*** INVALID ENTRY *** <Only (Y)es or (N)o are acceptable>: ");
		}
		else {
			switch (answer) {
			case 'y':
			case 'Y':
			case 'n':
			case 'N':
				number = 1;
				break;
			default:
				number = 0;
				printf("*** INVALID ENTRY *** <Only (Y)es or (N)o are acceptable>: ");
			}
		}
	} while (x != '\n' || number != 1);

	if (answer == 'y' || answer == 'Y') {
		return 1;
	}
	else {
		return 0;
	}
}

// menu:
int menu(void)
{
	int selection;

	printf("Contact Management System\n");
	printf("-------------------------\n");
	printf("1. Display contacts\n");
	printf("2. Add a contact\n");
	printf("3. Update a contact\n");
	printf("4. Delete a contact\n");
	printf("5. Search contacts by cell phone number\n");
	printf("6. Sort contacts by cell phone number\n");
	printf("0. Exit\n");
	printf("\n");
	printf("Select an option:> ");
	selection = getIntInRange(0, 6);


	return selection;
}

// contactManagerSystem:
void contactManagerSystem(void)
{

	int menu_selected;
	int exit_selected = 0;

	struct Contact contacts[MAXCONTACTS] =
	{ { { "Rick", {'\0'}, "Grimes" },
		{ 11, "Trailer Park", 0, "A7A 2J2", "King City" },
		{ "4161112222", "4162223333", "4163334444" } },
	  {
		 { "Maggie", "R.", "Greene" },
		 { 55, "Hightop House", 0, "A9A 3K3", "Bolton" },
		 { "9051112222", "9052223333", "9053334444" } },
	  {
		 { "Morgan", "A.", "Jones" },
		 { 77, "Cottage Lane", 0, "C7C 9Q9", "Peterborough" },
		 { "7051112222", "7052223333", "7053334444" } },
	  {
		 { "Sasha",{ '\0' }, "Williams" },
		 { 55, "Hightop House", 0, "A9A 3K3", "Bolton" },
		 { "9052223333", "9052223333", "9054445555" } },
	};



	do {

		menu_selected = menu();

		switch (menu_selected) {
		case 1:

			printf("\n");
			displayContacts(contacts, MAXCONTACTS);
			pause();
			printf("\n");
			break;

		case 2:
			printf("\n");
			addContact(contacts, MAXCONTACTS);
			printf("\n");
			pause();
			printf("\n");

			break;

		case 3:
			printf("\n");
			updateContact(contacts, MAXCONTACTS);
			printf("\n");
			pause();
			printf("\n");

			break;

		case 4:
			printf("\n");
			deleteContact(contacts, MAXCONTACTS);
			printf("\n");
			pause();
			printf("\n");

			break;

		case 5:
			printf("\n");
			searchContacts(contacts, MAXCONTACTS);
			printf("\n");
			pause();
			printf("\n");

			break;

		case 6:
			printf("\n");
			sortContacts(contacts, MAXCONTACTS);
			printf("\n");
			pause();
			printf("\n");

			break;

		case 0:
			printf("\n");
			printf("Exit the program? (Y)es/(N)o: ");
			if (yes() == 1) {
				exit_selected = 1;
			}
			printf("\n");
			break;
		default:
			break;
		}
	} while (exit_selected != 1);
	printf("Contact Management System: terminated\n");
}

// +-------------------------------------------------+
// | NOTE:  Copy/Paste your Assignment-2 Milestone-3 |
// |        empty function definitions below...      |
// +-------------------------------------------------+

// getTenDigitPhone:
void getTenDigitPhone(char telNum[])
{
	int i;
	int number;
	int needInput = 1;

	while (needInput == 1) {
		number = 0;
		scanf("%10s", telNum);
		clearKeyboard();

		// (String Length Function: validate entry of 10 characters)
		// Counting digital numbers which are in telNum array if counts are 10, that means all of the array members are digital numbers. 
		if (strlen(telNum) == 10) {
			for (i = 0; i < 10; i++) {
				if (telNum[i] >= '0' && telNum[i] <= '9') {
					number++;
				}
			}
			if (number == 10) {
				needInput = 0;
			}
			else {
				printf("Enter a 10-digit phone number: ");
			}
		}

		else {
			printf("Enter a 10-digit phone number: ");
		}
	}
}


// findContactIndex:
int findContactIndex(const struct Contact contact[], int size, const char cellNum[])
{
	int i, match_digit = -1;
	int result;
	for (i = 0; i < size; i++) {
		result = strcmp(contact[i].numbers.cell, cellNum);
		if (result == 0) {
			match_digit = i;
		}
	}
	return match_digit;
}

// displayContactHeader
void displayContactHeader(void)
{
	printf("+-----------------------------------------------------------------------------+\n");
	printf("|                              Contacts Listing                               |\n");
	printf("+-----------------------------------------------------------------------------+\n");
}

// displayContactFooter
void displayContactFooter(int Total_contacts)
{
	printf("+-----------------------------------------------------------------------------+\n");
	printf("Total contacts: %d\n\n", Total_contacts);
}

// displayContact:
void displayContact(const struct Contact* contact)
{
	if (strcmp(contact->name.middleInitial, "") == 0) {
		printf(" %s %s\n", contact->name.firstName, contact->name.lastName);
	}
	else {
		printf(" %s %s %s\n", contact->name.firstName, contact->name.middleInitial, contact->name.lastName);
	}

	printf("    C: %-10s   H: %-10s   B: %-10s\n", contact->numbers.cell, contact->numbers.home, contact->numbers.business);

	if (contact->address.apartmentNumber > 0) {
		printf("       %d %s, Apt# %d, %s, %s\n", contact->address.streetNumber, contact->address.street, contact->address.apartmentNumber, contact->address.city, contact->address.postalCode);
	}
	else {
		printf("       %d %s, %s, %s\n", contact->address.streetNumber, contact->address.street, contact->address.city, contact->address.postalCode);
	}
}


// displayContacts:
void displayContacts(const struct Contact contact[], int size)
{
	int i;
	int total_contacts = 0;

	displayContactHeader();

	for (i = 0; i < size; i++) {
		if (strlen(contact[i].numbers.cell) > 0) {
			displayContact(&contact[i]);
			total_contacts++;
		}
	}
	displayContactFooter(total_contacts);
}



// searchContacts:
void searchContacts(const struct Contact contact[], int size)
{
	char cellNum[11];
	int matched_Index = 0;

	printf("Enter the cell number for the contact: ");

	getTenDigitPhone(cellNum);

	matched_Index = findContactIndex(contact, size, cellNum);

	if (matched_Index == -1) {
		printf("*** Contact NOT FOUND ***\n");
	}
	else {
		printf("\n");
		displayContact(&contact[matched_Index]);
	}
}


// addContact:
void addContact(struct Contact contact[], int size)
{
	int i, available = -1;
	for (i = 0; i < size; i++) {
		if (strlen(contact[i].numbers.cell) == 0) {
			available = i;
		}
	}
	if (available > -1) {
		getContact(&contact[available]);
		printf("--- New contact added! ---\n");
	}
	else {
		printf("*** ERROR: The contact list is full! ***\n");
	}
}


// updateContact:
void updateContact(struct Contact contact[], int size)
{
	char input_Number[11];
	int founded_number_index;
	printf("Enter the cell number for the contact: ");
	getTenDigitPhone(input_Number);
	founded_number_index = findContactIndex(contact, size, input_Number);

	if (founded_number_index >= 0) {
		printf("\nContact found:\n");
		displayContact(&contact[founded_number_index]);

		printf("\nDo you want to update the name? (y or n): ");
		if (yes() == 1)
			getName(&contact[founded_number_index].name);

		printf("Do you want to update the address? (y or n): ");
		if (yes() == 1)
			getAddress(&contact[founded_number_index].address);

		printf("Do you want to update the numbers? (y or n): ");
		if (yes() == 1)
			getNumbers(&contact[founded_number_index].numbers);

		printf("--- Contact Updated! ---\n");
	}
	else {
		printf("*** Contact NOT FOUND ***\n");
	}
}


// deleteContact:
void deleteContact(struct Contact contact[], int size)
{
	char input_Number[11];
	int founded_number_index;
	printf("Enter the cell number for the contact: ");
	getTenDigitPhone(input_Number);
	founded_number_index = findContactIndex(contact, size, input_Number);

	if (founded_number_index >= 0) {
		printf("\nContact found:\n");
		displayContact(&contact[founded_number_index]);
		printf("\nCONFIRM: Delete this contact? (y or n): ");
		if (yes() == 1) {
			contact[founded_number_index].numbers.cell[0] = '\0';
			printf("--- Contact deleted! ---\n");
		}
	}
	else
		printf("*** Contact NOT FOUND ***\n");
}



// sortContacts:
// For sorting Contacts list, I make temperary_sturcture. I extract structure from original structures. and then comparing temperary sturctures.
// To do these, I used two for fuctions and strcmp fuction.
// Comparing criteria is that lowest to highest by cell number.
void sortContacts(struct Contact contact[], int size)
{
	int i, j, tot = 0;
	struct Contact temp_structure;

	for (i = 0; i < size; i++) {
		if (strlen(contact[i].numbers.cell) > 0) {
			tot++;
		}
	}

	for (i = 0; i < tot - 1; i++) {
		for (j = i; j < tot; j++) {
			if (strcmp(contact[i].numbers.cell, contact[j].numbers.cell) > 0) {
				temp_structure = contact[i];
				contact[i] = contact[j];
				contact[j] = temp_structure;
			}
		}
	}
	printf("--- Contacts sorted! ---\n");
}
