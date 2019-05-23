#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

// +-------------------------------------------------+
// | NOTE:  Include additional header files...       |
// +-------------------------------------------------+
#include "contacts.h"
#include "contactHelpers.h"
#include <string.h>


// +-------------------------------------------------+
// | NOTE:  Copy/Paste your Assignment-2 Milestone-3 |
// |        source code below...                     |
// +-------------------------------------------------+

// getName:
void getName(struct Name *name) {
	int Prompts;

	printf("Please enter the contact's first name: ");
	scanf("%30[^\n]s", name->firstName);
	clearKeyboard();

	printf("Do you want to enter a middle initial(s)? (y or n): ");
	Prompts = yes();


	if (Prompts == 1) {
		printf("Please enter the contact's middle initial(s): ");
		scanf("%6[^\n]s", name->middleInitial);
		clearKeyboard();
	}
	else {
		name->middleInitial[0] = '\0';
	}

	printf("Please enter the contact's last name: ");
	scanf("%35[^\n]s", name->lastName);
	clearKeyboard();
}

// getAddress:
void getAddress(struct Address *address) {
	int Prompts2;

	printf("Please enter the contact's street number: ");
	address->streetNumber = getInt();


	if (address->streetNumber < 0) // determining value is negetive number or not. If value is negative number, input number again. 
	{

		printf("Please enter the contact's street number: ");
		address->streetNumber = getInt();

	}


	printf("Please enter the contact's street name: ");
	scanf("%40[^\n]s", address->street);
	clearKeyboard();

	printf("Do you want to enter an apartment number? (y or n): ");
	Prompts2 = yes();


	if (Prompts2 == 1) {
		printf("Please enter the contact's apartment number: ");
		address->apartmentNumber = getInt();

		if (address->apartmentNumber < 0) // determining value is negetive number or not. If value is negative number, input number again. 
		{
			printf("Please enter the contact's apartment number: ");
			address->apartmentNumber = getInt();
		}

	}

	printf("Please enter the contact's postal code: ");
	scanf("%7[^\n]s", address->postalCode);
	clearKeyboard();

	printf("Please enter the contact's city: ");
	scanf("%40[^\n]s", address->city);
	clearKeyboard();

}
// getNumbers:
void getNumbers(struct Numbers *numbers)
{

	int Prompts3, Prompts4;

	printf("Please enter the contact's cell phone number: ");
	getTenDigitPhone(numbers->cell);

	printf("Do you want to enter a home phone number? (y or n): ");
	Prompts3 = yes();


	if (Prompts3 == 1) {
		printf("Please enter the contact's home phone number: ");
		getTenDigitPhone(numbers->home);
	}
	else {
		numbers->home[0] = '\0';
	}
	printf("Do you want to enter a business phone number? (y or n): ");
	Prompts4 = yes();

	if (Prompts4 == 1) {
		printf("Please enter the contact's business phone number: ");
		getTenDigitPhone(numbers->business);
	}
	else {
		numbers->business[0] = '\0';

	}
}
// getContact:
void getContact(struct Contact *contact)
{
	getName(&contact->name);
	getAddress(&contact->address);
	getNumbers(&contact->numbers);
}
