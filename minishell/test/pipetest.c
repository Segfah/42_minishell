/*
** pipex.c - multipipes support
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

/*
 * loop over commands by sharing
 * pipes.
 */
static void
pipeline(char ***cmd)
{
	int fd[2];
	pid_t pid;
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
			execvp((*cmd)[0], *cmd);
			exit(1);
		}
		else {
			wait(NULL); 		/* Collect childs */
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
	char *rev[] = {"grep", "nano", NULL};
	char *nl[] = {"rev", NULL};
	char **cmd[] = {ls, rev, nl, NULL};

	pipeline(cmd);
	return (0);
}
