#include <stdio.h>
#include <stdbool.h>
#define TRUE 1 
#define FALSE 0
#define FREE 1
#define OCC 1

typedef int set3[3];

int flipBool(int val) // flips the value every turn
{
    val ^= 1;
    return val;
}

int getInput(const char* prompt, int min, int max) {
    int value;
    do {
        printf("%s", prompt);
        scanf("%d", &value);
        if (value < min || value > max) {
            printf("Invalid input. Please enter a value between %d and %d.\n", min, max);
        }
    } while (value < min || value > max);
    return value;
}

void GetInput(int* row, int* col, int* peg) {
    *row = getInput("Enter the row (1-3): ", 1, 3);
    *col = getInput("Enter the column (1-3): ", 1, 3);
    *peg = getInput("Enter the peg (1-9): ", 1, 9);

    printf("\n");
    printf("-----------------\n");
    printf("\n");
}


int CheckPeg(int Peg[], int peg) // checks if the peg exists in the set Peg
{
	int i;
    for ( i = 0; i < 9; i++) {
        if (peg == Peg[i]) {
            return 1; // Return true (1) as soon as the peg is found
        }
    }
    return 0; // Return false (0) if the peg was not found
}

bool isPegInSet(int Peg[], int peg) // checks if the peg exists in the set Peg
{
	int i;
    for (i = 0; i < 9; i++) {
        if (peg == Peg[i]) {
            return true; // Return true as soon as the peg is found
        }
    }
    return false; // Return false if the peg was not found
}

bool isFreeAndNotOccupied(int Free[][3], int Occ[][3], int row, int col) // checks if (row, col) is FREE and (row, col) is not OCC
{
    bool isFree = (Free[row - 1][col - 1] == FREE);
    bool isNotOccupied = (Occ[row - 1][col - 1] != OCC);

    return isFree && isNotOccupied;
}

void AddPegtoSet(int A[3], int peg) // adds the peg to One, Two, Three, Four, Five, Six
{
	int i;
    for ( i = 0; i < 3; i++) 
    {
        if (A[i] == 0) 
        {
            A[i] = peg;
            break; // Stop the loop once the peg is added
        }
    }
}


	
void DisplayBoard(int Board[][3]) // displays the Board
{
	int i, j;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            printf("|%d", Board[i][j]);
        }
        printf("|\n");
    }
    printf("\n");
}

void RemovePeg(int Peg[], int peg) // removes the peg from the available pegs
{
    int i;
    for (i = 0; i < 9; i++) {
        if (Peg[i] == peg) {
            Peg[i] = 0; // Set the peg value to 0 to remove it
            break; // Stop the loop once the peg is removed
        }
    }
}

void NextPlayerMove(int Board[][3], int Free[][3], int Occ[][3], int Peg[], set3 One, set3 Two, set3 Three, set3 Four, set3 Five, set3 Six)
{
    bool isMoveValid = false;
    int isPegValid, isPositionValid;
    int row, col, peg;
    
    DisplayBoard(Board);

    while (!isMoveValid)
    {
        GetInput(&row, &col, &peg);
        isPegValid = CheckPeg(Peg, peg);
        isPositionValid = isFreeAndNotOccupied(Free, Occ, row, col);
        
        if (!isPegValid)
        {
            printf("Peg is Taken! Try Again\n");
        }
        if (!isPositionValid)
        {
            printf("Position is taken! Try Again\n");
        }
        else if (isPositionValid && isPegValid)
        {
            Board[row - 1][col - 1] = peg;
            RemovePeg(Peg, peg);
            Free[row - 1][col - 1] = flipBool(FREE);
            Occ[row - 1][col - 1] = OCC;
            isMoveValid = true;
        }
    }

    // Add peg to the appropriate set based on row and column
    if (isMoveValid)
    {
        switch (row)
        {
            case 1: AddPegtoSet(One, peg); break;
            case 2: AddPegtoSet(Two, peg); break;
            case 3: AddPegtoSet(Three, peg); break;
        }

        switch (col)
        {
            case 1: AddPegtoSet(Four, peg); break;
            case 2: AddPegtoSet(Five, peg); break;
            case 3: AddPegtoSet(Six, peg); break;
        }
    }
}



int CountVal(int A[]) // counts how many 0s are before it adds everything
{
	int i;
	int Count = 0;
	for(i=0; i<3; i++)
	{
		if(A[i] > 0)
		{
			Count++;
		}
	}
	return Count;
}
int Summation(int A[]) // gets the summation of all the values in the Array
{
    int sum = 0;
    int i;
    for ( i = 0; i < 3; i++) 
	{
        sum += A[i];
    }
    return sum;
}



