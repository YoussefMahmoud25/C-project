#include <stdio.h>
#include "../Server/server.h"

ST_accountsDB_t* User;
ST_accountsDB_t dataBase[255] =
{
        { 5000,RUNNING,"54863256745678956"},
        {35000.5,BLOCKED,"212369547234545671"},
        {7500.0,RUNNING,"56161593268471232"},
        {1000055.0,BLOCKED,"65987832439312361"},
        {45320.75,RUNNING,"253218646449321323"},
        {25000.0,BLOCKED,"6548237549865213549"},
        {23.05, RUNNING ,"9713128975745470126"},
        {150.25,  BLOCKED,"12345535341489562" },
        { 0.0, RUNNING,"689659879067545466"},
        { 275.5, BLOCKED,"322412569834765168"},
};
ST_transaction_t transactions[255] = { 0 };

EN_transState_t recieveTransactionData(ST_transaction_t* transData) {


    if (isValidAccount(transData, dataBase) == SERVER_OK) {
        if (isBlockedAccount(User) == RUNNING) {
            if (isAmountAvailable(transData, User) == SERVER_OK) 
            {
                saveTransaction(transData);
                printf("\nTransaction success:ENOUGH BALANCE!\n");
                return APPROVED;
            }
            else if (isAmountAvailable(transData, User) == LOW_BALANCE) {
                printf("\nTransaction failed:LOW BALANCE!");
                exit();
                return DECLINED_INSUFFECIENT_FUND;
            }
        }
        else if (isBlockedAccount(User) == BLOCKED)
        {
            
            return DECLINED_STOLEN_CARD;
        }
    }
    else {
        printf("\n%s", "Account is not Valid!");
        return FRAUD_CARD;
    }
}

EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence)
{

    for (uint32_t i = 0; i < 10; i++)
    {
        int x = strcmp(cardData->primaryAccountNumber, (accountRefrence + i)->primaryAccountNumber);
        if (x == 0) {

            printf("\nAccount is Valid!");
            User = (accountRefrence + i);
            return SERVER_OK;
        }
    }
    return ACCOUNT_NOT_FOUND;
}
EN_accountState_t isBlockedAccount(ST_accountsDB_t* accountRefrence) {
    if (accountRefrence->state == BLOCKED)
    {
        return BLOCKED;
    }
    else if (accountRefrence->state == RUNNING)
    {
        printf("\nRunning........");
        return RUNNING;
    }
}
EN_serverError_t isAmountAvailable(ST_transaction_t* termData, ST_accountsDB_t* accountRefrence)
{
    if (accountRefrence->balance < termData->terminalData.transAmount)
    {
        return LOW_BALANCE;
    }
    else
    {
        return SERVER_OK;
    }
}
uint8_t lastTransactionNum = 0;
EN_serverError_t saveTransaction(ST_transaction_t* transData) {
    
    transactions[lastTransactionNum].cardHolderData = transData->cardHolderData;
    transactions[lastTransactionNum].terminalData = transData->terminalData;
    transactions[lastTransactionNum].transactionSequenceNumber++;
    //editing the database
    User->balance -= transactions[lastTransactionNum].terminalData.transAmount;
    printf("\nyour transaction is done and your new balance is: %f", User->balance);
    //increment the index of last transaction to store the next transaction in a new place

    if (transactions[lastTransactionNum].transactionSequenceNumber == transData->transactionSequenceNumber) {
        lastTransactionNum++;
        return SERVER_OK;
    }
    else {
        return TRANSACTION_NOT_FOUND;
    }
}
void listSavedTransactions(void) {

        printf("\n#########################\n");
        printf("Transaction Sequence Number: %d\n", lastTransactionNum);
        printf("Transaction Date: %s\n", transactions[lastTransactionNum].terminalData.transactionDate);
        printf("Transaction Amount: %f\n", transactions[lastTransactionNum].terminalData.transAmount);
        printf("Transaction State: %d\n", dataBase[lastTransactionNum].state);
        printf("Terminal Max Amount: %.02f\n", transactions[lastTransactionNum].terminalData.maxTransAmount);
        printf("Cardholder Name: %s\n", transactions[lastTransactionNum].cardHolderData.cardHolderName);
        printf("PAN: %s\n", transactions[lastTransactionNum].cardHolderData.primaryAccountNumber);
        printf("Card Expiration Date: %s\n", transactions[lastTransactionNum].cardHolderData.cardExpirationDate);
        printf("#########################\n");
        lastTransactionNum++;

}
