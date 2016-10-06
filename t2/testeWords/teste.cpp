#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <ctype.h>
#include "InvertedList.hpp"

static const int manPageSize = 139900;
static const int lexicalIgnoredSize = 1000;

char manPage[manPageSize];
char lexicalIgnored[lexicalIgnoredSize];

std::vector<std::string> ignoredStrings = std::vector<std::string>();
std::vector<std::string> acceptedStrings = std::vector<std::string>();

void searchBySingleWord(){
	printf("\nInforme a palavra a ser procurada:\n");
  	char word[100];
    for(int i=0; i < 100; i++) {
         word[i] = ' ';
    }
	scanf("%s", word);

	InvertedList *avlInverted = new InvertedList(0, word);
	Word wordNode = avlInverted->search(avlInverted->getWord());
	if (wordNode.occurrenceIndex == -1) {
		printf("Palavra não encontrada\n");
		return;
	}
	for(int i = 0; i <= wordNode.occurrenceIndex; i++) {
		printf("ManPage: %ld\n", wordNode.occurrences[i]);
	}
	delete avlInverted;
}

int main() {
	{
		FILE* lexicalIgnoredTxt = fopen("lexicalIgnored.txt", "r");
		for(int j = 0; j < lexicalIgnoredSize; j++) {
				lexicalIgnored[j] = ' ';
		}
		int i;
		for(i = 0; !feof(lexicalIgnoredTxt); i++) {
				lexicalIgnored[i] = fgetc(lexicalIgnoredTxt);
		}

		lexicalIgnored[i-1] = '\0';

		char *pch;
		pch = strtok(lexicalIgnored,
					 " ',.-:<>[]()=;|_%*&$#@!?}{/^\"\\0123456789\t\r\n\f\v`");

		while(pch != NULL)
		{
			ignoredStrings.push_back(pch);
			pch = strtok (NULL,
						  " ',.-:<>[]()=;|_%*&$#@!?}{/^\"\\0123456789\t\r\n\f\v`");
		}
	}

	{
		FILE* manPageTxt = fopen("alias.1.txt", "r");
		for(int j = 0; j < manPageSize; j++) {
				manPage[j] = ' ';
		}
		int i;
		for(i = 0; !feof(manPageTxt); i++) {
				manPage[i] = tolower(fgetc(manPageTxt));
		}

		manPage[i-1] = '\0';

		char *pch;
		pch = strtok(manPage,
					 " ',.-:<>[]()=;|_%*&$#@!?}{/^\"0123456789\t\r\n\f\v");

		while(pch != NULL) {
			unsigned int k;
			const char *c;
			for(k = 0; k < ignoredStrings.size(); k++) {
				c = ignoredStrings[k].c_str();
				if(strcmp(pch, c) == 0)
					break;
			}
			if(k == ignoredStrings.size())
				acceptedStrings.push_back(pch);

			pch = strtok (NULL,
						  " ',.-:<>[]()=;|_%*&$#@!?}{/^\"\\0123456789\t\r\n\f\v`");
		}
	}

	sort(acceptedStrings.begin(), acceptedStrings.end());
	acceptedStrings.erase(unique(acceptedStrings.begin(), acceptedStrings.end()),
						  acceptedStrings.end());

	FILE* invertedDat = fopen("inverted.dat", "w+");
	long int invertedRoot = 0;
	fwrite(&invertedRoot, 8, 1, invertedDat);

	for(int j = 0; j < (int)acceptedStrings.size(); j++) {
        const char *c = acceptedStrings[j].c_str();
        InvertedList *invertedNode = new InvertedList(0, c);
        rewind(invertedDat);
        fread(&invertedRoot, 8, 1, invertedDat);
        invertedRoot = invertedNode->insert(invertedNode->getWord(), invertedRoot);
        rewind(invertedDat);
        fwrite(&invertedRoot, 8, 1, invertedDat);
        delete invertedNode;
    }

    searchBySingleWord();

	return 0;
}