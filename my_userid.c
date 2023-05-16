#include <stdio.h>
#include <stdlib.h>

#define STD_INPUT_SIZE        0x1000
#define STD_CMD_SIZE          0x1040

int main(void) {
  char username[STD_INPUT_SIZE];
  char cmd_silent[STD_CMD_SIZE];
  char cmd[STD_CMD_SIZE];
  
  scanf("%s", username); /* get the username from standard input */
  sprintf(cmd_silent, "id -u %s > /dev/null 2>&1", username);
  sprintf(cmd, "id -u %s", username);

  int status = system(cmd_silent); /* silent command to check validity of input */

  if (status != 0) {
    printf("no such user found\n");
    exit(EXIT_FAILURE);
  }

  system(cmd); /* display as usual when valid */

  exit(EXIT_SUCCESS);
}
