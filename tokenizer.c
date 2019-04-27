#include "tokenizer.h"

//theToken is the token to be populated
void read_token (token *theToken, FILE* in_file) {
  int i;
  char buffer[MAX_TOKEN_LENGTH + 1];
	char c = next_letter(in_file);
	if (c == EOF) {
			return;
	}
	buffer[0] = c;
  for (i=1; i<MAX_TOKEN_LENGTH; i++) {
    c = fgetc(in_file);
		if (c == EOF) {
			return;
		}
    if (c == ' ' || c == '\n' || c == '\t' || c == ';') {
      break;
    }
    buffer[i] = c;
  }
	if (c == ';') {
		c = skip_comment(in_file);
	}
  buffer[i] = '\0';
	strcpy(theToken->str, buffer);
	parse_token_type(theToken, buffer);
	
}


char skip_comment(FILE* in_file) {
	char c = fgetc(in_file);
	while (c != '\n') {
		c = fgetc(in_file);
	}
	//skip over new line
	return fgetc(in_file);
}

char next_letter(FILE* in_file) {
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
	return c;
}

void parse_token_type(token* token, char* buffer) {
	int i;
	int is_number = 1;
  char str[strlen(buffer)];
  strcpy(str, buffer);
  if (!strcmp(str, "+")) {
    token->type = PLUS;
		return;
  }
	if (!strcmp(str, "-")) {
    token->type = MINUS;
		return;
  }
	if (!strcmp(str, "*")) {
    token->type = MUL;
		return;
  }
	if (!strcmp(str, "/")) {
    token->type = DIV;
		return;
  }
	if (!strcmp(str, "%")) {
    token->type = MOD;
		return;
  }
	if (!strcmp(str, "^")) {
    token->type = POW;
		return;
  }
	if (!strcmp(str, "eq")) {
    token->type = EQ;
		return;
  }
	if (!strcmp(str, "lt")) {
    token->type = LT;
		return;
  }
	if (!strcmp(str, "gt")) {
    token->type = GT; 
		return;
  }
	if (!strcmp(str, "le")) {
    token->type = LE;
		return;
  }
	if (!strcmp(str, "ge")) {
    token->type = GE;
		return;
  }
	if (!strcmp(str, "and")) {
    token->type = AND;
		return;
  }
	if (!strcmp(str, "or")) {
    token->type = OR;
		return;
  }
	if (!strcmp(str, "xor")) {
    token->type = XOR;
		return;
  }
	if (!strcmp(str, "not")) {
    token->type = NOT;
		return;
  }
	if (!strcmp(str, "drop")) {
    token->type = DROP;
		return;
  }
	if (!strcmp(str, "dup")) {
    token->type = DUP;
		return;
  }
	if (!strcmp(str, "swap")) {
    token->type = SWAP;
		return;
  }
	if (!strcmp(str, "min")) {
    token->type = MIN;
		return;
  }
	if (!strcmp(str, "abs")) {
    token->type = ABS;
		return;
  }
	if (!strcmp(str, "avg")) {
    token->type = AVG;
		return;
  }
	if (!strncmp(str, "arg", 3)) {
		if (sscanf(str, "arg%d", &token->arg_no) == 1) {
			token->type = ARG;
		}else {
			token->type = BROKEN_TOKEN;
		}
		return;
  }
	if (!strcmp(str, "defun")) {
    token->type = DEFUN;
		return;
  }
	if (!strcmp(str, "ident")) {
    token->type = IDENT;
		return;
  }
	if (!strcmp(str, "return")) {
    token->type = RETURN;
		return;
  }
	if (!strcmp(str, "if")) {
    token->type = IF;
		return;
  }
	if (!strcmp(str, "else")) {
    token->type = ELSE;
		return;
  }
	if (!strcmp(str, "endif")) {
    token->type = ENDIF;
		return;
  }
	
	for(i=0;i<strlen(str);i++){
		is_number = is_number && (str[i] - '0' >= 0 && str[i] - '0' <= 9);
		if (!is_number) {
			token->type = BROKEN_TOKEN;
			return;
		}
	}
	if (is_number && i > 0) {
		sscanf(str, "%d", &token->literal_value);
		token->type = LITERAL;
		return;
	}
	
}

//used for debugging
void print_token (token *theToken) {
	printf("%s\n%", theToken->str);
}

   