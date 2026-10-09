#include "Sort.h"

// insertionSort:每次從未排序區域取出第一個元素，與已排序區域的元素從後往前比較，找到合適的位置後「插入」進去
void Sort::insertionSort(std::vector<int>& values) const {
    for (std::size_t i = 1; i < values.size(); i++) {
        int key = values[i];
        std::size_t j = i;

        while (j > 0 && values[j - 1] > key) {
            values[j] = values[j - 1];
            j--;
        }
        values[j] = key;
    }
}
// selectionSort:每次從未排序的資料中找出最小值（或最大值），將它放到已排序區域的最後面。
void Sort::selectionSort(std::vector<int>& values) const {
    for (std::size_t i = 0; i + 1 < values.size(); i++) {
        std::size_t minIndex = i;

        for (std::size_t j = i + 1; j < values.size(); j++) {
            if (values[j] < values[minIndex]) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            int temp = values[i];
            values[i] = values[minIndex];
            values[minIndex] = temp;
        }
    }
}

#include <utility> // 用於 std::swap
// Quick sort: 挑選一個基準值（Pivot），將資料分割成「比 Pivot 小」與「比 Pivot 大」兩群，再對這兩群分別遞迴進行排序.

// 分割函式：選取 pivot 並將小於 pivot 的元素放到左邊，大於 pivot 的放到右邊
int Sort::partition(std::vector<int>& values, int low, int high) {
    int pivot = values[high]; // 選取最後一個元素作為 pivot
    int i = low - 1;          // 小於 pivot 區域的邊界

    for (int j = low; j < high; j++) {
        if (values[j] < pivot) {
            i++;
            std::swap(values[i], values[j]);
        }
    }
    std::swap(values[i + 1], values[high]); // 將 pivot 放回正確的中間位置
    return i + 1;
}

// 遞迴輔助函式
void Sort::quickSortHelper(std::vector<int>& values, int low, int high) {
    if (low < high) {
        int pi = partition(values, low, high); // 取得 pivot 的正確索引位置

        // 遞迴排序左半部與右半部
        quickSortHelper(values, low, pi - 1);
        quickSortHelper(values, pi + 1, high);
    }
}
// quickSort: 對外的入口函式
void Sort::quickSort(std::vector<int>& values) {
    if (values.empty()) return;
    quickSortHelper(values, 0, static_cast<int>(values.size()) - 1);
}

// merge sort: 具體來說，就是先把陣列不斷對半分割，直到每個小子陣列只剩一個元素，然後再將這些子陣列兩兩「合併（Merge）」，在合併的過程中完成排序。
void Sort::merge(std::vector<int>& values, std::size_t left, std::size_t mid, std::size_t right) {
    std::size_t n1 = mid - left + 1;
    std::size_t n2 = right - mid;

    // 建立暫存陣列
    std::vector<int> leftArr(n1);
    std::vector<int> rightArr(n2);

    for (std::size_t i = 0; i < n1; i++) leftArr[i] = values[left + i];
    for (std::size_t j = 0; j < n2; j++) rightArr[j] = values[mid + 1 + j];

    // 合併暫存陣列回原本的 values 中
    std::size_t i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) { // '<=' 確保了排序的穩定性 (Stable)
            values[k] = leftArr[i];
            i++;
        } else {
            values[k] = rightArr[j];
            j++;
        }
        k++;
    }

    // 複製剩餘元素
    while (i < n1) values[k++] = leftArr[i++];
    while (j < n2) values[k++] = rightArr[j++];
}

// 遞迴拆分函式
void Sort::mergeSortHelper(std::vector<int>& values, std::size_t left, std::size_t right) {
    if (left < right) {
        std::size_t mid = left + (right - left) / 2; // 防溢位的取中間值點

        mergeSortHelper(values, left, mid);
        mergeSortHelper(values, mid + 1, right);

        merge(values, left, mid, right); // 合併
    }
}

// 對外入口
void Sort::mergeSort(std::vector<int>& values) {
    if (values.empty()) return;
    mergeSortHelper(values, 0, values.size() - 1);
}

// heapSort: 將陣列視為一個完全二元樹，先將其轉換為最大堆（Max-Heap），然後不斷將堆頂元素（最大值）與最後一個元素交換，並縮小堆的大小，最後再對新的堆進行調整，直到整個陣列排序完成。
// 調整以 i 為根節點的子樹，使其符合 Max-Heap 特性
void Sort::heapify(std::vector<int>& values, std::size_t n, std::size_t i) {
    std::size_t largest = i;       // 初始化最大值為根節點
    std::size_t left = 2 * i + 1;  // 左子節點索引
    std::size_t right = 2 * i + 2; // 右子節點索引

    // 若左子節點比根節點大
    if (left < n && values[left] > values[largest]) {
        largest = left;
    }

    // 若右子節點比當前最大值大
    if (right < n && values[right] > values[largest]) {
        largest = right;
    }

    // 若最大值不是根節點，進行交換並遞迴調整
    if (largest != i) {
        std::swap(values[i], values[largest]);
        heapify(values, n, largest);
    }
}

// 對外入口
void Sort::heapSort(std::vector<int>& values) {
    if (values.empty()) return;

    std::size_t n = values.size();

    // 1. 建立 Max-Heap（從最後一個非葉子節點開始往前調整）
    for (std::ptrdiff_t i = static_cast<std::ptrdiff_t>(n / 2) - 1; i >= 0; i--) {
        heapify(values, n, static_cast<std::size_t>(i));
    }

    // 2. 逐一取出 Heap 的最大值並放置到末端
    for (std::size_t i = n - 1; i > 0; i--) {
        std::swap(values[0], values[i]); // 將最大值移至陣列末端
        heapify(values, i, 0);           // 針對剩餘元素重新 Heapify
    }
}

