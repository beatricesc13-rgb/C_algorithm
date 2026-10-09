#include "Sort.h"

#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

int main() {
    // int count;
    // std::cout << "請輸入亂數個數：";
    // if (!(std::cin >> count) || count <= 0) {
    //     std::cerr << "請輸入正整數。\n";
    //     return 1;
    // }

    // std::srand(2);
    // std::vector<int> original(static_cast<std::size_t>(count));
    // for (int& value : original) {
    //     value = std::rand() % (1000000 - 10000 + 1) + 10000;
    // }


    std::ifstream inputFile("reverse_data.txt");
    if (!inputFile) {
        std::cerr << "無法開啟 sorted_data.txt。\n";
        return 1;
    }

    std::vector<int> original;
    int value;
    while (inputFile >> value) {
        original.push_back(value);
    }
    if (!inputFile.eof()) {
        std::cerr << "sorted_data.txt 內含無法讀取的資料。\n";
        return 1;
    }
    if (original.empty()) {
        std::cerr << "sorted_data.txt 沒有資料。\n";
        return 1;
    }



    
    std::vector<int> insertionData = original;
    std::vector<int> selectionData = original;
    std::vector<int> quickData = original;
    std::vector<int> mergeData = original;
    std::vector<int> heapData = original;
    Sort sorter;

    std::cout << "Insertion sort\n";
    std::clock_t start = std::clock();
    sorter.insertionSort(insertionData);
    std::clock_t end = std::clock();
    double cpuTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    std::cout << "CPU 執行時間：" << std::fixed << std::setprecision(6)
              << cpuTime << " 秒\n";
    // long long cpunumber = static_cast<long long>(count / cpuTime);
    // std::cout << "每秒可處理的數字個數：" << cpunumber << " 個\n";


    std::cout << "Selection sort\n";
    start = std::clock();
    sorter.selectionSort(selectionData);
    end = std::clock();
    cpuTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    std::cout << "CPU 執行時間：" << std::fixed << std::setprecision(6)
              << cpuTime << " 秒\n";
    // cpunumber = static_cast<long long>(count / cpuTime);
    // std::cout << "每秒可處理的數字個數：" << cpunumber << " 個\n";

    // --- Quick Sort 測試 ---
    std::cout << "Quick sort \n";
    start = std::clock();
    sorter.quickSort(quickData);
    end = std::clock();
    cpuTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    std::cout << "CPU 執行時間：" << std::fixed << std::setprecision(6)
              << cpuTime << " 秒\n";
    // cpunumber = static_cast<long long>(count / cpuTime);
    // std::cout << "每秒可處理的數字個數：" << cpunumber << " 個\n";

    // --- Merge Sort 測試 ---
    std::cout << "Merge sort \n";
    start = std::clock();
    sorter.mergeSort(mergeData);
    end = std::clock();
    cpuTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    std::cout << "CPU 執行時間：" << std::fixed << std::setprecision(6)
              << cpuTime << " 秒\n";
    // cpunumber = static_cast<long long>(count / cpuTime);
    // std::cout << "每秒可處理的數字個數：" << cpunumber << " 個\n";



    // --- Heap Sort 測試 ---
    std::cout << "Heap sort \n";
    start = std::clock();
    sorter.heapSort(heapData);
    end = std::clock();
    cpuTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    std::cout << "CPU 執行時間：" << std::fixed << std::setprecision(6)
              << cpuTime << " 秒\n";
    // cpunumber = static_cast<long long>(count / cpuTime);
    // std::cout << "每秒可處理的數字個數：" << cpunumber << " 個\n";

    return 0;
}
