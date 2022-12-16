#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Terminal/terminal.h"
#include "../Card/card.h"


EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
    // get the transaction date as string of char and store it in termData
    printf("Enter your Transaction date:");
    gets(termData->transactionDate);

    // Count the 2 digits entered of day and month to check for the number of days amd months
    uint8_t dayDigits = (termData->transactionDate[0] - '0') * 10 + (termData->transactionDate[1] - '0');
    uint8_t monthDigits = (termData->transactionDate[3] - '0') * 10 + (termData->transactionDate[4] - '0');
    uint8_t dd = dayDigits;
    uint8_t md = monthDigits;

    //check for length and format requirnments
    int x = strlen(termData->transactionDate);
    if (x < 10 || termData->transactionDate == NULL || termData->transactionDate[2] != '/' ||
        termData->transactionDate[5] != '/' || !(md >= 1 && md <= 12) || !(dd >= 1 && dd <= 31))
    {
        return WRONG_DATE;
    }
    return TERMINAL_OK;
}
EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t*  termData) 
{
    // Count the 2 digits entered of card month to get the number of months 
    uint32_t cardMonths = (cardData->cardExpirationDate[0] - '0') * 10 + cardData->cardExpirationDate[1] - '0';

    // Count the 2 digits entered of card month to get the number of months
    uint32_t transactionMonths = (termData->transactionDate[3] - '0') * 10 + termData->transactionDate[4] - '0';
    
    // Count the 2 digits entered of card year to get the number of year and add 2000 to be 4 digits to match the transaction year digits number
    uint32_t cardYear = (cardData->cardExpirationDate[3] - '0') * 10 + cardData->cardExpirationDate[4] - '0' + 2000;
   
    // Count the 4 digits entered of card year to get the number of year
    uint32_t transactionYear = (termData->transactionDate[6] - '0') * 1000 + (termData->transactionDate[7] - '0') * 100 + (termData->transactionDate[8] - '0') * 10 + (termData->transactionDate[9] - '0');

    //check for card date validity
    if (transactionYear > cardYear|| transactionYear == cardYear && transactionMonths > cardMonths)
    {
        return EXPIRED_CARD;
    }
    return TERMINAL_OK;
}
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
    // get the transaction amount as a float numbers and store it in termData
    printf("Enter your Transaction amount: ");
    scanf_s("%f", &termData->transAmount);

    // check for Amount requirnments
    if (termData->transAmount <= 0)
    {
        return INVALID_AMOUNT;
    }
    return TERMINAL_OK;
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {
    // comparing the transaction amount with the terminal max allowed amount
    if (termData->transAmount > termData->maxTransAmount)
    {
        return EXCEED_MAX_AMOUNT;
    }
    return TERMINAL_OK;
}
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData) {
    // get the Max amount as a float numbers and store it in termData
    printf("Enter your Max amount:");
    scanf_s("%f", &termData->maxTransAmount);

    //check for Max Amount requirnments
    if (termData->maxTransAmount <= 0)
    {
        return INVALID_MAX_AMOUNT;
    }
    return TERMINAL_OK;
}


/*******VOID TEST FUNCTIONS********/
// CHANGE THE RETURN VALUES (Wrong to be 2)  &   (ok to be 1)
void getTransactionDateTest(void)
{
    ST_cardData_t cardData;
    int x = getTransactionDate(&cardData);
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
void isCardExpiredTest(void)
{
    ST_cardData_t cardData;
    ST_terminalData_t  termData;
    getCardExpiryDate(&cardData);
    getTransactionDate(&termData);
    int x = isCardExpired(&cardData, &termData);
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
void getTransactionAmountTest(void)
{
    ST_terminalData_t termData;
    int x = getTransactionAmount(&termData);
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
void isBelowMaxAmountTest(void)
{

    ST_terminalData_t  termData;

    getTransactionAmount(&termData);
    setMaxAmount(&termData);
    int x = isBelowMaxAmount(&termData);
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
void setMaxAmountTest(void)
{
    ST_terminalData_t termData;
    int x = setMaxAmount(&termData);
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
                // getTransactionDate
void main()
{
    printf("Tester Name : yousof mahmoud abdelrazak\n");
    printf("Function name: getTransactionDate\n");
    printf("Test Case 1: *transaction date is NULL*\n");
    isCardExpiredTest();
    printf("\nTest Case 2: *less than 10 characters*\n");
    isCardExpiredTest();
    printf("\nTest Case 3: *wrong format*\n");
    getTransactionDateTest();
    printf("\nTest Case 4: *valid transaction date*\n");
    getTransactionDateTest();
}
               // isCardExpired
void main()
{
	printf("Tester Name : yousof mahmoud abdelrazak\n");
	printf("Function name: isCardExpired\n");
	printf("Test Case 1: *card expired*\n");
	isCardExpiredTest();
	printf("\nTest Case 2: *valid card*\n");
	isCardExpiredTest();
	
}          // getTransactionAmount
void main()
{
    printf("Tester Name : yousof mahmoud abdelrazak\n");
    printf("Function name: getTransactionAmount\n");
    printf("Test Case 1: *amount less than 0*\n");
    getTransactionAmountTest();
    printf("\nTest Case 2: *amount equal 0*\n");
    getTransactionAmountTest();
    printf("\nTest Case 3: *valid transaction amount*\n");
    getTransactionAmountTest();

}
               // setMaxAmount
void main()
{
    printf("Tester Name : yousof mahmoud abdelrazak\n");
    printf("Function name: setMaxAmountt\n");
    printf("Test Case 1: *amount less than 0*\n");
    setMaxAmountTest();
    printf("\nTest Case 2: *amount equal 0*\n");
    setMaxAmountTest();
    printf("\nTest Case 3: *valid max amount*\n");
    setMaxAmountTest();

}
                // isBelowMaxAmount
void main()
{
    printf("Tester Name : yousof mahmoud abdelrazak\n");
    printf("Function name: isBelowMaxAmount\n");
    printf("Test Case 1: *amount larger than the terminal max allowed amount*\n");
    isBelowMaxAmountTest();
    printf("\nTest Case 2: *amount is valid*\n");
    isBelowMaxAmountTest();
}

*/