/*****************************************************************
**
**	@(#) domaincmp.c -- compare two domain names
**
**	Copyright (c) Aug 2005, Karle Boss, Holger Zuleger (kaho).
**	All rights reserved.
**	
**	This software is open source.
**	
**	Redistribution and use in source and binary forms, with or without
**	modification, are permitted provided that the following conditions
**	are met:
**	
**	Redistributions of source code must retain the above copyright notice,
**	this list of conditions and the following disclaimer.
**	
**	Redistributions in binary form must reproduce the above copyright notice,
**	this list of conditions and the following disclaimer in the documentation
**	and/or other materials provided with the distribution.
**	
**	Neither the name of Karle Boss or Holger Zuleger (kaho) nor the
**	names of its contributors may be used to endorse or promote products
**	derived from this software without specific prior written permission.
**	
**	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
**	"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
**	TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
**	PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE
**	LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
**	CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
**	SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
**	INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
**	CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
**	ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
**	POSSIBILITY OF SUCH DAMAGE.
**
*****************************************************************/
# include <stdio.h>
# include <string.h>
# include <assert.h>
# include <ctype.h>
#define extern
# include "domaincmp.h"
#undef extern


#define	goto_labelstart(str, p)	while ( (p) > (str) && *((p)-1) != '.' ) \
					(p)--

/*****************************************************************
**      int domaincmp (a, b)
**      compare a and b as fqdns.
**      return <0 | 0 | >0 as in strcmp
**      A subdomain is less than the corresponding parent domain,
**      thus domaincmp ("z.example.net", "example.net") return < 0 !!
*****************************************************************/
int     domaincmp (const char *a, const char *b)
{
	register const  char    *pa;
	register const  char    *pb;

	if ( a == NULL ) return -1;
	if ( b == NULL ) return 1;

	if ( *a == '.' )	/* skip a leading dot */
		a++;
	if ( *b == '.' )	/* same at the other string */
		b++;

	/* let pa and pb point to the last non dot char */
	pa = a + strlen (a);
	do 
		pa--;
	while ( pa > a && *pa == '.' );	

	pb = b + strlen (b);
	do 
		pb--;
	while ( pb > b && *pb == '.' );

	/* cmp  both domains starting at the end */
	while ( *pa == *pb && pa > a && pb > b )
		pa--, pb--;

	if ( *pa != *pb )	/* both domains are different ? */
	{
		if ( *pa == '.' )
			pa++;			/* set to beginning of next label */
		else
			goto_labelstart (a, pa);	/* find begin of current label */
		if ( *pb == '.' )
			pb++;			/* set to beginning of next label */
		else
			goto_labelstart (b, pb);	/* find begin of current label */
	}
	else		/* maybe one of them has a subdomain */
	{
		if ( pa > a )
			if ( pa[-1] == '.' )
				return -1;
			else
				goto_labelstart (a, pa);
		else if ( pb > b )
			if ( pb[-1] == '.' )
				return 1;
			else
				goto_labelstart (b, pb);
		else
			return 0;	/* both are at the beginning, so they are equal */
	}

	/* both domains are definitly unequal */
	while ( *pa == *pb )	/* so we have to look at the point where they differ */
		pa++, pb++;

	return *pa - *pb;
}

#ifdef DOMAINCMP_TEST
static  struct {
         char    *a;
         char    *b;
         int     res;
} ex[] = {
         { ".",          ".",    0 },
         { "test",       "",   1 },
         { "",			 "test2", -1 },
         { "",			 "",     0 },
         { "de",         "de",   0 },
         { ".de",         "de",   0 },
         { "de.",        "de.",  0 },
         { ".de",        ".de",  0 },
         { ".de.",       ".de.", 0 },
         { ".de",        "zde",  -1 },
         { ".de",        "ade",  1 },
         { "zde",        ".de",  1 },
         { "ade",        ".de",  -1 },
         { "a.de",       ".de",  -1 },
         { ".de",        "a.de",  1 },
         { "a.de",       "b.de", -1 },
         { "a.de.",       "b.de", -1 },
         { "a.de",       "b.de.", -1 },
         { "a.de",       "a.de.", 0 },
         { "aa.de",      "b.de", -1 },
         { "ba.de",      "b.de", 1 },
         { "a.de",       "a.dk", -1 },
         { "anna.example.de",    "anna.example.de",      0 },
         { "anna.example.de",    "annamirl.example.de",  -1 },
         { "anna.example.de",    "ann.example.de",       1 },
         { "example.de.",        "xy.example.de.",       1 },
         { "example.de.",        "ab.example.de.",       1 },
         { "example.de",        "ab.example.de",       1 },
         { "ab.example.de",        "example.de",       -1 },
         { "ab.mast.de",          "axt.de",             1 },
         { "ab.mast.de",          "obt.de",             -1 },
         { "abc.example.de.",    "xy.example.de.",       -1 },
         { NULL, NULL,   0 }
};

const char	*progname;
main (int argc, char *argv[])
{
	
	int	expect;
	int	res;
	int	c;
	int	i;

	progname = *argv;

	for ( i = 0; ex[i].a; i++ )
	{
		expect = ex[i].res;
		if ( expect < 0 )
			c = '<'; 
		else if ( expect > 0 )
			c = '>'; 
		else 
			c = '='; 
		printf ("%-20s %-20s ==> %c 0 ", ex[i].a, ex[i].b, c);
		fflush (stdout);
		res = domaincmp (ex[i].a, ex[i].b);
		printf ("%3d  ", res);
		if ( res < 0 && expect < 0 || res > 0 && expect > 0 || res == 0 && expect == 0 ) 
			puts ("ok");
		else
			puts ("not ok");
	}
}
#endif
