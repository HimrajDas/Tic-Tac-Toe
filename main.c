#include <stdio.h>

void printBoard(char array[3][3]);
int isWon(int row, int col, char array[row][col]);
void greeting();

int main() {

    
    char array[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };
    char x = 'x';
    char o = 'o';
    char *address;
    int max_input = 9;
    int user_state = 0;

    greeting();

    while (max_input != 0)
    {   
        int num;
        printf("Enter the positon (1-9): ");
        scanf("%d", &num);

        if (num < 1 || num > 9) {
            printf("Invalid input. Please enter a number between 1-9.\n");
            continue;
        }

        switch (num) {
        case 1:
            address = &array[0][0];
            break;
        case 2:
            address = &array[0][1];
            break;
        case 3:
            address = &array[0][2];
            break;
        case 4:
            address = &array[1][0];
            break;
        case 5:
            address = &array[1][1];
            break;
        case 6:
            address = &array[1][2];
            break;
        case 7:
            address = &array[2][0];
            break;
        case 8:
            address = &array[2][1];
            break;
        case 9:
            address = &array[2][2];
        default:
            break;
        }

        // TODO: Handle the case if user provides same number twice.


        *address = (user_state == 0) ? x : o;  // managing the user state to switch between players.

        if (isWon(3, 3, array) == 1) {
            printBoard(array);
            printf("Player %d won!\n", user_state);
            break;
        }

        //  Managing the player state to switch between both players.
        if (user_state == 0) user_state = 1;
        else user_state = 0;

        printBoard(array);
        max_input--;
        if (max_input == 0) printf("DRAW!!");
    }
    
    return 0;
}


void printBoard(char array[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("| %c ", array[i][j]);
        }
        printf("|\n");
        printf("+---+---+---+\n");
    }
}


int isWon(int row, int col, char array[row][col]) {

    // row wise.
    for (int i = 0; i < row; i++) {
        int by_row = 1;
        for (int j = 0; j < col - 1; j++) {
            if (
                (by_row && (array[i][j] == 'x' && array[i][j + 1] == 'x')) ||
                (by_row && (array[i][j] == 'o' && array[i][j + 1] == 'o'))
            ) by_row = 1;
            else by_row = 0;
        }
        if (by_row == 1) return by_row;
    }


    // column wise.
    for (int i = 0; i < row; i++) {
        int by_col = 1;
        for (int j = 0; j < col - 1; j++) {
            if (
                (by_col && (array[j][i] == 'x' && array[j + 1][i] == 'x')) ||
                (by_col && (array[j][i] == 'o' && array[j + 1][i] == 'o'))
            ) by_col = 1;
            else by_col = 0;
        }

        if (by_col == 1) return by_col;
    }

    // diagonal.
    if (array[0][0] == 'x') {
        int by_diag = 1;
        for (int i = 0; i < row; i++) {
            if (by_diag && (array[i][i] == 'x')) by_diag = 1;
            else by_diag = 0;
        }
        if (by_diag == 1) return by_diag;
    } else if (array[0][0] == 'o') {
        int by_diag = 1;
        for (int i = 0; i < row; i++) {
            if (by_diag && (array[i][i] == 'o')) by_diag = 1;
            else by_diag = 0;
        }

        if (by_diag == 1) return by_diag;
    }


    // anti-diagonal.
    int max_col_index = col - 1;
    if (array[0][max_col_index] == 'x') {
        int by_antidiag = 1;
        for (int i = 0; i < row; i++) {
            if (by_antidiag && (array[i][max_col_index] == 'x')) by_antidiag = 1;
            else by_antidiag = 0;
            max_col_index--;
        }
        if (by_antidiag == 1) return by_antidiag;
    } else if (array[0][max_col_index] == 'o') {
        int by_antidiag = 1;
        for (int i = 0; i < row; i++) {
            if (by_antidiag && (array[i][max_col_index] == 'o')) by_antidiag = 1;
            else by_antidiag = 0;
            max_col_index--;
        }
        if (by_antidiag == 1) return by_antidiag;
    }


    return 0;
}


void greeting() {
    printf("________________________________________________________________________________\n");
    printf("\\\\      //\\\\      // |||||||||  ||      ||||||||   |||||||||     ||\\\\    //||  |||||||\n");
    printf(" \\\\    //  \\\\    //  ||         ||      ||        ||       ||    || \\\\  // ||  ||\n");
    printf("  \\\\  //    \\\\  //   |||||||    ||      ||        ||       ||    ||  \\\\//  ||  |||||||\n");
    printf("   \\\\//      \\\\//    ||         ||      ||        ||       ||    ||        ||  ||\n");
    printf("    \\/        \\/     |||||||||  ||||||  ||||||||   |||||||||     ||        ||  |||||||\n");
    printf("\n");
    printf("                                                                             ----\n");
    printf("                |||||||||| |||||||||   |||||||||| || ||||||    ||||||||||   //   \\\\  |||||||      |||||||||| |||||||| ||||||||||  \n");
    printf("                    ||     ||     ||       ||     || ||            ||      //     || ||               ||     ||    || ||          \n");
    printf("                    ||     ||     ||       ||     || ||            ||      ||     || ||               ||     ||    || ||||||||||  \n");
    printf("                    ||     ||     ||       ||     || ||            ||      ||     || ||               ||     ||    || ||          \n");
    printf("                    ||     |||||||||       ||     || ||||||        ||      ||     || |||||||          ||     |||||||| ||||||||||  \n");
    printf("________________________________________________________________________________\n");
}



