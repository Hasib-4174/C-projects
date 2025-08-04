#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"extra.h"
#include<unistd.h>

char *loadDistrict[50] = {"Dhaka", "Chittagong", "Dinajpur", "Jashore", "Noakhali"};

void loadData() {
    srand(time(NULL));
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