Copyright Bruno Marques Do Nascimento e Salomão Rodrigues Jacinto

Os arquivos abaixo:
	-FileNoAVL.hpp
	-lexicalIgnored.txt
	-main.cpp

Devem estar localizados todos no mesmo diretório. Além disso, os arquivos com extensão "txt" que possuem os conteúdos das manpages, devem estar dentro de um diretório nomeado "ManPages" junto com os arquivos acima.

Exemplo de retorno do comando "ls" na pasta com os arquivos:

FileNoAVL.hpp lexicalIgnored.txt main.cpp ManPages


LINHA DE COMANDO PARA COMPILAÇÃO:

g++ -o main  *.cpp -g -lm -lutil -std=c++11 -Wall -Werror

LINHA DE COMANDO PARA EXECUÇÃO:

./main ManPages/*.txt