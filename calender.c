#include<stdio.h>

void printCalender(int month, int year) {
    int i;
    int daysCount[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

    char monthsName[12][10] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };
    char weekNames[7][5] = {"Su", "Mo", "Tu", "We", "Th", "Fr", "Sa"};

    int y = year;
    int m = month;

    if((year%4==0&&year%100!=00) || year%400==0) {
        daysCount[1] = 29;
    }
    if(month==1||month==2) {
        m+=12;
        y--;
    }
    int q = 1;
    int k = y%100;
    int j = y/100;
    int h;

    h = (q + (13*(m+1)/5) + k + k/4 + j/4 + 5*j) % 7;
    int startDay = (h+6) % 7;
    int totalDays = daysCount[month-1];
    //printf("q:%d, m:%d, year: %d, k: %d, j: %d, h: %d, startDay: %d\n", q, month, year, k, j, h, startDay);

    printf("\n  %s  %d\n", monthsName[month-1], year);
    for(i=0;i<7;i++) {
        printf("%s ", weekNames[i]);
    }
    printf("\n");

    for(i=0;i<startDay;i++) {
        printf("   ");
    }

    for(i=1;i<=totalDays;i++) {
        printf("%2d ", i);
        if((startDay+i)%7==0)
            printf("\n");
    }
    printf("\n");


}

int main() {
    int month, year;
    printf("Enter year: ");
    scanf("%d", &year);
    printf("Enter month: ");
    scanf("%d", &month);


    printCalender(month, year);

    return 0;
}