#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Struct - this is the struct of the information
* that an account have. It collects the information of
* the customer in the bank.
*
*/
struct
{
    char accountNumber[20];
    char pinCode[20];
    int balance;
    char name[20];
    char sex[10];
}information[1000];

/*int createCounter - It is used to show that which one
* is empty. And it is also used to create a new account.
*
*
* int presentCounter - It is used to indicate which
* account number is being operated on.
*/
int createCounter, presentCounter;
int Counter();
void clearBuffer(void);
void welcomePage();
void thanksPage();
void valueStruct();
void askBankAccount();
void accountYes();
void accountNo();
void createAccount();
void checkPin();
void updateFile(int studentCounter);
void introduce();
void function();
void balance(int *o);
void transfer(int *t, int *o, int m2);
void withdraw(int *w, int *o);
void deposit(int *d, int *o);
void changePin();
void backPage();

/* main - 1--Welcome the user to use it.
* 2--Ask the user whether he has the BankAccount.
* 3--Introduce the user he has Logged in successfully.
* 4--Operate the function.
* 5--Thanks to the user for using it.
* 6--Write the data which have updated back to the FILE.
*
*/
int main (void)
{
    welcomePage();
    askBankAccount();
    introduce();
    function();
    thanksPage();
    updateFile(Counter());
    return (0);
}

/* clearBuffer - makes the computer clear something
* useless. Something like wrong input from the user and
* something like invalid input. It can reduce the possibility
* of the incidents of the ERROR.
*
*/
void clearBuffer(void)
{
   while (fgetc(stdin) != '\n');
}

/* Counter - tells the computer how many accounts should
* be written back to the File. It is a (int) function. The
* function returns the result of the count++.
*
* Parameters(written in the detailed function):
* (int count && char copyString[20]
* - int: count++ in the internal function.
* - char: used to tell when is the computer should stop
*         writing the data back to the File.
*         It just like a mark. I used "*" in my function.
*
*  Return value (int): the number is the result of count++.
*
*/
int Counter()
{
    int count = 0;
    char copyString[20] = {'*'};

    strcpy(information[createCounter + 1].accountNumber, copyString);
    while ((strcmp(information[count].accountNumber, information[createCounter + 1].accountNumber) != 0) && count != 1000)
    {
        count++;
    }

    return count;
}

/* welcomePage - The function displays the given sentence
* which is used to welcome person to use it on screen.
* It is a (void) function.
*
*/
void welcomePage()
{
    printf("Welcome to choose our bank!\n\n");
}

/* thanksPage - The function displays the given sentence
* which is used to thanks the person to use it. It is a
* (void) function.
*
*/
void thanksPage()
{
    printf("\nThanks for your Using!\n");
}

/* valueStruct - The function tells the route of the File
* which I need to use during the operation. It gives the
* values(data) to the Struct which is created by my own.
* It is a (void) function.
*
* Parameters(written in the detailed function):
* int i - It plays a role to count the lines in the File.
* int count - It is used to tell the computer when should
* it stopped to give the values to the Struct.
* FILE *fp - It used to show the computer which FILE should
* be opened to use.
*
*/
void valueStruct()
{
    int i = 0, count;
    FILE *fp;

    if (!(fp = fopen("tests.txt","r")))
    {
        fp = fopen("tests.txt","r");
    }

    while(count != EOF)
    {
        count = fscanf(fp, "%s %s %d %s %s", information[i].accountNumber, information[i].pinCode,
                                             &(information[i].balance), information[i].name, information[i].sex);
        i++;
    }
    createCounter = i - 1;
    fclose(fp);
}

