/*
 * b9ras.hpp
 *
 *  Created on: Mar 10, 2017
 *      Author: bjornvar
 */

#ifndef B9RAS_HPP_
#define B9RAS_HPP_

/*
 * @ddr_namespace: default
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define DDR_DAT_FILE "ddr.dat"
#define EYE_CATCHER "J9VMRAS"
#define BIT_PATTERN 0xaa55aa55
#define VERSION 1

typedef unsigned char U_8;
typedef unsigned int U_32;
typedef int I_32;
typedef unsigned long long U_64;
typedef unsigned long long UDATA;
typedef long long IDATA;

class ExecutionContext;

typedef struct B9RAS {
	U_8 eyecatcher[8];
	U_32 bitpattern1;
	U_32 bitpattern2;
	I_32 version;
	I_32 length;
	void* ddrData;
	UDATA mainThreadOffset;
	UDATA omrthreadNextOffset;
	UDATA osthreadOffset;
	UDATA idOffset;
	UDATA typedefsLen;
	UDATA typedefs;
	UDATA env;
	UDATA vm;
	U_64 buildID;
	U_8 osversion[128];
	U_8 osarch[16];
	U_8 osname[48];
	U_32 cpus;
	void* environment;
	U_64 memory;
	U_8 hostname[256];
	U_8 ipAddresses[256];
	UDATA pid;
	UDATA tid;
} B9RAS;

B9RAS *initializeJ9RAS(ExecutionContext const *b9context);

#endif /* B9RAS_HPP_ */
