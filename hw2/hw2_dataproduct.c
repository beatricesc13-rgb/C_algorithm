#include <stdio.h>

#define DATA_COUNT 100000

int main(void) {
	int arr[DATA_COUNT];

	for (int i = 0; i < DATA_COUNT; i++) {
		arr[i] = i + 1;
	}

	FILE *output = fopen("sorted_data.txt", "w");
    FILE *reverseoutput = fopen("reverse_data.txt", "w");

	for (int i = 0; i < DATA_COUNT; i++) {
		fprintf(output, "%d\n", arr[i]);
	}  
    for(int i = DATA_COUNT - 1; i >= 0; i--) {
        fprintf(reverseoutput, "%d\n", arr[i]);
    }

	printf("已將 1 到 %d 依序寫入 sorted_data.txt\n", DATA_COUNT);
	printf("已將 1 到 %d 依序寫入 reverse_data.txt\n", DATA_COUNT);
	return 0;
}





