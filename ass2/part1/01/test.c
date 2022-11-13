#include <stdbool.h>
#include <stdio.h>
#include <string.h>
int main() {
	FILE *f = fopen("url22.txt", "r");
	char x[1024];
	fseek(f, 16, SEEK_CUR);
	bool reachEnd = false;
	while (fscanf(f, " %1023s", x) == 1) {
		if (strcmp(x, "#end") == 0) {
			reachEnd = true;
			continue;
		} else if (reachEnd == true) {
			if (strcmp(x, "Section-1") == 0) {
				break;
			} else {
				reachEnd = false;
			}
		}
        puts(x);
	}
}