#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "bvernan.h"

long retrieveDim(const char* path){

    FILE *fp = NULL;
    long dim;

    fp = fopen(path, "rb");
    if (fp == NULL){
        perror("failed to fopen");
        exit(EXIT_FAILURE);
    }

    if (fseek(fp, 0, SEEK_END) == -1){
        perror("failed to fseek");
        exit(EXIT_FAILURE);
    }

    dim = ftell(fp);
    if (dim == -1){
        perror("failed to ftell");
        exit(EXIT_FAILURE);
    }

    fclose(fp);

	return dim;
}

void brokeFile(const char* pathKey, const char* pathInput, const char* pathOut){ 

    long dimKey = retrieveDim(pathKey);
    long dimFile = retrieveDim(pathInput);

    FILE* fpk;
    FILE* fpi;
    FILE* fpo;

    int numChunk = dimFile/dimKey;
    long dimChunk = dimKey;
    long irregularChunk = dimFile%dimKey;

    
    fpk = openCheck(pathKey, 1);
    fpi = openCheck(pathInput, 1);
    fpo = openCheck(pathOut, 2);

    int i = 0;
    while(i < numChunk){
        bvernam(dimChunk, fpk, fpi, fpo, i, dimKey);
        i++;
    }
    bvernam(irregularChunk, fpk, fpi, fpo, i, dimKey);

    fclose(fpk);
    fclose(fpi);
    fclose(fpo);
}
 
FILE* openCheck(const char* path, int type){

    FILE* fp = NULL;

    if(type == 1)
        fp = fopen(path, "rb");
    else if(type == 2)
        fp = fopen(path, "wb");

    if(fp == NULL){
        perror("Failed fopen:");
        exit(EXIT_FAILURE);
    }

    return fp;

}

block getBlock(long dim, FILE *fp){
    
    block chunk;

    unsigned char *p = (unsigned char*) malloc((dim+1)*sizeof(unsigned char));
    
    if(dim != fread(p, sizeof(unsigned char), dim, fp)){
        perror("Failed fread:");
        exit(EXIT_FAILURE);
    }
    chunk.buffer = p;
    chunk.sizeBlock = dim;
    return chunk;
}

void encodeXOR(block chunk, FILE *fpo, FILE *fpk, int seek, int dimk){

    unsigned char *buffer = chunk.buffer;
    int dim = chunk.sizeBlock;

    int i;
    
    unsigned char *k = (unsigned char*) malloc((dimk)*sizeof(unsigned char));
    if(dimk != fread(k, sizeof(unsigned char), dimk, fpk)){
        perror("Failed fread:");
    }
    unsigned char D;
    for(i = 0; i < dim; i++){

        D = *(buffer+i) ^ *(k+((i+seek)%dimk));
        if(fwrite(&D, sizeof(unsigned char), 1, fpo) != 1){
            perror("Failed fwrite:");
            exit(EXIT_FAILURE);
        }
    }
    
    free(k);
}

void bvernam(long dim, FILE *fpk, FILE *fpi, FILE *fpo, int seek, int dimk){

    block chunk = getBlock(dim, fpi);
    encodeXOR(chunk, fpo, fpk, seek, dimk);
    fseek(fpk, 0, SEEK_SET);
    free(chunk.buffer);

}