/* askBankAccount - ask the user whether he or she has an
* Bank Account in our system. If user enter "Yes", he will
* be taken into the function "accountYes". While, he will
* enter into the function "accountNo". This function will
* just allow user enter "1" && "2". If he entered something
* useless. The function will let him try again till he entered
* the valid input.
*
* Parameters(written in the detailed function):
* int choice1 - asks the user to enter his answer and deposit it.
* char character1 and int status - used in the readInteger.
*
*/
void askBankAccount()
{
    int choice1;
    char character1;
    int status1;


    printf("\nDo you have an account of our bank?\n\n");
    printf("1.Yes\t2.No > ");

    do
    {
        while ((status1 = scanf("%d%c", &choice1, &character1)) == 0 || (2 == status1 && character1 != '\n')) {
        clearBuffer();
        printf("\nYou did not enter an integer, try again > ");
        }

        switch (choice1)
        {
            default:
                {
                    printf("\nERROR! Please enter valid number. > ");
                }break;

            case 1:
                {
                    accountYes();
                    if (createCounter != 0)
                    {
                        checkPin();
                        break;
                    }
                }

            case 2:
                {
                    accountNo();
                }break;
        }
    }while(choice1 != 1 && choice1 != 2);
}

/* accountYes - It will make the user to enter his account number.
* And then, the computer will search the struct whether the input does exist.
* If there is no data in the struct when you first use it, the program will tell
* you that you should create an account first. But if you have already use it,
* you do not need to do it. What's more, if your input dose not exist. It will ask
* you whether you want to create right now.
*
* Parameters(written in the detailed function)
* int kSearching - it is used to represent its operating number.
* int kTemp - it is used to get the number from kSearching.
* int choice2, status and char character - they are used in readInteger
* and readString.
* char bankAccount[20] - It used to deposit your input.
*
*/
void accountYes()
{
    int kSearching = 0, kTemp = 0, choice2, status;
    char bankAccount[20], character;

    valueStruct();

    if (createCounter == 0)
    {
        printf("\nThere are no Accounts in the system!\n");
        printf("You should create an Account in the system first.\n");
    }

    if (createCounter != 0)
    {
        printf("\nPlease enter your Bank Account > ");
        fgets(bankAccount, 20, stdin);

        if (bankAccount[strlen(bankAccount)-1] == '\n')
            bankAccount[strlen(bankAccount)-1] = '\0';
        else
            clearBuffer();

        printf("\nWe are searching for you.\n\nPlease wait a minute ^_^ . . .\n");

        for(kSearching = 0; kSearching < 1000; kSearching++)
        {

            if (strcmp(bankAccount, information[kSearching].accountNumber) == 0)
            {

                kTemp = kSearching;
                presentCounter = kSearching;
                printf("\nMatching Successfully!\n");
                break;
            }
        }

        if(kSearching != kTemp)
        {
            do
            {
                printf("\nThe account you entered does not exist in our system.\n");
                printf("\nDo you want to correct your input?\n\n1.Yes\t2.No > ");

                while ((status = scanf("%d%c", &choice2, &character)) == 0 || (2 == status && character != '\n')) {
                clearBuffer();
                printf("\nYou did not enter an integer, try again > ");
                }

                if (choice2 != 1 && choice2 != 2)
                {
                    printf("\nERROR!\nPlease enter a valid number!\n\nDo you want to correct your input?\n\n1.Yes\t2.No > ");

                    while ((status = scanf("%d%c", &choice2, &character)) == 0 || (2 == status && character != '\n')) {
                    clearBuffer();
                    printf("\nYou did not enter an integer, try again > ");
                    }
                }

                if (choice2 == 2)
                {
                    askBankAccount();
                }

                if (choice2 == 1)
                {
                    printf("Please correct your input(Bank Account) > ");

                    fgets(bankAccount, 20, stdin);

                    if (bankAccount[strlen(bankAccount)-1] == '\n')
                        bankAccount[strlen(bankAccount)-1] = '\0';
                    else
                        clearBuffer();
                }

                for(kSearching = 0; kSearching < 1000; kSearching++)
                {
                    if (strcmp(bankAccount, information[kSearching].accountNumber) == 0)
                    {
                        break;
                    }
                }
            }while(choice2 == 1 && (strcmp(bankAccount, information[kSearching].accountNumber) != 0));
        }
    }

}

