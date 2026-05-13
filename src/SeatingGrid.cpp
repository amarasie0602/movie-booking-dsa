#include <iomanip>
#include "SeatingGrid.h"

SeatingGrid::SeatingGrid()        // Constructor to initialize member variables
{
    grid = NULL;
    rows = 0;
    cols = 0;
}

SeatingGrid::~SeatingGrid()      // Destructor to clean up resources
{
    if (grid != NULL)
    {
        for (int r = 0; r < rows; r++)
        {
            delete[] grid[r];
        }
        delete[] grid;
        grid = NULL;
    }
}

int SeatingGrid::encodeKey(int row, int col) const           // Encode row and column into a single integer key
{
    return row * cols + col;
}

int SeatingGrid::isValid(int row, int col) const           // Check if the given row and column are within the grid bounds
{
    return row >= 0 && row < rows && col >= 0 && col < cols;
}

void SeatingGrid::init(int rowCount, int colCount)          // Initialize the seating grid with the specified number of rows and columns, setting all seats to available
{  
    if (grid != NULL)
    {
        for (int r = 0; r < rows; r++)
        {
            delete[] grid[r];
        }
        delete[] grid;
        grid = NULL;
    }

    selectedSeats.clear();
    seatMap.init(rowCount * colCount);

    rows = rowCount;
    cols = colCount;

    grid = new int *[rows];
    for (int r = 0; r < rows; r++)              // Allocate memory for each row and initialize seats to available
    {
        grid[r] = new int[cols];
        for (int c = 0; c < cols; c++)
        {
            grid[r][c] = AVAILABLE;
            seatMap.put(encodeKey(r, c), encodeKey(r, c));
        }
    }
}

int SeatingGrid::selectSeat(int row, int col)      // Select a seat at the specified row and column, returning 1 if successful and 0 if the seat is not available
{
    if (!isValid(row, col))
    {
        return 0;
    }

    if (grid[row][col] != AVAILABLE)
    {
        return 0;
    }

    grid[row][col] = SELECTED;
    selectedSeats.insertLast(encodeKey(row, col));    // Add the selected seat to the list of currently selected seats
    return 1;
}

int SeatingGrid::deselectSeat(int row, int col)        // Deselect a previously selected seat at the specified row and column, returning 1 if successful and 0 if the seat is not currently selected
{
    if (!isValid(row, col))
    {
        return 0;
    }

    if (grid[row][col] != SELECTED)
    {
        return 0;
    }

    grid[row][col] = AVAILABLE;
    selectedSeats.removeValue(encodeKey(row, col));       // Remove the deselected seat from the list of currently selected seats
    return 1;
}

int SeatingGrid::confirmBooking()                 // Confirm the booking of all currently selected seats, changing their status to booked and clearing the selection list, returning 1 if successful and 0 if no seats were selected
{
    if (selectedSeats.getSize() == 0)
    {
        return 0;
    }

    SinglyLinkedListInt::Node *current = selectedSeats.getHead();        // Iterate through the list of currently selected seats and change their status to booked
    while (current != NULL)
    {
        int key = current->value;
        int row = key / cols;
        int col = key % cols;
        grid[row][col] = BOOKED;
        current = current->next;
    }

    selectedSeats.clear();
    return 1;
}

int SeatingGrid::cancelSeat(int row, int col)     // Cancel a booked seat at the specified row and column, changing its status back to available, returning 1 if successful and 0 if the seat was not currently booked
{
    if (!isValid(row, col))
    {
        return 0;
    }

    if (grid[row][col] != BOOKED)
    {
        return 0;
    }

    grid[row][col] = AVAILABLE;
    return 1;
}

int SeatingGrid::isAvailable(int row, int col) const        // Check if a seat at the specified row and column is available, returning 1 if available and 0 if not available or if the position is invalid
{
    if (!isValid(row, col))
    {
        return 0;
    }
    return grid[row][col] == AVAILABLE;
}

