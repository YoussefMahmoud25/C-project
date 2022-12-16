#include <stdio.h>
#include "../Card/card.h"
#include "../terminal/terminal.h"
#include "../server/server.h"

float maxAmount;
void appStart(void) 
{
	ST_cardData_t customer1 = { "","","" };
	ST_terminalData_t terminal1 = { 0,0,"" };
	uint8_t flag = 1;
	while (flag){
	printf("                  ............NEW PROCESS............                  \n");
	while (flag)
		{
			if (getCardHolderName(&customer1) == WRONG_NAME) printf("Please re-enter your name\n");
			else {
				printf("SUCCESS!\n");
				break;
			}
		}

	while (flag) 
	{
			if (getCardExpiryDate(&customer1) == WRONG_EXP_DATE) printf("Please re-enter the date in a right formula\n");
			else {
				printf("SUCCESS!\n");
				break;
			}
		}



		while (flag) {
			if (getCardPAN(&customer1) == WRONG_PAN) printf("Please enter a valid PAN\n");
			else {
				printf("SUCCESS!\n");
				break;
			}

		}
		while (flag) {
			if (getTransactionDate(&terminal1) == WRONG_DATE) printf("Please re-enter a valid date\n");
			else {
				printf("SUCCESS!\n");
				break;
			}

		}
		
		if (isCardExpired(&customer1, &terminal1) == TERMINAL_OK) {
			if (getTransactionAmount(&terminal1) == TERMINAL_OK) {
				if (setMaxAmount(&terminal1, maxAmount) == TERMINAL_OK) {
					if (isBelowMaxAmount(&terminal1) == TERMINAL_OK) {
						printf("Valid amount less than the maximum!");
					}
					else if (isBelowMaxAmount(&terminal1) == EXCEED_MAX_AMOUNT) {
						printf("Transaction failed! you have exceeded the max amount");
						exit();
					}
				}
				else if (setMaxAmount(&terminal1, maxAmount) == INVALID_MAX_AMOUNT) {
					printf("please enter a valid max amount");
				}
			}
			else if (getTransactionAmount(&terminal1) == INVALID_AMOUNT) {
				printf("please enter a valid amount");
			}

		}
		else if (isCardExpired(&customer1, &terminal1) == EXPIRED_CARD) {
			printf("EXPIRED CARD!");
			exit();
		}

		//creating the transaction
		ST_transaction_t transaction = { customer1,terminal1,APPROVED };
		recieveTransactionData(&transaction);

		listSavedTransactions();
}}