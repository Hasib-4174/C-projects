#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  while (1) {
    printf("$ ");
    char buf[1024];
    fgets(buf, 1024, stdin);
    if (!strcmp(buf, "exit\n"))
      return 0;
    system(buf);
  }
  return 0;
}
