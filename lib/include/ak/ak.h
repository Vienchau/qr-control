/**
 ******************************************************************************
 * @author: ThanNT
 * @date:   12/01/2017
 * @brief:  Main defination of active kernel
 ******************************************************************************
**/
#ifndef __AK_H__
#define __AK_H__


#include <stdint.h>
#include <pthread.h>
#include <stdbool.h>

#include "message.h"
#include "timer.h"
#include "port.h"
#include "ak_dbg.h"

#ifndef AK_APP_TYPE_IF
    #define AK_APP_TYPE_IF 0
#endif

#define AK_VERSION						"1.1"

#define AK_RET_OK						(0x00)
#define AK_RET_NG						(0x01)

#define AK_USER_DEFINE_SIG				(10)

#define TASK_PRI_MAX_SIZE				(8)

#define TASK_PRI_LEVEL_1				(1)
#define TASK_PRI_LEVEL_2				(2)
#define TASK_PRI_LEVEL_3				(3)
#define TASK_PRI_LEVEL_4				(4)
#define TASK_PRI_LEVEL_5				(5)
#define TASK_PRI_LEVEL_6				(6)
#define TASK_PRI_LEVEL_7				(7)
#define TASK_PRI_LEVEL_8				(8)

#define AK_COMMON_MSG_DATA_SIZE			(64)

typedef void* (*pf_task)(void*);

typedef struct {
	/* public interface */
	uint32_t		id;
	uint32_t		pri;
	pf_task			task;

	q_msg_t*		mailbox;

	const char*		info;

	/* private interface */
	pthread_t		pthread;
	pthread_attr_t	pthread_attr;
	pthread_cond_t	mailbox_cond;
	pthread_mutex_t	mt_mailbox_cond;
	uint32_t		mailbox_len;
} ak_task_t;

typedef enum {
	TIMER_ONE_SHOT,
	TIMER_PERIODIC
} timer_type_t;

typedef struct {
	uint8_t type;
	uint8_t src_task_id;
	uint8_t des_task_id;
	uint8_t sig;
	uint8_t if_src_type;
	uint8_t if_des_type;
} __AK_PACKETED ak_msg_if_header_t;

typedef struct {
	ak_msg_if_header_t header;
} __AK_PACKETED ak_msg_pure_if_t;

typedef struct {
	ak_msg_if_header_t header;

	uint8_t len;
	uint8_t data[AK_COMMON_MSG_DATA_SIZE];
} __AK_PACKETED ak_msg_common_if_t;

typedef struct {
	ak_msg_if_header_t header;

	uint32_t len;
	uint8_t* data;
} __AK_PACKETED ak_msg_dynamic_if_t;

/******************************************************************************
* init variable
*
*******************************************************************************/


/******************************************************************************
* message services
*
*******************************************************************************/
extern ak_msg_t* get_pure_msg();
extern ak_msg_t* get_dynamic_msg();
extern ak_msg_t* get_common_msg();
extern uint32_t get_msg_type(ak_msg_t* msg);
extern ak_msg_t* ak_memcpy_msg(ak_msg_t* src);
extern void ak_msg_free(ak_msg_t* msg);
extern ak_msg_t* ak_msg_rev(uint32_t des_task_id);

extern void set_msg_sig(ak_msg_t* msg, uint32_t sig);
extern void set_msg_des_task_id(ak_msg_t* msg, uint32_t des_task_id);
extern void set_msg_src_task_id(ak_msg_t* msg, uint32_t src_task_id);

extern void set_if_des_task_id(ak_msg_t* msg, uint32_t id);
extern void set_if_src_task_id(ak_msg_t* msg, uint32_t id);
extern void set_if_des_type(ak_msg_t* msg, uint32_t type);
extern void set_if_src_type(ak_msg_t* msg, uint32_t type);
extern void set_if_sig(ak_msg_t* msg, uint32_t sig);
extern void set_if_data_common_msg(ak_msg_t* msg, uint8_t* data, uint32_t len);
extern void set_if_data_dynamic_msg(ak_msg_t* msg, uint8_t* data, uint32_t len);

