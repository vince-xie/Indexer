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

void searchFile(char *filename){
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Cannot open input file \"%s\"\n", filename);
        return;
    }
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
        printf("%s\n", token);
    }
    TKDestroy(tk);
}

void searchDirectory(char *directory){
    DIR *dir = opendir(directory);
    char temp[256];
    if(!dir){
        printf("Could not open directory \"%s\"\n", directory);
    }
    struct dirent *ent;
    while((ent = readdir(dir)) != NULL) {
        if(ent->d_name[0] != '.'){
            strcpy(temp, directory);
            strcat(temp, "/");
            strcat(temp, ent->d_name);
            if(isDir(temp)){
                searchDirectory(temp);
            } else {
                searchFile(temp);
            }
        }
    }
    closedir(dir);
}

int main(int argc, char **argv) {
    if(argv[1] == NULL){
        printf("Usage: ./indexer [output file] [input file or directory]");
    }
    if(argv[2] == NULL){
        printf("Please enter a file or directory as an argument.\n");
        return 1;
    }
    DIR *dir = opendir(argv[2]);
    if(!dir){
        printf("Could not open directory or file\"%s\"\n", argv[2]);
        return 1;
    }
    struct dirent *ent;
    while((ent = readdir(dir)) != NULL) {
        if(strcmp(ent->d_name, argv[1]) == 0){
            printf("File already exists. Would you like to overwrite? 1 (yes) or 0 (no) \n");
            int *input = malloc(sizeof(int));
            scanf ("%d", input);
            if(*input == 0){
                printf("Quitting... \n");
                return 0;
            }
            free(input);
        }
    }
    if(isDir(argv[2])){
        searchDirectory(argv[2]);
    }
    if(isFile(argv[2])){
        searchFile(argv[2]);
    }
    return 0;
}