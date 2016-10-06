// Copyright Bruno Marques Do Nascimento e Salomão Rodrigues Jacinto <2016.1>

#include <vector>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <iostream>
#include "FileNoAVL.hpp"

static const int commandSize = 100;
static const int contentSize = 139900;
static const int lexicalIgnoredSize = 1200;
static const int wordSize = 100;
static const int occurrencesSize = 5642;

//!  Struct do elemento comando com manpage.
/*!  Struct que possui o nome do comando e
 *   conteúdo da manpage do comando.
 */
typedef struct ManPage {
	char command[commandSize];
	char content[contentSize];
} ManPage;

//!  Struct do elemento word com ocorrências.
/*!  Struct que possuí a palavra e todas as
 *	 manpages no qual ela existe.
 */
typedef struct Word {
	char word[wordSize];
	int occurrences[occurrencesSize];
	int occurrenceIndex;
} Word;

char lexicalIgnored[lexicalIgnoredSize];
char wordsManPage[contentSize];
std::vector<std::string> ignoredStrings = std::vector<std::string>();

//! Função ignoredWords.
/*! Inicializa a lista de palavras ignoradas,
 *	encontradas no arquivo lexicalIgnored.txt
 */
void ignoredWords() {
	// Abre o arquivo para leitura
	FILE* lexicalIgnoredTxt = fopen("lexicalIgnored.txt", "r");
	for(int j = 0; j < lexicalIgnoredSize; j++) {
			lexicalIgnored[j] = ' ';
	}

	// Adiciona todos os caracteres a um array
	int i;
	for(i = 0; !feof(lexicalIgnoredTxt); i++) {
			lexicalIgnored[i] = fgetc(lexicalIgnoredTxt);
	}

	// Seta o char de término do conteúdo
	lexicalIgnored[i-1] = '\0';

	// Corta o array de char na ocorrência de espacos
	char *pch;
	pch = strtok(lexicalIgnored,
				 " ',.-+:<>[]()=;|_%*&$#@!?}{/^\"\\0123456789\t\r\n\f\v`");

	// Realiza os cortes até o fim do array e adiciona as palavras em um vetor
	while(pch != NULL) {
		ignoredStrings.push_back(pch);
		pch = strtok (NULL,
					  " ',.-+:<>[]()=;|_%*&$#@!?}{/^\"\\0123456789\t\r\n\f\v`");
	}
	fclose(lexicalIgnoredTxt);
}

//! Função createDatFiles.
/*! Responsável por gerar os arquivos
 *  (manpage/manPageIndex/inverted/invertedIndex).dat
 *  \param argc número de arquivos.txt que serão lidos
 *  \param argv array com os nomes dos arquivos.txt a serem lidos
 */
