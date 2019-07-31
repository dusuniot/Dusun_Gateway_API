#ifndef __RBSDK_H_
#define __RBSDK_H_

#ifdef __cplusplus
extern "C" {
#endif
	/**> Basic */
	int rbsdk_init(void *unused, int (*msgcb)(char *src, char *dest, char *msg));

	int rbsdk_vers(char *version);

	int rbsdk_call(char *mac, char *attr, int setOrget, void *jvalue);

	/**> Externed */
	typedef struct stDevMsgCb {
		int (*rpt_dev_added)(char *mac, char *ModelStr, char *model, int type, int battery);
		int (*rpt_dev_deled)(char *mac);
		int (*rpt_dev_online)(char *mac, int online);
	
		int (*rpt_dev_battery)(char *mac, int battery);
		int (*rpt_dev_lowpower)(char *mac, char *ModelStr, char *model, int type, int lowpowerlr);

		/**> temphumi */
		int (*rpt_temp)(char *mac, float temp);
		int (*rpt_humi)(char *mac, float humi);


		/**> door */
		int (*rpt_door)(char *mac, int door);

		/**> pir */
		int (*rpt_pir) (char *mac, int pir);

		/**> leak */
		int (*rpt_leak)(char *mac, int pir);

		/**> lock */
		int (*ret_lock_password_add)(char *mac, int op_ret, int passid);
		int (*ret_lock_password_del)(char *mac, int op_ret, int passid);
		int (*ret_lock_password_mod)(char *mac, int op_ret, int passid);
		int (*ret_lock_password_clr)(char *mac, int op_ret);
		int (*ret_lock_dynamic_seed)(char *mac, int op_ret);

		int (*rpt_lock_checkrecord)(char *mac);
		int (*rpt_lock_system_locked)(char *mac, char *ModelStr, char *model, int type, int locked);

		/**> smoke */
		int (*rpt_smoke)(char *mac, char *ModelStr, char *model, int type, int smoke);

		/**> light */
		int (*rpt_light_onoff)(char *mac, int onoff);

		/**> window */
		int (*rpt_winctr_status)(char *mac, int status);
		int (*rpt_winctr_percent)(char *mac, int percent);

		/**> air ctr */
		int (*rpt_air_temp)(char *mac, int mode, int value, int unit);
		int (*rpt_air_fan)(char *mac, int fan);
		int (*rpt_air_mode)(char *mac, int mode);

		/**> rpt zcl command */
		int (*rpt_cmd)(char *mac, int ep, int cluster, int cmd, char *buf, int len);
		/**> rpt attribute */
		int (*rpt_attr)(char *mac, int ep, int cluster, int attr, char *buf, int len);
	} stDevMsgCb_t;

	int rbsdk_dev_msgcb_set(stDevMsgCb_t *dmc);

	int rbsdk_list_dev();

	int rbsdk_add_dev(char *mac, char *type);
	int rbsdk_del_dev(char *mac);

	int rbsdk_dev_lock_add_pass(char *mac, int type, int id, int passVal1, int passVal2, int startTime, int endTime, int suspend);
	int rbsdk_dev_lock_del_pass(char *mac, int type, int id);
	int rbsdk_dev_lock_mod_pass(char *mac, int type, int id, int passVal1, int passVal2, int startTime, int endTime, int suspend);
	int rbsdk_dev_lock_clr_pass(char *mac, int type);
	int rbsdk_dev_lock_set_seed(char *mac, int id, int seed, int interval, int startTime, int endTime);

	int rbsdk_dev_light_onoff(char *mac, int onoff);

	int rbsdk_dev_winctr_open(char *mac);
	int rbsdk_dev_winctr_stop(char *mac);
	int rbsdk_dev_winctr_close(char *mac);

	int rbsdk_dev_air_onoff(char *mac, int onoff);
	int rbsdk_dev_air_mode(char *mac, int mode);
	int rbsdk_dev_air_fan(char *mac, int fan);
	int rbsdk_dev_air_temp(char *mac, int temp_mode, int dir, int temp_delt);

	/**> send zcl command */
	int rbsdk_zcl_cmd(char *mac, int ep,	 int cluster, int cmdid,	char *data, int len);
	/**> set attribute */
	int rbsdk_set_attr(char *mac, int ep, int cluster, int attrid, int atype, char *data, int len);
	/**> get attribute */
	int rbsdk_get_attr(char *mac, int ep, int cluster, int attrid);

	/**> Internal don't use this*/

	stDevMsgCb_t * rbsdk_msg_cb_get();
	
	int rbsdk_reg_dev(char *mac, unsigned int user_type, char *version, char *model, char *ModelStr);
	int rbsdk_ung_dev(char *mac);
	int rbsdk_rpt_online(char *mac, int online);
	int rbsdk_rpt_battery(char *mac, int battey);
	int rbsdk_rpt_temp(char *mac, float temp);
	int rbsdk_rpt_humi(char *mac, float humi);
	int rbsdk_rpt_leak(char *mac, int leak);
	int rbsdk_rpt_pir(char *mac, int pir);
	int rbsdk_rpt_door(char *mac, int door);
	int rbsdk_rpt_pass_check_record(char *mac, int op_ret);
	int rbsdk_rpt_pass_add_result(char *mac, int op_ret, int passid);
	int rbsdk_rpt_pass_del_result(char *mac, int op_ret, int passid);
	int rbsdk_rpt_pass_clr_result(char *mac, int op_ret, int passid);
	int rbsdk_rpt_pass_mod_result(char *mac, int op_ret, int passid);
	int rbsdk_rpt_light_onoff(char *mac, int onoff);

	int rbsdk_rpt_winctr_status(char *mac, int status);
	int rbsdk_rpt_winctr_percent(char *mac, int percent);
	int rbsdk_rpt_air_mode(char *mac, int mode);
	int rbsdk_rpt_air_fan(char *mac, int fan);
	int rbsdk_rpt_air_temp(char *mac, int mode, int value, int unit);

	int rbsdk_rpt_atr(char *mac, int ep, int cluster, int attrid, char *data, int len);
	int rbsdk_rpt_cmd(char *mac, int ep, int cluster, int cmdid, char *data, int len);
#ifdef __cplusplus
}
#endif

#endif

