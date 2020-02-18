#include<bits/stdc++.h>
using namespace std;

#define ROW 9
#define COL 10


typedef pair<int, int> Pair;


typedef pair<double, pair<int, int> > pPair;

struct cell
{
	int parent_i, parent_j;
	double f, g, h;
};

//to check if the given cell is
bool isValid(int row, int col)
{
	// Returns true if row number and column number
	// is in range
	return (row >= 0) && (row < ROW) &&
		(col >= 0) && (col < COL);
}
//checking if cell is blocked or not
bool isUnBlocked(int grid[][COL], int row, int col)
{

	if (grid[row][col] == 1)
		return (true);
	else
		return (false);
}

// checking if we have reached destination
bool isDestination(int row, int col, Pair dest)
{
	if (row == dest.first && col == dest.second)
		return (true);
	else
		return (false);
}

//checking h value using euclid's distance formula
double calculateHValue(int row, int col, Pair dest)
{
	// distance formula
	return ((double)sqrt ((row-dest.first)*(row-dest.first)
						+ (col-dest.second)*(col-dest.second)));
}

// tracing the path from src to destination and printing it
void tracePath(cell cellDetails[][COL], Pair dest)
{
	printf ("\nThe Path is ");
	int row = dest.first;
	int col = dest.second;

	stack<Pair> Path;// declaring a stack which holds the path

	while (!(cellDetails[row][col].parent_i == row
			&& cellDetails[row][col].parent_j == col ))// pushing pairs until we reach the source pair
	{
		Path.push (make_pair (row, col));
		int temp_row = cellDetails[row][col].parent_i;
		int temp_col = cellDetails[row][col].parent_j;
		row = temp_row;
		col = temp_col;
	}

	Path.push (make_pair (row, col));// pushing parent pair of previously pushed pair
	while (!Path.empty())
	{
		pair<int,int> p = Path.top();
		Path.pop();
		printf("-> (%d,%d) ",p.first,p.second);// printing the path from top
	}

	return;
}