/* accountNo - This function is used to ask you whether you want
* to create a Bank Account right now. If yes, it will lead you to
* the function "createAccount". If not, it will ask you whether continue
* to use it. If yes, you can still use it. While, exit the program.
*
* Parameter(written in the detailed function):
* int choice3 - used to deposit the input whether you want to create an account.
* int choice4 - used to deposit the input whether continue to use ATM.
* int status - combined with int choice3 && int choice4 && char character to readInteger.
*
*/
void accountNo()
{
    int choice3, choice4, status;
    char character;

    printf("\nDo you want to create an account of our bank right now?\n\n1.Yes\t2.No > ");

    do
    {
        while ((status = scanf("%d%c", &choice3, &character)) == 0 || (2 == status && character != '\n')) {
        clearBuffer();
        printf("\nYou did not enter an integer, try again > ");
        }

        switch(choice3)
        {
            default:
                {
                    printf("ERROR!\nPlease enter valid number!\n");

                }break;

            case 1:
                {
                    createAccount();

                }break;

            case 2:
                {
                    exit(0);

                }break;
        }
    }while(choice3 != 1 && choice3 != 2);

    do
    {
        printf("\nDo you want to continue to use our ATM?\n\n1.Yes\t2.No > ");

        while ((status = scanf("%d%c", &choice4, &character)) == 0 || (2 == status && character != '\n')) {
        clearBuffer();
        printf("\nYou did not enter an integer, try again > ");
        }

        if(choice4 == 1)
        {
            askBankAccount();
            break;
        }

        else if (choice4 == 2)
        {
            updateFile(Counter());
            exit (0);
        }

        else if (choice4 != 1 && choice4 != 2)
        {
            printf("\nERROR!\nPlease enter a valid number!");
        }
    }while (choice4 != 1 && choice4 != 2);
}

/* createAccount - This function is used to create a new account. If
* the number you give has been registered by others. It will let you to
* change your number. If created successfully. It will mark the next empty BankAccount with "*".
*
* Parameters(written in the detailed function):
* int status && int choice && char character - used to readInteger and readString.
* int kSearching - used to search whether your input does exist in our system. If yes,
* it will let you to change your input. If not, move to next step.
* int kTemp - used to be the requirements to justice whether you need to change your input.
* char name[20], sex[20], bankAccount[20], pinCode[20] - used to deposit your input(information).
* char copyString[20] - to be a mark.
*
*/
void createAccount()
{
    valueStruct();

    int status, kSearching = 0, choice, kTemp = 0;
    char name[20], sex[20], bankAccount[20], pinCode[20], copyString[20] = {'*'}, character;

    printf("\nThis is the interface for creating an Account in our Bank!\n");
    printf("\nPlease enter your Name > ");
    fgets(name, 20, stdin);

    if (name[strlen(name)-1] == '\n')
        name[strlen(name)-1] = '\0';
    else
        clearBuffer();

    strcpy(information[createCounter].name, name);

    printf("\nPlease enter your Sex (Mr or Mrs) > ");
    fgets(sex, 20, stdin);

    if (sex[strlen(sex)-1] == '\n')
        sex[strlen(sex)-1] = '\0';
    else
        clearBuffer();

    strcpy(information[createCounter].sex, sex);

    if (createCounter == 0)
    {
        printf("\nPlease give the number for your Bank Account > ");
        fgets(bankAccount, 20, stdin);

        if (bankAccount[strlen(bankAccount)-1] == '\n')
            bankAccount[strlen(bankAccount)-1] = '\0';
        else
            clearBuffer();

        strcpy(information[createCounter].accountNumber, bankAccount);
        printf("\nPlease set your PIN > ");
        fgets(pinCode, 20, stdin);

        if (pinCode[strlen(pinCode)-1] == '\n')
            pinCode[strlen(pinCode)-1] = '\0';
        else
            clearBuffer();

        strcpy(information[createCounter].pinCode, pinCode);
    }

    if (createCounter != 0)
    {
        do
        {
            printf("\nPlease give the number for your Bank Account > ");
            fgets(bankAccount, 20, stdin);

            if (bankAccount[strlen(bankAccount)-1] == '\n')
                    bankAccount[strlen(bankAccount)-1] = '\0';
            else
                   clearBuffer();

            for (kSearching = 0; kSearching < 1000; kSearching++)
            {
                if(strcmp(information[kSearching].accountNumber, bankAccount) == 0)break;
            }
            kTemp = 1;

            if(kSearching == 1000) kTemp = 2;

            if (kTemp == 1)
            {
                printf("\nThis account has been registered by others.");
                printf("\nDo you want to continue to create an Account?\n\n1.Yes\t2.No > ");

                while ((status = scanf("%d%c", &choice, &character)) == 0 || (2 == status && character != '\n')) {
                    clearBuffer();
                printf("\nYou did not enter an integer, try again > ");
                }

                if (choice == 2)
                {
                    exit(0);
                }

                while (1)
                {
                    if (choice != 1 && choice != 2)
                    {
                        printf("\nPlease enter a valid number > ");

                        while ((status = scanf("%d%c", &choice, &character)) == 0 || (2 == status && character != '\n')) {
                            clearBuffer();
                        printf("\nYou did not enter an integer, try again > ");
                        }
                    }

                    if (choice == 1 || choice == 2) break;
                }
            }


            if (kTemp != 1)
            {
                strcpy(information[createCounter].accountNumber, bankAccount);
                printf("\nPlease set your PIN > ");
                fgets(pinCode, 20, stdin);

                if (pinCode[strlen(pinCode)-1] == '\n')
                    pinCode[strlen(pinCode)-1] = '\0';
                else
                    clearBuffer();

                strcpy(information[createCounter].pinCode, pinCode);

                information[createCounter].balance = 0;
                strcpy(information[createCounter + 1].accountNumber, copyString);
            }
        }while(choice == 1 && kTemp == 1);
    }
    updateFile(Counter());
}

