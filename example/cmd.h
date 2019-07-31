#ifndef __CMD_H_
#define __CMD_H_

typedef struct stCmd {
	const char *name;
	void (*func)(char *argv[], int argc);
	const char *desc;
}stCmd_t;

stCmd_t *cmd_search(const char *cmd);

#endif
