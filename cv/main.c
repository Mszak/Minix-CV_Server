#include "inc.h"
#include "constants.h"

#include <minix/endpoint.h>
#include <minix/callnr.h>


#define mutex_number m1_i1
#define cond_var_number m1_i2

static endpoint_t who_e;
static int callnr;
static int req_mutex;
static int req_cvar;

/* Declare some local functions. */
static void get_work(message *m_ptr);
static void reply(endpoint_t whom, message *m_ptr);

/* SEF functions and variables. */
static void sef_local_startup(void);
static int sef_cb_init_fresh(int type, sef_init_info_t *info);
static void sef_cb_signal_handler(int signo);

/*===========================================================================*
 *				main                                         *
 *===========================================================================*/
int main(int argc, char **argv) {
  message m;
  int result;             

  /* SEF local startup. */
  env_setargs(argc, argv);
  sef_local_startup();
      
  while (TRUE) {
    get_work(&m);
    printf("CV: got from %d: %d\n", who_e, callnr);
    switch (callnr) {
      //TODO signals
      case CV_LOCK:
        result = do_lock();
        break;
      case CV_UNLOCK:
        result = do_unlock();
        break;
      case CV_WAIT:
        result = do_wait();
        break;
      case CV_BROADCAST:
        result = do_broadcast();
        break;
      default:
        printf("CV warning: got illegal request from %d\n", who_e);
        result = EINVAL;
    }

    if (result != EDONTREPLY) {
      m.m_type = result;
      reply(who_e, &m);
    }
  }

  /*Never gets here*/
  return -1;
}

/*===========================================================================*
 *				get_work                                     *
 *===========================================================================*/
static void get_work(message *m_ptr) {
  int status = sef_receive(ANY, m_ptr);
  if (OK != status) {
    panic("Failed to receive message!: %d", status);
  }
  who_e = m_ptr->m_source;
  callnr = m_ptr->m_type;
  req_mutex = m_ptr->mutex_number;
  req_cvar = m_ptr->cond_var_number;
}

/*===========================================================================*
 *				reply					     *
 *===========================================================================*/
static void reply(endpoint_t who_e, message *m_ptr) {
  int s = send(who_e, m_ptr);
  if (OK != s) {
    printf("CV: unable to send reply to %d: %d\n", who_e, s);
  }
}

/*===========================================================================*
 *             sef_local_startup           *
 *===========================================================================*/
static void sef_local_startup()
{
  /* Register init callbacks. */
  sef_setcb_init_fresh(sef_cb_init_fresh);
  sef_setcb_init_restart(sef_cb_init_fresh);

  /* No live update support for now. */

  /* Register signal callbacks. */
  sef_setcb_signal_handler(sef_cb_signal_handler);

  /* Let SEF perform startup. */
  sef_startup();
}

/*===========================================================================*
 *                sef_cb_init_fresh                                *
 *===========================================================================*/
static int sef_cb_init_fresh(int UNUSED(type), sef_init_info_t *UNUSED(info))
{
/* Initialize the cv server. */

  return(OK);
}

/*===========================================================================*
 *                sef_cb_signal_handler                            *
 *===========================================================================*/
static void sef_cb_signal_handler(int signo)
{
  /* Only check for termination signal, ignore anything else. */
  if (signo != SIGTERM) return;
}

/*===========================================================================*
 *              do_lock                      *
 *===========================================================================*/
static int do_lock()
{
  
    return 1;
}

/*===========================================================================*
 *              do_unlock                      *
 *===========================================================================*/
static int do_unlock()
{
  return 2;
}

/*===========================================================================*
 *              do_wait                      *
 *===========================================================================*/
static int do_wait()
{
  return 3;
}

/*===========================================================================*
 *              do_broadcast                      *
 *===========================================================================*/
static int do_broadcast()
{
    return 4;
}
