#pragma once

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
typedef long int TSize;
typedef int mint ;
typedef unsigned char muchar ;
typedef double mdouble ;
typedef void* TVar;
typedef void** TPtrHld;
typedef TVar(*TFVarVar)(TVar);
typedef char(*TFCharVarVar)(TVar, TVar);
typedef void(*TFVoidPtrHld)(TPtrHld);
typedef TVar(*TFVarVoid)(void);
typedef void(*TFVoidVarVar)(TVar, TVar);
typedef TSize(*TFLinTVar)(TVar);
typedef TVar(*TFVarVarLint)(TVar, TSize);
typedef void(*TFVoidVar)(TVar);
typedef TSize(*TFLinTVarVar)(TVar, TVar);
typedef void(*TFVoidVarVarVar)(TVar,TVar,TVar);

void* mnalloc(size_t size);
void* mnrealloc(void* ptr,size_t size);
void* mncalloc(size_t count,size_t size);
void mnfree(void* ptr);
