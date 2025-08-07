#include"utils.h"
#include"extra.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>



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
        printf("Enter 'exit' go to Admin Menu: ");
        scanf("%s", prompt);
        if(strcmp(prompt, "exit")==0)
            break;
    }
}