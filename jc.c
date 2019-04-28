#include "hash.h"
#include "tokenizer.h"
typedef struct {
  //used for keeping track of looping
  int loop_id;
  int next_loop;
  //whether we are in an if statement or not
  int if_statement;
  //whether we are in an else statement or not
  int else_statement;
  //whether we are in an function definition or not
  int defun_statement;
  //used for debug
  char defun_name[MAX_TOKEN_LENGTH];
} state;

int main(int argc, char *argv[]) {
  FILE* in_file;
  FILE* out_file;
  state q = {-1, -1, 0, 0, 0, ""};
  hash_struct* loops = initTable(15);
  if (argc != 2 || argv[1][strlen(argv[1]) - 2] != '.' || argv[1][strlen(argv[1]) - 1] != 'j') {
    printf("Invalid argument.\n");
    return 0;
  }
  in_file = fopen(argv[1], "r");
  if (in_file == NULL) {
    printf("Invalid file.\n");
    return 0;
  }
  while (1) {
    token* tok = init_token();
    read_token(tok, in_file);
    //print_token(tok);
    //
    //DFA 
    switch (tok->type) {
      case DEFUN:
        if (q.defun_statement) { //can't declare a function within a function
          printf("Error. Function \"%s\" is missing return call.\n", q.defun_name);
          return 0;
        }
        q.defun_statement = 1;
        strcpy(q.defun_name, tok->str);
        put(loops, q.loop_id + 1, q.next_loop);
        q.loop_id++;
        q.next_loop++;
        printf("%s\n", tok->str);
        break; 
      case RETURN:
        if (!q.defun_statement) {
          printf("Error. Return call does not correspond to a function declaration.\n");
          return 0;
        }
        printf("return\n");
        q.defun_statement = 0;
        q.next_loop = get(loops, q.next_loop)->value;
        break;
      case IF:
        printf("if\n");
        q.if_statement = 1;
        put(loops, q.loop_id + 1, q.next_loop);
        q.loop_id++;
        q.next_loop++;
        //printf("loop %d %s\n", q.next_loop, tok->str);
        break;
      case ELSE:
        if (!q.if_statement) {
          printf("Error. Else statement must correspond to an if statement.\n");
          return 0;
        }
        printf("else\n");
        q.if_statement = 0;
        q.else_statement = 1;
        //printf("loop %d %s\n", q.next_loop, tok->str);
        break;
      case ENDIF:
        if (!q.if_statement && !q.else_statement) {
          printf("Error. Endif does not correspond to an if statement.\n");
          return 0;
        }
        printf("endif\n");
        q.if_statement = 0;
        q.else_statement = 0;
        //printf("loop %d %s\n", q.next_loop, tok->str);
        q.next_loop = get(loops, q.next_loop)->value;
        break;
    }
    //end DFA
    //
		delete_token(tok);
		if (feof(in_file)) {
			break;
		}
  }
  done(loops);
  fclose(in_file);
  return 1;
}
