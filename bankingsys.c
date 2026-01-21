#include<stdio.h>
#include<string.h>

/* Structure to store account details */
typedef struct 
{
    char name[50];     // Account holder name
    int acc_no;        // Account number
    float acc_bal;     // Account balance
} Account;

/* File name to store account records */
const char* ACC_dat = "account.dat";

/* Function declarations */
void create_acc();
void withdraw_acc();
void deposite_acc();
void check_balance();

int main()
{
    int choise;

    /* Infinite loop for menu-driven program */
    while(1)
    {
        printf("\n*** BANK MANAGMENT SYSTEM ***\n"); 
        printf("1.Create a account\n");
        printf("2.Withdraw Money\n");
        printf("3.deposite Money\n");
        printf("4.Check Balance\n");
        printf("5.Exit\n");
        printf("Enter Your Choise :");
        scanf("%d", &choise);

        /* Switch case for user choice */
        switch(choise)
        {
            case 1:
                create_acc();   // Create new account
                break;

            case 2:
                withdraw_acc(); // Withdraw money
                break;

            case 3:
                deposite_acc(); // Deposit money
                break;

            case 4:
                check_balance(); // Check balance
                break;

            case 5:
                printf("\n Closing of Bank , Thanks for visiting \n");
                return 0;       // Exit program

            default:
                printf("INVALID CHOISE");
        }
    }
}

/* Function to create a new account */
void create_acc()
{
    Account acc;

    /* Open file in append binary mode */
    FILE *file = fopen(ACC_dat, "ab+");

    if (file == NULL)
    {
        printf("\nUnable to open file!!");
        return;
    }

    getchar();  // Clear input buffer

    /* Take account holder name */
    printf("\nEnter your name :");
    fgets(acc.name, sizeof(acc.name), stdin);

    /* Remove newline character from name */
    acc.name[strcspn(acc.name, "\n")] = '\0';

    /* Take account number */
    printf("\nEnter Account No :");
    scanf("%d", &acc.acc_no);

    /* Initial balance is zero */
    acc.acc_bal = 0;

    /* Write account data to file */
    fwrite(&acc, sizeof(acc), 1, file);

    fclose(file);

    printf("\nAccount create Successfully");
}

/* Function to withdraw money */
void withdraw_acc()
{
    /* Open file in read + write binary mode */
    FILE *file = fopen(ACC_dat, "rb+");

    if (file == NULL)
    {
        printf("\nUnable to open file!!");
        return;
    }

    Account acc_r;
    int money;
    int acc_no;

    /* Take account number and withdraw amount */
    printf("Enter your Account no:");
    scanf("%d", &acc_no);

    printf("Enter Amount to withdraw ");
    scanf("%d", &money);

    /* Read each account from file */
    while (fread(&acc_r, sizeof(acc_r), 1, file))
    {
        /* Check if account number matches */
        if (acc_r.acc_no == acc_no)
        {
            /* Check sufficient balance */
            if (acc_r.acc_bal >= money)
            {
                acc_r.acc_bal -= money;  // Deduct money

                /* Move file pointer back to overwrite record */
                fseek(file, -sizeof(acc_r), SEEK_CUR);

                /* Write updated account */
                fwrite(&acc_r, sizeof(acc_r), 1, file);

                fclose(file);

                printf("\nSuccessfully withdraw Rs.%d, new Account Balance is Rs.%.2f",
                       money, acc_r.acc_bal);
                return;
            }
            else
            {
                printf("Insufficient Balance");
                fclose(file);
                return;
            }
        }
    }

    /* If account number not found */
    fclose(file);
    printf("\nEntered Account no is invalid ");
}

/* Function to deposit money */
void deposite_acc()
{
    FILE *file = fopen(ACC_dat, "rb+");

    if (file == NULL)
    {
        printf("\nUnable to open file!!");
        return;
    }

    Account acc_r;
    int money;
    int acc_no;

    printf("Enter your Account no:");
    scanf("%d", &acc_no);

    printf("Enter Amount to deposite ");
    scanf("%d", &money);

    /* Read each account to find matching account number */
    while (fread(&acc_r, sizeof(acc_r), 1, file))
    {
        if (acc_r.acc_no == acc_no)
        {
            acc_r.acc_bal += money;  // Add money

            /* Move pointer back to update same record */
            fseek(file, -sizeof(acc_r), SEEK_CUR);
            fwrite(&acc_r, sizeof(acc_r), 1, file);

            fclose(file);

            printf("\nSuccessfully Deposited Rs.%d, new Account Balance is Rs.%.2f",
                   money, acc_r.acc_bal);
            return;
        }
    }

    fclose(file);
    printf("\nEntered Account no is invalid ");
}

/* Function to check account balance */
void check_balance()
{
    FILE *file = fopen(ACC_dat, "rb");

    if (file == NULL)
    {
        printf("\nUnable to open file!!");
        return;
    }

    int acc_no;
    Account acc_read;

    printf("Enter your account number :");
    scanf("%d", &acc_no);

    /* Read each record and compare account number */
    while (fread(&acc_read, sizeof(acc_read), 1, file))
    {
        if (acc_read.acc_no == acc_no)
        {
            printf("Your current balance is Rs.%.2f", acc_read.acc_bal);
            fclose(file);
            return;
        }
    }

    /* If account not found */
    printf("\nAccount No:%d was not found.\n", acc_no);
    fclose(file);
}
