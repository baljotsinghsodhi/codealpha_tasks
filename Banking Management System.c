#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account {
    int accNo;
    char name[50];
    float balance;
};

void createAccount();
void deposit();
void withdraw();
void balanceEnquiry();

int main() {
    int choice;

    while (1) {
        printf("\n========== BANK MANAGEMENT SYSTEM ==========\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Balance Enquiry\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                deposit();
                break;
            case 3:
                withdraw();
                break;
            case 4:
                balanceEnquiry();
                break;
            case 5:
                printf("Thank You!\n");
                exit(0);
            default:
                printf("Invalid Choice!\n");
        }
    }

    return 0;
}

// Create New Account
void createAccount() {
    FILE *fp;
    struct Account a;

    fp = fopen("bank.dat", "ab");
    if (fp == NULL) {
        printf("File Error!\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &a.accNo);

    printf("Enter Account Holder Name: ");
    scanf(" %[^\n]", a.name);

    printf("Enter Initial Balance: ");
    scanf("%f", &a.balance);

    fwrite(&a, sizeof(a), 1, fp);
    fclose(fp);

    printf("Account Created Successfully.\n");
}

// Deposit Amount
void deposit() {
    FILE *fp;
    struct Account a;
    int acc;
    float amount;
    int found = 0;

    fp = fopen("bank.dat", "rb+");
    if (fp == NULL) {
        printf("No Accounts Found!\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &acc);

    while (fread(&a, sizeof(a), 1, fp)) {
        if (a.accNo == acc) {
            printf("Enter Amount to Deposit: ");
            scanf("%f", &amount);

            a.balance += amount;

            fseek(fp, -sizeof(a), SEEK_CUR);
            fwrite(&a, sizeof(a), 1, fp);

            printf("Deposit Successful.\n");
            printf("Updated Balance = %.2f\n", a.balance);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Account Not Found.\n");

    fclose(fp);
}

// Withdraw Amount
void withdraw() {
    FILE *fp;
    struct Account a;
    int acc;
    float amount;
    int found = 0;

    fp = fopen("bank.dat", "rb+");
    if (fp == NULL) {
        printf("No Accounts Found!\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &acc);

    while (fread(&a, sizeof(a), 1, fp)) {
        if (a.accNo == acc) {
            printf("Enter Amount to Withdraw: ");
            scanf("%f", &amount);

            if (amount > a.balance) {
                printf("Insufficient Balance!\n");
            } else {
                a.balance -= amount;

                fseek(fp, -sizeof(a), SEEK_CUR);
                fwrite(&a, sizeof(a), 1, fp);

                printf("Withdrawal Successful.\n");
                printf("Remaining Balance = %.2f\n", a.balance);
            }
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Account Not Found.\n");

    fclose(fp);
}

// Balance Enquiry
void balanceEnquiry() {
    FILE *fp;
    struct Account a;
    int acc;
    int found = 0;

    fp = fopen("bank.dat", "rb");
    if (fp == NULL) {
        printf("No Accounts Found!\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &acc);

    while (fread(&a, sizeof(a), 1, fp)) {
        if (a.accNo == acc) {
            printf("\nAccount Number : %d\n", a.accNo);
            printf("Account Holder : %s\n", a.name);
            printf("Current Balance: %.2f\n", a.balance);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Account Not Found.\n");

    fclose(fp);
}