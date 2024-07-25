#ifndef SOLL_H
#define SOLL_H

#include "general/general.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct soll soll;
typedef struct Node Node;

typedef enum { none, mtf, transpose } orgtype;

const char* solltype_to_string(const soll* s);

soll* soll_init(orgtype type);

void soll_add(soll* s, char* str);

bool soll_remove(soll* s, char* str);

bool soll_isin(soll* s, char* str, long* cnt);

int soll_freq(soll* s, char* str);

int soll_size(soll* s);

void soll_tostring(soll* s, char* str);

bool soll_free(soll* s);

#endif // SOLL_H
