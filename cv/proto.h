#ifndef _CV_PROTO_H
#define _CV_PROTO_H

/* Function prototypes. */

/* main.c */
int main(int argc, char **argv);

/* cv.c */
static int do_lock(void);
static int do_unlock(void);
static int do_wait(void);
static int do_broadcast(void);

#endif