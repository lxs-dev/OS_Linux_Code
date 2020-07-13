#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <glob.h>
#include <string.h>
#define DELIMS " \n\t"

#if 0
#define Debug debug
#else
#define Debug 
#endif
struct cmd_st
{
	glob_t globres;
};
void debug(int i)
{
	printf("*******debug:%d*******\n",i);
}
void prompt(void)
{
	printf("mysh-01$ ");
}
void parse(char*line,struct cmd_st *res)
{
	char* tok;
	int i=0;
	while(1)
	{
		tok = strsep(&line,DELIMS);
		if(tok == NULL)
			{
				Debug(2);
				break;
			}
		if(tok[0] == '\0')
			{
				Debug(3);
				continue;
			}
		Debug(4);
		glob(tok,GLOB_NOCHECK|GLOB_APPEND*i,NULL,&res->globres);
		i = 1;
	}
}

int main(int argc, char const *argv[])
{
	pid_t pid;
	char *linebuf =NULL;
	size_t line_size = 0;
	struct cmd_st cmd;
	
	while(1)
	{
			
		/*打印提示符*/
			prompt();
		/*获取命令*/
			if(getline(&linebuf,&line_size,stdin)<0)
				{
					Debug(1);
					break;
				}
		/*解析命令*/
			parse(linebuf,&cmd);
		/*判断命令是否内部命令*/
			if(0)
			{
				/*内部命令*/
			}else
			{
				pid = fork();
				if(pid < 0 )
				{
					perror("fork()");
					exit(0);
				}
				if(pid == 0)
				{
					execvp(cmd.globres.gl_pathv[0],cmd.globres.gl_pathv);
					perror("execvp()");
					exit(1);
				}else
				{
					wait(NULL);
					memset(cmd.globres.gl_pathv,0,sizeof(cmd.globres.gl_pathv));
				//	exit(0);
				}
			}
	}
	return 0;
}
