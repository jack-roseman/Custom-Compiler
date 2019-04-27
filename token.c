#include "token.h"

token* init_token() {
	//make sure you initialize char* in token. The length of str will be MAX_TOKEN_LENGTH
	token* tok = (token*) malloc(sizeof(token));
	tok->str = (char*) malloc(MAX_TOKEN_LENGTH*sizeof(char));
	tok->type = EMPTY;
	return tok;
}

void delete_token(token* theToken) {
	//make sure you delete char* in token 
	free(theToken->str);
  free(theToken);
}
  