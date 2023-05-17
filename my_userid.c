#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PW_PATH         "/etc/passwd"
#define TOK_DELIMITER   "\n"
#define ARG_SIZE        300

int main(void) {

  FILE* fp;
  int file_size;
  char* file_content;
  char username[2 * ARG_SIZE];

  fp = fopen(PW_PATH, "r");
  fseek(fp, 0, SEEK_END);
  file_size = ftell(fp);
  rewind(fp);

  file_content = (char*) calloc(file_size + 5, sizeof(char));
  fread(file_content, file_size, sizeof(char), fp);
  fclose(fp);

  printf("Enter your username: ");
  scanf("%s", username); /* get the username from standard input */

  char* tok = strtok(file_content, TOK_DELIMITER);
  while(tok != NULL) {
    char* tmp = tok;
    char* u_name = (char*) calloc(ARG_SIZE, sizeof(char));
    
    for (; *tmp != ':'; ++tmp) u_name[tmp - tok] = *tmp;

    if (!strcmp(u_name, username)) {
      tmp += 3;
      
      for (; *tmp != ':'; ++tmp) printf("%c", *tmp);
      printf(TOK_DELIMITER);
      
      free(file_content);
      free(u_name);
      exit(EXIT_SUCCESS);
    }
    
    tok = strtok(NULL, TOK_DELIMITER);
    free(u_name);
  }
 
  free(file_content);
  char cmd[3 * ARG_SIZE];
  char cmd_silent[3 * ARG_SIZE];

  sprintf(cmd_silent, "id -u %s >/dev/null 2>&1", username);
  sprintf(cmd, "id -u %s", username);

  int status = system(cmd_silent);

  if (!status) {
    system(cmd);
    exit(EXIT_SUCCESS);
  }

  printf("no such user found\n"); 

  exit(EXIT_SUCCESS);
}
