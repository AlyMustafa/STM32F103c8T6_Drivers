#ifndef AUTOSAR_PLATFORM_TYPES_H_
#define AUTOSAR_PLATFORM_TYPES_H_

/*------------bool definition---------------*/
#include <stdbool.h>
#ifndef _Bool
#define _Bool unsigned char
#endif

/*------------SYMPOLES---------------*/
#define CPU_TYPE                 CPU_TYPE_32
#define CPU_BIT_ORDER            MSB_FIRST
#define CPU_BYTE_ORDER           HIGH_BYTE_FIRST

/*------boolean(TRUE OR FALSE)PLATFORM------*/
#ifndef FALSE
#define FALSE         (boolean)false
#endif
#ifndef TURE
#define TRUE          (boolean)TRUE
#endif

/*----------------------------------------*-

/*   boolean   */
typedef _Bool                    			boolean;

/*-------UnSigned DATA TYPES--------*/
typedef unsigned char            			uint8_t;
typedef unsigned short           			uint16_t;
typedef unsigned int             			uint32_t;
typedef unsigned long int      			    uint64_t;

/*-------Signed DATA TYPES--------*/
typedef signed char            				sint8_t;
typedef signed short           				sint16_t;
typedef signed int             				sint32_t;
typedef signed long int       				sint64_t;


typedef  float        	 					float32_t;
typedef  volatile float        	 			vfloat32_t;

typedef  double          					float64_t;
typedef volatile double         			vfloat64_t;

typedef long double     					sint80_t;
typedef volatile long double    			Vuint80_t;


/*-------Volatile UnSigned DATA TYPES--------*/
typedef volatile unsigned char				vuint8_t;
typedef volatile unsigned short				vuint16_t;
typedef volatile unsigned int				vuint32_t;
typedef volatile unsigned long int          vuint64_t;

/*-------Volatile Signed DATA TYPES--------*/
typedef volatile signed char           	    vsint8_t;
typedef volatile signed short          	    vsint16_t;
typedef volatile signed int                 vsint32_t;
typedef volatile signed long int            vsint64_t;

#define NULL 								((void*)0)


#endif