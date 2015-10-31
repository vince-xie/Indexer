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

void searchFile(char *directory, char *relativePath, Indexer *wordlist);

void searchDirectory(char *directory, char *relativePath, Indexer *wordlist);

void writeToOutputFile(FILE *output, Indexer *list);

#endif /* indexer_h */