/* checkPin - This function is used to check your input(Pin) whether it is the
* pin for the corresponding account.
*
* Parameter(written in the detailed function):
* int status && int choice && choice2 && char character - used to readInteger.
* int choice - used to deposit your input for whether you want to correct your input.
* int choice2 - used to deposit whether you want to continue to use ATM.
* char pinCode[20] - used to ask the user to enter the PIN and deposit it.
*
*/
void checkPin()
{
    int status, choice, n = 2, choice2;
    char pinCode[20], character;

    printf("\nPlease enter your PIN > ");
    fgets(pinCode, 20, stdin);

    if (pinCode[strlen(pinCode)-1] == '\n')
        pinCode[strlen(pinCode)-1] = '\0';
    else
        clearBuffer();

    if (strcmp(pinCode, information[presentCounter].pinCode) == 0)
    {
        printf("\nMatching Successfully!\n");
    }

    else
    {
        printf("\nWrong PIN!\nPlease check your input.\n");
        printf("\nDo you want to correct your PIN?\n\n1.Yes\t2.No > ");

        while ((status = scanf("%d%c", &choice, &character)) == 0 || (2 == status && character != '\n')) {
        clearBuffer();
        printf("\nYou did not enter an integer, try again > ");
        }

        if (choice != 1 && choice != 2)
        {
            printf("\nPlease enter a valid number!\n\nDo you want to correct your PIN?\n\n1.Yes\t2.No > ");

            while ((status = scanf("%d%c", &choice, &character)) == 0 || (2 == status && character != '\n')) {
            clearBuffer();
            printf("\nYou did not enter an integer, try again > ");
            }
        }
        if (choice == 1)
        {
            do
            {
                printf("\nYou only have %d chance(s) left.\nPlease correct your PIN > ", n);
                fgets(pinCode, 20, stdin);

                if (pinCode[strlen(pinCode)-1] == '\n')
                    pinCode[strlen(pinCode)-1] = '\0';
                else
                    clearBuffer();

                if (strcmp(pinCode, information[presentCounter].pinCode) == 0)
                {
                    printf("\nMatching Successfully!\n");
                    break;
                }

                if (strcmp(pinCode, information[presentCounter].pinCode) != 0)
                {
                    printf("\nWrong PIN!\n");
                }

                n--;

            }while (n > 0 && (strcmp(pinCode, information[presentCounter].pinCode) != 0));

            if (n == 0 && (strcmp(pinCode, information[presentCounter].pinCode) != 0))
            {
                printf("\nYour Bank Account has been locked!\n");

                do
                {
                    printf("\nDo you want to continue to use ATM?\n\n1.Yes\t2.No > ");

                    while ((status = scanf("%d%c", &choice2, &character)) == 0 || (2 == status && character != '\n')) {
                    clearBuffer();
                    printf("\nYou did not enter an integer, try again > ");
                    }
                    if (choice2 != 1 && choice2 != 2)
                    {
                        printf("\nWrong number. Please enter a valid number!\n");
                    }

                    if (choice2 == 1)
                    {
                        askBankAccount();
                    }

                    if (choice2 == 2)
                    {
                        exit(0);
                    }
                }while (choice2 != 1 && choice2 != 2);

            }
        }

        if (choice == 2)
        {
            askBankAccount();
        }
    }
}

