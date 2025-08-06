#ifndef UTILS_H
#define UTILS_H


#define MAX_DISTRICT 64
#define MAX_MARKET 20
#define MAX_PRODUCT 15


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
    int marketCount;
} District;

extern District districts[MAX_DISTRICT];
extern int districtCount;

void addDistrict();
void addMarket();
void addProduct();
void printData();

#endif