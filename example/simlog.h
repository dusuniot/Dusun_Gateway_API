#ifndef __SIMPLE_LOG_H_
#define __SIMPLE_LOG_H_

static char *appname = "test";

#define LOG_DEFAULT		39
#define LOG_RED			31
#define LOG_GREEN		32
#define LOG_YELLOW		33
#define LOG_BLUE		34
#define LOG_MAGENTA		35
#define LOG_CYAN		36
#define LOG_LIGHTGRAY		37
#define LOG_DARKGRAY		90
#define LOG_LIGHTRED		91
#define LOG_LIGHTGREEN		92
#define LOG_LIGHTYELLOW		93
#define LOG_LIGHTBLUE		94
#define LOG_LIGHTMAGENTA	95
#define LOG_LIGHTCYAN		96
#define LOG_WHITE		97

#ifndef LOG_FMT_DISABLE
#define LOG_FMT_ESC(code)	"\e[" #code "m"
#else
#define LOG_FMT_ESC(code)
#endif
#define LOG_FMT(code)		LOG_FMT_ESC(code)
#define LOG_FMT_BOLD(code)	LOG_FMT_ESC(1) LOG_FMT_ESC(code)
#define LOG_FMT_CLEAR		LOG_FMT_ESC(0)

#define log_info(...)			(printf(LOG_FMT_BOLD(LOG_GREEN)  "[INF]" LOG_FMT_CLEAR "%s::%s() " , appname, __func__), printf(__VA_ARGS__), printf("\n"))
#define log_debug(...)		(printf(LOG_FMT_BOLD(LOG_YELLOW) "[DBG]" LOG_FMT_CLEAR "%s::%s() " , appname, __func__), printf(__VA_ARGS__), printf("\n"))
#define log_err(...)			(printf(LOG_FMT_BOLD(LOG_RED)		 "[ERR]" LOG_FMT_CLEAR "%s::%s() " , appname, __func__), printf(__VA_ARGS__), printf("\n"))

#define log_debug_hex(str, buf, len) (printf(LOG_FMT_BOLD(LOG_YELLOW)  "[DBG]" LOG_FMT_CLEAR "%s::%s() ", appname, __func__), printf("%s", str), ({ \
	int i = 0; \
	for (i = 0; i < len; i++) { \
		printf("[%02X] ", buf[i]&0xff);\
	}	 \
}), printf("\n"))



#endif
