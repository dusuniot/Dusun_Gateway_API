#ifndef __RBSDK_H_
#define __RBSDK_H_

#ifdef __cplusplus
extern "C" {
#endif
	/** rbsdk_init
   *
	 * init the sdk must be called first before any rbsdk_* api to be called.
	 *
	 * @param[in] unused	reserved, not used now 
	 * @param[in] msgcb		reserved, not used now
	 *
	 * @return 0->ok, else failed.
	 *
	 * @warning none
	 *
	 * @note none
	 *
	 * @see none
	 */
	int rbsdk_init(void *unused, int (*msgcb)(char *src, char *dest, char *msg));

	/** rbsdk_vers
   *
   * get rbsdk version
   *
   * @param[in] version the buffer to return the version string, must be lagger than 32 bytes.
   *
   * @return 0->ok, else failed
   *
   * @warning none
   *
   * @note none
   *
   * @see none
   */
	int rbsdk_vers(char *version);

	/** rbsdk_call
   *
   * general call test function, reserved, not used.
   * */
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


	/** rbsdk_dev_msgcb_set
   * 
   * set the callback functions for rbsdk
   *
   * @param[in] dmc the callback struct pointer to set
   *
   * @return 0->ok, else failed
   *
   * @warning none
   *
   * @note none
   *
   * @see none
   */
	int rbsdk_dev_msgcb_set(stDevMsgCb_t *dmc);

	/** rbsdk_list_dev
   * 
   * query the device list
   *
   * @param none
   *
   * @return 0->ok, else failed
   *
   * @warning none
   *
   * @note none
   *
   * @see none
   */
	int rbsdk_list_dev();


	/** rbsdk_add_dev
   * 
   * requset add device, this will open the zigbee network to permit new device to join.
   *
   * @param[in] mac the device's mac address to add
   * @param[in] type, the device's type to add, not used now, use "" or "0000"
   *
   * @return 0->ok, else failed
   *
   * @warning none
   *
   * @note when send this request, it will wait a few minitues or seconds to commission this device 
   *       if this device success joined to network, there will have a callback rpt_dev_added function
   *       to be called.
   *
   * @see none
   */
	int rbsdk_add_dev(char *mac, char *type);

	/** rbsdk_del_dev
   * 
   * request delete device, this will delete the device that has been added in the zigbee network.
   *
   * @param[in] mac the deivce's mac to delete.
   *
   * @return 0->ok, else failed
   *
   * @warning none
   *
   * @note when send this request, if the device has joinded to the nework, there will have a callback 
   *       rpt_dev_deled function to be called.
   *
   * @see none
   */
	int rbsdk_del_dev(char *mac);

	/** rbsdk_dev_lock_add_pass
   *
   * request add password to lock
   *
   * @param[in] mac the lock's mac address to add password to
   * @param[in] type the password type, 0->normal password, 5->count password
   * @param[in] id the password id, unique identification for the password
   * @param[in] passVal1 the password to add, the integer's string format must be 6 digits
   * @param[in] passVal2 the password second argments, when this password is a count password, the passVal2 is the count for the password, must be less then 100
   * @param[in] startTime the password's start timestamp
   * @param[in] endTime the password's end timestamp
   * @param[in] suspend the password's valid status.
   *
   * @return 0->ok, else failed
   *
   * @warning  none
   * 
   * @note  none
   *
   * @see none
   */
	int rbsdk_dev_lock_add_pass(char *mac, int type, int id, int passVal1, int passVal2, int startTime, int endTime, int suspend);


	/** rbsdk_dev_lock_del_pass
   * 
   * request delete password from lock
   *
   * @param[in] mac  the lock's mac address
   * @param[in] type the password's type, 0->normal password, 5->count password
   * @param[in] id the password's id to deleted
   *
   * @return 0->ok, else failed
   * 
   * @warning none
   *
   * @note none
   *
   * @see none 
   */
	int rbsdk_dev_lock_del_pass(char *mac, int type, int id);

	/** rbsdk_dev_lock_mod_pass
   * 
   * request modify password in the lock
   *
   * @param[in] mac  the lock's mac address
   * @param[in] type the password's type, 0->normal password, 5->count password
   * @param[in] passVal1 the new password to set to
   * @param[in] passVal2 the second argment for the new password
   * @param[in] startTime the new password's start timestamp
   * @param[in] endTime the new password's end timestamp
   * @param[in] suspend the new password's valid status
   *
   * @return 0->ok, else failed
   * 
   * @warning none
   *
   * @note none
   *
   * @see none
   */
	int rbsdk_dev_lock_mod_pass(char *mac, int type, int id, int passVal1, int passVal2, int startTime, int endTime, int suspend);

	/** rbsdk_dev_lock_clr_pass
   * 
   * request clear the password int the lock
   *
   * @param[in] mac the lock's mac address
   * @param[in] type the password's type to be used, reseved, not used
   *
   * @return 0->ok, else failed
   *
   * @warning none
   *
   * @note none
   *
   * @see none
   */
	int rbsdk_dev_lock_clr_pass(char *mac, int type);

	/** rbsdk_dev_lock_set_seed
   *
   * request set dynamic password to the lock
   *
   * @param[in] mac the lock's mac address
   * @param[in] id the seed password's id
   * @param[in] interval the seed password's interval 
   * @param[in] startTime the seed password's start timestamp
   * @param[in] endtime the seed password's end timestamp
   *
   * @return 0->ok, else failed
   *
   * @warning none
   *
   * @note none
   *
   * @see none
   */
	int rbsdk_dev_lock_set_seed(char *mac, int id, int seed, int interval, int startTime, int endTime);

	/** rbsdk_dev_light_onoff
   *
   * request switch the light device onoff status
   *
   * @param[in] mac the light's mac address
   * @param[in] onoff 0->open, 1->close
   * 
   * @return 0->ok, else failed
   *
   * @warning none
   *
   * @note none
   *
   * @see none
   */
	int rbsdk_dev_light_onoff(char *mac, int onoff);

	/** rbsdk_dev_winctr_open
   *
   * reqeust open window
   *
   * @param[in] mac the window's mac address
   *
   * @return 0->ok, else failed
   *
   * @warning none
   *
   * @note none
   *
   * @see none
   */
	int rbsdk_dev_winctr_open(char *mac);

	/** rbsdk_dev_winctr_stop
   *
   * reqeust stop window
   *
   * @param[in] mac the window's mac address
   *
   * @return 0->ok, else failed
   *
   * @warning none
   *
   * @note none
   *
   * @see none
   */
	int rbsdk_dev_winctr_stop(char *mac);

	/** rbsdk_dev_winctr_close
   *
   * reqeust close window
   *
   * @param[in] mac the window's mac address
   *
   * @return 0->ok, else failed
   *
   * @warning none
   *
   * @note none
   *
   * @see none
   */
	int rbsdk_dev_winctr_close(char *mac);

	/** rbsdk_dev_air_onoff
   *
   * reqeust open/close air 
   *
   * @param[in] mac the air's mac address
   * @param[in] onoff 0->open, 1->close
   *
   * @return 0->ok, else failed
   *
   * @warning none
   *
   * @note none
   *
   * @see none
   */
	int rbsdk_dev_air_onoff(char *mac, int onoff);

	/** rbsdk_dev_air_mode
   *
   * reqeust set the mode for the air
   *
   * @param[in] mac the air's mac address
   * @param[in] mode 3(cool)|4(heat)|7(normal)
   *
   * @return 0->ok, else failed
   *
   * @warning none
   *
   * @note none
   *
   * @see none
   */
	int rbsdk_dev_air_mode(char *mac, int mode);

	/** rbsdk_dev_air_fan
   *
   * reqeust set the fan for the air
   *
   * @param[in] mac the air's mac address
   * @param[in] fan <1(low)|2(mid)|3(high)>
   *
   * @return 0->ok, else failed
   *
   * @warning none
   *
   * @note none
   *
   * @see none
   */
	int rbsdk_dev_air_fan(char *mac, int fan);

	/** rbsdk_dev_air_temp
   *
   * reqeust set the temperature for the air
   *
   * @param[in] the air's mac address
   * @param[in] temp_mode <0(heat)|1(cool)|2(both)>
   * @param[in] dir <1(+)|0(-)>
   * @param[in] temp_delt 10->1`C, 20->2`C
   * 
   * @return 0->ok, else failed
   *
   * @warning none
   *
   * @note none
   *
   * @see none
   */
	int rbsdk_dev_air_temp(char *mac, int temp_mode, int dir, int temp_delt);

	/** rbsdk_zcl_command
   * 
   * request zcl command
   *
   * @param[in] mac the device's mac address
   * @param[in] cluster the cluster to send to
   * @param[in] cmdid the command id to send
   * @param[in] data the data to send
   * @param[in] len the len of the data
   *
   * @return 0-ok, else failed
   *
   * @warning none
   *
   * @note none
   *
   * @see none
   */
	int rbsdk_zcl_cmd(char *mac, int ep,	 int cluster, int cmdid,	char *data, int len);

	/** rbsdk_set_attr
   *
   * request set attribute
   *
   * @param[in] mac the device's mac address
   * @param[in] cluster the cluster to send to
   * @param[in] attrid attribute id to set
   * @param[in] atype attribute data type
   * @param[in] data the attribute's data 
   * @param[in] len the len for the data
   *
   * @warning none
   *
   * @note atype can referenc the zigbee cluster specification.
   *
   * @see none
   */
	int rbsdk_set_attr(char *mac, int ep, int cluster, int attrid, int atype, char *data, int len);

	/** rbsdk_get_attr
   *
   * request get attribute 
   *
   * @param[in] mac the device's mac address
   * @param[in] cluster the cluster to send to
   * @param[in] attrid attribute id to get
   *
   * @warning none
   * 
   * @note none
   *
   * @see none
   */
	int rbsdk_get_attr(char *mac, int ep, int cluster, int attrid);


	// ZWave interface=====================================================================
	typedef struct stZwMsgCb {
		/**> new zwave device add */
		int (*rpt_zwdev_added)(char *mac, const char *skeleton);

		/**> device delete or leaved */
		int (*rpt_zwdev_deled)(char *mac);

		/**> device online status changed */
		int (*rpt_zwdev_online)(char *mac, int online);

		/**> devcie has data */
		int (*rpt_zwdev_cmd)(char *mac, int ep, int class, int cmd, char *buf, int len);

		/**> zwave net info */
		int (*rpt_zw_netinfo)(int homeid, int nodeid, const char *version);
	} stZwMsgCb_t;

	
	/** rbsdk_zw_include
   * 
   * requst zw to include new device
   *
   * @param none
   *
   * @warning none
   *
   * @note none
   *
   * @see none
   */
	int rbsdk_zw_include();



	/** rbsdk_zw_exclude
   * 
   * requst zw to exinclude device
   *
   * @param none
   *
   * @warning none
   *
   * @note none
   *
   * @see none
   */
	int rbsdk_zw_exclude();

	/** rbsdk_zw_devlist
   * 
   * request zwave device list
   *
   * @param none
   *
   * @warning none
   *
   * @note none
   *
   * @see none
   */
	int rbsdk_zw_devlist();

	/** rbsdk_zw_netinfo
   * 
   * request zwave netinfo
   *
   * @param none
   *
   * @waring none
   *
   * @note none
   *
   * @see none
   */
	int rbsdk_zw_netinfo();

	/** rbsdk_zw_del_node
   *
   * request zwave to delete a node
   *
   * @param[in] mac, the deivce's mac to remove, eg: 00158d00005c331b
   *
   * @warning none
   *
   * @note none
   *
   * @see none
   */
	int rbsdk_zw_del_node(char *mac);

	
	/** rbsdk_zw_class_cmd()
   *
   * request to send class command to device
   *
   * @param[in] mac the device's mac to send to.
   * @param[in] ep  the endpoint to send to
   * @param[in] class the class id to send to
   * @param[in] cmd the command id to send to
   * @param[in] data the data buffer
   * @param[in] len the data len
   *
   * @warning none
   * 
   * @note if multi endpoint, use 0x60 class to set command, see `zcmd 30AE7B63F3164242 0 96 13 0002250100`
   *
   * @see none
   */
	int rbsdk_zw_class_cmd(char *mac, int ep, int class, int cmd, char *data, int len);


	/** rbsdk_zw_msgcb_set()
   * 
   * set the zwave message callback 
   *
   * @paran[in] zmc the callback struct pointer to set
   *
   * @return 0->ok, else failed
   *
   * @warning noen
   *
   * @note none
   *
   * @see none
   */
	int rbsdk_zw_msgcb_set(stZwMsgCb_t *zmc);

#ifdef __cplusplus
}
#endif

#endif

