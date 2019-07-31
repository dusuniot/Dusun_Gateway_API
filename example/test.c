#include <stdio.h>
#include <stdlib.h>

#include "rbsdk.h"
#include "simlog.h"

int rpt_dev_added(char *mac, char *ModelStr, char *model, int type, int battery) {
	log_info("[%s] - %s added", __func__, mac);
	return 0;
}
int rpt_dev_deled(char *mac) {
	log_info("[%s] - %s deleted", __func__, mac);
	return 0;
}
int rpt_dev_online(char *mac, int online) {
	log_info("[%s] - %s online : %d", __func__, mac, online);
	return 0;
}
int rpt_door(char *mac, int door) {
	log_info("[%s] - %s door status:%d", __func__, mac, door);
	return 0;
}


int rpt_cmd(char *mac, int ep, int cluster, int cmd, char *buf, int len) {
	log_info("[%s] - ep:%02X, cluster:%04X, cmd:%02X, buf:", mac, ep&0xff, cluster&0xffff, cmd&0xff);
	int i = 0;
	for (i = 0; i < len; i++) {
		printf("[%02X] ", buf[i]&0xff);
	}
	printf("\n");
	return 0;
}
int rpt_attr(char *mac, int ep, int cluster, int attr, char *buf, int len) {
	log_info("[%s] - ep:%02X, cluster:%04X, attr:%04X, buf:", mac, ep&0xff, cluster&0xffff, attr&0xffff);
	int i = 0;
	for (i = 0; i < len; i++) {
		printf("[%02X] ", buf[i]&0xff);
	}
	printf("\n");
	return 0;
}


int rpt_zwdev_added(char *mac, const char *epstr) {
	log_info("[%s] - epstr:%s", mac, epstr);
	return 0;
}

int rpt_zwdev_deled(char *mac) {
	log_info("[%s] - ", mac);
	return 0;
}

int rpt_zwdev_online(char *mac, int online) {
	log_info("[%s] - online:%d", mac, online);
	return 0;
}

int rpt_zwdev_cmd(char *mac, int ep, int class, int cmd, char *buf, int len) {
	log_info("[%s] - ep:%d, class:%02X, cmd:%02X", mac, ep&0xff, class&0xff, cmd&0xff);
	log_debug_hex("buf:", buf, len);
	return 0;
}

int main(int argc, char *argv[]) {

	rbsdk_init(NULL, NULL);

	char sver[32];
	rbsdk_vers(sver);
	log_info("rbsdk version : %s\n", sver);

	stDevMsgCb_t dmc = {
		.rpt_dev_added			= rpt_dev_added, 
		.rpt_dev_deled			= rpt_dev_deled,
		.rpt_dev_online			= rpt_dev_online,
		.rpt_attr	= rpt_attr,
		.rpt_cmd  = rpt_cmd,

		
		/*
		.rpt_dev_battery		= NULL,
		.rpt_dev_lowpower		= NULL,
		
		.rpt_temp						= NULL,
		.rpt_humi						= NULL,
		.rpt_door						= NULL,
		.rpt_pir						= NULL,
		.rpt_leak						= NULL,

		.ret_lock_password_add	= NULL,
		.ret_lock_password_del	= NULL,
		.ret_lock_password_mod	= NULL,
		.ret_lock_password_clr	= NULL,
		.ret_lock_dynamic_seed	= NULL,
		.rpt_lock_checkrecord		= NULL,
		.rpt_lock_system_locked	= NULL,
		
		.rpt_smoke							= NULL,

		.rpt_light_onoff				= NULL,
		.rpt_winctr_status			= NULL,
		.rpt_winctr_percent			= NULL,
		*/
	};
	rbsdk_dev_msgcb_set(&dmc);

	stZwMsgCb_t zmc = {
		.rpt_zwdev_added = rpt_zwdev_added,
		.rpt_zwdev_deled = rpt_zwdev_deled,
		.rpt_zwdev_online= rpt_zwdev_online,
		.rpt_zwdev_cmd	 = rpt_zwdev_cmd,	
	};
	rbsdk_zw_msgcb_set(&zmc);

	while (1) {
		fd_set	fds;
		FD_ZERO(&fds);
		FD_SET(0, &fds);

		struct timeval	tv;
		tv.tv_sec = 4;
		tv.tv_usec = 80;
		int ret = select(0 + 1, &fds, NULL, NULL, &tv);
		if (ret <= 0) {
			continue;
		}
		extern void cmd_in(void *arg, int fd);
		cmd_in(NULL, 0);
	}
	
	return 0;
}
