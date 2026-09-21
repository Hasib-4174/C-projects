#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  while (1) {
    printf("$ ");
    char buf[1024];

    fgets(buf, 1024, stdin);
    char *nl = strchr(buf, '\n');
    if (nl)
      *nl = '\0';

    // Spliting input
    char *args[20];
    int nargs = 0;

    args[0] = strtok(buf, " ");
    while (args[nargs] != NULL && nargs < 19) {
      args[++nargs] = strtok(NULL, " ");
    }

    if (nargs == 0)
      continue;

    if (strcmp(args[0], "exit") == 0)
      return 0;

    pid_t pid = fork();

    if (pid == 0) {
      // child
      execvp(args[0], args);
    } else if (pid > 0) {
      // parent
      waitpid(pid, NULL, 0);

    } else {
      printf("Error fork");
    }
  }
  return 0;
}
