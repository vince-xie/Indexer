//
//  indexer.h
//  Indexer
//
//  Created by Vince Xie on 10/28/15.
//  Copyright © 2015 Vince Xie. All rights reserved.
//

#ifndef indexer_h
#define indexer_h

#include <stdio.h>
#include "utils.h"

void searchFile(char *filename, Node * root);

void searchDirectory(char *directory, Node * root);

void writeToOutputFile(FILE *output, Node * root);

void traverseTree(Node * temp, FILE *output);

void traverseList(Entry * entry, FILE *output);

#endif /* indexer_h */
