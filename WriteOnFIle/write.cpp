#include <stdio.h>

typedef struct registro_st {
	char nome[50];
	char endereco[100];
} registro;

void saveOnDisc(registro r[], int length) {
	FILE *f = fopen("banco.txt", "w");

	for(int i = 0; i < length; i++)
		fwrite(&r[i], 150, 1, f);

	fclose(f);
}

long numberOfRegisters() {
	FILE *f = fopen("banco.txt", "r");
	fseek(f, 0, SEEK_END);
	long i = ftell(f);
	fclose(f);

	return i/150;
}

void readFromDisc(int index) {
	FILE *f = fopen("banco.txt", "r");
	fseek(f, 150*index, SEEK_SET);
	registro r;
	fread(&r, 150, 1, f);
	fclose(f);

	printf("Nome: %s, Endereço: %s\n", r.nome, r.endereco);

}

int main(int argc, char *argv[]) {
	registro r[10] = {{"Joao", "End tal"}, {"Maria", "GG"}};
	saveOnDisc(r, 2);
	readFromDisc(0);
	printf("%li\n", numberOfRegisters());
}