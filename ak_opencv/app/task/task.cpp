/*
 ============================================================================
 Name        : task.cpp
 Author      : chuongtd4
 Date        : 03/06/2019
 Version     :
 Copyright   : Your copyright notice
 Description : task C, Ansi-style
 ============================================================================
 */
#include <unistd.h>

#include "ak.h"

#include "sys_dbg.h"

#include "app.h"
#include "app_dbg.h"
#include "app_data.h"

#include "task_list.h"

#include "task.h"
#include "api_app.h"

#include "spi.h"
int spi_test();
q_msg_t task_1_mailbox;
q_msg_t task_2_mailbox;
q_msg_t task_3_mailbox;
void* task_1(void*) {
    wait_all_tasks_started();
    SYS_PRINT("task_1 run\n");
    ak_msg_t* msg;
    while(1)
    {
        msg = ak_msg_rev(TASK_1);

        switch (msg->header->sig) {
        case SIG_2: {

         SYS_PRINT("task_1 SIG_2\n");
           timer_set(TASK_3, SIG_1, 1000, TIMER_ONE_SHOT);
        }
            break;
        default:
         SYS_PRINT("task_1 default\n");
            break;
         }
        /* free message */
        ak_msg_free(msg);
       }
    return (void*)0;
}

void* task_2(void*) {
    wait_all_tasks_started();
    SYS_PRINT("task_2 run\n");
    task_post_pure_msg(TASK_3,SIG_1);
    return (void*)0;
}
void* task_3(void*) {
    wait_all_tasks_started();
    SYS_PRINT("task_3 run\n");

    ak_msg_t* msg;
    while(1)
    {
        msg = ak_msg_rev(TASK_3);

        switch (msg->header->sig) {
        case SIG_1: {
         SYS_PRINT("task_3 SIG_1\n");
         task_post_pure_msg(TASK_1,SIG_2);
        }
            break;
        case SIG_2: {
         SYS_PRINT("task_3 SIG_2\n");
        }
            break;
        default:
         SYS_PRINT("task_3 default\n");
            break;
         }
        /* free message */
        ak_msg_free(msg);
       }
    return (void*)0;
}




