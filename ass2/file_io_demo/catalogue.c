// Demonstration of fscanf
// Prints out catalogue from products listed in products.txt
// Assumes product names are no longer than MAX_PRODUCT_NAME
// Usage: ./catalogue products.txt

#include <stdio.h>
#include <stdlib.h>

#define MAX_PRODUCT_NAME 20

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s [File]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	// See linenos.c for description of fopen and fclose
	FILE *fp = fopen(argv[1], "r");
	if (fp == NULL) {
		fprintf(stderr, "Can't open %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	char name[MAX_PRODUCT_NAME];
	int quantity;
	double price;

	// fscanf works similarly to scanf, except it reads from a file.
	// It takes a file pointer as its first argument. The remaining
	// arguments are the same as what you would pass to scanf.
	while (fscanf(fp, "%s %d %lf", name, &quantity, &price) == 3) {
		printf("%d %s(s) for sale at $%.2lf each\n", quantity, name, price);
	}

	fclose(fp);
}

