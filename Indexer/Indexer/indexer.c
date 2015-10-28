//
//  indexer.c
//  Indexer
//
//  Created by Vince Xie on 10/28/15.
//  Copyright © 2015 Vince Xie. All rights reserved.
//

#include "indexer.h"
#include "tokenizer.h"
#include <stdlib.h>
#include <unistd.h>
#include "utils.h"
#include <dirent.h>
#include <string.h>

void searchFile(char *filename, char *relativePath, FILE *output){
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Cannot open input file \"%s\"\n", filename);
        return;
    }
    fputs("\n", output); //next 4 lines will be changed. For testing purposes
    fputs("FILE: ", output);
    fputs(relativePath, output);
    fputs("\n", output);
    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    rewind(file);
    char *string = malloc((filesize + 1) * sizeof(char));
    fread(string, sizeof(char), filesize, file);
    string[filesize] = '\0';
    fclose(file);
    TokenizerT *tk = TKCreate(string);
    while(tk->current[0] != '\0'){
        char *token = TKGetNextToken(tk);
        if(token == NULL){
            break;
        }
        fputs(token, output); //next 2 lines will be changed. For testing purposes
        fputc('\n', output);
    }
    TKDestroy(tk);
}

void searchDirectory(char *directory, char *relativePath, FILE *output){
    DIR *dir = opendir(directory);
    char temp[256];
    char path[256];
    if(!dir){
        printf("Could not open directory \"%s\"\n", directory);
    }
    struct dirent *ent;
    while((ent = readdir(dir)) != NULL) {
        if(ent->d_name[0] != '.'){
            strcpy(temp, directory);
            strcat(temp, "/");
            strcat(temp, ent->d_name);
            strcpy(path, relativePath);
            strcat(path, "/");
            strcat(path, ent->d_name);
            if(isDir(temp)){
                searchDirectory(temp, path, output);
            } else {
                searchFile(temp, path, output);
            }
        }
    }
    closedir(dir);
}

void writeToOutputFile(FILE *output){
    
}

int main(int argc, char **argv) {
    if(argc != 3){
        printf("Wrong number of inputs\n");
        return 1;
    }
    if(argv[1] == NULL){
        printf("Usage: ./indexer [output file] [input file or directory]");
    }
    if(argv[2] == NULL){
        printf("Please enter a file or directory as an argument.\n");
        return 1;
    }
    char pathToOutput[256];
    char pathToFoD[256];
    
    getFullPath(argv[0], argv[1], pathToOutput);
    getFullPath(argv[0], argv[2], pathToFoD);
    
    FILE *test = fopen(pathToOutput, "r");
    if(test){
        printf("Output file already exists. Would you like to overwrite? (y/n) \n");
        char input = 'n';
        scanf ("%c", &input);
        if(input == 'n'){
            printf("Quitting...\n");
            return 0;
        } else if(input != 'y'){
            printf("Invalid input. Quitting...\n");
            return 1;
        }
    }
    fclose(test);
    
    if(!isDir(pathToFoD) && !isFile(pathToFoD)){
        printf("Could not open directory or file \"%s\"\n", argv[2]);
        return 1;
    }
    FILE *output = fopen(pathToOutput, "w");
    if(isDir(pathToFoD)){
        searchDirectory(pathToFoD, argv[2], output);
    }
    if(isFile(pathToFoD)){
        searchFile(pathToFoD, argv[1], output);
    }
    
    writeToOutputFile(output);
    fclose(output);
    printf("Done.\n");
    return 0;
}