void createDatFiles(int argc, char *argv[]) {
	// Inicializa o vetor com palavras ignoradas
	ignoredWords();

	// Cria o arquivo manpage.dat (guarda as manpages)
	FILE* manPageDat = fopen("manpage.dat", "w");

	// Cria o arquivo inverted.dat (guarda o arquivo invertido, chaves secundarias)
	FILE* invertedDat = fopen("inverted.dat", "w+");

	// Cria o arquivo manPageIndex.dat (guarda a arvore de chave primaria)
	FILE* manPageIndexDat = fopen("manPageIndex.dat", "w+");
	int manPageIndexRoot = 0;
	fwrite(&manPageIndexRoot, sizeof(int), 1, manPageIndexDat);

	// Cria o arquivo invertedIndex.dat (guarda a arvore de chave secundaria)
	FILE* invertedIndexDat = fopen("invertedIndex.dat", "w+");
	int invertedIndexRoot = 0;
	fwrite(&invertedIndexRoot, sizeof(int), 1, invertedIndexDat);

	printf("\nGerando (manpage/manPageIndex/inverted/invertedIndex).dat \n");

	for(int i = 1; i < argc; i++) {
		///////////////
		//MANPAGE.DAT//
		///////////////
		printf("%d - %s\n", i, &argv[i][9]);
		// Abre manpage.txt
		FILE* manPageTxt = fopen(argv[i], "r");

		// Verifica se ocorreu erro ao abrir o arquivo
		if(manPageTxt == NULL) {
			perror ("Erro ao abrir manpage.txt");
		}

		ManPage manPage;

		// Preenche o comando com espaço em branco
		for(int j = 0; j < commandSize; j++) {
			manPage.command[j] = ' ';
		}

		// Altera a ultima ocorrencia do '.' para o char de término '\0'
		*strrchr(argv[i], '.') = '\0';

		// Copia o nome do comando
		strcpy(manPage.command, argv[i]);

		// Retorna o argv[i] ao nome original
		*strchr(argv[i], '\0') = '.';

		// Preenche o conteudo com espaços em branco e as palavras
		for(int j = 0; j < contentSize; j++) {
			manPage.content[j] = ' ';
			wordsManPage[j] = ' ';
		}

		// Copia o conteudo e as palavras do txt
		int k;
		for(k = 0; !feof(manPageTxt); k++) {
			char c = fgetc(manPageTxt);
			manPage.content[k] = c;
			wordsManPage[k] = tolower(c);
		}

		// Seta o char de término do conteúdo
		manPage.content[k-1] = '\0';
		wordsManPage[k-1] = '\0';

		// Fecha o arquivo txt
		fclose(manPageTxt);

		// Escreve em manpages.dat
		int manpagePosition = ftell(manPageDat);
		fwrite(&manPage, sizeof(ManPage), 1, manPageDat);

		////////////////////
		//MANPAGEINDEX.DAT//
		////////////////////
		// Cria um nó com o comando atual
		FileNoAVL *avlNode = new FileNoAVL(manpagePosition,
										   manPage.command,
										   fopen("manPageIndex.dat", "r+"));
		rewind(manPageIndexDat);
		// Lê a raiz
		fread(&manPageIndexRoot, sizeof(int), 1, manPageIndexDat);
		// Insere o nó na árvore
		manPageIndexRoot = avlNode->insert(avlNode->getNode(), manPageIndexRoot);
		rewind(manPageIndexDat);
		// Atualiza a raiz
		fwrite(&manPageIndexRoot, sizeof(int), 1, manPageIndexDat);
		delete avlNode;

		////////////////////////////////////
		//INVERTED.DAT E INVERTEDINDEX.DAT//
		////////////////////////////////////
		// Corta o array de char na ocorrência dos delimitadores
		char *pch;
		pch = strtok(wordsManPage,
					 " ',.-+:<>[]()=;|_%*&$#@!?}{/^\"0123456789\t\r\n\f\v");

		// Realiza os cortes até o fim do array e também compara com a lista de
		// palavras ignoradas
		while(pch != NULL) {
			const char *c;
			bool accepted = true;
			for(unsigned int i = 0; i < ignoredStrings.size(); i++) {
				c = ignoredStrings[i].c_str();
				if(strcmp(pch, c) == 0) {
					accepted = false;
					break;
				}
			}
			if(accepted == true) {
				char pchTmp[100];
				for(int i=0; i<commandSize; i++) {
		 			pchTmp[i] = ' ';
				}
				strcpy(pchTmp, pch);
				FileNoAVL *avlNode = new FileNoAVL(0, pchTmp, fopen("invertedIndex.dat", "r+"));
				int wordAddress = avlNode->search(avlNode->getNode());
				delete avlNode;
				if (wordAddress == -1) {
					Word wordTmp;
					wordTmp.occurrenceIndex = 0;
					wordTmp.occurrences[wordTmp.occurrenceIndex] = manpagePosition;
					for(int j = 0; j < wordSize; j++) {
						wordTmp.word[j] = ' ';
					}
					strcpy(wordTmp.word, pch);
					fseek(invertedDat, 0, SEEK_END);
					int invertedPosition = ftell(invertedDat);
					fwrite(&wordTmp, sizeof(Word), 1, invertedDat);

					FileNoAVL *avlNode = new FileNoAVL(invertedPosition,
										   			   wordTmp.word,
										  			   fopen("invertedIndex.dat", "r+"));
					rewind(invertedIndexDat);
					// Lê a raiz
					fread(&invertedIndexRoot, sizeof(int), 1, invertedIndexDat);
					// Insere o nó na árvore
					invertedIndexRoot = avlNode->insert(avlNode->getNode(), invertedIndexRoot);
					rewind(invertedIndexDat);
					// Atualiza a raiz
					fwrite(&invertedIndexRoot, sizeof(int), 1, invertedIndexDat);
					delete avlNode;
				} else {
					fseek(invertedDat, wordAddress, SEEK_SET);
					Word wordTmp;
					fread(&wordTmp, sizeof(Word), 1, invertedDat);
					if(wordTmp.occurrences[wordTmp.occurrenceIndex] != manpagePosition) {
						wordTmp.occurrenceIndex++;
						wordTmp.occurrences[wordTmp.occurrenceIndex] = manpagePosition;
						fseek(invertedDat, wordAddress, SEEK_SET);
						fwrite(&wordTmp, sizeof(Word), 1, invertedDat);
						fflush(invertedDat);
					}
				}
			}

			pch = strtok (NULL,
						  " ',.-+:<>[]()=;|_%*&$#@!?}{/^\"\\0123456789\t\r\n\f\v`");
		}
	}

	// Fecha os arquivos
	fclose(invertedDat);
	fclose(invertedIndexDat);
	fclose(manPageDat);
	fclose(manPageIndexDat);
	ignoredStrings.clear();
	printf("Arquivos gerados com sucesso\n");
}