int GameOver(int turn, int over, set3 One, set3 Two, set3 Three, set3 Four, set3 Five, set3 Six)
{
	int flag = FALSE;
	if(CountVal(One) == 3 && Summation(One) < 15) // checks if there are no 0s in Array and if the Summation is less than 15
	{
		if(turn==TRUE)
		{
			printf("Player B wins!\n");
			flag = TRUE;
		}
		else if(turn==FALSE)
		{
			printf("Player A wins!\n");
			flag = TRUE;

		}
	}
	else if(CountVal(Two) == 3 && Summation(Two) < 15)
	{
		if(turn==TRUE)
		{
			printf("Player B wins!\n");
			flag = TRUE;
		}
		else if(turn==FALSE)
		{
			printf("Player A wins!\n");
			flag = TRUE;
		}
	}
	else if(CountVal(Three) == 3 && Summation(Three) < 15)
	{
		if(turn==TRUE)
		{
			printf("Player B wins!\n");
			flag = TRUE;
		}
		else if(turn==FALSE)
		{
			printf("Player A wins!\n");
			flag = TRUE;
		}	
	}
	else if(CountVal(Four) == 3 && Summation(Four) < 15)
	{
		if(turn==TRUE)
		{
			printf("Player B wins!\n");
			flag = TRUE;
		}
		else if(turn==FALSE)
		{
			printf("Player A wins!\n");
			flag = TRUE;
		}	
	}
	else if(CountVal(Five) == 3 && Summation(Five) < 15)
	{
		if(turn==TRUE)
		{
			printf("Player B wins!\n");
			flag = TRUE;
		}
		else if(turn==FALSE)
		{
			printf("Player A wins!\n");
			flag = TRUE;
		}	
	}	
	else if(CountVal(Six) == 3 && Summation(Six) < 15)
	{
		if(turn==TRUE)
		{
			printf("Player B wins!\n");
			flag = TRUE;
		}
		else if(turn==FALSE)
		{
			printf("Player A wins!\n");
			flag = TRUE;
		}	
	}
	else if(Summation(One) == 15 && Summation(Two) == 15 && Summation (Three) == 15 && Summation(Four) == 15 && Summation(Five) == 15 && Summation (Six) == 15 && CountVal(One) == 3 && CountVal(Two) == 3 && CountVal(Three) == 3 && CountVal(Four) == 3 && CountVal(Five) == 3 && CountVal(Six) == 3) 
	{
		if(turn==TRUE)
		{
			printf("Player A wins!\n");
			flag = TRUE;
		}
		else if(turn==FALSE)
		{
			printf("Player B wins!\n");
			flag = TRUE;
		}	
	}
return flag;
}

void RemainingPeg(int A[9]) 
{
    int B[9];
    int count = 0;
    int i;
    for (i = 0; i < 9; i++) 
	{
    	
        if (A[i] != 0) {
            B[count] = A[i];
            count++;
        }
    }
    printf("Remaining Pegs: %d\n", count);

    for (i = 0; i < count; i++) 
	{
        printf("%d", B[i]);
        if (i != count - 1) {
            printf(",");
        }
    }
    printf("\n\n");

}

int main()
{
int Board[3][3] = {};
int Free[3][3] = {{FREE, FREE,FREE},{FREE, FREE,FREE},{FREE, FREE,FREE}}; // if FREE, peg can be placed in (row, col). If Peg is placed FREE will be false.
int Occ[3][3] = {{!OCC, !OCC, !OCC},{!OCC, !OCC, !OCC}, {!OCC, !OCC, !OCC}}; // if OCC, peg cannot be placed in (row, col). If peg was placed in a FREE (row, col), OCC will then be true. 
int Peg[9] = {1,2,3,4,5,6,7,8,9};
int over = FALSE;
int turn = TRUE; 
set3 One = {};
set3 Two = {};
set3 Three = {};
set3 Four = {};
set3 Five= {};
set3 Six = {};

while(over == FALSE)
{
if(turn==TRUE) 
		{
			printf("Player A's turn\n");
			RemainingPeg(Peg);
		}
else if(turn==FALSE)
		{
			printf("Player B's turn\n");
			RemainingPeg(Peg);
		}
NextPlayerMove(Board, Free, Occ, Peg, One, Two, Three, Four, Five, Six);
over = GameOver(turn, over, One, Two, Three, Four, Five, Six);
if(over == FALSE) // prints the Taken Pegs, Remaining Pegs, and flips the turn
{
//DisplayTakenPegs(One, Two, Three, Four, Five, Six);
turn = flipBool(turn);
}
}
DisplayBoard(Board);
return 0;
}

