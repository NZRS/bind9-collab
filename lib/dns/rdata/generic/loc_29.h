/*
 * Copyright (C) 1999, 2000  Internet Software Consortium.
 * 
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS" AND INTERNET SOFTWARE CONSORTIUM
 * DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL
 * INTERNET SOFTWARE CONSORTIUM BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING
 * FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
 * WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef GENERIC_LOC_29_H
#define GENERIC_LOC_29_H 1

/* $Id: loc_29.h,v 1.12 2000/07/27 09:49:07 tale Exp $ */

/* RFC 1876 */

typedef struct dns_rdata_loc_0 {
	isc_uint8_t	version;	/* must be first and zero */
	isc_uint8_t	size;
	isc_uint8_t	horizontal;
	isc_uint8_t	vertical;	
	isc_uint32_t	latitude;
	isc_uint32_t	longitude;
	isc_uint32_t	altitude;
} dns_rdata_loc_0_t;

typedef struct dns_rdata_loc {
	dns_rdatacommon_t	common;
	union {
		dns_rdata_loc_0_t v0;
	} v;
} dns_rdata_loc_t;

#endif /* GENERIC_LOC_29_H */
