#include "tokenizer.h"

//theToken is the token to be populated
void read_token (token* theToken, FILE* in_file) {
  int i;
  seek_letter(in_file);
  read_string_into(theToken, in_file);
	parse_token_type(theToken);
  if (theToken->type == DEFUN) {
    seek_letter(in_file);
    read_string_into(theToken, in_file);
  }
}

void read_string_into(token* theToken, FILE* in_file) {
  char buffer[MAX_TOKEN_LENGTH];
  char c;
  int i = 0;
  while (i < MAX_TOKEN_LENGTH) {
    c = fgetc(in_file);
    if (c == ' ' || c == '\n' || c == '\t' || c == ';' || c == EOF) {
      ungetc(c, in_file);
      break;
    }
    buffer[i] = c;
    i++;
  }
  buffer[i] = '\0';
  memcpy(theToken->str, buffer, (i+1)*sizeof(char));
}

//in the case where we are expecting the next token to be separated by whitespace or a comment
void seek_letter(FILE* in_file) {
	char c = fgetc(in_file);
	while (c == ' ' || c == ';' || c == '\n' || c == '\t') {
		switch(c) {
			case ';':
				c = skip_comment(in_file);
				break;
			default:
				c = fgetc(in_file);
				break;
		}
	}
  ungetc(c, in_file);
}

//in the case we just want to skip a comment (skips rest of line)
char skip_comment(FILE* in_file) {
	char c = fgetc(in_file);
	while (c != '\n') {
		c = fgetc(in_file);
    if (c == EOF) {
      return EOF;
    }
	}
	//skip over new line
	return fgetc(in_file);
}


void parse_token_type(token* theToken) {
	int i;
	int is_number = 1;
  if (!strcmp(theToken->str, "+")) {
    theToken->type = PLUS;
		return;
  }
	if (!strcmp(theToken->str, "-")) {
    theToken->type = MINUS;
		return;
  }
	if (!strcmp(theToken->str, "*")) {
    theToken->type = MUL;
		return;
  }
	if (!strcmp(theToken->str, "/")) {
    theToken->type = DIV;
		return;
  }
	if (!strcmp(theToken->str, "%")) {
    theToken->type = MOD;
		return;
  }
	if (!strcmp(theToken->str, "^")) {
    theToken->type = POW;
		return;
  }
	if (!strcmp(theToken->str, "eq")) {
    theToken->type = EQ;
		return;
  }
	if (!strcmp(theToken->str, "lt")) {
    theToken->type = LT;
		return;
  }
	if (!strcmp(theToken->str, "gt")) {
    theToken->type = GT; 
		return;
  }
	if (!strcmp(theToken->str, "le")) {
    theToken->type = LE;
		return;
  }
	if (!strcmp(theToken->str, "ge")) {
    theToken->type = GE;
		return;
  }
	if (!strcmp(theToken->str, "and")) {
    theToken->type = AND;
		return;
  }
	if (!strcmp(theToken->str, "or")) {
    theToken->type = OR;
		return;
  }
	if (!strcmp(theToken->str, "xor")) {
    theToken->type = XOR;
		return;
  }
	if (!strcmp(theToken->str, "not")) {
    theToken->type = NOT;
		return;
  }
	if (!strcmp(theToken->str, "drop")) {
    theToken->type = DROP;
		return;
  }
	if (!strcmp(theToken->str, "dup")) {
    theToken->type = DUP;
		return;
  }
	if (!strcmp(theToken->str, "swap")) {
    theToken->type = SWAP;
		return;
  }
	if (!strcmp(theToken->str, "min")) {
    theToken->type = MIN;
		return;
  }
	if (!strcmp(theToken->str, "abs")) {
    theToken->type = ABS;
		return;
  }
	if (!strcmp(theToken->str, "avg")) {
    theToken->type = AVG;
		return;
  }
	if (!strncmp(theToken->str, "arg", 3)) {
		if (sscanf(theToken->str, "arg%d", &theToken->arg_no) == 1) {
			theToken->type = ARG;
		}else {
			theToken->type = BROKEN_TOKEN;
		}
		return;
  }
	if (!strcmp(theToken->str, "defun")) {
    theToken->type = DEFUN;
		return;
  }
	if (!strcmp(theToken->str, "ident")) {
    theToken->type = IDENT;
		return;
  }
	if (!strcmp(theToken->str, "return")) {
    theToken->type = RETURN;
		return;
  }
	if (!strcmp(theToken->str, "if")) {
    theToken->type = IF;
		return;
  }
	if (!strcmp(theToken->str, "else")) {
    theToken->type = ELSE;
		return;
  }
	if (!strcmp(theToken->str, "endif")) {
    theToken->type = ENDIF;
		return;
  }
	
  if (theToken->str[0] == '-') {
    //negative
    i = 1;
  } else {
    i = 0;
  }
  
	for(i;i<strlen(theToken->str);i++){
		is_number = is_number && (theToken->str[i] - '0' >= 0 && theToken->str[i] - '0' <= 9);
		if (!is_number) {
			theToken->type = BROKEN_TOKEN;
			return;
		}
	}
	if (is_number && i > 0) {
		sscanf(theToken->str, "%d", &theToken->literal_value);
		theToken->type = LITERAL;
		return;
	}
	theToken->type = BROKEN_TOKEN;
	return;
}

//used for debugging
void print_token (token *theToken) {
	printf("%s\n%", theToken->str);
}

   