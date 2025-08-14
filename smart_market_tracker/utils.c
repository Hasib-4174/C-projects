#include"utils.h"
#include"extra.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>

//int price = district[0].markets[0].products[0].price[0];
//districts[i].name
//(*current_district[i]).name

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


void addProduct() {
    char districtName[50];
    int choice;
    char marketName[50];
    do {
        system("clear");
        printf("==Add Product==\n");
        printf("[1] Select district\n");
        printf("[0] Cancel\n");
        scanf("%d", &choice);
        if(choice == 0)
            return;
        else if(choice == 1)
            break;
        clearInputBuffer();
    } while(1);
    int numD;
    do {
        numD = 0;
        printf("Enter district number or district's name: \n");
        printf("'exit' to return to Admin Menu\n-> ");
        scanf("%s", districtName);
        clearInputBuffer();
        if(strspn(districtName, "0123456789") == strlen(districtName))
            numD = atoi(districtName);
        else if(strcmp(districtName, "exit")==0)
            return;
        else {
            bool found = false;
            for(int i=0;i<districtCount;i++) {
                if(strstr(districts[i].name, districtName)!=NULL) {
                    if(!found) printf("Matches found: \n");
                    found = true;
                    printf("[%d] %s\n", i+1, districts[i].name);
                    break;
                }
                else if(i == districtCount -1 && !found) {
                    printf("District's name not found\n");
                    delayTime();
                    printf("\n");
                    continue;
                }
            }
        }

        if(numD != 0 && (numD < 1 || numD > districtCount)) {
            printf("Invalid district number\n");
            delayTime();
            continue;
        }
        else if(numD == 0)
            continue;
        else
            break;

    } while(1);
    District *current_district = &districts[numD-1];//   #######
    while(1) {
        system("clear");
        printf("===Add product===\n");
        if(current_district->marketCount == 0) {
            printf("No markets found for %s district\n", current_district->name);
            delayTime();
            break;
        }
        printf("========== District[%02d]-%s ==========\n", numD, current_district->name);
        char marketName[50];
        int numM;
        //............................................
        while(1) {
        numM = 0;
        printf("Enter market number or market's name: \n");
        printf("'exit' to return to Admin Menu\n-> ");
        scanf("%s", marketName);
        clearInputBuffer();
        if(strspn(marketName, "0123456789") == strlen(marketName))
            numM = atoi(marketName);
        else if(strcmp(marketName, "exit")==0)
            return;
        else {
            bool found = false;
            for(int i=0;i<current_district->marketCount;i++) {
                Market *current_market = &current_district->markets[i];//   #######
                if(strstr(current_market->name, marketName)!=NULL) {
                    if(!found) printf("Matches found: \n");
                    found = true;
                    printf("[%d] %s\n", i+1, current_market->name);
                    //break;
                }
                else if(i == current_district->marketCount -1 && !found) {
                    printf("Market's name not found\n");
                    delayTime();
                    printf("\n");
                    continue;
                }
            }
        }

        if(numM != 0 && (numM < 1 || numM > current_district->marketCount)) {
            printf("Invalid Market number\n");
            delayTime();
            continue;
        }
        else if(numM == 0)
            continue;
        else
            break;
        } 
        //..........................
        Market *current_market = &current_district->markets[numM-1];
        while(1) {
            int i, j;
            char productName[50];
            system("clear");
            if(current_market->productCount >= MAX_PRODUCT) {
                printf("Maximum number of products for %s market has been reached\n", current_market->name);
                delayTime();
                break;
            }
            i = current_market->productCount;
            //Product *current_product = &current_market->products[i];
            for(;i<MAX_PRODUCT;i++) {
                if(current_market->productCount >= MAX_PRODUCT) {
                    //printf("Maximum number of products for %s market has been reached\n", current_market->name);
                    //delayTime();
                    break;
                }
                Product *current_product = &current_market->products[i];
                printf("Enter product name: ");
                //scanf("%s", productName);
                fgets(productName, sizeof(productName), stdin);
                productName[strcspn(productName, "\n")] = '\0';
                //clearInputBuffer();
                if(strlen(productName)==0) {
                    printf("Product name cannot be empty\n");
                    delayTime();
                    continue;
                }
                strcpy(current_product->name, productName);
                float price;
                for(j=0;j<7;j++) {
                    printf("Enter price of product[%s] for day[%d]: ", productName, j+1);
                    scanf("%f", &price);
                    clearInputBuffer();
                    current_product->price[j] = price;
                }
                current_market->productCount++;
                printf("Product and prices added successfully\n");
                delayTime();
                printf("\n");
                //break;
                char prompt;
                do {
                    printf("Do u want to add more products? [y/n]: ");
                    scanf("%c", &prompt);
                    clearInputBuffer();
                    prompt = tolower(prompt);
                    if(prompt == 'n')
                        return;
                    else if(prompt == 'y')
                        break;
                } while(prompt != 'y' || prompt != 'n');

            }
                

        }

    }

}

void addMarket() {
    char district[50];
    int choice;
    char marketName[50];
    do {
        system("clear");
        printf("==Add Market==\n");
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
            bool found = false;
            for(int i=0;i<districtCount;i++) {
                if(strstr(districts[i].name, district)!=NULL) {
                    if(!found) printf("Matches found: \n");
                    found = true;
                    printf("[%d] %s\n", i+1, districts[i].name);
                    break;
                }
                else if(i == districtCount -1 && !found) {
                    printf("District's name not found\n");
                    delayTime();
                    printf("\n");
                    continue;
                }
            }
        }

        if(num != 0 && (num < 1 || num > districtCount)) {
            printf("Invalid district number\n");
            delayTime();
            continue;
        }
        else if(num == 0)
            continue;
        else
            break;

    } while(1);
    District *current_district = &districts[num-1];
    do {
        system("clear");
        if(current_district->marketCount >= MAX_MARKET) {
            printf("Maximum number of markets for %s district has been reached\n", current_district->name);
            delayTime();
            break;
        }
        printf("----- %s -----\n", current_district->name);
        Market *current_market = &current_district->markets[current_district->marketCount];
        printf("Enter market[%d] name: ", current_district->marketCount+1);
        //scanf("%s", marketName);
        fgets(marketName, sizeof(marketName), stdin);
        marketName[strcspn(marketName, "\n")] = '\0';
        //clearInputBuffer();
        if(strlen(marketName)==0) {
            printf("Market name cannot be empty\n");
            delayTime();
            continue;
        }
        strcpy(current_market->name, marketName);
        current_market->productCount = 0;
        printf("Market added successfully\n");
        districts[num-1].marketCount++;

    } while(1);
    //while(current_district->marketCount > MAX_MARKET);

}


void addDistrict() {
    char choice[5];
    char districtName[50];
    do {
        system("clear");
        printf("Enter district name: ");
        //scanf("%s", districtName);
        fgets(districtName, sizeof(districtName), stdin);
        districtName[strcspn(districtName, "\n")] = '\0';
        //clearInputBuffer();
        if(districtCount >= MAX_DISTRICT) {
            printf("Maximum number of districts reached\n");
            delayTime();
            break;
        } 
        else if(strlen(districtName)==0)
            break;
        
        strcpy(districts[districtCount].name, districtName);
        districts[districtCount].marketCount = 0;
        printf("District added successfully\n");
        delayTime();
        districtCount++;
        do {
            printf("\nWant to add more districts? [yes/no]: ");
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
            addProduct();
    } while(choice != 0);
}


//....................... search data....

void searchData() {

    //code...

}



//....................... search data....

//....................... delete data ....



void deleteData() {

    //code...

}



//....................... delete data....