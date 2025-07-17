#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_IN 128
#define MAX_TOK 32

size_t tokenize(char *s, char *t[])
{
    size_t i = 0;
    char* tok;

    s[strcspn(s, "\n")] = 0;

    tok = strtok(s, " ");
    while (tok && (i < MAX_TOK-1))
    {
        t[i] = tok;
        tok = strtok(NULL, " ");
        i++;
    };
    t[i] = NULL;
    return i;
}

int main(void)
{
    char in[MAX_IN];
    char* tok[MAX_TOK];
    pid_t pid;
    int status;

    while(1)
    {
        memset(in,0,MAX_IN);

        if (getuid() == 0) { printf("# "); }
        else { printf("%% "); }

        if (fgets(in, MAX_IN, stdin) == NULL)
        { break; }

        tokenize(in,tok);

        if (strcmp(tok[0],"exit") == 0) { break; }
        if (strcmp(tok[0],"help") == 0) { puts("pleh"); continue; }

        pid = fork();
        if (pid == -1) { perror("fork"); }
        else if (pid == 0)
        {
            execvp(tok[0],tok);
            perror("execvp");
            _exit(1);
        }
        else { wait(&status); }
    };
    return 0;
}