/* updateFile - Make the computer write the information from the struct back to the File.
* Its work just like updating the data in the File.
*
* Parameters*(written in the detailed function):
* int i - used to count the operation times.
* int studentCounter - used to be the mark of the end
* for writing the data back to the FILE.
*
*/
void updateFile(int studentCounter)
{
    int i;

    FILE *fp;

    if(!(fp = fopen("tests.txt","w")))
    {
        printf("\nSorry!\nSystem has broken!\n");
    }
    for (i = 0; i < studentCounter; i++)
    {
        fprintf(fp, "%s %s %d %s %s\n", information[i].accountNumber, information[i].pinCode,
                                             information[i].balance, information[i].name, information[i].sex);
    }

    fclose(fp);
}

/* introduce - The function displays the given sentence
* which is used to introduce the person to use it on screen.
*
*/
void introduce()
{
    printf("\nDear %s %s :\n", information[presentCounter].sex, information[presentCounter].name);
}

/* function - It contains most functions that ATM should have.
* Such as 1--Withdraw money, 2--Check the balance, 3--Deposit money,
* 4--Transfer money to another BankAccount which has been registered
* in the system, 5--Change PIN, 6--Back to the page above.
*
* Parameters(written in the detailed function)
* int choice - asks the user to enter his service and deposit it.
* int withdraw1, balance1, deposit1, transfer1 - used to give its initial value
* in this function.
* int i1 - used to search the No. of the account you want to transfer
* int status - Combined with int choice && char character && char account[20]
* to readInteger and readString.
*
*/
void function()
{
    int choice, status, withdraw1 = 0, balance1 = 0, deposit1 = 0, transfer1 = 0;
    char character;

    balance1 = information[presentCounter].balance;

    while (1)
    {
        do
            {
                printf("\nPlease choose your business:\t\n\n1--Withdraw\t2--Balance\n3--Deposit\t4--Transfer\n5--Change PIN\t6--Back");
                printf("\n > ");
                while ((status = scanf("%d%c", &choice, &character)) == 0 || (2 == status && character != '\n')) {
                    clearBuffer();
                    printf("You did not enter an integer, try again > ");
                }
                if (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6) printf("\nERROR! Please enter the correct number.");
            }while ( choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6);


            switch(choice)
            {
                case 1:
                {

                    printf("\nPlease enter the amount of the money you want to withdraw: \n");

                    while ((status = scanf("%d%c", &withdraw1, &character)) == 0 || (2 == status && character != '\n')) {
                        clearBuffer();
                        printf("You did not enter an integer, try again > ");
                    }

                    withdraw(&withdraw1, &balance1);

                }break;

                case 2:
                {

                    balance(&balance1);


                }break;

                case 3:
                {

                    printf("\nPlease enter the amount of the money you want to deposit: ");

                    while ((status = scanf("%d%c", &deposit1, &character)) == 0 || (2 == status && character != '\n')) {
                        clearBuffer();
                        printf("You did not enter an integer, try again > ");
                    }

                    deposit(&deposit1, &balance1);

                }break;

                case 4:
                {
                    int choice2, i, i1;
                    char account[20];

                    printf("\nPlease enter the account which you want to transfer: ");
                    fgets(account, 20, stdin);

                    if (account[strlen(account)-1] == '\n')
                        account[strlen(account)-1] = '\0';
                    else
                        clearBuffer();

                    for (i = 0; i < 1000; i++)
                    {
                        if (strcmp(account, information[i].accountNumber) == 0)
                        {
                            i1 = i;
                            break;
                        }
                    }

                    if (i1 == i && i1 != presentCounter)
                    {
                        printf("\nThe name of the account you transfered is > %s %s\n", information[i1].sex, information[i1].name);
                        printf("\nPlease enter the amount of the money you want to transfer: ");
                        while ((status = scanf("%d%c", &transfer1, &character)) == 0 || (2 == status && character != '\n')) {
                            clearBuffer();
                            printf("You did not enter an integer, try again > ");
                        }
                        transfer(&transfer1, &balance1, i1);
                    }

                    if (i1 != i)
                    {
                        printf("\nThe account you want to transfer does not exist in our bank.Please check!\n");
                    }

                    if (i1 == presentCounter)
                    {
                        printf("\nYou cannot transfer to yourself!\n");
                    }

                }break;

                case 5:
                {
                    changePin();
                }break;

                case 6:
                    {
                        backPage();
                    }
            }

                printf("\nDo you want to continue to use our ATM?\n\n1--Continue\t2--Finish > ");

                while ((status = scanf("%d%c", &choice, &character)) == 0 || (2 == status && character != '\n')) {
                    clearBuffer();
                    printf("You did not enter an integer, try again > ");
                    }

                if (choice != 1 && choice != 2)
                {
                    do
                    {
                            printf("\nERROR! Please enter a valid number > ");

                            while ((status = scanf("%d%c", &choice, &character)) == 0 || (2 == status && character != '\n')) {
                                clearBuffer();
                            printf("You did not enter an integer, try again > ");
                            }
                    }while (choice != 1 && choice != 2);
                }


                if (choice == 2) break;
    }

    information[presentCounter].balance = balance1;

}

