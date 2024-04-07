#include <iostream>
#include <unistd.h>
using namespace std;


#define X 20
#define Y 30


bool grid[Y][X];

void choose_next_tile(int, int);


int main(int argc, char** argv) {
    int x = 19,
        y = 9;

    grid[2][9] = true;

    for(int i=0; i<Y; i++) {
        for(int j=0; j<X; j++) {
            if(grid[i][j]) {
                printf("[X]");
            } else if((j == x) && (i == y)) {
                printf("< >");
            } else {
                printf("[ ]");
            }
        }
        printf("\n");            
    }
    sleep(3);
    
    choose_next_tile(x, y);
}


void choose_next_tile(int posX, int posY) {
    int size, move_to_max_x, perimeter, x, y,
        ans_x = -1,
        ans_y = -1;

    for(int ring=0; (ring<=X)&&(ring<=Y);ring++) {
        size = 3 + 2 * ring;
        move_to_max_x = 1 + ring;

        x = 0;
        y = -1 - ring;

        perimeter = size * 2 + size * 2 - 4;
        
        for(int n=0; n<perimeter; n++) {
            if((posX+x >= 0) && (posY+y >= 0) && (posX+x <= X) && (posY+y <= Y) && grid[posY+y][posX+x]) {
                ans_x = posX + x;
                ans_y = posY + y;
                break;
            }
            if((n < move_to_max_x) || (n >= (move_to_max_x + size * 3 - 3))) {
                x++;
            } else if(n < (move_to_max_x + size - 1)) {
                y++;
            } else if(n < (move_to_max_x + size * 2 - 2)) {
                x--;
            } else if(n < (move_to_max_x + size * 3 - 3)){
                y--;
            }
        }
        printf("x : %d, y : %d, ring : %d\n", ans_x, ans_y, ring);
        for(int y_inc=-1-ring; y_inc<(2+ring); y_inc++) {
            for(int x_inc=-1-ring; x_inc<(2+ring); x_inc++) {
                if((ans_x >= 0) && (ans_y >= 0) && (y_inc == (ans_y-posY)) && (x_inc == (ans_x-posX))) {
                    printf("[X]");
                } else if((y_inc == 0) && (x_inc == 0)) {
                    printf("< >");
                } else if((posY+y_inc > Y) || (posX+x_inc > X) || (posY+y_inc < 0) || (posX+x_inc < 0)) {
                    printf("[-]");
                } else {
                    printf("[ ]");
                }
            }
            printf("\n");
        }
        if((ans_x != -1) && (ans_y != -1))
            break;
        sleep(1);
    }
}