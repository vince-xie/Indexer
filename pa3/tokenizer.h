//
//  Tokenizer.h
//  Indexer
//
//  Created by Vince Xie on 10/28/15.
//  Copyright © 2015 Vince Xie. All rights reserved.
//

#ifndef tokenizer_h
#define tokenizer_h

struct TokenizerT_ {
    char *current;
    char *token;
};

typedef struct TokenizerT_ TokenizerT;

TokenizerT *TKCreate( char * ts );

void TKDestroy( TokenizerT * tk );

char *TKGetNextToken( TokenizerT * tk );

#endif /* tokenizer_h */
