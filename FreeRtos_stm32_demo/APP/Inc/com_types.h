#ifndef _COM_TYPES_H_
#define _COM_TYPES_H_

#define RAM_FUNC __ramfunc

typedef unsigned long int ulong;
typedef unsigned short int ushort;
typedef unsigned int uint;
typedef unsigned char u_int8_t;
typedef unsigned short int u_int16_t;
typedef unsigned int u_int32_t;
typedef unsigned long long u_int64_t;
typedef unsigned char BOOL;

typedef unsigned char BYTE;

typedef short         SHORT;
typedef unsigned short WORD;
typedef unsigned short WCHAR;

typedef int    INT;
typedef unsigned int  UINT;

typedef long   LONG;
typedef unsigned long DWOED;

#ifdef  FALSE
#undef  FALSE
#endif
#define FALSE  (0)

#ifdef  TRUE
#undef  TRUE
#endif 
#define TRUE   (1)

#define SUCCESS (0)

#define ELEMENT_OF(x) (sizeof(x) / sizeof((x)[0]))

#endif