#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {

  FILE* fp;
  int file_size;
  char* file_content;
  char username[300];

  fp = fopen("/etc/passwd", "r");
  fseek(fp, 0, SEEK_END);
  file_size = ftell(fp);
  rewind(fp);

  file_content = (char*) calloc(file_size + 5, sizeof(char));
  fread(file_content, file_size, sizeof(char), fp);
  fclose(fp);
			      
  scanf("%s", username); /* get the username from standard input */

  char* tok = strtok(file_content, "\n");
  while(tok != NULL) {
    char* tmp = tok;
    char* u_name = (char*) calloc(300, sizeof(char));
    
    for (; *tmp != ':'; ++tmp) u_name[tmp - tok] = *tmp;

    if (!strcmp(u_name, username)) {
      tmp += 3;
      
      for (; *tmp != ':'; ++tmp) printf("%c", *tmp);
      printf("\n");
      
      free(file_content);
      free(u_name);
      exit(EXIT_SUCCESS);
    }
    
    tok = strtok(NULL, "\n");
    free(u_name);
  }

  printf("no such user found");
  free(file_content);

  exit(EXIT_SUCCESS);
}
