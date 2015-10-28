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

void searchFile(char *directory, char *relativePath, FILE *output);

void searchDirectory(char *directory, char *relativePath, FILE *output);

void writeToOutputFile(FILE *output);

#endif /* indexer_h */
