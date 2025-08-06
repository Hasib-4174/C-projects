#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"extra.h"
#include"utils.h"
#include<unistd.h>

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

    // Define constants for clarity
    const int markets_to_load = 15;
    const int products_to_load = 15;
    const int price_history_days = 7;

    
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