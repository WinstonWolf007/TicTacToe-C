#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char letter[] = {'A', 'B', 'C'};

time_t t;

void displayMatrix(int matrix[3][3]) {

    // default variable
    int lenght = sizeof(matrix[0]) / sizeof(int);
    int last = 0;
    int last2 = 0;

    // row in matrix
    for (int i=0; i<lenght; i++) {

        printf("%d  ", i+1);

        // reset last2 value
        last2 = 0;

        if ((i+1) == lenght) {last = 1;}
        
        // column in matrix (in row)
        for (int j=0; j<3; j++) {

            if ((j+1) == 3) {last2 = 1;}
            
            // different symbol. 0 == " "; 1 == "x "; 2 == "o"
            if (matrix[i][j] == 0) {
                printf("   ");
            } else if (matrix[i][j] == 1) {
                printf(" x ");
            } else if (matrix[i][j] == 2) {
                printf(" o ");
            }

            // ends case
            if (!last2) {printf("|");}
        }

        // switch row
        printf("\n");

        if (!last) {printf("   ---o---o---\n");}
    }

    printf("\n    A   B   C \n\n");
}

int checkMatrix(int matrix[3][3]) {

    // win var
    int win_x = 0;
    int win_o = 0;

    // row win
    for (int rowWin=0; rowWin<3; rowWin++) {
        if (matrix[rowWin][0] == matrix[rowWin][1] && matrix[rowWin][0] == matrix[rowWin][2]) {
            if (matrix[rowWin][0] == 1) {
                win_x = 1;
            }
            else if (matrix[rowWin][0] == 2) {
                win_o = 1;
            }
        }
    }

    // column win
    for (int columnWin=0; columnWin<3; columnWin++) {
        if (matrix[0][columnWin] == matrix[1][columnWin] && matrix[0][columnWin] == matrix[2][columnWin]) {
            if (matrix[0][columnWin] == 1) {
                win_x = 1;
            }
            else if (matrix[0][columnWin] == 2) {
                win_o = 1;
            }
        }
    }

    // diagonal win
    for (int diagonalWin=0; diagonalWin<2; diagonalWin++) {
        if (diagonalWin == 0) {
            if (matrix[0][0] == matrix[1][1] && matrix[0][0] == matrix[2][2]) {
                if (matrix[0][0] == 1) {
                    win_x = 1;
                }
                else if (matrix[0][0] == 2) {
                    win_o = 1;
                }
            }
        }
        else {
            if (matrix[0][2] == matrix[1][1] && matrix[0][2] == matrix[2][0]) {
                if (matrix[0][2] == 1) {
                    win_x = 1;
                }
                else if (matrix[0][2] == 2) {
                    win_o = 1;
                }
            }
        }
    }

    // win message
    if (win_o) {
        printf("\n\n'o' won !!!\n\n\n");
        return 1;
    }
    else if (win_x) {
        printf("\n\n'x' won !!!\n\n\n");
        return 1;
    }
    else {
        return 0;
    }
}

int updateMatrix(int matrix[3][3], char choice[2]) {
    // get choice[0] index in letter array
    int idx = 0;
    for (idx; idx<3; idx++) {
        if (choice[0] == letter[idx]) {
            break;
        }
    }

    // get value from matrix position
    int caseValue = matrix[((int)(choice[1]-'0')-1)][idx];
    
    // verify if case is already busy
    if (caseValue == 1 || caseValue == 2) {
        return -1;
    }
    else {
        return idx;
    }
}

int checkUserInput(char input[2]) {
    // Verify if user input is correct [letter: uppercase][num]
    if (input[0] == 'A' || input[0] == 'B' || input[0] == 'C') {
        if (input[1] == '1' || input[1] == '2' || input[1] == '3') {
            return 1;
        }
    }
    return 0;
}

int botChoice(int matrix[3][3]) {
    int y;
    int x;

    // check all posibility in matrix. if is equal to 0. Pick this position
    while (1) {
        srand((unsigned) time(&t));

        y = rand() % 3;
        x = rand() % 3;

        if (matrix[y][x] == 0) {
            break;
        }
    }
    
    // convert string to int
    char s1 = y+'0';
    char s2 = x+'0';

    char s[2] = {s1, s2};

    return atoi(s);
}

int main() {
    // Matrix Map
    int matrix[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };


    // symbol code
    char playerSymbol;
    char allSymbol[2] = {'x', 'o'};
    int symbol = 1;
    int symbol2 = 2;

    printf("Choice symbol [x] or [o]: ");
    scanf("%c", &playerSymbol);

    if(playerSymbol != 'x' && playerSymbol != 'o') {
        printf("Invalid symbol !!!\n");
        return 0;
    }

    if (playerSymbol == allSymbol[1]) {
        symbol = 2;
        symbol2 = 1;
    }

    
    displayMatrix(matrix);


    while (1) {
        
        // get user code (Ex: A1, B3, C2, etc)
        char code[2];
        printf("> ");
        scanf(" %c%c", &code[0], &code[1]);

        // verify all input value
        char sBotChoice[2];

        if (checkUserInput(code)) {
            int correct = updateMatrix(matrix, code);
            if (correct != -1) {
                
                // change 0 to user symbol
                matrix[((int)(code[1]-'0')-1)][correct] = symbol;

                // bot choice in the matrix
                int iBotChoice = botChoice(matrix);
                sprintf(sBotChoice, "%d", iBotChoice);

                // change 0 to bot symbol
                matrix[(sBotChoice[0]-'0')][(sBotChoice[1]-'0')] = symbol2;

                // if bot or player win == break game loop
                if (checkMatrix(matrix)) {
                    break;
                }
            }
        }

        displayMatrix(matrix);
    }
    displayMatrix(matrix);

    return 0;
}