/*
 * malloc483.c
 * Copyright (C) 2020 Aravind SUKUMARAN RAJAM (asr) <aravind_sr@outlook.com>
 *
 * Distributed under terms of the GNU LGPL3 license.
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

char* malloc483(uint64_t bytes, char* fname, uint64_t lineno)
{
	printf("Intercepted malloc for %lu bytes from file %s lineno %lu\n", bytes, fname, lineno);
	return (char*) malloc(bytes);
}


