/*-
 * Copyright (c) 2016 Adam Starak <starak.adam@gmail.com>
 * All rights reserved.
 *
 * This software was developed by Pawel Jakub Dawidek under sponsorship from
 * the FreeBSD Foundation.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHORS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD$
 */

// TODO: co w przypadku uzycia zlej funkcji dla danego cookie?

#include <sys/cdefs.h>
__FBSDID("$FreeBSD$");

#ifdef _KERNEL

#include <sys/types.h>
#include <sys/param.h>
#include <sys/kernel.h>
#include <sys/systm.h>
#include <sys/malloc.h>

#include <machine/stdarg.h>

#else
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#endif

#include <sys/dnv.h>
#include <sys/nv.h>

#include "nv_impl.h"

#define	CNVLIST_GET(ftype, type, nvtype)				\
ftype									\
cnvlist_get_##type(void **cookiep)					\
{									\
	if (nvpair_type(*cookiep) == NV_TYPE_##nvtype)			\
		return (nvpair_get_##type(*cookiep));			\
}

CNVLIST_GET(bool, bool, BOOL)
CNVLIST_GET(uint64_t, number, NUMBER)
CNVLIST_GET(const char *, string, STRING)
CNVLIST_GET(const nvlist_t *, nvlist, NVLIST)
CNVLIST_GET(int, descriptor, DESCRIPTOR)

#undef	DNVLIST_GET

const void *
cnvlist_get_binary(void **cookiep, size_t *sizep)
{
	const void *value;
	if (nvpair_type(*cookiep) == NV_TYPE_BINARY) {
		value = nvpair_get_binary(*cookiep, sizep);
		return (value);
	}
}

#define	CNVLIST_TAKE(ftype, type, nvtype)			    	\
ftype									\
dnvlist_take_##type(nvlist_t *nvl, void **cookiep)			\
{									\
	ftype value = cnvlist_get_##type(cookiep);			\
	nvlist_remove_nvpair(nvl, *cookiep);				\
	return (value);							\
}

CNVLIST_TAKE(bool, bool, BOOL)
CNVLIST_TAKE(uint64_t, number, NUMBER)
CNVLIST_TAKE(const char *, string, STRING)
CNVLIST_TAKE(const nvlist_t *, nvlist, NVLIST)
CNVLIST_TAKE(int, descriptor, DESCRIPTOR)

#undef	CNVLIST_TAKE

void *
cnvlist_take_binary(nvlist_t *nvl, void **cookiep, size_t *sizep)
{
	const void *value = cnvlist_get_binary(cookiep, sizep);
	nvlist_remove_nvpair(nvl, *cookiep);
	return (value);
}

#define	CNVLIST_FREE(ftype, type, nvtype)			    	\
void									\
dnvlist_FREE_##type(nvlist_t *nvl, void **cookiep)			\
{									\
	nvlist_remove_nvpair(nvl, *cookiep);				\
}

CNVLIST_FREE(bool, bool, BOOL)
CNVLIST_FREE(uint64_t, number, NUMBER)
CNVLIST_FREE(const char *, string, STRING)
CNVLIST_FREE(const nvlist_t *, nvlist, NVLIST)
CNVLIST_FREE(int, descriptor, DESCRIPTOR)

#undef	CNVLIST_TAKE

