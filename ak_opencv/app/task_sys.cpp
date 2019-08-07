#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ak.h"
#include "timer.h"

#include "app.h"

#include "app_dbg.h"
#include "app_data.h"

#include "task_list.h"
#include "task_sys.h"

q_msg_t gw_task_sys_mailbox;

void* gw_task_sys_entry(void*) {
	wait_all_tasks_started();

	APP_DBG("[STARTED] gw_task_sys_entry\n");

	ak_msg_t* msg;

	while (1) {
		/* get messge */
		msg = ak_msg_rev(GW_TASK_SYS_ID);

		switch (msg->header->sig) {

		case GW_SYS_WATCH_DOG_REPORT_REQ: {
			static int gw_sys_watch_dog_report_req_count = 0;
			if (gw_sys_watch_dog_report_req_count++ >= 1000) {
				gw_sys_watch_dog_report_req_count = 0;
				APP_DBG_SIG("GW_SYS_WATCH_DOG_REPORT_REQ\n");
			}
		}
			break;

		case GW_SYS_WATCH_DOG_DBG_1: {

		}
			break;

		case GW_SYS_WATCH_DOG_DBG_2: {
			ak_msg_t* s_msg = ak_memcpy_msg(msg);
			set_msg_sig(s_msg, GW_SYS_WATCH_DOG_DBG_6);
			set_msg_src_task_id(s_msg, GW_TASK_SYS_ID);
			task_post(GW_TASK_SYS_ID, s_msg);
		}
			break;

		case GW_SYS_WATCH_DOG_DBG_3: {
			ak_msg_t* s_msg = ak_memcpy_msg(msg);
			set_msg_sig(s_msg, GW_SYS_WATCH_DOG_DBG_5);
			set_msg_src_task_id(s_msg, GW_TASK_SYS_ID);
			task_post(GW_TASK_SYS_ID, s_msg);
		}
			break;

		case GW_SYS_WATCH_DOG_DBG_4: {

		}
			break;

		case GW_SYS_WATCH_DOG_DBG_5: {
		}
			break;

		case GW_SYS_WATCH_DOG_DBG_6: {

		}
			break;

		default:
			break;
		}

		/* free message */
		ak_msg_free(msg);
	}

	return (void*)0;
}
