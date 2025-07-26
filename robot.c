#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<unistd.h>
#define MAX 20


void printScreen(char ground[MAX][MAX], int n, int px, int py) {
    system("clear");
    printf("  Find treasure 󰦄 \n\n");
    int i, j;
    for(i=0;i<n;i++) {
        for(j=0;j<n;j++) {
            if(i==py && j==px)
                printf("  ");
            else
                printf(" %c ", ground[i][j]);
        }
        printf("\n");
    }

}
int absValue(int x) {
    return (x<0) ? -x : x;
}

int distance_Count(int px, int py, int x, int y) {
    return absValue(px-x) + absValue(py-y);
}


int main() {
    int i, j;
    int n;
    int px=0, py=0;
    int tx, ty;
    int bx, by;
    int hearts = 3;

    char ground[MAX][MAX];
    srand((unsigned int)time(NULL));

    printf("  Find treasure 󰦄 \n");

    do {
        printf("Enter ground size NxN (5 to 20): ");
        scanf("%d", &n);
        while(getchar() != '\n');
    } while(n>MAX || n<5);

    for(i=0;i<n;i++) {
        for(j=0;j<n;j++)
            ground[i][j] = '+';
    }

    do {
    bx = rand() % n;
    by = rand() % n;

    } while(bx==px && by==py);

    do {
        tx = rand() % n;
        ty = rand() % n;
    } while ((tx == bx && ty == by) || (tx==px && ty==py));

    ground[px][py] = '+';

    char move;
    while(1) {
        printScreen(ground, n, px, py);

        printf("Hearts: ");
        for(i=0;i<hearts;i++)
            printf("󱐮 ");
        printf("\n");

        int disT = distance_Count(px, py, tx, ty);
        int disB = distance_Count(px, py, bx, by);

        printf("Treasure is %d tiles away\n", disT);
        printf("Bomb is %d tiles away\n", disB);
        

        printf("Move left(a)/up(w)/down(s)/right(d) 'q' to quit: ");
        scanf(" %c", &move);
        while(getchar()!='\n');

        int x = px, y = py;
        printf("n: %d, px: %d, py: %d\n", n, x, y);

        if(move=='w' && y>0)
            y--; 
        if(move=='a' && x>0)
            x--;
        if(move=='s' && y<n-1)
            y++;
        if(move=='d' && x<n-1)
            x++;
        else if(move=='q')
            break;
        else
            printf("Invalid move\n");

        px = x;
        py = y;

        if(px==bx && py==by) {
            hearts--;
            if(hearts==0)
                break;
        }
        if(px==tx && py==ty)
            break;

    }

//    ground[by][bx] = '';
//    ground[ty][tx] = '󱉏';

//    printScreen(ground, n, -1, -1);

    system("clear");
    
    if(px==bx && py==by)
        printf("Oopsie! 󱚡 \n");
    else if(px==tx && py==ty)
        printf("CONGRATULATION 󱜙 \n");

    for(i=0;i<n;i++) {
        for(j=0;j<n;j++) {
            if(i==by && j==bx)
                printf("  ");
            else if(i==ty && j==tx)
                printf(" 󱉏 ");
            else
                printf(" %c ", ground[i][j]);
        }
        printf("\n");
    }

    if(px==bx && py==by) {
        printf("You are out of heart 󱐰 \n");
        printf("You lost 󱚡 \n");
    }
    else if(px==tx && py==ty)
        printf("You found the treasure 󱉏. You win  !!\n");
    

}
