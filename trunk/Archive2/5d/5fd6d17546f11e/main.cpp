//  =============== BEGIN ASSESSMENT HEADER ================
/// @file percolate.cpp
/// @brief lab10/percolate
///
/// @author Tina Nagai [tnaga001@ucr.edu]
/// @date June 3, 2014
///
/// @par Plagiarism Section
/// I hereby certify that I have not received assistance on this assignment,
/// or used code, from ANY outside source other than the instruction team.
//  ================== END ASSESSMENT HEADER ===============


//        Requires grid file as input (input redirection).
//        Grid file looks similar to:
//
//            xxxSxxxxxxxxxxxxxxx
//            x                 x
//            xxxxxxx xxxxxxxxxxx
//            x                 x
//            xxxxxxxxxxxxxxGxxxx
//
//        Spaces represent empty grid blocks.  Init in EMPTY state.
//        S represents the starting grid block(s). Init in COLOR state.
//        G represents the goal grid block. More than one can exist.
//        Any non-space (x here) is considered a wall. Init in WALL state.

#include <iostream>
#include <vector>

using namespace std;

// Provided functions
void animationPause();
void clearScreen();
void printEmpty();
void printColor();
void printWall();
void readGrid(vector <vector <int> > &, vector <vector <bool> > &);
void LAB_DEBUG_printGrid(const vector <vector <int> > &grid);


// States for grid spots for use throughout the program
const int EMPTY = 1;
const int WALL = 2;
const int COLOR = 3;
const int TO_BE_COLORED = 4;



/// @brief percolates the fluid from grid blocks with fluid in them
/// @param grid the current grid filled with current states
void perc(vector <vector <int> > &grid)
{
    
    /// Traverse 2D grid setting intermediate state where applicable
    for (int r=0; r < grid.size(); r++) //rows
    {
        for (int c=0; c < grid.at(r).size(); c++) //columns
        {
            if (grid.at(r).at(c)==3)
            {
                //down
                if (r < (grid.size()-1))
                {
                    if (grid.at(r+1).at(c) == 1)
                    {
                        grid.at(r+1).at(c) = 4;
                    }
                }
                //up
                if (r > 0)
                {
                    if (grid.at(r-1).at(c) == 1)
                    {
                        grid.at(r).at(c) = 4;
                    }
                }
                //right
                if (c < (grid.at(r).size()-1))
                {
                    if (grid.at(r).at(c+1) == 1)
                    {
                        grid.at(r).at(c+1) = 4;
                    }
                }
                //left
                if (c > 0)
                {
                    if (grid.at(r).at(c-1) == 1)
                    {
                        grid.at(r).at(c-1) = 4;
                    }
                }
            }
        }
    }

    /// Traverse 2D grid converting intermediate states to color state
    for (int r = 0; r< grid.size(); r++)
    {
        for (int c = 0; c< grid.at(r).size(); c++)
        {
            if (grid.at(r).at(c) == 4)
            {
                grid.at(r).at(c) = 3;
            }
        }
    }
}


/// @brief determines whether the percolation has reached goal cell
/// @param grid the grid in its current state
/// @param goals the 2D vector filled with true/false based on if cell is goal
/// @return true if grid block is a goal and it is colored, otherwise false
bool percComplete(const vector <vector <int> > &grid,
    const vector <vector <bool> > &goals)
{
    // TODO: Implement this function
    
    /// Traverse the 2D goals vector and return true if the cell is a goal
    /// and the same cell within the grid is in the COLOR state. Making sure
    /// to check bounds when appropriate.    
    
    return false;
}


/// @brief prints the NxM grid 
/// 
///     Calls the respective print helper function based on state of grid cell.
///     The 3 helpers are void functions printWall, printEmpty and printColor.
///
/// @param grid the grid to print, filled with integer states for each cell
void printGrid(const vector <vector <int> > &grid)
{
    // Comment this function call out before turning into R'Sub
    //LAB_DEBUG_printGrid(grid);
    // TODO: implement this function
    
    /// Clear the screen
    
    /// Traverse 2D grid, print each cell using each state's helper functions.
}


// DO NOT alter code in main
int main()
{
    // 2D vectors to store states of grid and whether it is a goal cell
    vector <vector <int> > grid;
    vector <vector <bool> > goals;
   
    // Read in the grid from input
    readGrid(grid, goals);

    // Print initial grid
    printGrid(grid);

    // Run the simulation
    do
    {
        // Animation
        animationPause();

        // Percolate
        perc(grid);

        // Print updated grid
        printGrid(grid);
    }
    while(!percComplete(grid, goals));

    return 0;
}
