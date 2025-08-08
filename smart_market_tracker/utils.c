#include"utils.h"
#include"extra.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>



void printData() {
    system("clear");
    int i, j, k, l;
    for(i=0;i<districtCount;i++) {
        printf("\n");
        District *current_district = &districts[i];
        printf("========== District[%02d]-%s ==========\n", i+1, current_district->name);
        for(j=0;j<districts[i].marketCount;j++) {
            printf("\n");
            Market *current_market = &current_district->markets[j];
            printf("----- Market[%02d]-%s -----\n", j+1, current_market->name);
            for(k=0;k<districts[i].markets[j].productCount;k++) {
                Product *current_product = &current_market->products[k];
                printf("Product[%02d]-%-15s | Prices: ", k+1, current_product->name);
                for(l=0;l<7;l++) {
                    printf("%5.0f |", current_product->price[l]);
                }
                printf("\n");
            }
        }
    }
    char prompt[10];
    while(1) {
        printf("Enter 'exit'to go back to Admin Menu: ");
        scanf("%s", prompt);
        if(strcmp(prompt, "exit")==0)
            break;
    }
}
void addMarket() {
    char district[50];
    int choice;
    char marketName[50];
    do {
        system("clear");
        printf("[1] Select district to add market\n");
        printf("[0] Cancel\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        if(choice == 0)
            return;
        else if(choice == 1) {
            system("clear");
            break;
        }
        clearInputBuffer();
    } while(1);
    int num;
    do {
        num = 0;
        printf("Enter district number or district's name: \n");
        printf("'exit' to return to Admin Menu\n-> ");
        scanf("%s", district);
        clearInputBuffer();
        if(strspn(district, "0123456789") == strlen(district))
            num = atoi(district);
        else if(strcmp(district, "exit")==0)
            return;
        else {
            for(int i=0;i<districtCount;i++) {
                if(strstr(districts[i].name, district)!=NULL) {
                    printf("Matches found: \n");
                    printf("[%d] %s\n", i+1, districts[i].name);
                }
                else {
                    printf("District's name not found\n");
                    delayTime();
                    continue;
                }
            }
        }

        if(num != 0 && (num < 1 || num > districtCount)) {
            printf("Invalid district number\n");
            delayTime();
            continue;
        }
        break;
    } while(1);
    District *current_district = &districts[num-1];
    do {
        Market *current_market = &current_district->markets[current_district->marketCount];
        printf("Enter market[%d] name: ", current_district->marketCount+1);
        scanf("%s", marketName);
        clearInputBuffer();
        if(strcmp(marketName, "")==0) {
            printf("Market name cannot be empty\n");
            continue;
        }
        else if(current_district->marketCount < MAX_MARKET) {
            printf("Maximum number of markets for %s district has been reached\n", current_district->name);
            delayTime();
            break;
        }
        strcpy(current_market->name, marketName);
        current_market->productCount = 0;
        printf("Market added successfully\n");
        districts[num-1].marketCount++;

    } while(current_district->marketCount < MAX_MARKET);


}

void addDistrict() {
    char choice[5];
    char districtName[50];
    do {
        system("clear");
        printf("Enter district name: ");
        scanf("%s", districtName);
        if(districtCount >= MAX_DISTRICT) {
            printf("Maximum number of districts reached\n");
            delayTime();
            break;
        } 
        else if(strcmp(districtName, "")==0)
            break;
        
        strcpy(districts[districtCount].name, districtName);
        districts[districtCount].marketCount = 0;
        printf("District added successfully\n");
        delayTime();
        districtCount++;
        do {
            printf("Want to add more districts? [yes/no]: ");
            scanf("%s", choice);
            clearInputBuffer();
            toLowerStr(choice);
        } while(strcmp(choice, "yes")!=0 && strcmp(choice, "no")!=0);
        if(strcmp(choice, "no")==0)
            break;
    
    } while(1);
}

void addData() {
    int choice;
    do {
        system("clear");
        printf("[1] Add District\n");
        printf("[2] Add Market\n");
        printf("[3] Add Product\n");
        printf("[0] Cancel\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        if(choice == 1)
            addDistrict();
        else if(choice == 2)
            addMarket();
        else if(choice == 3)
            continue;
            //addProduct();
    } while(choice != 0);
}


