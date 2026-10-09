#ifndef SORT_H
#define SORT_H

#include <vector>

class Sort {
public:
    void insertionSort(std::vector<int>& values) const;
    void selectionSort(std::vector<int>& values) const;
    void quickSort(std::vector<int>& values); 
    void mergeSort(std::vector<int>& values);
    void heapSort(std::vector<int>& values); 

private:
    void quickSortHelper(std::vector<int>& values, int low, int high);
    int partition(std::vector<int>& values, int low, int high);

    void mergeSortHelper(std::vector<int>& values, std::size_t left, std::size_t right);
    void merge(std::vector<int>& values, std::size_t left, std::size_t mid, std::size_t right);

    void heapify(std::vector<int>& values, std::size_t n, std::size_t i);

};



#endif
