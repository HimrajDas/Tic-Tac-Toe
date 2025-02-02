#include <stdio.h>
#include <string.h>

void printBoard(int size, char grid[size][size]);
int isWon(int row, int col, char grid[row][col]);
void greeting();

const int BUFFER_SIZE = 10;

int main()
{
    greeting();

    char *address;
    int user_state = 0;
    int size;
    char first_player[BUFFER_SIZE];
    char second_player[BUFFER_SIZE];
    char first_player_letter;  // either 'x' or 'o'
    char second_player_letter; // either 'x' or 'o'

    do {
        printf("Enter Grid Size: ");
        scanf("%d", &size);
        if (size < 3)
            printf("Grid Size Must Be Greater or Equal than 3.\n");
    } while (size < 3);

    char grid[size][size];

    int max_input = size * size;

    // filled the grid with empty spaces.
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            grid[i][j] = ' ';
        }
    }

    getchar(); // to consume the leftover \n of input buffer.

    // Take the player names.
    printf("Name of the first player: ");
    fgets(first_player, BUFFER_SIZE, stdin);

    // Removing the newline character if present
    first_player[strcspn(first_player, "\n")] = '\0';

    printf("Name of the second player: ");
    fgets(second_player, BUFFER_SIZE, stdin);

    // Removing the newline character if present
    second_player[strcspn(second_player, "\n")] = '\0';

    // Let the player choose a letter.
    do {
        printf("Pick letters: 'x' or 'o'\n");
        printf("Choose your letter %s: ", first_player);
        scanf(" %c", &first_player_letter);
    } while (
        (first_player_letter != 'x' && first_player_letter != 'o'));

    // Assigning letter to second player based on first player.
    second_player_letter = (first_player_letter == 'x') ? 'o' : 'x';

    char current_player[BUFFER_SIZE];  // player state.
    strcpy(current_player, first_player);

    printBoard(size, grid);

    while (max_input != 0)
    {
        int postion;
        if (strcmp(current_player, first_player) == 0) {
            printf("Turn: %s | Chosen Letter: %c | Postion Upto: 1-%d --> ", current_player, first_player_letter, size * size);
        } else {
            printf("Turn: %s | Chosen Letter: %c | Postion Upto: 1-%d --> ", current_player, second_player_letter, size * size);
        }
        scanf("%d", &postion);

        if (postion < 1 || postion > size * size)
        {
            printf("Invalid input. Please enter a number between 1-%d.\n", max_input);
            continue;
        }

        // Mapping postion to get the indexes.
        int m = 0, n = 0;
        int found = 0; // flag to indicate when to stop the loop.
        for (int i = 0; i < size && !found; i++) {
            for (int j = 0; j < size; j++) {
                n += 1;
                if (n == postion) {
                    m = i;
                    n = j;
                    found = 1;
                    break;
                }
            }
        }

        address = &grid[m][n];
        // Assigning letters to the players..
        if (*address == ' ') *address = (strcmp(current_player, first_player) == 0) ? first_player_letter : second_player_letter;
        else {
            printf("Invalid postion! Try agin.\n");
            continue;
        }

        if (isWon(size, size, grid) == 1)
        {
            printBoard(size, grid);
            printf("Bam! you won %s:)\n", current_player);
            break;
        }

        // Managing the player state to switch between both player.
        if (strcmp(current_player, first_player) == 0)
            strcpy(current_player, second_player);
        else
            strcpy(current_player, first_player);

        printBoard(size, grid);

        max_input--;
        if (max_input == 0)
            printf("DRAW!!");
    }

    return 0;
}

void printBoard(int size, char grid[size][size])
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf("| %c ", grid[i][j]);
        }
        printf("|\n");
        for (int k = 0; k < size; k++)
        {
            printf("+---");
        }
        printf("+\n");
    }
}

int isWon(int row, int col, char grid[row][col])
{

    // TODO: Refactor asshole.

    // row wise.
    for (int i = 0; i < row; i++) {
        int is_won = 1;
        for (int j = 0; j < col - 1; j++) {
            if (
                (is_won && (grid[i][j] == 'x' && grid[i][j + 1] == 'x')) ||
                (is_won && (grid[i][j] == 'o' && grid[i][j + 1] == 'o')) ||
                (is_won && (grid[j][i] == 'x' && grid[j + 1][i] == 'x')) ||
                (is_won && (grid[j][i] == 'o' && grid[j + 1][i] == 'o'))
            )
                is_won = 1;
            else is_won = 0;
        }
        if (is_won == 1) return is_won;
    }


    // diagonal.
    if (grid[0][0] == 'x') {
        int by_diag = 1;
        for (int i = 0; i < row; i++) {
            if (by_diag && (grid[i][i] == 'x')) by_diag = 1;
            else by_diag = 0;
        }

        if (by_diag == 1) return by_diag;
    }
    else if (grid[0][0] == 'o') {
        int by_diag = 1;
        for (int i = 0; i < row; i++) {
            if (by_diag && (grid[i][i] == 'o')) by_diag = 1;
            else by_diag = 0;
        }

        if (by_diag == 1) return by_diag;
    }

    // anti-diagonal.
    int max_col_index = col - 1;
    if (grid[0][max_col_index] == 'x') {
        int by_antidiag = 1;
        for (int i = 0; i < row; i++) {
            if (by_antidiag && (grid[i][max_col_index] == 'x')) by_antidiag = 1;
            else by_antidiag = 0;
            max_col_index--;
        }

        if (by_antidiag == 1) return by_antidiag;
    }
    else if (grid[0][max_col_index] == 'o') {
        int by_antidiag = 1;
        for (int i = 0; i < row; i++) {
            if (by_antidiag && (grid[i][max_col_index] == 'o')) by_antidiag = 1;
            else by_antidiag = 0;
            max_col_index--;
        }

        if (by_antidiag == 1) return by_antidiag;
    }

    return 0;
}

void greeting()
{
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
