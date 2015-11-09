//
//  utils.h
//  Indexer
//
//  Created by Vince Xie on 10/28/15.
//  Copyright © 2015 Vince Xie. All rights reserved.
//

#ifndef utils_h
#define utils_h

#include <stdio.h>

typedef struct dataEntry{
    char *path;
    int occur;
    struct dataEntry *next;
    struct dataEntry *prev;
} Entry;

typedef struct node { 
	char *word; 
	struct node * left; 
	struct node * right;
	Entry* head;
}Node;


Entry *createEntry(char *path);

void freeEntry(Entry *entry);

void freeEntryList(Entry *entry);

int compareEntries(Entry *entry, char *path, int occur);

Entry *insertEntry(char *path, Entry *head);

int isDir(const char *path);

int isFile(const char *path);

void getFullPath(char *path, char *relative, char *dest);

Node * createNode(char *token);

Node * insertTree(Node *root, Node* element);

Node * searchTree(Node * root, char * word);

void freeTree(Node * root);

char *strlwr(char *string);



#endif /* utils_h */
