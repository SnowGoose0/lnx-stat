#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SHELL_PATH         "/etc/shells"
#define SHELL_SET_SIZE     2
#define TOK_DELIMITER      "\n"
#define TOK_NEEDLE         "/bin/"

typedef struct {
  int capacity;
  int cur;
  char** shells;
} my_set;

my_set* create_set() {
  my_set* s = (my_set*) malloc(sizeof(my_set));
  s->capacity = SHELL_SET_SIZE;
  s->cur = 0;
  s->shells = (char**) malloc((s->capacity) * sizeof(char*));

  return s;
}

void insert_set(my_set* s, char* str) {
  int offset = s->cur;

  for (int i = 0; i < s->cur; ++i) {
    if (!strcmp(str, *(s->shells + i))) return;
  }
  
  *(s->shells + offset) = str;
  s->cur++;

  if (s->cur == s->capacity) {
    int new_capacity = s->capacity * 2;
    s->shells = (char**) realloc(s->shells, new_capacity * sizeof(char*));
    s->capacity = new_capacity;
  }
}

void print_set(my_set* s) {
  for (int i = 0; i < s->cur; ++i) {
    printf("%s\n", *(s->shells + i));
  }
}

void free_set(my_set* s) {
  free(s->shells);
  free(s);
}

int main() {
  
  FILE* fp;
  int file_size;
  char* file_content;
  my_set* shell_set = create_set();

  /* get file size to dynamically allocate for buffer content */
  fp = fopen(SHELL_PATH, "r");
  fseek(fp, 0, SEEK_END);
  file_size = ftell(fp);
  rewind(fp);

  file_content = (char*) calloc(file_size + 5, sizeof(char));
  fread(file_content, file_size, sizeof(char), fp);
  fclose(fp);

  char* tok = strtok(file_content, TOK_DELIMITER);
  while (tok != NULL) {
    char* occurence = strstr(tok, TOK_NEEDLE);
    
    if (occurence != NULL)
      insert_set(shell_set, occurence + strlen(TOK_NEEDLE));
    
    tok = strtok(NULL, TOK_DELIMITER);
  }

  print_set(shell_set);

  free(file_content);
  free_set(shell_set);
  exit(EXIT_SUCCESS);
}
