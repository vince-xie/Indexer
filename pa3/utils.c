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
#include <ctype.h>

//Creates an entry struct. Time: O(1)
Entry *createEntry(char *path){
    Entry *entry = (Entry *)malloc(sizeof(Entry));
    entry->occur = 1;
    entry->path = (char *)malloc((strlen(path) + 1) * sizeof(char));
    strcpy(entry->path, path);
    entry->next = NULL;
    entry->prev = NULL;
    return entry;
}

//Frees an entry struct. Time: O(1)
void freeEntry(Entry *entry){
    free(entry->path);
    free(entry);
}

//Frees a list of entries. Time: O(l), l = size of list
void freeEntryList(Entry *entry){
    Entry *temp = entry;
    while(temp != NULL){
        temp = temp->next;
        freeEntry(entry);
        entry = temp;
    }
}

//Compares two entries. If they have the same number of occurances, then it compares the path names. Time: O(l), l = size of list
int compareEntries(Entry *entry, char *path, int occur){
    int diff = entry->occur - occur;
    if(diff != 0){
        return diff;
    }
    return strcmp(path, entry->path);
}

//Frees a list of entries. Time: O(l), l = size of list
Entry *insertEntry(char *path, Entry *head){
    if(head == NULL || path == NULL){
        return 0;
    }
    Entry *temp = head;
    int occur = 1;
    while(temp != NULL){
        if(strcmp(path, temp->path) == 0){
            occur = temp->occur + 1;
			if(temp == head){
                head->occur = occur;
				return head;
            }
            if(temp->prev){
                temp->prev->next = temp->next;
            }
            if(temp->next){
                temp->next->prev = temp->prev;
            }
            freeEntry(temp);
            break;
        }
        temp = temp->next;
    }
    Entry *entry = createEntry(path);
    entry->occur = occur;
    temp = head;
    while(temp != NULL){
        if(compareEntries(temp, path, occur) < 0){
            break;
        }
        if(temp->next == NULL){
            entry->prev = temp;
            temp->next = entry;
            return head;
        }
        temp = temp->next;
    }
    if(head == NULL){
        head = createEntry(path);
        head->occur = occur;
        return head;
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

//Checks to see if the path is to a directory. Time: O(1)
int isDir(const char *path) {
    struct stat buf;
    stat(path, &buf);
    return S_ISDIR(buf.st_mode);
}

//Checks to see if the path is to a file. Time: O(1)
int isFile(const char *path) {
    struct stat buf;
    stat(path, &buf);
    return S_ISREG(buf.st_mode);
}

//Not used. Gets full path from relative path.
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

//Creates a new tree node. Time: O(1)
Node * createNode(char *token){
	int length;
    Node* temp;
    temp = (Node*)malloc(sizeof(Node));

    
    length = strlen(token);

    
    temp->word = (char*)malloc(sizeof(char*) * length);

	
	
    strcpy(temp->word, token);
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

//Inserts a new tree node into a tree. Time: O(m), m = length of tree
Node * insertTree(Node * root, Node * element){
	
    if(root == NULL){
        return element;
	}else{
     
       if(strcmp(element->word, root->word) < 0){
            
            if (root->left != NULL)
                root->left = insertTree(root->left, element);
            else{
                root->left = element;
            }
        }
        else{

            if(root->right != NULL)
                root->right = insertTree(root->right, element);
            else
                root->right = element;
        }
            return root;
    }
    

}

//Searches for a word in a tree. Time: O(m), m = length of tree
Node * searchTree(Node * root, char * word){

	if (root != NULL) {

		if (strcmp(root->word, word) == 0){
			return root;
    }

    if (strcmp(word, root->word) < 0)
		return searchTree(root->left, word);

    else
		return searchTree(root->right, word);
	}

  else
    return NULL;
}

//Frees a tree. Time: O(m), m = number of nodes in tree
void freeTree(Node * root){
	if (root == NULL){
		return;
	}

	freeTree(root->left);
	freeTree(root->right);
	
	freeEntryList(root->head);
	free(root->word);
	free(root);
}

//Converts a string to lower case. Time: O(s) = length of string
char *strlwr(char *string)
{
	int i;
	int length = strlen(string);

	for(i=0; i<length; i++){
		string[i]=tolower((unsigned char)string[i]);
	}

	return string;
}
