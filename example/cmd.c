#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "simlog.h"
#include "parse.h"
#include "cmd.h"
#include "rbsdk.h"


void do_cmd_exit(char *argv[], int argc);
void do_cmd_help(char *argv[], int argc);
void do_cmd_permit(char *argv[], int argc);
void do_cmd_include(char *argv[], int argc);
void do_cmd_exclude(char *argv[], int argc);
void do_cmd_zinfo(char *argv[], int argc);
void do_cmd_class_cmd(char *argv[], int argc);

static stCmd_t cmds[] = {
	{"exit",		do_cmd_exit, "exit the programe!"},
	{"help",		do_cmd_help, "help info"},
	{"permit",	do_cmd_permit, "permit add device"},
	{"include",	do_cmd_include, "include zwave device"},
	{"exclude", do_cmd_exclude, "exclude zwave device"},
	{"zcmd",		do_cmd_class_cmd, "execute class cmd command, cmd <mac> <ep> <class> <buffstr>"},
	{"zinfo",		do_cmd_zinfo,		"get zwave netinfo"},
};

void cmd_in(void *arg, int fd) {
	char buf[1024];	
	int  size = 0;

	int ret = read(fd, buf, sizeof(buf));
	if (ret < 0) {
		log_debug("what happend?");
		return;
	}

	if (ret == 0) {
		log_debug("error!");
		return;
	}

	size = ret;
	buf[size] = 0;
	if (size >= 1 && buf[size-1] == '\n') {
		buf[size-1] = 0;
		size--;
	}
	char *p = buf;
	while (*p == ' ') {
		p++;
		size--;
	}
	if (size > 0) {
		memcpy(buf, p, size);
	} else {
		buf[0] = 0;
		size = 0;
	}

	if (strcmp(buf, "") != 0) {
		log_debug("console input:[%s]", buf);
		char* argv[20];
		int argc;
		argc = parse_argv(argv, sizeof(argv), buf);

		stCmd_t *cmd = cmd_search(argv[0]);
		if (cmd == NULL) {
			log_debug("invalid cmd!");
		} else {
			cmd->func(argv, argc);
		}
	}
	log_debug("$");
}

stCmd_t *cmd_search(const char *cmd) {
	int i = 0;
	for (i = 0; i < sizeof(cmds)/sizeof(cmds[0]); i++) {
		if (strcmp(cmds[i].name, cmd) == 0) {
			return &cmds[i];
		}
	}
	return NULL;
}


//////////////////////////////////////////////////
void do_cmd_exit(char *argv[], int argc) {
	exit(0);
}
void do_cmd_help(char *argv[], int argc) {
	int i = 0;
	for (i = 0; i < sizeof(cmds)/sizeof(cmds[0]); i++) {
		log_debug("%-12s\t-\t%s", cmds[i].name, cmds[i].desc);
	}
}

void do_cmd_permit(char *argv[], int argc) {
	log_debug(" ");
	rbsdk_add_dev("ffffffffffffffff", "0000");
}
void do_cmd_include(char *argv[], int argc) {
	log_debug(" ");
		rbsdk_zw_include();
}
void do_cmd_exclude(char *argv[], int argc) {
	log_debug(" ");
		rbsdk_zw_exclude();
}
void do_cmd_zinfo(char *argv[], int argc) {
	log_debug(" ");
	rbsdk_zw_netinfo();
}

static unsigned char _hex_ascii_to_nibble(char c)
{
	if (c >= '0' && c <= '9') {
		return c - '0';
	} else if (c >= 'A' && c <= 'F') {
		return c - 'A' + 10;
	} else if (c >= 'a' && c <= 'f') {
		return c - 'a' + 10;
	}
	return -1;
}


static const char *_hex_parse_byte(const char *str, u8 *byte)
{
	unsigned char high, low;

	high = _hex_ascii_to_nibble(*str);
	if (high < 0) {
		return NULL;
	}
	++str;
	low = _hex_ascii_to_nibble(*str);
	if (low < 0) {
		return NULL;
	}
	*byte = (high << 4) | low;
	return ++str;
}

static ssize_t _hex_parse_n(u8 *buf, size_t size, const char *str, size_t len,
	char *delim)
{

	size_t nbytes = 0;
	char found_delim = 0;

	if (len < 2) {
		return -1;
	}
	/* Detect delimiter after first byte */
	if (len > 4) {
		if (_hex_ascii_to_nibble(str[2]) < 0) {
			found_delim = str[2];
		}
	}
	/* Check length and buffer size (str must have complete hex bytes) */
	if (found_delim) {
		if ((len - 2) % 3 || size < (len - 2) / 3 + 1) {
			return -1;
		}
	} else {
		if (len % 2 || size < len / 2) {
			return -1;
		}
	}
	for (;;) {
		if (nbytes >= size) {
			return -1;
		}
		str = _hex_parse_byte(str, buf + nbytes);
		if (!str) {
			return -1;
		}
		++nbytes;
		len -= 2;
		if (!len) {
			/* Done */
			break;
		}
		/* Check delimiter */
		if (found_delim) {
			if (*str != found_delim) {
				return -1;
			}
			++str;
			--len;
		}
	}
	if (delim) {
		*delim = found_delim;
	}
	return nbytes;
}


ssize_t _hex_parse(u8 *buf, size_t size, const char *str, char *delim)
{		
	return _hex_parse_n(buf, size, str, strlen(str), delim);
}

void do_cmd_class_cmd(char *argv[], int argc) {
	if (argc < 6) {
		log_debug("zcmd <mac> <ep> <class> <cmd> <hexbuffer>");
		return;
	}
	char *mac	= argv[1];
	int ep		= atoi(argv[2])&0xff;
	int	class	= atoi(argv[3])&0xff;
	int cmd		= atoi(argv[4])&0xff;
	char *datastr = argv[5];
	char data[256];

	int len = _hex_parse((unsigned char *)data, sizeof(data), datastr, 0);
	if (len < 0) {
		log_debug("zcmd <mac> <ep> <class> <cmd> <0101?>");
		return;
	}
		
	rbsdk_zw_class_cmd(mac, ep, class, cmd, data, len);
}



