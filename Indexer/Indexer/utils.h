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

int isDir(const char *path);

int isFile(const char *path);

void getFullPath(char *path, char *relative, char *dest);

#endif /* utils_h */
