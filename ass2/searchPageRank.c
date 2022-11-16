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
	int pageRank;
	char *url;
} Info;
static int getNumUrl();
void initInfoArr(Info *urls, int numUrl);
void updateMatchedTerms(Info *urls, int numUrl, int numWords, char *argv[]);
static List getMatchedUrls(char *s);

int main(int argc, char *argv[]) {
	int numUrl = getNumUrl();
	Info urls[numUrl];
	initInfoArr(urls, numUrl);

	updateMatchedTerms(urls, numUrl, argc, argv);
}

void updateMatchedTerms(Info *urls, int numUrl, int numWords, char *argv[]) {
	for (int i = 1; i < numWords; i++) {
        List l = getMatchedUrls(argv[i]);
        ListPrint(l);
    }
}

// given a word s return a List of urls that contain s in its section2
static List getMatchedUrls(char *s) {
	char word[MAX_WORD_LEN];
	FILE *f = fopen("invertedIndex.txt", "r");
    List matchedUrl = ListNew();
	while (!feof(f)) {
		fscanf(f, "%s%*[^\n]", word);
		if (strcmp(word, s) != 0) {
			char url[MAX_URL_LEN];
            int c,n = 0;
			while ((c = fgetc(f)) != '\n') {
                if(c == ' '){
                    url[n++] = '\0';
                    if(strlen(url) > 0){
                        ListAppend(matchedUrl,url);
                        strcpy(url, "");
                        n = 0;
                    }
                }else{
				    url[n++] = (char)c;
                }
			}
            break;
		}
	    strcpy(word, "");
	}
	fclose(f);
    return matchedUrl;
}

void initInfoArr(Info *urls, int numUrl) {
	char url[MAX_URL_LEN];
	FILE *f = fopen("pageRankList.txt", "r");
	for (int i = 0; i < numUrl; i++) {
		fscanf(f, "%s%*[^\n]", url);
		urls[i].url = malloc(MAX_URL_LEN * sizeof(char));
		strcpy(urls[i].url, url);
		urls[i].numMatchTerms = 0;
		urls[i].pageRank = i + 1;
		strcpy(url, "");
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