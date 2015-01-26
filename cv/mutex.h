#ifndef _MUTEX_H
#define _MUTEX_H

void init_mutex_table(void);
int lock(int, int);
int unlock(int, int);

#endif