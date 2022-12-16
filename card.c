#include <stdio.h>
#include <string.h>
#include "../Card/card.h"


EN_cardError_t getCardHolderName(ST_cardData_t* cardData) 
{
	// get the name as string of char
	printf("Enter your Name (BETWEEN 20 to 24 characters): ");
	char name[30]; 
	char ch = 0;
	int i=0;
	while (ch != '\n')
	{
		ch = getchar();
		name[i] = ch;
		i++;
	}
	name[i] = '\0';
	
	strcpy_s(cardData->cardHolderName, 30, name); //store the name in carddata
	
	//check for length requirnments

	int x = strlen(cardData->cardHolderName);
	if (cardData->cardHolderName == NULL || x > 24 || x < 20)
	{
		return WRONG_NAME;
	}
	return CARD_OK;
}
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {
	// get the date as string of char and store it in cardData
	printf("Enter your Card Expiry date:");
	gets(cardData->cardExpirationDate);
	
	// Count the 2 digits entered of month to check for the number of months
	uint8_t monthDigits = (cardData->cardExpirationDate[0] - '0') * 10 + (cardData->cardExpirationDate[1] - '0');
	uint8_t md = monthDigits;

	//check for length and format requirnments 
	int x = strlen(cardData->cardExpirationDate); 
	if (x < 5 || cardData->cardExpirationDate[2] != '/' || cardData->cardExpirationDate == NULL
		|| !(md > 0 && md <= 12))
	{
		return WRONG_EXP_DATE;
	}
	return CARD_OK;
}
EN_cardError_t getCardPAN(ST_cardData_t* cardData) 
{
	// get the Pan as string of char and store it in cardData
	printf("Enter your Card PAN: ");
	gets(cardData->primaryAccountNumber);
	
	//check for length requirnments
	int x = strlen(cardData->primaryAccountNumber);
	if (x > 19 || x < 16 || cardData->primaryAccountNumber == NULL)
	{
		return WRONG_PAN;
	}
	return CARD_OK;
}


/*******VOID TEST FUNCTIONS********/
// CHANGE THE RETURN VALUES (Wrong to be 2)  &   (ok to be 1)
void getCardHolderNameTest(void)
{
	ST_cardData_t cardData;
	int x = getCardHolderName(&cardData);
	switch (x) {
	case 1:
	{
		if (x = 1)
		{
			printf("\nActual Result: ok");
		}break;
	}
	case 2:

		if (x = 2);
		{
			printf("\nActual Result: error");

		}break;
	}
}
void getCardExpiryDateTest(void)
{
		ST_cardData_t cardData;
		int x = getCardExpiryDate(&cardData);	
		switch (x) {
		case 1:
		{
			if (x = 1)
			{
				printf("\nActual Result: ok");
			}break;
		}
		case 2:

			if (x = 2);
			{
				printf("\nActual Result: error");

			}break;
		}
}
void getCardPANTest(void)
{
	ST_cardData_t cardData;
	int x = getCardPAN(&cardData);
	switch (x) {
	case 1:
	{
		if (x = 1)
		{
			printf("\nActual Result: ok");
		}break;
	}
	case 2:

		if (x = 2);
		{
			printf("\nActual Result: error");

		}break;
	}
}

/************MAIN TO TEST VOID FUNCTIONS************/
/*
              // getCardHolderName
void main()
{
	printf("Tester Name : yousof mahmoud abdelrazak\n");
	printf("Function name : getCardHolderName\n");
	printf("Test Case 1:    *name is NULL*\n");
	getCardHolderNameTest();
	printf("\nTest Case 2:    *less than 20 characters*\n");
	getCardHolderNameTest();
	printf("\nTest Case 3:    *more than 24 chracters*\n");
	getCardHolderNameTest();
	printf("\nTest Case 4:    *20<characters<24*\n");
	getCardHolderNameTest();
}

			  // getCardExpiryDate
void main()
{
	printf("Tester Name : yousof mahmoud abdelrazak\n");
	printf("Function name : getCardExpiryDate\n");
	printf("Test Case 1:    *date is NULL*\n");
	getCardExpiryDateTest();
	printf("\nTest Case 2:    *less than 5 characters*\n");
	getCardExpiryDateTest();
	printf("\nTest Case 3:    *Wrong format*\n");
	getCardExpiryDateTest();
	printf("\nTest Case 4:    *Valid date*\n");
	getCardExpiryDateTest();
}

			  // getCardPan
void main()
{
	printf("Tester Name : yousof mahmoud abdelrazak\n");
	printf("Function name : getCardPan\n");
	printf("Test Case 1:    *pan is NULL*\n");
	getCardPANTest();
	printf("\nTest Case 2:    *less than 16 characters*\n");
	getCardPANTest();
	printf("\nTest Case 3:    *more than 19 chracters*\n");
	getCardPANTest();
	printf("\nTest Case 4:    *16<characters<19*\n");
	getCardPANTest();
}

void main()
{
	printf("Tester Name : yousof mahmoud abdelrazak\n");
	printf("Function name:\n");
	printf("Test Case 1: \n");
	Function nameTest();
	printf("\nTest Case 2:\n");
	Function nameTest();
	printf("\nTest Case 3:\n");
	Function nameTest();
	printf("\nTest Case 4:\n");
	Function nameest();
}


*/
