// Copyright Bruno Marques Do Nascimento e Salomão Rodrigues Jacinto <2016.1>

#include <vector>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "FileNoAVL.hpp"
#include "InvertedList.hpp"

static const int commandSize = 100;
static const int contentSize = 139900;
static const int lexicalIgnoredSize = 1380;

//!  Struct do elemento comando com manpage.
/*!  Struct que possui o nome do comando e
 *   conteúdo da manpage do comando.
 */
typedef struct ManPage {
	char command[commandSize];
	char content[contentSize];
} ManPage;

char lexicalIgnored[lexicalIgnoredSize];
char wordsManPage[contentSize];
std::vector<std::string> ignoredStrings = std::vector<std::string>();
std::vector<std::string> acceptedStrings = std::vector<std::string>();

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
}

//! Função createDatFiles.
/*! Responsável por gerar os arquivos (manpage/index/inverted).dat
 *  \param argc número de arquivos.txt que serão lidos
 *  \param argv array com os nomes dos arquivos.txt a serem lidos
 */
void createDatFiles(int argc, char *argv[]) {
	// Cria o arquivo manpage.dat (guarda as manpages)
	FILE* manPageDat = fopen("manpage.dat", "w");

	// Cria o arquivo inverted.dat (guarda o arquivo invertido, chaves secundarias)
	FILE* invertedDat = fopen("inverted.dat", "w+");
	int invertedRoot = 0;
	fwrite(&invertedRoot, sizeof(int), 1, invertedDat);
	ignoredWords();

	// Cria o arquivo index.dat (guarda a arvore de chave primaria)
	FILE* indexDat = fopen("index.dat", "w+");
	int indexRoot = 0;
	fwrite(&indexRoot, sizeof(int), 1, indexDat);
	printf("\nGerando MAPAGE.DAT, INDEX.DAT E INVERTED.DAT\n");
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

		// Preenche o conteudo com espaços em branco
		for(int j = 0; j < contentSize; j++) {
			manPage.content[j] = ' ';
			wordsManPage[j] = ' ';
		}

		// Copia o conteudo do txt e as palavras aceitas
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

		/////////////
		//INDEX.DAT//
		/////////////

		// Cria um nó com o comando atual
		FileNoAVL *avlNode = new FileNoAVL(manpagePosition, manPage.command);
		rewind(indexDat);
		// Lê a raiz
		fread(&indexRoot, sizeof(int), 1, indexDat);
		// Insere o nó na árvore
		indexRoot = avlNode->insert(avlNode->getNode(), indexRoot);
		rewind(indexDat);
		// Atualiza a raiz
		fwrite(&indexRoot, sizeof(int), 1, indexDat);
		delete avlNode;

		////////////////
		//INVERTED.DAT//
		////////////////

		// Corta o array de char na ocorrência dos delimitadores
		char *pch;
		pch = strtok(wordsManPage,
					 " ',.-+:<>[]()=;|_%*&$#@!?}{/^\"0123456789\t\r\n\f\v");

		// Realiza os cortes até o fim do array e também compara com a lista de
		// palavras ignoradas
		while(pch != NULL) {
			unsigned int w;
			const char *c;
			for(w = 0; w < ignoredStrings.size(); w++) {
				c = ignoredStrings[w].c_str();
				if(strcmp(pch, c) == 0)
					break;
			}
			if(w == ignoredStrings.size())
				acceptedStrings.push_back(pch);

			pch = strtok (NULL,
						  " ',.-+:<>[]()=;|_%*&$#@!?}{/^\"\\0123456789\t\r\n\f\v`");
		}

		// Remove duplicatas de uma mesma ManPage
		sort(acceptedStrings.begin(), acceptedStrings.end());
		acceptedStrings.erase(unique(acceptedStrings.begin(), acceptedStrings.end()),
															  acceptedStrings.end());

		for(int j = 0; j < (int)acceptedStrings.size(); j++) {
			const char *word = acceptedStrings[j].c_str();
			// Cria um nó com a palavra atual
			InvertedList *invertedNode = new InvertedList(manpagePosition, word);
			rewind(invertedDat);
			// Lê a raiz
			fread(&invertedRoot, sizeof(int), 1, invertedDat);
			// Insere o nó na árvore e atualiaz a raiz
			invertedRoot = invertedNode->insert(invertedNode->getWord(), invertedRoot);
			rewind(invertedDat);
			// Atualiza a raiz
			fwrite(&invertedRoot, sizeof(int), 1, invertedDat);
			delete invertedNode;
	   }

	   acceptedStrings.clear();
	}

	// Fecha os arquivos
	fclose(invertedDat);
	fclose(manPageDat);
	fclose(indexDat);
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

	FileNoAVL *avlNode = new FileNoAVL(0, command);
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

	InvertedList *avlInverted = new InvertedList(0, word);
	Word wordNode = avlInverted->search(avlInverted->getWord());
	if (wordNode.occurrenceIndex == -1) {
		printf("Palavra não encontrada\n");
		return;
	}

	FILE* manPageDat = fopen("manpage.dat", "r");
	for(int i = 0; i <= wordNode.occurrenceIndex; i++) {
		ManPage manPage;
		fseek(manPageDat, wordNode.occurrences[i], SEEK_SET);
		fread(&manPage, sizeof(ManPage), 1, manPageDat);
		printf("%s\n", manPage.command);
	}
	delete avlInverted;
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

	InvertedList *avlInverted = new InvertedList(0, word);
	Word wordNode = avlInverted->search(avlInverted->getWord());
	if (wordNode.occurrenceIndex == -1) {
		printf("Palavra não encontrada\n");
		delete avlInverted;
		return;
	}

	printf("\nInforme a segunda palavra a ser procurada:\n");
	char word2[100];
	for(int i=0; i<commandSize; i++) {
		 word2[i] = ' ';
	}
	scanf("%s", word2);

	InvertedList *avlInverted2 = new InvertedList(0, word2);
	Word wordNode2 = avlInverted2->search(avlInverted2->getWord());
	if (wordNode2.occurrenceIndex == -1) {
		printf("Palavra não encontrada\n");
		delete avlInverted;
		delete avlInverted2;
		return;
	}

	std::vector<int> wordOccurrences = std::vector<int>();
	for(int i = 0; i <= wordNode.occurrenceIndex; i++)
		wordOccurrences.push_back(wordNode.occurrences[i]);
	sort(wordOccurrences.begin(), wordOccurrences.end());

	std::vector<int> wordOccurrences2 = std::vector<int>();
	for(int i = 0; i <= wordNode2.occurrenceIndex; i++)
		wordOccurrences2.push_back(wordNode2.occurrences[i]);
	sort(wordOccurrences2.begin(), wordOccurrences2.end());

	std::vector<int> intersection;
	set_intersection(wordOccurrences.begin(), wordOccurrences.end(),
					 wordOccurrences2.begin(), wordOccurrences2.end(),
					 back_inserter(intersection));

	if(intersection.size() == 0) {
		printf("\nNão existe a ocorrência destas duas palavras em um única manpage\n");
		delete avlInverted;
		delete avlInverted2;
		return;
	}

	FILE* manPageDat = fopen("manpage.dat", "r");
	for(int i = 0; i < (int)intersection.size(); i++) {
		ManPage manPage;
		fseek(manPageDat, intersection[i], SEEK_SET);
		fread(&manPage, sizeof(ManPage), 1, manPageDat);
		printf("%s\n", manPage.command);
	}
	delete avlInverted;
	delete avlInverted2;
	fclose(manPageDat);
}


int main (int argc, char* argv[]) {
	// INICIA O MENU DO PROGRAMA
	int input;
	system("clear");
	do{
		printf("\n");
		printf("Escolha o número desejado:\n");
		printf("[1] - Gerar (manpage/index/inverted).dat\n");
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