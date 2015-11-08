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

typedef struct table{
    //FILL OUT
} Indexer;

Entry *createEntry(char *path);

void freeEntry(Entry *entry);

void freeEntryList(Entry *entry);

Indexer *createIndexer();

void freeIndexer(Indexer *indexer);

int compareEntries(Entry *entry, char *path, int occur);

Entry *insertEntry(char *path, Entry *head);

int isDir(const char *path);

int isFile(const char *path);

void getFullPath(char *path, char *relative, char *dest);


#endif /* utils_h */
