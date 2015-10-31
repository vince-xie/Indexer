//
//  utils.c
//  Indexer
//
//  Created by Vince Xie on 10/28/15.
//  Copyright © 2015 Vince Xie. All rights reserved.
//

#include "utils.h"
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

Entry *createEntry(char *path){
    Entry *entry = (Entry *)malloc(sizeof(Entry));
    entry->occur = 1;
    entry->path = (char *)malloc(sizeof((strlen(path) + 1) * sizeof(char)));
    strcpy(entry->path, path);
    entry->next = NULL;
    entry->prev = NULL;
    return entry;
}

void freeEntry(Entry *entry){
    free(entry->path);
    free(entry);
}

void freeEntryList(Entry *entry){
    Entry *temp = entry->next;
    while(temp != NULL){
        temp = temp->next;
        free(entry);
        entry = temp;
    }
}

Indexer *createIndexer(){ //COMPLETE THIS
    Indexer *indexer = (Indexer *)malloc(sizeof(Indexer));
    return indexer;
}

void freeIndexer(Indexer *indexer){ //COMPLETE THIS, should also free all entrys associated with the indexer list
    free(indexer);
}

Entry *insertEntry(char *path, Entry *head){
    if(head == NULL || path == NULL){
        return 0;
    }
    Entry *temp = head;
    int occur = 1;
    while(temp != NULL){
        if(strcmp(path, temp->path) == 0){
            occur = temp->occur + 1;
            if(temp->prev){
                temp->prev->next = temp->next;
            }
            if(temp->next){
                temp->next->prev = temp->prev;
            }
            if(temp == head){
                head = head->next;
            }
            freeEntry(temp);
            break;
        }
        temp = temp->next;
    }
    temp = head;
    Entry *entry = createEntry(path);
    entry->occur = occur;
    temp = head;
    while(temp != NULL){
        if(temp->occur <= occur){
            break;
        }
        temp = temp->next;
    }
    while(strcmp(path, temp->path) < 0 && occur == temp->occur){
        if(temp->next == NULL){
            entry->prev = temp;
            temp->next = entry;
            return head;
        }
        temp = temp->next;
    }
    if(temp->prev){
        entry->prev = temp->prev;
    }
    entry->next = temp;
    entry->prev = temp->prev;
    if(temp->prev){
        temp->prev->next = entry;
    }
    temp->prev = entry;
    if(temp == head){
        head = entry;
    }
    return head;
}

int isDir(const char *path) {
    struct stat buf;
    stat(path, &buf);
    return S_ISDIR(buf.st_mode);
}

int isFile(const char *path) {
    struct stat buf;
    stat(path, &buf);
    return S_ISREG(buf.st_mode);
}

void getFullPath(char *path, char *relative, char *dest){
    long i = strlen(path);
    for(; i >= 0; i--){
        if(path[i] == '/'){
            break;
        }
    }
    strncpy(dest, path, i);
    strcat(dest, "/");
    strcat(dest, relative);
}