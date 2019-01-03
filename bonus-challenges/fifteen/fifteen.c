/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */

#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void swap(int* a, int* b);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile;
        scanf("%d", &tile);

        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(50000);
        }

        // sleep thread for animation's sake
        usleep(50000);
    }

    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(200000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).
 */
void init(void)
{
    //declare value, row + column
    int value = (d*d) - 1, row, column;

    //initialize row loop
    for (row = 0; row < d; row++)
    {
        //initialize column loop
        for (column = d - 1; column >= 0; column--)
        {
            if (value == 0)
            {
                board[row][column] = '_';
                break;
            }

            else
            {
                board[row][column] = value;
                value--;
            }
        }
    }

    //swap 1 + 2 if board dimensions are even
    if (d % 2 == 0)
    {
        swap(&board[row-1][column+1], &board[row-1][column+2]);
    }

    //success
    return;
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    //initialize row loop
    for (int row = 0; row < d; row++)
    {
        //initialize column loop
        for (int column = d - 1; column >= 0; column--)
        {
            if (board[row][column] == '_')
            {
                printf(" %c   ", board[row][column]);
            }

            else if (board[row][column] > 9)
            {
                printf("%d   ", board[row][column]);
            }

            else
            {
                printf(" %d   ", board[row][column]);
            }
        }
        printf("\n\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false.
 */
bool move(int tile)
{
    //declare int temp
    int temp;

    //initialize row loop
    for (int row = 0; row < d; row++)
    {
        //initialize column loop
        for (int column = d - 1; column >= 0; column--)
        {
            if (board[row][column] == tile)
            {
                //if there is space to the left of cursor
                if (row > 0)
                {
                    if (board[row-1][column] == '_')
                    {
                        temp = board[row-1][column];
                        board[row-1][column] = board[row][column];
                        board[row][column] = temp;
                        return true;
                    }
                }

                //if there is space to the right of cursor
                if (row < d - 1)
                {
                    if (board[row+1][column] == '_')
                    {
                        temp = board[row+1][column];
                        board[row+1][column] = board[row][column];
                        board[row][column] = temp;
                        return true;
                    }
                }

                //if there is space above cursor
                if (column < d - 1)
                {
                    if (board[row][column+1] == '_')
                    {
                        temp = board[row][column+1];
                        board[row][column+1] = board[row][column];
                        board[row][column] = temp;
                        return true;
                    }
                }

                //if there is space below cursor
                if (column > 0)
                {
                    if (board[row][column-1] == '_')
                    {
                        temp = board[row][column-1];
                        board[row][column-1] = board[row][column];
                        board[row][column] = temp;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration),
 * else false.
 */
bool won(void)
{
    //initialize value;
    int value = 1;

    //initialize row loop
    for (int row = 0; row < d; row++)
    {
        //initialize column loop
        for (int column = d - 1; column >= 0; column--)
        {
            if (row == d - 1 && column == 0)
            {
                break;
            }

            else if (board[row][column] != value)
            {
                return false;
            }
            value++;
        }
    }
    return true;
}

//swaps two integers
void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;

    return;
}