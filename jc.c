#include "hash.h"
#include "tokenizer.h"

int main(int argc, char *argv[]) {
  FILE* in_file;
  FILE* out_file;
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
		if (tok->type != BROKEN_TOKEN && tok->type != EMPTY) {
			print_token(tok);
		}
		delete_token(tok);
		if (feof(in_file)) {
			break;
		}
  }
  fclose(in_file);
  return 1;
}