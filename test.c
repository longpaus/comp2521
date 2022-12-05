#include <stdio.h>
#include <stdlib.h>


int main() {
	for(int i = 0; i < 10; i++){
      if(i == 2) i = 7;
      printf("%d\n",i);
   }

}


void bubbleSort(int a[], int lo, int hi)
{
   int i, j, nswaps;
   for (i = lo; i < hi; i++) {
      nswaps = 0;
      for (j = hi; j > i; j--) {
         if (a[j] < a[j-1]) {
            int tmp = a[j];
            a[j] = a[j -1];
            a[j -1] = tmp;
            nswaps++;
         }
      }
      if (nswaps == 0) break;
   }
}
