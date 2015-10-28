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