extern void set_data_common_msg(ak_msg_t* msg, uint8_t* data, uint32_t len);
extern void get_data_common_msg_func(ak_msg_t* msg, uint8_t* data, uint32_t len);
extern uint8_t* get_data_common_msg(ak_msg_t* msg);
extern uint8_t get_data_len_common_msg(ak_msg_t* msg);

extern void set_data_dynamic_msg(ak_msg_t* msg, uint8_t* data, uint32_t len);
extern void get_data_dynamic_msg(ak_msg_t* msg, uint8_t* data, uint32_t len);
extern uint8_t get_data_len_dynamic_msg(ak_msg_t* msg);

extern void task_post(uint32_t task_dst_id, ak_msg_t* msg);
extern void task_post_pure_msg_func(uint32_t task_src_id, uint32_t task_dst_id, uint32_t sig);
extern void task_post_pure_msg(uint32_t task_dst_id, uint32_t sig);
extern void task_post_common_msg_func(uint32_t task_src_id, uint32_t task_dst_id, uint32_t sig, uint8_t* data, uint32_t len);
extern void task_post_common_msg(uint32_t task_dst_id, uint32_t sig, uint8_t* data, uint32_t len);
extern void task_post_dynamic_msg_func(uint32_t task_src_id, uint32_t task_dst_id, uint32_t sig, uint8_t* data, uint32_t len);
extern void task_post_dynamic_msg(uint32_t task_dst_id, uint32_t sig, uint8_t* data, uint32_t len);

/******************************************************************************
* task function
*
*******************************************************************************/
/* function is called before create threads */
extern void ak_init_tasks(uint32_t ak_thread_table_len_init, ak_task_t* task_list_init);
extern void ak_start_all_tasks(void);
extern void ak_start_task(uint32_t task_id);
extern void ak_stop_all_tasks(void);
extern void ak_stop_task(uint32_t task_id);
/* function using to make sure that all task is initialed */
extern void wait_all_tasks_started();

extern int get_task_id();
/******************************************************************************
* timer services
*
*******************************************************************************/
extern uint32_t timer_set(uint32_t des_task_id, uint32_t sig, uint32_t duty, timer_type_t timer_type);
extern uint32_t timer_remove_attr(uint32_t des_task_id, uint32_t sig);
extern uint32_t timer_stick_get();

/******************************************************************************
* fsm services
*
*******************************************************************************/
#define FSM(me, init_func)  ((fsm_t*)me)->state = (state_handler)init_func
#define FSM_TRAN(me, target)    ((fsm_t*)me)->state = (state_handler)target

typedef void (*state_handler)(ak_msg_t* msg);

typedef struct {
	state_handler state;
} fsm_t;

extern void fsm_dispatch(fsm_t* me, ak_msg_t* msg);

/******************************************************************************
* fsm services
*
*******************************************************************************/
#define TSM_FUNCTION_NULL		((tsm_func_f)0)
typedef void (*tsm_func_f)(ak_msg_t*);

typedef uint8_t tsm_state_t;

typedef void (*on_tsm_state)(tsm_state_t);

typedef struct {
	uint8_t sig;				/* signal */
	tsm_state_t next_state;		/* next state */
	tsm_func_f tsm_func;		/* state handler function */
} tsm_t;

typedef struct tsm_tbl_t {
	tsm_state_t state;
	on_tsm_state on_state;
	tsm_t** table;
} tsm_tbl_t;

#define TSM(t, tbl, s) tsm_init(t, tbl, s)
#define TSM_TRAN(t, s) tsm_tran(t, s)

void tsm_init(tsm_tbl_t* tsm_tbl, tsm_t** tbl, tsm_state_t state);
void tsm_dispatch(tsm_tbl_t* tsm_tbl, ak_msg_t* msg);
void tsm_tran(tsm_tbl_t* tsm_tbl, tsm_state_t state);

#endif //__AK_H__
