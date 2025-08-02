#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define MAX_DISTRICT 64
#define MAX_MARKET 20
#define MAX_PRODUCT 15

#define ADMIN "admin"
#define ADMIN_PASS "admin987"
#define USER1 "user1"
#define USER1_PASS "user123"

typedef struct {
    char name[50];
    float price[7];
} Product;

typedef struct {
    char name[50];
    Product products[MAX_PRODUCT];
    int productCount;
} Market;

typedef struct {
    char name[50];
    Market markets[MAX_MARKET];
    int districtCount;
} District;

District district[MAX_DISTRICT];
int districtCount = 0;

//------------------------- //         unfinished login system
int validationCheck(char *role) {
    char user[50], pass[50];
    int Role = atoi(role);
    while(true) {
        if(Role == 1) {
            printf("Login as a developer: ");
            scanf("%s", user);
            if(strcmp(user, ADMIN) != 0) {
                printf("This user doesnt exist\n");
                return false;
            }
            printf("Password: ");
            scanf("%s", pass);
            if(strcmp(pass, ADMIN_PASS) != 0) {
                printf("Invalid password\n");
                return false;
            }
            return true;
        }
        else if(Role == 2) {
            printf("Enter username: ");
            scanf("%s", user);
            printf("Password: ");
            scanf("%s", pass);
            if(strcmp(user, USER1)!=0 || strcmp(pass, USER1_PASS)!=0) {
                printf("Invalid user or password\n");
                return false;
            }
            return true;
        }
    }

}

int userLogin() {
    char role[10];
    while(true) {
        system("clear");
        bool isValid;
        printf("Login: \n");
        printf("[1] Admin\n[2] User\n[*]: ");
        scanf("%s", role);
        if(strcmp(role, "exit")==0)
            return -1;
        else if(strcmp(role,"1")==0 || strcmp(role,"2")==0)
            isValid = validationCheck(role);
        while(getchar() != '\n');
        

        if(isValid && strcmp(role,"1")==0)
            return 1;
        else if(isValid && strcmp(role,"2")==0)
            return 2;
    }
}
//---------------------------------

int main() {
    int login;
    login = userLogin();
    if(login == -1) {
        printf("Logged out");
        return 0;
    }

}