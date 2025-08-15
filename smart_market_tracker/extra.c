#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"extra.h"
#include"utils.h"
#include<unistd.h>
#include<ctype.h>

void greeting() {
    printf("╔════════════════════════╗\n");
    printf("║  SMART MARKET TRACKER  ║\n");
    printf("╚════════════════════════╝\n");
}

char *loadDistrict[5] = {"Dhaka", "Chittagong", "Dinajpur", "Jashore", "Noakhali"};
char *loadProduct[15] = {"Rice", "Flour", "Sugar", "Salt", "Lentils", "Cooking Oil",
    "Turmeric", "Onions", "Garlic", "Potatoes", "Tomatoes",
    "Chili Powder", "Cumin Seeds", "Mustard Oil", "Ginger"};
char *loadMarket[15] = {
    "Central Bazaar",
    "Green Valley Market",
    "New Town Market",
    "Golden Plaza",
    "City Super Mart",
    "Riverfront Market",
    "North Square",
    "Bazaar-e-Bangla",
    "People's Market",
    "Sunset Market",
    "Heritage Market",
    "Unity Trade Center",
    "Global Food Market",
    "Downtown Market",
    "East End Bazaar"
};

void loadData() {
    if (districtCount >= 5) {
        printf("All dummy districts have been loaded.\n");
        delayTime();
        return;
    }
    const int markets_to_load = 15;
    const int products_to_load = 15;
    const int price_history_days = 7;
    int i, j, k, l;
    srand(time(NULL));
    District *current_district = &districts[districtCount];
    strcpy(current_district->name, loadDistrict[districtCount]);
    
    current_district->marketCount = markets_to_load;

    for(j=0;j<markets_to_load;j++) {
        Market *current_market = &current_district->markets[j];
        strcpy(current_market->name, loadMarket[j]);
        current_market->productCount = products_to_load;

        for(k=0;k<products_to_load;k++) {
            Product *current_product = &current_market->products[k];
            strcpy(current_product->name, loadProduct[k]);
            for(l=0;l<price_history_days;l++) {
                int random_price = 70 + rand() % (150 - 70 + 1);
                current_product->price[l] = (float)random_price;
            }
        }
    }
    printf("Data loaded successfully for district %s\n", current_district->name);
    delayTime();
    districtCount++;
}

void clearInputBuffer() {
    int n;
    while((n = getchar() != '\n') && n != EOF);
}

void delayTime() {
    for(int i=0;i<4;i++) {
        printf(". ");
        usleep(500000);
        fflush(stdout);
    }
}

void toLowerStr(char *str) {
    for(int i=0;str[i]!='\0';i++)
        str[i] = tolower(str[i]);
}

/*
char *loadProducts[30] = {
    "Rice", "Flour", "Sugar", "Salt", "Lentils", "Cooking Oil",
    "Turmeric", "Onions", "Garlic", "Potatoes", "Tomatoes",
    "Chili Powder", "Cumin Seeds", "Mustard Oil", "Ginger",
    "Tea Leaves", "Milk Powder", "Bread", "Biscuits", "Soap",
    "Detergent", "Toothpaste", "Shampoo", "Eggs", "Chicken",
    "Beef", "Fish", "Bananas", "Apples", "Oranges"
};

char *marketNames[15] = {
    "Central Bazaar",
    "Green Valley Market",
    "New Town Market",
    "Golden Plaza",
    "City Super Mart",
    "Riverfront Market",
    "North Square",
    "Bazaar-e-Bangla",
    "People's Market",
    "Sunset Market",
    "Heritage Market",
    "Unity Trade Center",
    "Global Food Market",
    "Downtown Market",
    "East End Bazaar"
};

*/