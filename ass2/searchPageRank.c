// COMP2521 Assignment 2

// Written by:
// Date:

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
	int numMatchTerms;  //the number of mathcing terms a url have
	double weight;
	char *url;
} Info;
static int getNumUrl();
void initInfoArr(Info *urls, int numUrl);
static void updateMatchedTerms(Info *urls, int numUrl, int numWords,
                               char *argv[]);
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

	updateMatchedTerms(urls, numUrl, argc, argv);
	order(urls, numUrl);
	print(urls, numUrl);
}

static void print(Info *urls, int numUrl) {
    numUrl = (numUrl > 30) ? 30 : numUrl;
	for (int i = 0; i < numUrl; i++) {
		printf("%s\n",urls[i].url);
		free(urls[i].url);
	}
}

static void updateMatchedTerms(Info *urls, int numUrl, int numWords,
                               char *argv[]) {
	for (int i = 1; i < numWords; i++) {
		getMatchedUrls(argv[i], urls, numUrl);
	}
}

static void order(Info *urls, int numUrl) {
	sortByMatchedTerms(urls, numUrl);
	int hi = 0;
	int lo = 0;
	while (hi < numUrl) {
		while (hi < numUrl &&
		       urls[lo].numMatchTerms == urls[hi].numMatchTerms) {
			hi++;
		}
		sortByWeight(urls, lo, hi - 1);
		lo = hi;
	}
	hi = 0;
	lo = 0;
	while (hi < numUrl) {
		while (hi < numUrl &&
		       urls[lo].numMatchTerms == urls[hi].numMatchTerms &&
		       urls[lo].weight == urls[hi].weight) {
			hi++;
		}
		sortByName(urls, lo, hi - 1);
		lo = hi;
	}
}

static void sortByName(Info *urls, int lo, int hi) {
	for (int i = lo; i <= hi; ++i) {
		for (int j = i + 1; j <= hi; ++j) {
			if (strcmp(urls[i].url,urls[j].url) > 0) {
				Info tmp = urls[i];
				urls[i] = urls[j];
				urls[j] = tmp;
			}
		}
	}
}

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

static void sortByMatchedTerms(Info *urls, int numUrl) {
	for (int i = 0; i < numUrl; ++i) {
		for (int j = i + 1; j < numUrl; ++j) {
			if (urls[i].numMatchTerms < urls[j].numMatchTerms) {
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
			urls[i].numMatchTerms++;
			return true;
		}
	}
	return false;
}

void initInfoArr(Info *urls, int numUrl) {
	FILE *f = fopen("pageRankList.txt", "r");
	char x[MAX_URL_LEN];
	int i = 0;
	int count = 1;
	while (fscanf(f, "%99s", x) == 1) {
		if (count == 1) {
			urls[i].url = malloc(MAX_URL_LEN * sizeof(char));
			strcpy(urls[i].url, x);
			urls[i].numMatchTerms = 0;
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