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

void searchFile(char *filename, char *relativePath, Indexer *wordlist){
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
        /* Pseudo-code
            if(word found in word list){
                insertEntry(relativePath, head);
            } else {
                Entry *entry = createEntry();
                put entry in word list
            }
        */
    }
    TKDestroy(tk);
}

void printList(Entry *head){
    Entry *temp = head;
    while(temp != NULL){
        printf("%s: %d\n", temp->path, temp->occur);
        temp = temp->next;
    }
}

void searchDirectory(char *directory, char *relativePath, Indexer *wordlist){
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
                searchDirectory(temp, path, wordlist);
            } else {
                searchFile(temp, path, wordlist);
            }
        }
    }
    closedir(dir);
}

void writeToOutputFile(FILE *output, Indexer *list){
    //FILL THIS OUT (outputs JSON using data in the data structure into the file)
}

/* int main(int argc, char **argv){ //used for testing linked list implementation - ignore
    Entry *head = createEntry("test");
    head = insertEntry("test", head);
    head = insertEntry("test", head);
    head = insertEntry("test", head);
    head = insertEntry("test3", head);
    head = insertEntry("test3", head);
    head = insertEntry("test2", head);
    head = insertEntry("test2", head);
    head = insertEntry("apple", head);
    head = insertEntry("apple", head);
    head = insertEntry("apple", head);
    head = insertEntry("aa", head);
    head = insertEntry("test3", head);
    head = insertEntry("bb", head);
    head = insertEntry("bb", head);
    head = insertEntry("a", head);
    head = insertEntry("c", head);
    head = insertEntry("tester", head);
    head = insertEntry("tester", head);
    head = insertEntry("tester", head);
    head = insertEntry("tester", head);
    printList(head);
    freeEntryList(head);
} */
 
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
    
    Indexer *list = createIndexer();
    
    FILE *output = fopen(pathToOutput, "w");
    if(isDir(pathToFoD)){
        searchDirectory(pathToFoD, argv[2], list);
    }
    if(isFile(pathToFoD)){
        searchFile(pathToFoD, argv[1], list);
    }
    
    writeToOutputFile(output, list);
    freeIndexer(list);
    fclose(output);
    printf("Done.\n");
    return 0;
}