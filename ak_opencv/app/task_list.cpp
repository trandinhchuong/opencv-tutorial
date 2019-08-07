#include "timer.h"

#include "task_list.h"

ak_task_t task_list[] = {
	/* SYSTEM TASKS */
	{	AK_TASK_TIMER_ID,				TASK_PRI_LEVEL_1,	timer_entry						,	&timer_mailbox						,	"timer service"			},

	/* APP TASKS */
    {   TASK_1,                          TASK_PRI_LEVEL_1,  task_1                          ,   &task_1_mailbox                      ,  "task_1"                },
    {   TASK_2,                          TASK_PRI_LEVEL_1,  task_2                          ,   &task_2_mailbox                      ,  "task_2"                },
    {   TASK_3,                          TASK_PRI_LEVEL_1,  task_3                          ,   &task_3_mailbox                      ,  "task_3"                },

};
