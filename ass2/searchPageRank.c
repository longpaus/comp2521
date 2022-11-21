// COMP2521 Assignment 2

// Written by:Long Hoang Pham
// Date: 18/11/22

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "List.h"

#define MAX_URL_LEN 100
#define MAX_WORD_LEN 1000
typedef struct info {
	int matchTerms;  //the number of mathcing terms a url have
	double weight;
	char *url;
} Info;
static int getNumUrl();
void initInfoArr(Info *urls, int numUrl);
static void getMatchedUrls(char *s, Info *urls, int numUrl);
static bool isUrl(char *url, Info *urls, int numUrl);
static void sortByMatchedTerms(Info *urls, int numUrl);
static void sortByWeight(Info *urls, int lo, int hi);
static void order(Info *urls, int numUrl);
static void sortByName(Info *urls, int lo, int hi);
static void print(Info *urls, int numUrl);

int main(int argc, char *argv[]) {
	int numUrl = getNumUrl();
	Info urls[numUrl];
	initInfoArr(urls, numUrl);

	for (int i = 1; i < argc; i++) {
		getMatchedUrls(argv[i], urls, numUrl);
	}
	order(urls, numUrl);
	print(urls, numUrl);
	for (int i = 0; i < numUrl; i++) {
		free(urls[i].url);
	}
    return 0;
}
//print ant element in Info array that has matchedTerms of over 0
static void print(Info *urls, int numUrl) {
	numUrl = (numUrl > 30) ? 30 : numUrl;
	for (int i = 0; i < numUrl; i++) {
		if (urls[i].matchTerms > 0) {
			printf("%s\n", urls[i].url);
		}
	}
}

//sort the urls by their number of matched terms then by their weight then
//by their name.
static void order(Info *urls, int numUrl) {
	sortByMatchedTerms(urls, numUrl);
	int hi = 0;
	int lo = 0;
	while (hi < numUrl) {
		while (hi < numUrl && urls[lo].matchTerms == urls[hi].matchTerms) {
			hi++;
		}
		sortByWeight(urls, lo, hi - 1);
		lo = hi;
	}
	hi = 0;
	lo = 0;
	while (hi < numUrl) {
		while (hi < numUrl && urls[lo].matchTerms == urls[hi].matchTerms &&
		       urls[lo].weight == urls[hi].weight) {
			hi++;
		}
		sortByName(urls, lo, hi - 1);
		lo = hi;
	}
}
//sort the Info array by name in ascending order from lo to hi
static void sortByName(Info *urls, int lo, int hi) {
	for (int i = lo; i <= hi; ++i) {
		for (int j = i + 1; j <= hi; ++j) {
			if (strcmp(urls[i].url, urls[j].url) > 0) {
				Info tmp = urls[i];
				urls[i] = urls[j];
				urls[j] = tmp;
			}
		}
	}
}

//sort the Info array by weight in descending order from lo to hi
static void sortByWeight(Info *urls, int lo, int hi) {
	for (int i = lo; i <= hi; ++i) {
		for (int j = i + 1; j <= hi; ++j) {
			if (urls[i].weight < urls[j].weight) {
				Info tmp = urls[i];
				urls[i] = urls[j];
				urls[j] = tmp;
			}
		}
	}
}

// sort the given Info array by their matchedTerms
static void sortByMatchedTerms(Info *urls, int numUrl) {
	for (int i = 0; i < numUrl; ++i) {
		for (int j = i + 1; j < numUrl; ++j) {
			if (urls[i].matchTerms < urls[j].matchTerms) {
				Info tmp = urls[i];
				urls[i] = urls[j];
				urls[j] = tmp;
			}
		}
	}
}

// given a word s update the numMatchTerms for any url that matches it
static void getMatchedUrls(char *s, Info *urls, int numUrl) {
	FILE *f = fopen("invertedIndex.txt", "r");
	char x[1024];
	bool collectUrl = false;
	while (fscanf(f, " %1023s", x) == 1) {
		if (strcmp(x, s) == 0) {
			collectUrl = true;
			continue;
		}
		if (collectUrl) {
			if (isUrl(x, urls, numUrl)) {
				continue;
			} else {
				break;
			}
		}
	}
	fclose(f);
}

//given a url check if it exist, if it does increase that
// url numMatchTerms by one and return true, returns false otherwise
static bool isUrl(char *url, Info *urls, int numUrl) {
	for (int i = 0; i < numUrl; i++) {
		if (strcmp(url, urls[i].url) == 0) {
			urls[i].matchTerms++;
			return true;
		}
	}
	return false;
}

//get the weight and url of each url in pageRankList.txt
void initInfoArr(Info *urls, int numUrl) {
	FILE *f = fopen("pageRankList.txt", "r");
	char x[MAX_URL_LEN];
	int i = 0;
	int count = 1;
	while (fscanf(f, "%99s", x) == 1) {
		if (count == 1) {
			urls[i].url = malloc(MAX_URL_LEN * sizeof(char));
			strcpy(urls[i].url, x);
			urls[i].matchTerms = 0;
		}
		if (count == 3) {
			urls[i].weight = atof(x);
			count = 0;
			i++;
		}
		count++;
	}
	fclose(f);
}

// get the number of url from the file pageRankList.txt
static int getNumUrl() {
	char url[MAX_URL_LEN];
	int numUrl = 0;
	FILE *f = fopen("pageRankList.txt", "r");
	while (!feof(f)) {
		fscanf(f, "%s%*[^\n]", url);
		if (strcmp(url, "") != 0) {
			numUrl++;
		}
		strcpy(url, "");
	}
	fclose(f);
	return numUrl;
}