//! Função searchByCommand.
/*! Realiza a busca da manpage de um comando, pela sua chave primária.
 */
void searchByCommand(){
	printf("\nInforme o nome do comando a ser procurado:\n");
	char command[100] = "ManPages/";
	for(int i=9; i<commandSize; i++) {
		 command[i] = ' ';
	}
	scanf("%s", &command[9]);

	FileNoAVL *avlNode = new FileNoAVL(0, command, fopen("manPageIndex.dat", "r+"));
	int commandAddress = avlNode->search(avlNode->getNode());
	if (commandAddress == -1) {
		printf("Comando inexistente\n");
		return;
	}
	ManPage manPage;
	FILE* manPageDat = fopen("manpage.dat", "r");
	fseek(manPageDat, commandAddress, SEEK_SET);
	fread(&manPage, sizeof(ManPage), 1, manPageDat);
	printf("COMANDO: %s\n", manPage.command);
	printf("CONTEÚDO: %s\n", manPage.content);
	delete avlNode;
	fclose(manPageDat);
}

//! Função searchBySingleWord
/*! Realiza a busca de manpages que contém a
 * 	chave secundária definida pelo usuário
 */
void searchBySingleWord(){
	printf("\nInforme a palavra a ser procurada:\n");
	char word[100];
	for(int i=0; i<commandSize; i++) {
		 word[i] = ' ';
	}
	scanf("%s", word);

	FileNoAVL *avlNode = new FileNoAVL(0, word, fopen("invertedIndex.dat", "r+"));
	int wordAddress = avlNode->search(avlNode->getNode());
	delete avlNode;
	if (wordAddress == -1) {
		printf("Palavra inexistente\n");
		return;
	}

	Word wordTmp;
	FILE* invertedDat = fopen("inverted.dat", "r");
	fseek(invertedDat, wordAddress, SEEK_SET);
	fread(&wordTmp, sizeof(Word), 1, invertedDat);
	fclose(invertedDat);

	FILE* manPageDat = fopen("manpage.dat", "r");
	for(int i = 0; i <= wordTmp.occurrenceIndex; i++) {
		ManPage manPage;
		fseek(manPageDat, wordTmp.occurrences[i], SEEK_SET);
		fread(&manPage, sizeof(ManPage), 1, manPageDat);
		printf("%s\n", manPage.command);
	}
	fclose(manPageDat);
}

