#ifndef SORTING_H
#define SORTING_H

#include <cstdlib> 
#include <utility> 


template <typename T, typename Compare>
void insertionSort(T arr[], int size, Compare comp) {
    for (int i = 1; i < size; i++) {
        T key = arr[i];
        int j = i - 1;
        while (j >= 0 && comp(key, arr[j])) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}


template <typename T, typename Compare>
int partitionArray(T arr[], int low, int high, Compare comp) {
    // Pick a random index between low and high
    int randomIndex = low + rand() % (high - low + 1);
    
    // Swap the random pivot to the end
    std::swap(arr[randomIndex], arr[high]);
    T pivot = arr[high];
    
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (comp(arr[j], pivot)) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

template <typename T, typename Compare>
void quickSortHelper(T arr[], int low, int high, Compare comp) {
    if (low < high) {
        int pivotIndex = partitionArray(arr, low, high, comp);
        quickSortHelper(arr, low, pivotIndex - 1, comp);
        quickSortHelper(arr, pivotIndex + 1, high, comp);
    }
}

template <typename T, typename Compare>
void quickSort(T arr[], int size, Compare comp) {
    if (size > 1) {
        quickSortHelper(arr, 0, size - 1, comp);
    }
}


template <typename T>
int binarySearchById(T arr[], int size, int targetID) {
    int low = 0;
    int high = size - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid].patientID == targetID) {
            return mid;
        } else if (arr[mid].patientID < targetID) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

#endif