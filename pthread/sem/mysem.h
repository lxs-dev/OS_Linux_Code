#ifndef __MYSEM_H
#define __MYSEM_H

typedef void sem_t;

sem_t* sem_init(int val);

int sem_add(sem_t*st,int val);

int sem_sub(sem_t*st,int val);

int sem_destroy(sem_t*st);


#endif