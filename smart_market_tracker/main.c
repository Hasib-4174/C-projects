#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>
#include<unistd.h>
#include"utils.h"
#include"extra.h"


#define ADMIN "admin"
#define ADMIN_PASS "admin987"
#define USER1 "user1"
#define USER1_PASS "user123"

District districts[MAX_DISTRICT];
int districtCount = 0;

//------------------------- //       
int validationCheck(char *role) {
    char user[50], pass[50];
    int Role = atoi(role);

    if(Role == 2) {
        system("clear");
        greeting();
        printf("Enter username: ");
        scanf("%s", user);
        if(strcmp(user, USER1) != 0) {
            printf("This user doesnt exist\n");
            delayTime();
            return false;
        }
        printf("Password: ");
        scanf("%s", pass);
        if(strcmp(pass, USER1_PASS) != 0) {
            printf("Login failed. Ensure your username and password are correct\n");
            delayTime();
            return false;
        }
        return true;
    }
    else if(Role == 1) {
        system("clear");
        greeting();
        printf("Login as a developer: \n");
        printf("Username: ");
        scanf("%s", user);
        printf("Password: ");
        scanf("%s", pass);
        if(strcmp(user, ADMIN)!=0 || strcmp(pass, ADMIN_PASS)!=0) {
            printf("Admin access denied!!\n");
            printf("Exiting ");
            delayTime();
            return false;
        }
        return true;
    }

}

int userLogin() {
    char role[10];
    while(true) {
        system("clear");
        bool isValid;
        greeting();
        printf("Login: \n");
        printf("[1] Admin\n[2] User\n[0] Exit\n[*]: ");
        scanf("%s", role);
        if(strcmp(role, "exit")==0 || strcmp(role, "0")==0)
            return -1;
        else if(strcmp(role,"1")==0 || strcmp(role,"2")==0)
            isValid = validationCheck(role);
        clearInputBuffer();

        if(isValid && strcmp(role,"1")==0)
            return 1;
        else if(isValid && strcmp(role,"2")==0)
            return 2;
    }
}
//---------------------------------
int dummyloaded = false;
int dataloaded = false;
void adminMenu() {
    int choice;
    do {
        system("clear");
        greeting();
        printf("\n------ Admin Menu ------\n");
        printf("1. Add Data\n");
        printf("2. Edit Data\n");
        printf("3. Delete (Product / Market / District)\n");
        printf("4. View All Data\n");
        printf("5. Search Data\n");
        printf("6. Compare Prices\n");
        printf("7. Load dummy data\n");
        printf("0. Logout / Exit\n");
        printf("------------------------\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch(choice) {
            case 1: addData(); break;
            case 2: editData(); break;
            case 3: deleteData(); break;
            case 4: printData(); break;
            case 5: searchData(); break;
            case 6: compareData(); break;
            case 7: loadData(); break;
            case 0:
                printf("Logging out ");
                delayTime();
                return;
        }
    } while(choice != 0);
}


void userMenu() {
    int choice;

    do {
        system("clear");
        greeting();
        printf("=====User Menu=====\n");
        printf("1. Search Data\n");
        printf("2. View All Data\n");
        printf("3. Compare Prices\n");
        printf("0. Logout / Exit\n");
        printf("------------------------\n");

        printf("Enter choice: ");
        scanf("%d", &choice);
        clearInputBuffer();
        switch(choice) {
            case 1: searchData(); break;
            case 2: printData(); break;
            case 3: compareData(); break;
            case 0: 
                printf("Logging out ");
                delayTime();
                return;
            default:
                printf("Invalid choice\n");

        }
    } while(choice != 0);


}


int main() {
    int login;
    while(1) {

        login = userLogin();
        if(login == -1) {
            printf("Thank you for using our system\nProgram exiting");
            delayTime();
            return 0;
        }
        else if(login == 1) {
            delayTime();
            printf("\nAuthentication successful. Admin privileges activated\n");
        }
        else if(login == 2) {
            delayTime();
            printf("\nLogin successful. Welcome user!\n");
        }

        if(login == 1) {
            printf("Redirecting to Admin Dashboard "); 
            delayTime();
            adminMenu();
        }
        else if(login ==2) {
            printf("Redirecting to User Dashboard "); 
            delayTime();
            userMenu();

        }
    }

}


