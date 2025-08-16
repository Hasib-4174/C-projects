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
    greeting();
    printf("==All Data==\n");
    printf("Total districts: %d\n", districtCount);
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
                    printf("%6.02f |", current_product->price[l]);
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
        greeting();
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
    system("clear");
    greeting();
    printf("==Add Product==\n");
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
        greeting();
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
            greeting();
            printf("==Add Product==\n");
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
        greeting();
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
    system("clear");
    greeting();
    printf("==Add Market==\n");
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
        greeting();
        printf("==Add Market==\n");
        printf("========== District[%02d]-%s ==========\n", num, current_district->name);
        if(current_district->marketCount >= MAX_MARKET) {
            printf("Maximum number of markets for %s district has been reached\n", current_district->name);
            delayTime();
            break;
        }
        Market *current_market = &current_district->markets[current_district->marketCount];
        printf("Enter market[%d] name: ", current_district->marketCount+1);
        //scanf("%s", marketName);
        fgets(marketName, sizeof(marketName), stdin);
        marketName[strcspn(marketName, "\n")] = '\0';
        //clearInputBuffer();
        if(strlen(marketName)==0) {
            printf("Market name cannot be empty\n");
            delayTime();
            continue;  // 1. break 2. return (fix it.....)
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

    if(districtCount >= MAX_DISTRICT) {
        printf("District count reached maximum limit\n");
        delayTime();
        return;
    }

    do {
        system("clear");
        greeting();
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
        greeting();
        printf("==Add Data==\n");
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

void editProduct() {
    int choice;
    char marketName[50];
    char districtName[50];
    greeting();
    if(districtCount==0) {
        printf("No districts found\n");
        delayTime();
        return;
    }
    while(1) {
        system("clear");
        greeting();
        printf("==Edit Product Name==\n");
        printf("[1] Select district/market/product\n");
        printf("[0] Cancel\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        clearInputBuffer();
        if(choice == 0)
            return;
        else if(choice == 1)
            break;
    }

    int numD;
    system("clear");
    greeting();
    printf("==Edit Product Name==\n");
    while(1) {
        
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

    }
    District *current_district = &districts[numD-1];

    system("clear");
    greeting();
    printf("===Edit Product===\n");
    if(current_district->marketCount == 0) {
        printf("No market found for %s district\n", current_district->name);
        delayTime();
        return;
    }
    int numM;
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
    Market *current_market = &current_district->markets[numM-1];

    while(1) {
        int i, j;
        char productName[50];
        system("clear");
        greeting();
        printf("==Edit Product==\n");
        printf("========== District[%02d]-%s ==========\n", numD, current_district->name);
        printf("----- Market[%02d]-%s -----\n", numM, current_market->name);
        for(i=0;i<current_market->productCount;i++) {
            Product *current_product = &current_market->products[i];
            printf("Product[%02d] - %-15s\n", i+1, current_product->name);
        }
        int numP;
        while(1) {
            numP = 0;
            printf("Enter product number: ");
            scanf("%d", &numP);
            clearInputBuffer();
            if(numP < 1 || numP > current_market->productCount) {
                printf("Invalid product number\n");
                printf("enter '-1' to return to Admin Menu\n");
                
            } 
            else if(numP == 0)
                continue;
            else if(numP == -1)
                return;
            else
                break;
        }
        Product *current_product = &current_market->products[numP-1];
        
        while(1) {
            system("clear");
            greeting();
            printf("==Edit Product==\n");
            printf("Old name: %s\n", current_product->name);
            printf("Enter new name: ");
            fgets(productName, sizeof(productName), stdin);
            productName[strcspn(productName, "\n")] = '\0';
            if(strlen(productName)==0) {
                printf("Product name cannot be empty\n");
                printf("Enter 'exit' to return\n");
                delayTime();
                continue;
            }
            else if(strcmp(productName, "exit")==0)
                return;
            
            strcpy(current_product->name, productName);
            printf("Product name updated successfully\n");
            delayTime();
            break;

        }
        char prompt;
        while(1) {
            system("clear");
            greeting();
            printf("\nDo you want to edit the prices of this product? [y/n]: ");
            scanf("%c", &prompt);
            clearInputBuffer();
            prompt = tolower(prompt);
            if(prompt == 'n')
                break;
            else if(prompt == 'y') {}
            else {
                printf("Invalid choice\n");
                continue;
            }
            for(i=0;i<7;i++) {
                printf("Enter price of product[%s] for day[%d]: ", current_product->name, i+1);
                scanf("%f", &current_product->price[i]);
                clearInputBuffer();
            }
            printf("Prices updated successfully\n");
            delayTime();
            break;
        }
        while(1) {
            printf("\nDo you want to edit more products inside this market? [y/n]: ");
            scanf("%c", &prompt);
            clearInputBuffer();
            prompt = tolower(prompt);
            if(prompt == 'n')
                return;
            else if(prompt == 'y')
                break;
            else
                printf("Invalid choice\n");
            delayTime();
        }

    }
}

void editMarketName() {
    int choice;
    char marketName[50];
    char districtName[50];
    while(1) {
        system("clear");
        greeting();
        printf("==Edit Market Name==\n");
        printf("[1] Select district/market\n");
        printf("[0] Cancel\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        clearInputBuffer();
        if(choice == 0)
            return;
        else if(choice == 1)
            break;
    }
    int numD;
    system("clear");
    greeting();
    printf("==Edit Market Name==\n");
    while(1) {
        
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

    }
    District *current_district = &districts[numD-1];

    system("clear");
    greeting();
    printf("===Edit Market===\n");
    if(current_district->marketCount == 0) {
        printf("No markets found for %s district\n", current_district->name);
        delayTime();
        return;
    }
    
    int numM;

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
    Market *current_market = &current_district->markets[numM-1];

    while(1) {

        system("clear");
        greeting();
        printf("==Edit Market Name==\n");
        printf("Old name: %s\n", current_market->name);
        printf("Enter new name: ");
        fgets(marketName, sizeof(marketName), stdin);
        marketName[strcspn(marketName, "\n")] = '\0';
        if(strlen(marketName)==0) {
            printf("Market name cannot be empty\n");
            printf("Enter 'exit' to return\n");
            delayTime();
            continue;
        }
        else if(strcmp(marketName, "exit")==0)
            return;
        
        strcpy(current_market->name, marketName);
        printf("Market name updated successfully\n");
        delayTime();
        break;
    }
    

}

void editDistrictName() {
    int choice;
    char districtName[50];
    while(1) {
        system("clear");
        greeting();
        printf("==Edit District Name==\n");
        printf("[1] Select district\n");
        printf("[0] Cancel\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        clearInputBuffer();
        if(choice == 0)
            return;
        else if(choice == 1)
            break;
    }
    int num;
    system("clear");
    greeting();
    printf("==Edit District Name==\n");
    while(1) {

        num = 0;
        printf("Enter district number or district's name: \n");
        printf("'exit' to return to Admin Menu\n-> ");
        scanf("%s", districtName);
        clearInputBuffer();
        if(strspn(districtName, "0123456789") == strlen(districtName))
            num = atoi(districtName);
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

        if(num != 0 && (num < 1 || num > districtCount)) {
            printf("Invalid district number\n");
            delayTime();
            continue;
        }
        else if(num == 0)
            continue;
        else
            break;
    }
    District *current_district = &districts[num-1];
    while(1) {
        system("clear");
        greeting();
        printf("==Edit District Name==\n");
        printf("Old name: %s\n", current_district->name);
        printf("Enter new name: ");
        //scanf("%s", districtName);
        //clearInputBuffer();
        fgets(districtName, sizeof(districtName), stdin);
        districtName[strcspn(districtName, "\n")] = '\0';
        if(strlen(districtName)==0) {
            printf("District name cannot be empty\n");
            printf("Enter 'exit' to return\n");
            delayTime();
            continue;
        }
        else if(strcmp(districtName, "exit")==0)
            return;
        
        strcpy(current_district->name, districtName);
        printf("District name updated successfully\n");
        delayTime();
        break;

    }

}

void editData() {
    int choice;
    do {
        system("clear");
        greeting();
        printf("=== Edit Data ===\n");
        printf("[1] Edit District Name\n");
        printf("[2] Edit Market Name\n");
        printf("[3] Edit Product (Name or Prices)\n");
        printf("[0] Back to Admin Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        clearInputBuffer();
        
        switch(choice) {
            case 1:
                editDistrictName();
                break;
            case 2:
                editMarketName();
                break;
            case 3:
                editProduct();
                break;
            case 0:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
                delayTime();
        }
    } while (choice != 0);
}


void printFoundData(int dIndex, int mIndex) {
    system("clear");
    greeting();
    printf("=== Found Data ===\n");
    printf("======= District[%02d]-%s ==========\n", dIndex+1, districts[dIndex].name);
    printf("----- Market[%02d]-%s -----\n", mIndex, districts[dIndex].markets[mIndex].name);

    for(int p=0;p<districts[dIndex].markets[mIndex].productCount;p++) {

        printf("Product[%02d]-%-15s | Prices: ", p+1, districts[dIndex].markets[mIndex].products[p].name);
        for(int l=0;l<7;l++) {
            printf("%6.02f |", districts[dIndex].markets[mIndex].products[p].price[l]);
        }
        printf("\n");


    }

    
}

void searchData() {

    int choice;
    int dIndex, mIndex;
    char confirm;

    if(districtCount == 0) {
        printf("No districts found\n");
        delayTime();
        return;
    }

    while(1) {
        system("clear");
        greeting();
        printf("==Search Data==\n");
        printf("[1] Select district/market/product\n");
        printf("[0] Cancel");
        printf("Enter choice: ");
        scanf("%d", &choice);
        clearInputBuffer();
        if(choice == 0)
            return;
        else if(choice == 1)
            break;
    }
    while(1) {
        system("clear");
        greeting();
        printf("===Search Data===\n");
        printf("----- Districts -----\n");

        for (int d = 0; d < districtCount; d++) {
            printf("[%d] %s\n", d + 1, districts[d].name);
        }
        printf("\n[*] Select district: ");
        scanf("%d", &dIndex);
        dIndex--;
        if (dIndex < 0 || dIndex >= districtCount) {
            printf("Invalid district selected.\n");
            delayTime();
            break;
        }
        clearInputBuffer();

        if (districts[dIndex].marketCount == 0) {
            printf("No markets available in this district.\n");
            delayTime();
            break;
        }

        system("clear");
        greeting();
        printf("----- Districts -----\n");
        printf("======= District[%02d]-%s ==========\n", dIndex+1, districts[dIndex].name);
        printf("----- Markets -----\n");

        for (int m = 0; m < districts[dIndex].marketCount; m++) {
            printf("[%d] %s\n", m + 1, districts[dIndex].markets[m].name);
        }
        printf("[*] Select market: ");
        scanf("%d", &mIndex);
        mIndex--;
        if (mIndex < 0 || mIndex >= districts[dIndex].marketCount) {
            printf("Invalid market selected.\n");
            delayTime();
            break;
        }
        clearInputBuffer();

        if (districts[dIndex].markets[mIndex].productCount == 0) {
            printf("No products available in this market.\n");
            delayTime();
            break;
        }

        printf("Data found..\n");
        printf("printing data...\n");
        delayTime();

        printFoundData(dIndex, mIndex);
        printf("\nDo you want to search more data? [y/n]:");
        scanf("%c", &confirm);
        clearInputBuffer();
        if(confirm == 'y' || confirm == 'Y')
            continue;
        else
            break;


    }

}


void deleteData() {
    int choice;
    int dIndex, mIndex, pIndex;
    char confirm;

    system("clear");
    greeting();
    printf("---delete menu---\n");
    printf("[1] Delete Product\n");
    printf("[2] Delete Market\n");
    printf("[3] Delete District\n");
    printf("[0] Cancel\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    clearInputBuffer();

    if (choice == 0) {
        return;
    }

    if (districtCount == 0) {
        printf("No districts available.\n");
        delayTime();
        return;
    }

    switch (choice) {
        case 1: {
            system("clear");
            greeting();
            printf("---delete menu---\n");
            printf("----- Districts -----\n");

            for (int d = 0; d < districtCount; d++) {
                printf("[%d] %s\n", d + 1, districts[d].name);
            }
            printf("\n[*] Select district: ");
            scanf("%d", &dIndex);
            dIndex--;
            if (dIndex < 0 || dIndex >= districtCount) {
                printf("Invalid district selected.\n");
                delayTime();
                break;
            }
            clearInputBuffer();

            if (districts[dIndex].marketCount == 0) {
                printf("No markets available in this district.\n");
                delayTime();
                break;
            }

            system("clear");
            greeting();
            printf("---delete menu---\n");
            printf("======= District[%02d]-%s ==========\n", dIndex+1, districts[dIndex].name);
            printf("----- Markets -----\n");

            for (int m = 0; m < districts[dIndex].marketCount; m++) {
                printf("[%d] %s\n", m + 1, districts[dIndex].markets[m].name);
            }
            printf("[*] Select market: ");
            scanf("%d", &mIndex);
            mIndex--;
            if (mIndex < 0 || mIndex >= districts[dIndex].marketCount) {
                printf("Invalid market selected.\n");
                delayTime();
                break;
            }
            clearInputBuffer();

            if (districts[dIndex].markets[mIndex].productCount == 0) {
                printf("No products available in this market.\n");
                delayTime();
                break;
            }

            system("clear");
            greeting();
            printf("---delete menu---\n");
            printf("======= District[%02d]-%s ==========\n", dIndex+1, districts[dIndex].name);
            printf("-----Market[%02d]-%s-----\n", mIndex+1, districts[dIndex].markets[mIndex].name);
            printf("----- Products -----\n");

            for (int p = 0; p < districts[dIndex].markets[mIndex].productCount; p++) {
                printf("[%d] %s\n", p + 1, districts[dIndex].markets[mIndex].products[p].name);
            }
            printf("[*] Select Product: ");
            scanf("%d", &pIndex);
            pIndex--;
            clearInputBuffer();
            if (pIndex < 0 || pIndex >= districts[dIndex].markets[mIndex].productCount) {
                printf("Invalid product selected.\n");
                delayTime();
                break;
            }

            printf("Delete '%s'? (y/n): ", districts[dIndex].markets[mIndex].products[pIndex].name);
            scanf("%c", &confirm);
            clearInputBuffer();

            if (confirm == 'y' || confirm == 'Y') {
                for (int i = pIndex; i < districts[dIndex].markets[mIndex].productCount - 1; i++) {
                    districts[dIndex].markets[mIndex].products[i] = districts[dIndex].markets[mIndex].products[i + 1];
                }
                districts[dIndex].markets[mIndex].productCount--;
                printf("Product deleted successfully.\n");
                delayTime();
            }
            break;
        }

        case 2: {
            system("clear");
            greeting();
            printf("---delete menu---\n");
            printf("----- Districts -----\n");

            for (int d = 0; d < districtCount; d++) {
                printf("[%d] %s\n", d + 1, districts[d].name);
            }
            printf("[*] Select district: ");
            scanf("%d", &dIndex);
            dIndex--;
            if (dIndex < 0 || dIndex >= districtCount) {
                printf("Invalid district selected.\n");
                delayTime();
                break;
            }
            clearInputBuffer();

            system("clear");
            greeting();
            printf("---delete menu---\n");
            printf("======= District[%02d]-%s ==========\n", dIndex+1, districts[dIndex].name);
            printf("----- Markets -----\n");

            for (int m = 0; m < districts[dIndex].marketCount; m++) {
                printf("[%d] %s\n", m + 1, districts[dIndex].markets[m].name);
            }
            printf("[*] Select market: ");
            scanf("%d", &mIndex);
            mIndex--;
            if (mIndex < 0 || mIndex >= districts[dIndex].marketCount) {
                printf("Invalid market selected.\n");
                delayTime();
                break;
            }
            clearInputBuffer();

            printf("Delete market '%s'? (y/n): ", districts[dIndex].markets[mIndex].name);
            scanf("%c", &confirm);
            clearInputBuffer();

            if (confirm == 'y' || confirm == 'Y') {
                for (int i = mIndex; i < districts[dIndex].marketCount - 1; i++) {
                    districts[dIndex].markets[i] = districts[dIndex].markets[i + 1];
                }
                districts[dIndex].marketCount--;
                printf("Market deleted successfully.\n");
                delayTime();
            }
            break;
        }

        case 3: {
            system("clear");
            greeting();
            printf("---delete menu---\n");
            printf("----- Districts -----\n");

            for (int d = 0; d < districtCount; d++) {
                printf("[%d] %s\n", d + 1, districts[d].name);
            }
            printf("[*] Select district: ");
            scanf("%d", &dIndex);
            dIndex--;
            if (dIndex < 0 || dIndex >= districtCount) {
                printf("Invalid district selected.\n");
                delayTime();
                break;
            }
            clearInputBuffer();

            printf("Delete district '%s'? (y/n): ", districts[dIndex].name);
            scanf("%c", &confirm);
            clearInputBuffer();

            if (confirm == 'y' || confirm == 'Y') {
                for (int i = dIndex; i < districtCount - 1; i++) {
                    districts[i] = districts[i + 1];
                }
                districtCount--;
                printf("District deleted successfully.\n");
                delayTime();
            }
            break;
        }

        default: {
            printf("Invalid choice.\n");
            printf("Returning to Admin Menu...\n");
            delayTime();
            break;
        }
    }

}


void printComparison(int dIndex, int mIndex) {
    printf("\n=== Price Comparison ===\n");

    for (int p = 0; p < districts[dIndex].markets[mIndex].productCount; p++) {
        Product *current_product = &districts[dIndex].markets[mIndex].products[p];

        float maxPrice = current_product->price[0];
        float minPrice = current_product->price[0];
        int maxDay = 1, minDay = 1;
        float sum = current_product->price[0];

        for (int l = 1; l < 7; l++) {
            if (current_product->price[l] > maxPrice) {
                maxPrice = current_product->price[l];
                maxDay = l + 1;
            }
            if (current_product->price[l] < minPrice) {
                minPrice = current_product->price[l];
                minDay = l + 1;
            }
            sum += current_product->price[l];
        }

        float avg = sum / 7.0;

        printf("Product[%02d]-%-15s | Highest: %.2f (Day %d) | Lowest: %.2f (Day %d) | Avg: %.2f\n |",
               p + 1, current_product->name, maxPrice, maxDay, minPrice, minDay, avg);
    }
}


void compareData() {
    int choice;
    int dIndex, mIndex;
    char confirm;

    if(districtCount == 0) {
        printf("No districts found\n");
        delayTime();
        return;
    }

    while(1) {
        system("clear");
        greeting();
        printf("== Compare Data ==\n");
        printf("[1] Select district/market/product\n");
        printf("[0] Cancel\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        clearInputBuffer();
        if(choice == 0)
            return;
        else if(choice == 1)
            break;
    }

    while(1) {
        system("clear");
        greeting();
        printf("=== Compare Data ===\n");
        printf("----- Districts -----\n");

        for (int d = 0; d < districtCount; d++) {
            printf("[%d] %s\n", d + 1, districts[d].name);
        }
        printf("\n[*] Select district: ");
        scanf("%d", &dIndex);
        dIndex--;
        if (dIndex < 0 || dIndex >= districtCount) {
            printf("Invalid district selected.\n");
            delayTime();
            break;
        }
        clearInputBuffer();

        if (districts[dIndex].marketCount == 0) {
            printf("No markets available in this district.\n");
            delayTime();
            break;
        }

        system("clear");
        greeting();
        printf("----- Districts -----\n");
        printf("======= District[%02d]-%s ==========\n", dIndex+1, districts[dIndex].name);
        printf("----- Markets -----\n");

        for (int m = 0; m < districts[dIndex].marketCount; m++) {
            printf("[%d] %s\n", m + 1, districts[dIndex].markets[m].name);
        }
        printf("[*] Select market: ");
        scanf("%d", &mIndex);
        mIndex--;
        if (mIndex < 0 || mIndex >= districts[dIndex].marketCount) {
            printf("Invalid market selected.\n");
            delayTime();
            break;
        }
        clearInputBuffer();

        if (districts[dIndex].markets[mIndex].productCount == 0) {
            printf("No products available in this market.\n");
            delayTime();
            break;
        }

        printFoundData(dIndex, mIndex);

        printComparison(dIndex, mIndex);

        printf("\nDo you want to compare more data? [y/n]: ");
        scanf("%c", &confirm);
        clearInputBuffer();
        if(confirm == 'y' || confirm == 'Y')
            continue;
        else
            break;
    }
}
