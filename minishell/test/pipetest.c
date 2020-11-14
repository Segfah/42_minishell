/*
** pipex.c - multipipes support
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

/*
 * loop over commands by sharing
 * pipes.
 */
static void
pipeline(char ***cmd)
{
	int fd[2];
	pid_t pid;
	pid_t w;
	int fdd = 0;				/* Backup */

	while (*cmd != NULL) {
		pipe(fd);				/* Sharing bidiflow */
		if ((pid = fork()) == -1) {
			perror("fork");
			exit(1);
		}
		else if (pid == 0) {
			dup2(fdd, 0);
			if (*(cmd + 1) != NULL) {
				dup2(fd[1], 1);
			}
			close(fd[0]);
			//execvp((*cmd)[0], *cmd);
			if (execvp((*cmd)[0], *cmd) == -1)
			{
				//printf("strerrno = [%s]\n", strerror(errno));
				exit(15);
			}
			exit(1);
		}
		else {
			int status;
			
			if ((w = waitpid(pid, &status, WUNTRACED | WCONTINUED)) == -1)
				exit(1);
			if (WIFEXITED(status))
				if (WEXITSTATUS(status) == 15)
					printf("zsh: command not found: %s\n", (*cmd)[0]);
			close(fd[1]);
			fdd = fd[0];
			cmd++;
		}
	}
}

/*
 * Compute multi-pipeline based
 * on a command list.
 */
int
//ls -la | grep nano | rev
main(int argc, char *argv[])
{
	char *ls[] = {"ls", "-al", NULL};
	char *rev[] = {"nono", "e", NULL};
	char *nl[] = {"pwd", "e", NULL};
	char *nl1[] = {"hjhbjk", NULL};
	char **cmd[] = {ls, rev, nl, nl1 NULL};

	pipeline(cmd);
	return (0);
}
