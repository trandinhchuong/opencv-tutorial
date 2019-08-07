#ifndef __TASK_LIST_H__
#define __TASK_LIST_H__

#include "ak.h"
#include "message.h"

#include "app_data.h"
#include "task.h"





/** default if_des_type when get pool memory
 * this define MUST BE coresponding with app.
 */
#define AK_APP_TYPE_IF						IF_TYPE_APP_GW

enum {
    AK_TASK_TIMER_ID,

    /* APP TASKS */
    TASK_1,
    TASK_2,
    TASK_3,

    /* LINK TASKS */


    /* EOT task ID */
    AK_TASK_LIST_LEN,
};

extern ak_task_t task_list[];

#endif //__TASK_LIST_H__
