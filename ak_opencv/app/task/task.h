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
#ifndef __IF_APP_H__
#define __IF_APP_H__

#include "message.h"




extern q_msg_t task_1_mailbox;
extern q_msg_t task_2_mailbox;
extern q_msg_t task_3_mailbox;
extern void* task_1(void*);
extern void* task_2(void*);
extern void* task_3(void*);

enum {

    SIG_1,
    SIG_2,
    SIG_3,
};

#endif //__IF_APP_H__
