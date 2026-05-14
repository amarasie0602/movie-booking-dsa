#include <string>

#include "MergeSortShows.h"
#include "Store.h"

void MergeSortShows::sortIndices(int arr[], int count, const Store &store) // Sort an array of show indices
{
    if (count <= 1)
    {
        return;
    }

    mergeSort(arr, 0, count - 1, store); 
}

void MergeSortShows::mergeSort(int arr[], int left, int right, const Store &store) // Recursive function to perform merge sort on the array
{
    int mid;

    if (left >= right)
    {
        return;
    }

    mid = (left + right) / 2;
    mergeSort(arr, left, mid, store);
    mergeSort(arr, mid + 1, right, store);
    merge(arr, left, mid, right, store);
}

void MergeSortShows::merge(int arr[], int left, int mid, int right, const Store &store) // Merge two sorted subarrays into a single sorted array
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int *leftArr = new int[n1];
    int *rightArr = new int[n2];
    int i;
    int j;
    int k;

    for (i = 0; i < n1; i++) 
    {
        leftArr[i] = arr[left + i]; // Copy the left subarray into a temporary array
    }

    for (j = 0; j < n2; j++)
    {
        rightArr[j] = arr[mid + 1 + j]; // Copy the right subarray into a temporary array
    }

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) 
    {
        if (store.shows[leftArr[i]].datetime <= store.shows[rightArr[j]].datetime) //compare show date and time
        {
            arr[k] = leftArr[i];
            i++;
        }
        else
        {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = rightArr[j];
        j++;
        k++;
    }

    delete[] leftArr; // Clean up the temporary arrays
    delete[] rightArr;
}