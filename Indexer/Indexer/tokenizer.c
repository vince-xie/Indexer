//
//  main.c
//  Tokenizer
//
//  Created by Vince Xie on 9/5/15.
//  Copyright (c) 2015 Vince Xie, Jacob Rizer. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "tokenizer.h"

/*
 * TKCreate creates a new TokenizerT object for a given token stream
 * (given as a string).
 *
 * TKCreate should copy the arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

TokenizerT *TKCreate( char * ts ) {
    TokenizerT *token = (TokenizerT *)malloc(sizeof(TokenizerT));
    token->token = (char *)malloc(strlen(ts) + 1);
    token->current = ts;
    return token;
}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy( TokenizerT * tk ) {
    free(tk->token);
    free(tk);
}


/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

char *TKGetNextToken( TokenizerT * tk ) {
    
    int i, j;
    
    for(i = 0; i < strlen(tk->current); i++){
        while(isspace(tk->current[i]) || !isalpha(tk->current[i])){
            if(tk->current[i] == '\0'){
                return NULL;
            }
            tk->current = &tk->current[1]; //deals with case of spaces in the beginning of input, multiple spaces
        }
        if(isalpha(tk->current[i])){ //checks if word
            for(j = i; j <= strlen(tk->current); j++){
                if(isspace(tk->current[j]) || !isalnum(tk->current[j]) || tk->current[j] == '\0'){
                    if(j == 0){ j = 1; }
                    strncpy(tk->token, tk->current, j);
                    tk->token[j] = '\0';
                    tk->current = &tk->current[j];
                    return tk->token;
                }
            }
        }
    }
    return NULL;
}
