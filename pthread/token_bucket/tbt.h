#ifndef __TBT_H_
#define __TBT_H_

#define NUM_MAX  1024
typedef void token_t;



token_t *token_init(int cps,int token_max);

int GetTokenNum(token_t* tk,int want_num);

int ReturnTokenNum(token_t* tk ,int ret_num);

void token_destroy(token_t *tk);


#endif