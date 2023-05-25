/**
 ******************************************************************************
 * @author: ThanNT
 * @date:   12/01/2017
 * @brief: mailbox
 ******************************************************************************
**/
#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include <stdint.h>
#include <pthread.h>
#include <stdbool.h>

#define AK_MSG_NULL ((ak_msg_t*)0)

#define DYNAMIC_MSG_TYPE				(0x40)
#define PURE_MSG_TYPE					(0x80)
#define COMMON_MSG_TYPE					(0xC0)

#define MAX_MSG_REF_COUNT				10

typedef struct {
	/* message type */
	uint32_t type;

	/* task header */
	uint32_t src_task_id;
	uint32_t des_task_id;
	uint32_t sig;

	/* interface task header */
	uint32_t if_src_task_id;
	uint32_t if_des_task_id;
	uint32_t if_src_type;
	uint32_t if_des_type;
	uint32_t if_sig;

	/* payload */
	uint32_t len;
	void* payload;
} header_t;

typedef struct ak_msg_t{
	struct ak_msg_t* next;
	struct ak_msg_t* prev;
	header_t* header;
} ak_msg_t;

typedef struct {
	pthread_mutex_t mt;
	uint32_t len;
	ak_msg_t* head;
	ak_msg_t* tail;
} q_msg_t;

extern void q_msg_init(q_msg_t* q_msg);

extern void q_msg_put(q_msg_t* q_msg, ak_msg_t* msg);
extern ak_msg_t* q_msg_get(q_msg_t* q_msg);
extern void q_msg_free(ak_msg_t* msg);

extern uint32_t q_msg_len(q_msg_t* q_msg);
extern bool q_msg_available(q_msg_t* q_msg);

#endif // __MESSAGE_H__
