/*
author: Giorgio Saldana 	Matricola: 110201	AnnoAccademico: 2020/2021

Progetto rappresentante l'implementazione di un sistema crittografico
Attuo a cifrare i file usando una variante del cifrario di Vernam. Questo sistema
è implementato usando la funzione XOR con la seguente formula:
	(A XOR B) XOR B = A

Abbiamo un file usato come chiave formato da k-byte(b[0]..b[k-1]) va a codificare 
un altro file dato dalla sequenza (d[0]..d[n]).
Ciò avviene dividendo la sequenza d in (N/K) blocchi formando cosi una sequenza 
D[0]..D[(N/K)-1] tutti della grandezza di K byte.

Successivamente la sequenza D[j]=D[j][0]..D[j][K-1] viene trasformata nella sequenza
D'[j]=D'[j][0]..D'[j][K-1] tale che per ogni i:
				d'[j][i] = b[(j+1)mod K] XOR d[j][i] 

Quindi il byte in posizione i del blocco j viene messo in XOR con il 
byte[(j+1)mod K] dell chiave

*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "bvernan.h"

int main(int argc, char** argv){

	char* keyFile;
	char* inputFile;
	char* outputFile;

	if(argc != 4){
		perror("Errore durante il passaggio degli argomenti. bvernam [keyfile] [inputfile] [outputfile]");
		exit(EXIT_FAILURE);
	}

	keyFile = argv[1];
	inputFile = argv[2];
	outputFile = argv[3];

	brokeFile(keyFile, inputFile, outputFile);

	return EXIT_SUCCESS;
}