/* balance - Tells the user how much money does his account have.
*
* Parameter:
* int *o - It is the first letter of "original". Used to get the
* address from the function "&balance".
*
*/
void balance(int *o)
{
    *o = *o;
    printf("\nYour balance is %d Euro.\n", *o);
}

/* transfer - Used to transfer your money to another bank account.
*
* Parameter:
* int *t - It is the first letter of "transfer". Used to get the address
* from the function "&transfer1".
* int *o - It is the first letter of "original". Used to get the address
* from the function "&balance1".
* int m2 - used to get the value from the function "i1"(which has been explained above);
*
*/
void transfer(int *t, int *o, int m2)
{

    if (*t > *o)
    {
        printf("\nYour balance is insufficient!\n");
    }

    if (*t < *o)
    {
        *o = *o - *t;
        information[m2].balance = *t + information[m2].balance;
        printf("\nYour balance is %d Euro.\n", *o);
    }
}

/* withdraw - Used to withdraw money from the bank account, also
* show the balance to the user after withdrawing.
*
* Parameter:
* int *w - It is the first letter of "withdraw". Used to get the address
* from the function - "&withdraw1".
* int *o - It is the first letter of "original". Used to get the address
* from the function - "&balance1".
* int x, int y - show the numbers for 50 Euro, numbers for 20 Euro.
*
*/
void withdraw(int *w, int *o)
{
    int x, y;
    if (*o >= *w)
    {
        if(*w % 10 == 0 && *w != 30 && *w != 10)
        {
            if ((*w % 50) % 20 == 0)
            {
                x = *w/50;
                y = (*w % 50)/20;
            }
            else if (*w % 50 == 0)
            {
                x = *w/50;
                y = 0;
            }
            else
            {
                x = (*w/50) - 1;
                y = (*w - (x * 50))/20;
            }   printf("\nYou will be given as--> %d * 50 and %d * 20\n", x, y);
            printf("\nPlease collect your money.\n");
            *o = *o - *w;
        }
        else
        {
            printf("\nPlease enter correct number!\n");
        }
    }
    else printf("\nYour balance is insufficient.\n"); if(*o >= *w)printf("\nYour balance right now is %d Euro.\n", *o);
}

