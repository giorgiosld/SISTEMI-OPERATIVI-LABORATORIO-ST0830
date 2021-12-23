#ifndef BVERNAM__H
#define BVERNAM__H

//typedef unsigned char byte;

typedef struct{
	unsigned char *buffer;
	unsigned long sizeBlock;
}block;

/*
Funzione necessaria per determinare la dimensione di un file
Utile per eseuire la divisione tra chiave e fileInput

@param path 	path relativo al file dal quale si vuole
				calcolare la dimensione

@return	long	uso di un valore di ritorno di tipo long per 
				calcolare la dim di file superiori a 2 GB			
*/
long retrieveDim(const char* path);

/*
Funzione necessaria per dividere il file "input" in una sequenza eseguendo la divisione
tra dimFileInput e dimKeyFile

@param pathKey
@param pathInput
@param pathOut
*/
void brokeFile(const char* pathKey, const char* pathInput, const char* pathOut);

/*
Funzione usata per aprire e controllre eventuali errori nei file

@param path		path relativo al file che si vuole aprire e controllare
@param type 	tipo per apertura del file
*/
FILE* openCheck(const char* path, int type);

/*
Funzione che divide il file in blocchi. Alloco un chunk della dimensione
mandata come parametro 

@param dim 			dimensione del blocco da allocare
@param *fp 			puntatore a file 
*/
block getBlock(long dim, FILE *fp);

/*
Funzione che codifica il file secondo la funzione XOR. 
Legge i byte dal chunk da criptare e cripta, byte per byte, con la chiave
usando la funzione xor. Successivamente scrive questo chunk criptato nel file 
di output

@param chunk 		il blocco da criptare
@fp1				il file dove bisogna scrivere byte crittografato
@fp2				il file con il quale si cripta
*/
void encodeXOR(block chunk, FILE *fp1, FILE *fp2, int seek, int dimk);

/*
Funzione principale di bvernam.c. Ha lo scopo di richiamare le altre funzioni 
all'interno della funzione chiamata dal main

@param dim 			dimensione del chunk con cui si lavorerà
*/
void bvernam(long dim, FILE *fp1, FILE *fp2, FILE *fp3, int seek, int dimk);

#endif