#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define WRITE_FILE_CMD        "df -h > my_storage_details.txt"
#define FILE_NAME_DEFAULT     "my_storage_details.txt"
#define TOK_DELIMITER         " "

bool is_numeric(char c);
int parse_int(char* s);

/* ========================================================================= */

int main(void) {
  FILE* fp;
  int file_size;
  char* file_content;

  int* usage;
  int usage_len;
  
  system(WRITE_FILE_CMD);

  /* get file size to dynamically allocate for buffer content */
  fp = fopen(FILE_NAME_DEFAULT, "r");
  fseek(fp, 0, SEEK_END);
  file_size = ftell(fp);
  rewind(fp);

  file_content = (char*) calloc(file_size + 5, sizeof(char));
  fread(file_content, file_size, sizeof(char), fp);
  fclose(fp);

  

  int total = 0;
  int total_len = 0;

  /* tokenize the file content */
  char* tok = strtok(file_content, TOK_DELIMITER);
  while (tok != NULL) {
    int c = parse_int(tok);

    /* if the c is a valid percentage number then tally */
    if (c > 0) {
      total += c;
      ++total_len;
    }
    
    tok = strtok(NULL, TOK_DELIMITER);
  }

  printf("%.2f\n", (float) total / total_len);
  free(file_content);
  exit(EXIT_SUCCESS);
}

bool is_numeric(char c) {
  return c < 58 && c > 47;
}

int parse_int(char* s) {
  char* it = s + strlen(s) - 1;
  int pos = 1;
  int num = 0;

  if (*it != '%')
    return -1;

  it--;

  /* process the numbers with Use% */
  while (it != s - 1) {

    if (!is_numeric(*it))
      return -1;
    
    num += (*it - 48) * pos;
    pos *= 10;
    --it;
  }

  return num;
}