void SeatingGrid::suggestSeats(int count) const           // Suggest a block of  consecutive available seats of the specified count, printing the suggested seats to the console. If no such block is available, print a message indicating that.
{
    for (int r = 0; r < rows; r++)             // Iterate through each row to find a block of consecutive available seats
    {
        int consecutive = 0;
        int startCol = -1;

        for (int c = 0; c < cols; c++)         // Check if the current seat is available and count consecutive available seats
        {
            if (grid[r][c] == AVAILABLE)
            {
                if (consecutive == 0)
                {
                    startCol = c;
                }
                consecutive++;

                if (consecutive == count)
                {
                    cout << "  Suggested: Row " << (char)('A' + r)
                         << ", Seats " << (startCol + 1)
                         << " - " << (c + 1) << endl;
                    return;
                }
            }
            else
            {
                consecutive = 0;
                startCol = -1;
            }
        }
    }

    cout << "  No " << count << " consecutive seats available." << endl;
}

void SeatingGrid::displayGrid() const           // Display the current seating grid to the console, showing available, selected, and booked seats with different symbols, along with row and column labels and a legend for the symbols
{
    cout << "\n";
    cout << "  +-";
    for (int c = 0; c < cols; c++)
    {
        cout << "----";
    }
    cout << "-+" << endl;

    /// Calculate padding for the "SCREEN" label to center it above the grid
    int totalWidth = cols * 4;
    int labelLen = 6;
    int padding = (totalWidth - labelLen) / 2;
    cout << "  | ";
    for (int i = 0; i < padding; i++) cout << " ";
    cout << "SCREEN";
    for (int i = 0; i < padding; i++) cout << " ";
    cout << " |" << endl;

    cout << "  +-";
    for (int c = 0; c < cols; c++)
    {
        cout << "----";
    }
    cout << "-+" << endl;

    cout << "\n";

    cout << "     ";
    for (int c = 0; c < cols; c++)
    {
        cout << setw(3) << (c + 1) << " ";
    }
    cout << "\n\n";

    // Display each row of the grid with appropriate symbols for available, selected, and booked seats
    for (int r = 0; r < rows; r++)
    {
        cout << "  " << (char)('A' + r) << "  ";
        for (int c = 0; c < cols; c++)
        {
            if (grid[r][c] == AVAILABLE)
            {
                cout << "[ ] ";
            }
            else if (grid[r][c] == SELECTED)
            {
                cout << "[*] ";
            }
            else
            {
                cout << "[X] ";
            }
        }
        cout << "\n";
    }

    // Print the legend and counts of available, selected, and booked seats
    cout << "\n";
    cout << "  [ ] Available   [*] Selected   [X] Booked" << endl;
    cout << "  +-";
    for (int c = 0; c < cols; c++)
    {
        cout << "----";
    }
    cout << "-+" << endl;

    // Print the counts of available, selected, and booked seats
    cout << "  Available: " << getAvailableCount()
         << "   Selected: "  << getSelectedCount()
         << "   Booked: "    << getBookedCount()
         << endl;

    cout << "  +-";
    for (int c = 0; c < cols; c++)   // Print the bottom border of the grid
    {
        cout << "----";
    }
    cout << "-+" << endl;
    cout << "\n";
}

// Return the total number of available seats in the grid
int SeatingGrid::getAvailableCount() const
{
    int count = 0;
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            if (grid[r][c] == AVAILABLE)
            {
                count++;
            }
        }
    }
    return count;
}

// Return the total number of currently selected seats in the grid
int SeatingGrid::getSelectedCount() const
{
    return selectedSeats.getSize();
}

// Return the total number of booked seats in the grid
int SeatingGrid::getBookedCount() const
{
    int count = 0;
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            if (grid[r][c] == BOOKED)
            {
                count++;
            }
        }
    }
    return count;
}