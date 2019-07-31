/*
 * Copyright 2011-2017 Ayla Networks, Inc.  All rights reserved.
 *
 * Use of the accompanying software is permitted only in accordance
 * with and subject to the terms of the Software License Agreement
 * with Ayla Networks, Inc., a copy of which can be obtained from
 * Ayla Networks, Inc.
 */
#include "parse.h"

/*
 * Parse string into arguments.
 * Modifies string in buffer to change white space to NULs.
 * Handles simple quoting cases.
 * Doesn't use isspace().
 * Ignores leading spaces.
 */
int parse_argv(char **argv, int argv_len, char *buf)
{
	int argc = 0;
	char *cp = buf;
	char *dest = buf;
	char quote;
	char c;

	while (argc < argv_len && *cp != '\0') {
		/*
		 * Skip leading blanks and tabs.
		 */
		while ((c = *cp) != '\0' && (c == ' ' || c == '\t')) {
			cp++;
		}
		if (c == '\0') {
			break;
		}

		/*
		 * copy arg and skip until next blank, tab, or end of string.
		 * If quoted, look for matching quote.
		 */
		quote = 0;
		*argv++ = cp;
		argc++;
		for (dest = cp; (c = *cp) != '\0'; cp++) {
			if (quote) {
				if (c == quote) {
					quote = 0;
					continue;
				}
			} else {
				/*
				 * Look for start quote.
				 */
				if (c == '\'' || c == '\"') {
					quote = c;
					continue;
				}
				if (c == ' ' || c == '\t') {
					break;
				}
			}
			*dest++ = c;
		}
		*dest = '\0';
		if (c == '\0') {
			break;
		}
		cp++;
	}
	if (argc < argv_len) {
		*argv = 0;
	}
	return argc;
}

#ifdef TEST_PARSE_ARGV

#include <stdio.h>
#include <string.h>

#define ARGV_LEN 8

void dump_argv(int argc, char **argv)
{
	int i;

	printf("argc %d\n", argc);
	for (i = 0; i <= argc; i++) {
		if (argv[i] && argv[i] != (char *)-1) {
			printf("arg[%d] = \"%s\"\n", i, argv[i]);
		} else {
			printf("arg[%d] = %p\n", i, argv[i]);
		}
	}
	printf("\n");
}

char *test_cases[] = {
	" a ab abc d ",
	" test 1 \"2 3\" 4\"56\"",
	" test 2 \'2 3\' 4\'56\'7",
	"test 3 \"\'2 3\' 4\'56\'7\"",
	"test 4 abc \"def\"ghi\"jkl\"",
	NULL
};

int main(int real_argc, char **real_argv)
{
	char *argv[ARGV_LEN];
	int argc;
	char **test;
	char buf[128];

	for (test = test_cases; *test; test++) {
		memset(argv, 0xff, sizeof(argv));
		snprintf(buf, sizeof(buf), *test);
		printf("buf <%s>\n", buf);
		argc = parse_argv(argv, ARGV_LEN, buf);
		dump_argv(argc, argv);
	}
	return 0;
}
#endif /* TEST_PARSE_ARGV */
