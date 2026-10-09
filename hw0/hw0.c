#include <stdio.h>

int main() {
    int year, month, day;
    // 讀取 yyyy/mm/dd 格式的輸入
    while (scanf("%d/%d/%d", &year, &month, &day) != EOF) {
        if (month < 1 || month > 12 || day < 1 || day > 31) {
            printf("Invalid date format.\n");
            continue;
        }
        // 印出 "Month dd, yyyy" 格式
        if (month == 1) {
            printf("January %d, %d\n", day, year);
        } else if (month == 2) {
            printf("February %d, %d\n", day, year);
        } else if (month == 3) {
            printf("March %d, %d\n", day, year);
        } else if (month == 4) {
            printf("April %d, %d\n", day, year);
        } else if (month == 5) {
            printf("May %d, %d\n", day, year);
        } else if (month == 6) {
            printf("June %d, %d\n", day, year);
        } else if (month == 7) {
            printf("July %d, %d\n", day, year);
        } else if (month == 8) {
            printf("August %d, %d\n", day, year);
        } else if (month == 9) {
            printf("September %d, %d\n", day, year);
        } else if (month == 10) {
            printf("October %d, %d\n", day, year);
        } else if (month == 11) {
            printf("November %d, %d\n", day, year);
        } else if (month == 12) {
            printf("December %d, %d\n", day, year);
        }
    }

    return 0;


}