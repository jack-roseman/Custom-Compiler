#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "token.h"

//helper functions (implement these)
void parse_token_type(token* theToken);
//skips over whitespace
void seek_letter(FILE* in_file);
//skips over a comment in the file
char skip_comment(FILE* in_file);
//theToken is the token to be populated
void read_token (token *theToken, FILE* in_file);
void read_string_into(token* theToken, FILE* in_file);
//used for debugging
void print_token (token *theToken);


#endif
