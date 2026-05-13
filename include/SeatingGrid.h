#ifndef SEATINGGRID_H
#define SEATINGGRID_H

#include <iostream>
#include "HashTableIntToIndex.h"
#include "SinglyLinkedListInt.h"

using namespace std;

class SeatingGrid
{
public:
    static const int AVAILABLE = 0;
    static const int SELECTED  = 1;
    static const int BOOKED    = 2;

private:
    int **grid;
    int rows;
    int cols;

    HashTableIntToIndex seatMap;
    SinglyLinkedListInt selectedSeats;

    int encodeKey(int row, int col) const;       // Encode row and column into a single integer key
    int isValid(int row, int col) const;        // Check if the given row and column are within the grid bounds

public:
    SeatingGrid();
    ~SeatingGrid();

    void init(int rows, int cols);              // Initialize the seating grid with the specified number of rows and columns, setting all seats to available

    int selectSeat(int row, int col);           // Select a seat at the specified row and column, returning 1 if successful and 0 if the seat is not available
    int deselectSeat(int row, int col);        // Deselect a previously selected seat at the specified row and column, returning 1 if successful and 0 if the seat is not currently selected
    int confirmBooking();                      // Confirm the booking of all currently selected seats, changing their status to booked and clearing the selection list, returning 1 if successful and 0 if no seats were selected
    int cancelSeat(int row, int col);          // Cancel a booked seat at the specified row and column, changing its status back to available, returning 1 if successful and 0 if the seat was not currently booked
    int isAvailable(int row, int col) const;   // Check if a seat at the specified row and column is available, returning 1 if available and 0 if not available or if the position is invalid

    void suggestSeats(int count) const;        // Suggest a block of  consecutive available seats of the specified count, printing the suggested seats to the console. If no such block is available, print a message indicating that.
    void displayGrid() const;                 // Display the current seating grid to the console, showing available, selected, and booked seats with different symbols, along with row and column labels and a legend for the symbols

    int getAvailableCount() const;            // Return the total number of available seats in the grid
    int getSelectedCount() const;            // Return the total number of currently selected seats in the grid
    int getBookedCount() const;              // Return the total number of booked seats in the grid
};

#endif