//! Função searchByTwoWord
/*! Realiza a busca de manpages que contém as duas
 * 	chaves secundárias definidas pelo usuário
 */
void searchByTwoWords() {
	printf("\nInforme a primeira palavra a ser procurada:\n");
	char word[100];
	for(int i=0; i<commandSize; i++) {
		 word[i] = ' ';
	}
	scanf("%s", word);

	FileNoAVL *avlNode = new FileNoAVL(0, word, fopen("invertedIndex.dat", "r+"));
	int wordAddress = avlNode->search(avlNode->getNode());
	delete avlNode;
	if (wordAddress == -1) {
		printf("Palavra inexistente\n");
		return;
	}

	printf("\nInforme a segunda palavra a ser procurada:\n");
	char word2[100];
	for(int i=0; i<commandSize; i++) {
		 word2[i] = ' ';
	}
	scanf("%s", word2);

	FileNoAVL *avlNode2 = new FileNoAVL(0, word2, fopen("invertedIndex.dat", "r+"));
	int wordAddress2 = avlNode2->search(avlNode2->getNode());
	delete avlNode2;
	if (wordAddress2 == -1) {
		printf("Palavra inexistente\n");
		return;
	}

	Word wordTmp;
	FILE* invertedDat = fopen("inverted.dat", "r");
	fseek(invertedDat, wordAddress, SEEK_SET);
	fread(&wordTmp, sizeof(Word), 1, invertedDat);

	Word wordTmp2;
	fseek(invertedDat, wordAddress2, SEEK_SET);
	fread(&wordTmp2, sizeof(Word), 1, invertedDat);
	fclose(invertedDat);


	std::vector<int> wordOccurrences = std::vector<int>();
	for(int i = 0; i <= wordTmp.occurrenceIndex; i++)
		wordOccurrences.push_back(wordTmp.occurrences[i]);
	sort(wordOccurrences.begin(), wordOccurrences.end());

	std::vector<int> wordOccurrences2 = std::vector<int>();
	for(int i = 0; i <= wordTmp2.occurrenceIndex; i++)
		wordOccurrences2.push_back(wordTmp2.occurrences[i]);
	sort(wordOccurrences2.begin(), wordOccurrences2.end());

	std::vector<int> intersection;
	set_intersection(wordOccurrences.begin(), wordOccurrences.end(),
					 wordOccurrences2.begin(), wordOccurrences2.end(),
					 back_inserter(intersection));

	if(intersection.size() == 0) {
		printf("\nNão existe a ocorrência destas duas palavras em um única manpage\n");
		return;
	}

	FILE* manPageDat = fopen("manpage.dat", "r");
	for(int i = 0; i < (int)intersection.size(); i++) {
		ManPage manPage;
		fseek(manPageDat, intersection[i], SEEK_SET);
		fread(&manPage, sizeof(ManPage), 1, manPageDat);
		printf("%s\n", manPage.command);
	}
	fclose(manPageDat);
}


int main (int argc, char* argv[]) {
	// INICIA O MENU DO PROGRAMA
	int input;
	system("clear");
	do{
		printf("\n");
		printf("Escolha o número desejado:\n");
		printf("[1] - Gerar (manpage/manPageIndex/inverted/invertedIndex).dat\n");
		printf("[2] - Buscar conteudo por nome do comando\n");
		printf("[3] - Buscar manpages por uma palavra secundária\n");
		printf("[4] - Buscar manpages por duas palavras\n");
		printf("[0] - Para sair\n");
		printf("\n");
		scanf("%d",&input);
		switch (input) {
			case 0:
				exit(0);
			case 1:
				createDatFiles(argc, argv);
				break;
			case 2:
				searchByCommand();
				break;
			case 3:
				searchBySingleWord();
				break;
			case 4:
				searchByTwoWords();
				break;
			default: printf("Opção inválida\n");
		}
	} while(input != 0);
	return 0;
}