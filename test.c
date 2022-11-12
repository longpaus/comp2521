#include <stdio.h>


void swap(int *xp, int *yp) {
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

int selectionSort(int *arr, int n) {
	int i, j, min_idx;
    int comp = 0;
	// One by one move boundary of unsorted subarray
	for (i = 0; i < n - 1; i++) {
		// Find the minimum element in unsorted array
		min_idx = i;
		for (j = i + 1; j < n; j++){
            comp++;
			if (arr[j] < arr[min_idx]){
				min_idx = j;
               
            }
        }

		// Swap the found minimum element with the first element
		if (min_idx != i)
			swap(&arr[min_idx], &arr[i]);
	}
    return comp;
}

int main() {
    int arr[6] = { 1, 7, 4, 8, 5, 3 };
    int num = selectionSort(arr,6);
    for(int i = 0; i < 6; i++){
        printf("%d\n",arr[i]);
    }
    printf( "num: %d\n",num);
}
