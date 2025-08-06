#include"utils.h"
#include"extra.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>



void printData() {

    int i, j, k, l;
    for(i=0;i<districtCount;i++) {
        District *current_district = &districts[i];
        printf("========== District[%d]-%s ==========\n", i+1, current_district->name);
        for(j=0;j<districts[i].marketCount;j++) {
            Market *current_market = &current_district->markets[j];
            printf("----- Market[%d]-%s -----\n", j+1, current_market->name);
            for(k=0;k<districts[i].markets[j].productCount;k++) {
                Product *current_product = &current_market->products[k];
                printf("Product[%d]-%-15s | Prices: ", k+1, current_product->name);
                for(l=0;l<7;l++) {
                    printf("%5d |", current_product->price);
                }
                printf("\n");
            }
        }
    }
}