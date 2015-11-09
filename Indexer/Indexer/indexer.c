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

//Reads in tokens from a file and adds them to the tree. O(mn), n = length of file, m = length of tree
void searchFile(char *filename, Node * root){
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
    
    char *token;
    //get first token for root of tree
    if(root->word == NULL){
        char *token = TKGetNextToken(tk);
        int numChars;
        if(token == NULL){
            TKDestroy(tk);
            return;
        }
        token = strlwr(token);
        
        Entry *entry = createEntry(filename);
        
        numChars = strlen(token)+1;
        
        root->word = (char*)malloc(sizeof(char) * numChars);
        
        strcpy(root->word, token);
        
        root->head = entry;
    }
    
    while(tk->current[0] != '\0'){
        token = TKGetNextToken(tk);
        if(token == NULL){
            break;
        }
        
        token = strlwr(token);
        
        
        Node * search = searchTree(root, token);
        
        
        if(search != NULL){
            
            Entry * head = search->head;
            search->head = insertEntry(filename, head);
            
        }else{
            Entry *entry = createEntry(filename);
            Node * x = createNode(token);
            x->head = entry;
            insertTree(root, x);
            
        }
        
        
    }
    TKDestroy(tk);
    free(string);
}

//Prints out list of entries
void printList(Entry *head){
    Entry *temp = head;
    while(temp != NULL){
        printf("%s: %d\n", temp->path, temp->occur);
        temp = temp->next;
    }
}

//Recursively traverses directories and calls searchFile() to add tokens to the tree. Time: O(mno), n = length of file, m = length of tree, o = number of directories and files
void searchDirectory(char *directory, Node * root){
    DIR *dir = opendir(directory);
    char path[256];
    if(!dir){
        printf("Could not open directory \"%s\"\n", directory);
    }
    struct dirent *ent;
    while((ent = readdir(dir)) != NULL) {
        if(ent->d_name[0] != '.'){
            strcpy(path, directory);
            strcat(path, "/");
            strcat(path, ent->d_name);
            if(isDir(path)){
                searchDirectory(path, root);
            } else {
                searchFile(path, root);
            }
        }
    }
    closedir(dir);
}

//Writes out all data from the tree to the output file by calling traverseTree(). Time: O(m), m = length of tree
void writeToOutputFile(FILE *output, Node * root){
    
    fputs("{\"list\" : [\n", output);
    
    Node * temp = root;
    
    traverseTree(temp, output);
    
    fseeko(output,-2,SEEK_END);
    
    fputs("\n]}", output);
    
}

//Recursively traverses through the tree using an in-order traversal and outputs it to the output file. Time: O(m), m = length of tree
void traverseTree(Node * temp, FILE *output) {
    if (temp != NULL && temp->word != NULL) {
        traverseTree(temp->left, output);
        
        fprintf(output, "\t{\"%s\" : [\n", temp->word);
        
        traverseList(temp->head, output);
        
        fputs("\t]},\n", output);
        
        traverseTree(temp->right, output);
    }
}

//Traverses through a list of Entry structs and outputs it to the file. Time: O(p), p = length of list
void traverseList(Entry * head, FILE *output){
    
    Entry * temp = head;
    
    while(temp != NULL){
        if(temp->next != NULL){
            fprintf(output, "\t\t{\"%s\" : %d},\n", temp->path, temp->occur);
        }else{
            fprintf(output, "\t\t{\"%s\" : %d}\n", temp->path, temp->occur);
        }
        
        temp = temp->next;
    }
    
    
    
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
    
    FILE *test = fopen(argv[1], "r");
    if(test != NULL){
        printf("Output file already exists. Would you like to overwrite? (y/n) \n");
        char input = 'n';
        scanf ("%c", &input);
        if(input == 'n'){
            fclose(test);
            printf("Quitting...\n");
            return 0;
        } else if(input != 'y'){
            fclose(test);
            printf("Invalid input. Quitting...\n");
            return 1;
        }
        fclose(test);
    }
    
    if(!isDir(argv[2]) && !isFile(argv[2])){
        printf("Could not open directory or file \"%s\"\n", argv[2]);
        return 1;
    }
    
    Node * Root = (Node*)malloc(sizeof(Node));
    Root->word = NULL;
    Root->left = NULL;
    Root->right = NULL;
    Root->head = NULL;
    
    FILE *output = fopen(argv[1], "w");
    if(isDir(argv[2])){
        searchDirectory(argv[2], Root);
    }
    if(isFile(argv[2])){
        searchFile(argv[2], Root);
    }
    
    writeToOutputFile(output, Root);
    freeTree(Root);
    fclose(output);
    printf("Done.\n");
    
    return 0;
}