// a* algorithm itself
void aStarSearch(int grid[][COL], Pair src, Pair dest)
{
	// If the source is out of range
	if (isValid (src.first, src.second) == false)
	{
		printf ("Source is invalid\n");
		return;
	}

	// If the destination is out of range
	if (isValid (dest.first, dest.second) == false)
	{
		printf ("Destination is invalid\n");
		return;
	}

	// Either the source or the destination is blocked
	if (isUnBlocked(grid, src.first, src.second) == false ||
			isUnBlocked(grid, dest.first, dest.second) == false)
	{
		printf ("Source or the destination is blocked\n");
		return;
	}

	// If the destination cell is the same as source cell
	if (isDestination(src.first, src.second, dest) == true)
	{
		printf ("We are already at the destination\n");
		return;
	}

	//closed list which represents elements
	bool closedList[ROW][COL];
	memset(closedList, false, sizeof (closedList));
     // 2d array that stores details of each cell
	cell cellDetails[ROW][COL];

	int i, j;

	for (i=0; i<ROW; i++)
	{
		for (j=0; j<COL; j++)
		{
			cellDetails[i][j].f = FLT_MAX;     //initialising f to be infinity for all cells and making parent as -1,-1
			cellDetails[i][j].g = FLT_MAX;
			cellDetails[i][j].h = FLT_MAX;
			cellDetails[i][j].parent_i = -1;
			cellDetails[i][j].parent_j = -1;
		}
	}

	// Initialising the parameters of the starting node
	i = src.first, j = src.second;
	cellDetails[i][j].f = 0.0;
	cellDetails[i][j].g = 0.0;
	cellDetails[i][j].h = 0.0;
	cellDetails[i][j].parent_i = i;
	cellDetails[i][j].parent_j = j;

	// creating open list which has adjacent members from the current node
	set<pPair> openList;

	// inserting source into open list
	openList.insert(make_pair (0.0, make_pair (i, j)));

	//initialising found_destination to be false
	bool foundDest = false;

	while (!openList.empty())// we continue the process until open list is empty that is
	{
		pPair p = *openList.begin();

		// Remove this vertex from the open list
		openList.erase(openList.begin());

		// Add this vertex to the closed list
		i = p.second.first;
		j = p.second.second;
		closedList[i][j] = true;



		// To store the 'g', 'h' and 'f' of the 8 successors
		double gNew, hNew, fNew;

		// 1st Successor (North)

		// Only process this cell if this is a valid one
		if (isValid(i-1, j) == true)
		{
			// If the destination cell is the same as the
			// current successor
			if (isDestination(i-1, j, dest) == true)
			{
				// Set the Parent of the destination cell
				cellDetails[i-1][j].parent_i = i;
				cellDetails[i-1][j].parent_j = j;
				printf ("The destination cell is found\n");
				tracePath (cellDetails, dest);
				foundDest = true;
				return;
			}
			// If the successor is already on the closed
			// list or if it is blocked, then ignore it.
			// Else do the following
			else if (closedList[i-1][j] == false &&
					isUnBlocked(grid, i-1, j) == true)
			{
				gNew = cellDetails[i][j].g + 1.0;
				hNew = calculateHValue (i-1, j, dest);
				fNew = gNew + hNew;


				if (cellDetails[i-1][j].f == FLT_MAX ||
						cellDetails[i-1][j].f > fNew)
				{
					openList.insert( make_pair(fNew,
											make_pair(i-1, j)));

					// Update the details of this cell
					cellDetails[i-1][j].f = fNew;
					cellDetails[i-1][j].g = gNew;
					cellDetails[i-1][j].h = hNew;
					cellDetails[i-1][j].parent_i = i;
					cellDetails[i-1][j].parent_j = j;
				}
			}
		}

		//----------- 2nd Successor (South) ------------

		// Only process this cell if this is a valid one
		if (isValid(i+1, j) == true)
		{
			// If the destination cell is the same as the
			// current successor
			if (isDestination(i+1, j, dest) == true)
			{
				// Set the Parent of the destination cell
				cellDetails[i+1][j].parent_i = i;
				cellDetails[i+1][j].parent_j = j;
				printf("The destination cell is found\n");
				tracePath(cellDetails, dest);
				foundDest = true;
				return;
			}
			// If the successor is already on the closed
			// list or if it is blocked, then ignore it.
			// Else do the following
			else if (closedList[i+1][j] == false &&
					isUnBlocked(grid, i+1, j) == true)
			{
				gNew = cellDetails[i][j].g + 1.0;
				hNew = calculateHValue(i+1, j, dest);
				fNew = gNew + hNew;

				// If it isn’t on the open list, add it to
				// the open list. Make the current square
				// the parent of this square. Record the
				// f, g, and h costs of the square cell
				//			 OR
				// If it is on the open list already, check
				// to see if this path to that square is better,
				// using 'f' cost as the measure.
				if (cellDetails[i+1][j].f == FLT_MAX ||
						cellDetails[i+1][j].f > fNew)
				{
					openList.insert( make_pair (fNew, make_pair (i+1, j)));
					// Update the details of this cell
					cellDetails[i+1][j].f = fNew;
					cellDetails[i+1][j].g = gNew;
					cellDetails[i+1][j].h = hNew;
					cellDetails[i+1][j].parent_i = i;
					cellDetails[i+1][j].parent_j = j;
				}
			}
		}

		//----------- 3rd Successor (East) ------------

		// Only process this cell if this is a valid one
		if (isValid (i, j+1) == true)
		{
			// If the destination cell is the same as the
			// current successor
			if (isDestination(i, j+1, dest) == true)
			{
				// Set the Parent of the destination cell
				cellDetails[i][j+1].parent_i = i;
				cellDetails[i][j+1].parent_j = j;
				printf("The destination cell is found\n");
				tracePath(cellDetails, dest);
				foundDest = true;
				return;
			}

			// If the successor is already on the closed
			// list or if it is blocked, then ignore it.
			// Else do the following
			else if (closedList[i][j+1] == false &&
					isUnBlocked (grid, i, j+1) == true)
			{
				gNew = cellDetails[i][j].g + 1.0;
				hNew = calculateHValue (i, j+1, dest);
				fNew = gNew + hNew;

				// If it isn’t on the open list, add it to
				// the open list. Make the current square
				// the parent of this square. Record the
				// f, g, and h costs of the square cell
				//			 OR
				// If it is on the open list already, check
				// to see if this path to that square is better,
				// using 'f' cost as the measure.
				if (cellDetails[i][j+1].f == FLT_MAX ||
						cellDetails[i][j+1].f > fNew)
				{
					openList.insert( make_pair(fNew,
										make_pair (i, j+1)));

					// Update the details of this cell
					cellDetails[i][j+1].f = fNew;
					cellDetails[i][j+1].g = gNew;
					cellDetails[i][j+1].h = hNew;
					cellDetails[i][j+1].parent_i = i;
					cellDetails[i][j+1].parent_j = j;
				}
			}
		}

		//----------- 4th Successor (West) ------------

		// Only process this cell if this is a valid one
		if (isValid(i, j-1) == true)
		{
			// If the destination cell is the same as the
			// current successor
			if (isDestination(i, j-1, dest) == true)
			{
				// Set the Parent of the destination cell
				cellDetails[i][j-1].parent_i = i;
				cellDetails[i][j-1].parent_j = j;
				printf("The destination cell is found\n");
				tracePath(cellDetails, dest);
				foundDest = true;
				return;
			}

			// If the successor is already on the closed
			// list or if it is blocked, then ignore it.
			// Else do the following
			else if (closedList[i][j-1] == false &&
					isUnBlocked(grid, i, j-1) == true)
			{
				gNew = cellDetails[i][j].g + 1.0;
				hNew = calculateHValue(i, j-1, dest);
				fNew = gNew + hNew;

				// If it isn’t on the open list, add it to
				// the open list. Make the current square
				// the parent of this square. Record the
				// f, g, and h costs of the square cell
				//			 OR
				// If it is on the open list already, check
				// to see if this path to that square is better,
				// using 'f' cost as the measure.
				if (cellDetails[i][j-1].f == FLT_MAX ||
						cellDetails[i][j-1].f > fNew)
				{
					openList.insert( make_pair (fNew,
										make_pair (i, j-1)));

					// Update the details of this cell
					cellDetails[i][j-1].f = fNew;
					cellDetails[i][j-1].g = gNew;
					cellDetails[i][j-1].h = hNew;
					cellDetails[i][j-1].parent_i = i;
					cellDetails[i][j-1].parent_j = j;
				}
			}
		}

		//----------- 5th Successor (North-East) ------------

		// Only process this cell if this is a valid one
		if (isValid(i-1, j+1) == true)
		{
			// If the destination cell is the same as the
			// current successor
			if (isDestination(i-1, j+1, dest) == true)
			{
				// Set the Parent of the destination cell
				cellDetails[i-1][j+1].parent_i = i;
				cellDetails[i-1][j+1].parent_j = j;
				printf ("The destination cell is found\n");
				tracePath (cellDetails, dest);
				foundDest = true;
				return;
			}

			// If the successor is already on the closed
			// list or if it is blocked, then ignore it.
			// Else do the following
			else if (closedList[i-1][j+1] == false &&
					isUnBlocked(grid, i-1, j+1) == true)
			{
				gNew = cellDetails[i][j].g + 1.414;
				hNew = calculateHValue(i-1, j+1, dest);
				fNew = gNew + hNew;

				// If it isn’t on the open list, add it to
				// the open list. Make the current square
				// the parent of this square. Record the
				// f, g, and h costs of the square cell
				//			 OR
				// If it is on the open list already, check
				// to see if this path to that square is better,
				// using 'f' cost as the measure.
				if (cellDetails[i-1][j+1].f == FLT_MAX ||
						cellDetails[i-1][j+1].f > fNew)
				{
					openList.insert( make_pair (fNew,
									make_pair(i-1, j+1)));

					// Update the details of this cell
					cellDetails[i-1][j+1].f = fNew;
					cellDetails[i-1][j+1].g = gNew;
					cellDetails[i-1][j+1].h = hNew;
					cellDetails[i-1][j+1].parent_i = i;
					cellDetails[i-1][j+1].parent_j = j;
				}
			}
		}

		//----------- 6th Successor (North-West) ------------

		// Only process this cell if this is a valid one
		if (isValid (i-1, j-1) == true)
		{
			// If the destination cell is the same as the
			// current successor
			if (isDestination (i-1, j-1, dest) == true)
			{
				// Set the Parent of the destination cell
				cellDetails[i-1][j-1].parent_i = i;
				cellDetails[i-1][j-1].parent_j = j;
				printf ("The destination cell is found\n");
				tracePath (cellDetails, dest);
				foundDest = true;
				return;
			}

			// If the successor is already on the closed
			// list or if it is blocked, then ignore it.
			// Else do the following
			else if (closedList[i-1][j-1] == false &&
					isUnBlocked(grid, i-1, j-1) == true)
			{
				gNew = cellDetails[i][j].g + 1.414;
				hNew = calculateHValue(i-1, j-1, dest);
				fNew = gNew + hNew;

				// If it isn’t on the open list, add it to
				// the open list. Make the current square
				// the parent of this square. Record the
				// f, g, and h costs of the square cell
				//			 OR
				// If it is on the open list already, check
				// to see if this path to that square is better,
				// using 'f' cost as the measure.
				if (cellDetails[i-1][j-1].f == FLT_MAX ||
						cellDetails[i-1][j-1].f > fNew)
				{
					openList.insert( make_pair (fNew, make_pair (i-1, j-1)));
					// Update the details of this cell
					cellDetails[i-1][j-1].f = fNew;
					cellDetails[i-1][j-1].g = gNew;
					cellDetails[i-1][j-1].h = hNew;
					cellDetails[i-1][j-1].parent_i = i;
					cellDetails[i-1][j-1].parent_j = j;
				}
			}
		}

		//----------- 7th Successor (South-East) ------------

		// Only process this cell if this is a valid one
		if (isValid(i+1, j+1) == true)
		{
			// If the destination cell is the same as the
			// current successor
			if (isDestination(i+1, j+1, dest) == true)
			{
				// Set the Parent of the destination cell
				cellDetails[i+1][j+1].parent_i = i;
				cellDetails[i+1][j+1].parent_j = j;
				printf ("The destination cell is found\n");
				tracePath (cellDetails, dest);
				foundDest = true;
				return;
			}

			// If the successor is already on the closed
			// list or if it is blocked, then ignore it.
			// Else do the following
			else if (closedList[i+1][j+1] == false &&
					isUnBlocked(grid, i+1, j+1) == true)
			{
				gNew = cellDetails[i][j].g + 1.414;
				hNew = calculateHValue(i+1, j+1, dest);
				fNew = gNew + hNew;

				// If it isn’t on the open list, add it to
				// the open list. Make the current square
				// the parent of this square. Record the
				// f, g, and h costs of the square cell
				//			 OR
				// If it is on the open list already, check
				// to see if this path to that square is better,
				// using 'f' cost as the measure.
				if (cellDetails[i+1][j+1].f == FLT_MAX ||
						cellDetails[i+1][j+1].f > fNew)
				{
					openList.insert(make_pair(fNew,
										make_pair (i+1, j+1)));

					// Update the details of this cell
					cellDetails[i+1][j+1].f = fNew;
					cellDetails[i+1][j+1].g = gNew;
					cellDetails[i+1][j+1].h = hNew;
					cellDetails[i+1][j+1].parent_i = i;
					cellDetails[i+1][j+1].parent_j = j;
				}
			}
		}

		//----------- 8th Successor (South-West) ------------

		// Only process this cell if this is a valid one
		if (isValid (i+1, j-1) == true)
		{
			// If the destination cell is the same as the
			// current successor
			if (isDestination(i+1, j-1, dest) == true)
			{
				// Set the Parent of the destination cell
				cellDetails[i+1][j-1].parent_i = i;
				cellDetails[i+1][j-1].parent_j = j;
				printf("The destination cell is found\n");
				tracePath(cellDetails, dest);
				foundDest = true;
				return;
			}

			// If the successor is already on the closed
			// list or if it is blocked, then ignore it.
			// Else do the following
			else if (closedList[i+1][j-1] == false &&
					isUnBlocked(grid, i+1, j-1) == true)
			{
				gNew = cellDetails[i][j].g + 1.414;
				hNew = calculateHValue(i+1, j-1, dest);
				fNew = gNew + hNew;

				// If it isn’t on the open list, add it to
				// the open list. Make the current square
				// the parent of this square. Record the
				// f, g, and h costs of the square cell
				//			 OR
				// If it is on the open list already, check
				// to see if this path to that square is better,
				// using 'f' cost as the measure.
				if (cellDetails[i+1][j-1].f == FLT_MAX ||
						cellDetails[i+1][j-1].f > fNew)
				{
					openList.insert(make_pair(fNew,
										make_pair(i+1, j-1)));

					// Update the details of this cell
					cellDetails[i+1][j-1].f = fNew;
					cellDetails[i+1][j-1].g = gNew;
					cellDetails[i+1][j-1].h = hNew;
					cellDetails[i+1][j-1].parent_i = i;
					cellDetails[i+1][j-1].parent_j = j;
				}
			}
		}
	}
// if we couldnt reach the destination
	if (foundDest == false)
		printf("Failed to find the Destination Cell\n");

	return;
}



int main()
{
	// initialising the grid
	int grid[ROW][COL] =
	{
		{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
		{ 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
		{ 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
		{ 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
		{ 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
		{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
		{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
		{ 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 }
	};


	Pair src = make_pair(0, 0);

	Pair dest = make_pair(8, 0);

	aStarSearch(grid, src, dest);

	return(0);
}
