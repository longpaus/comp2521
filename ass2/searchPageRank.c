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
static List getMatchedUrls(char *s,Info *urls,int numUrl);
static bool isUrl(char *s,Info *urls,int numUrl);

int main(int argc, char *argv[]) {
	int numUrl = getNumUrl();
	Info urls[numUrl];
	initInfoArr(urls, numUrl);

	updateMatchedTerms(urls, numUrl, argc, argv);
}

void updateMatchedTerms(Info *urls, int numUrl, int numWords, char *argv[]) {
	for (int i = 1; i < numWords; i++) {
        List l = getMatchedUrls(argv[i],urls,numUrl);
        ListPrint(l);
        printf("\n");
		ListFree(l);
    }
}

// given a word s return a List of urls that contain s in its section2
static List getMatchedUrls(char *s,Info *urls,int numUrl) {
	FILE *f = fopen("invertedIndex.txt", "r");
    List matchedUrl = ListNew();
	char x[1024];
    bool collectUrl = false;
	while (fscanf(f, " %1023s", x) == 1) {
		if(strcmp(x,s) == 0){
            collectUrl = true;
            continue;
        }
        if(collectUrl){
            if(isUrl(x,urls,numUrl)){
                ListAppend(matchedUrl,x);
            }else{
                break;
            }
        }
	}
	fclose(f);
    return matchedUrl;
}

static bool isUrl(char *s,Info *urls,int numUrl){
    for(int i = 0; i < numUrl; i++){
        if(strcmp(s,urls[i].url) == 0){
            return true;
        }
    }
    return false;
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