/* deposit - Used to deposit money, and tell the user how much money does
* he have after that.
*
* Parameters:
* int *d - It is the first letter of "deposit". Used to get address from the
* function - "&deposit1".
* int *o - It is the first letter of "original". Used to get address from the
* function - "&balance1"
*
*/
void deposit(int *d, int *o)
{
    *o = *o + *d;

    printf("\nYour balance right now is %d Euro.\n", *o);
}

/* changePin - This function can make the user change his PIN.
*
* Parameters(written in the detailed function)
* int choice3 - used to ask the user whether continue to change his PIN
* int chances - used to tell the user how many times does he can try his PIN
* char pin[20] - used to ask the user to enter his original pin and deposit it
* int status - combined with int choice3 && char character && char pin[20] to readInteger
* and readString
*
*/
void changePin()
{
    int status;
    int chances = 3, choice3;
    char character, pin[20];

    printf("\nThis is the interface for changing your PIN!\n");
    printf("\nPlease enter your original PIN >");
    fgets(pin, 20, stdin);

    if (pin[strlen(pin)-1] == '\n')
        pin[strlen(pin)-1] = '\0';
    else
        clearBuffer();

    if (strcmp(pin, information[presentCounter].pinCode) == 0)
    {
        printf("\nPlease set your NEW PIN > ");
        fgets(pin, 20, stdin);

        if (pin[strlen(pin)-1] == '\n')
            pin[strlen(pin)-1] = '\0';
        else
            clearBuffer();

        strcpy(information[presentCounter].pinCode, pin);

        printf("\nChanging Successfully!\n");
    }

    else
    {
        do
        {
            chances--;
            printf("\nWrong PIN! Please check your original input (PIN)\nYou only have %d chance(s) left.\n", chances);
            printf("\nDo you want to change your PIN?\n\n1.Yes\t2.No > ");

            while ((status = scanf("%d%c", &choice3, &character)) == 0 || (2 == status && character != '\n')) {
                clearBuffer();
                printf("You did not enter an integer, try again > ");
            }

            if (choice3 == 1)
            {
                printf("\nPlease enter your original PIN > ");
                fgets(pin, 20, stdin);

                if (pin[strlen(pin)-1] == '\n')
                    pin[strlen(pin)-1] = '\0';
                else
                    clearBuffer();

                if (strcmp(pin, information[presentCounter].pinCode) == 0)
                {
                    printf("\nPlease set your NEW PIN > ");
                    fgets(pin, 20, stdin);

                    if (pin[strlen(pin)-1] == '\n')
                        pin[strlen(pin)-1] = '\0';
                    else
                        clearBuffer();

                    strcpy(information[presentCounter].pinCode, pin);
                    printf("\nChanging Successfully!\n");
                    break;
                }
            }

            else if (choice3 == 2)
            {
                break;
            }
        } while (chances != 0 && choice3 != 1 && choice3 != 2);
    }
}

/* backPage - used to make the user get back to the page above
* int choice - asks the user to enter his option to whether continue to use ATM,
* and deposits it.
* int status - combined with int choice && char character to readInteger
*
*/
void backPage()
{
    int choice, status;
    char character;
    do
    {
        printf("\nDo you want to continue to use ATM?\n\n1.Yes\t2.No > ");

        while ((status = scanf("%d%c", &choice, &character)) == 0 || (2 == status && character != '\n')) {
            clearBuffer();
        printf("\nYou did not enter an integer, try again > ");
        }

        if (choice == 1)
        {
            introduce();
            function();
        }

        if (choice == 2)
        {
            updateFile(Counter());
            exit(0);
        }

        if (choice != 1 && choice != 2)
        {
            printf("\nPlease enter a valid number > ");
        }
    }while (choice != 1 && choice != 2);
}

