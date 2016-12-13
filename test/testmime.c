/* 
 * Copyright (c) 2016 Lammert Bies
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */


#include <stdio.h> 
#include "libhttp.h"
#include "../src/httplib_main.h"
#include "../src/httplib_string.h"

#define BUFLEN		1024

/*
 * int main( void );
 *
 * The main() routine of the testmime program crawls through the list of MIME
 * types and checks if the list has been properly sorted. It also checks for
 * all the records in the list if the binary search algorithm returns the
 * proper MIME type.
 */

int main( void ) {

	int a;
	int index;
	int problems;
	const char *p1;
	const char *p2;
	char buffer[BUFLEN];

	problems = 0;

	p1    = XX_httplib_builtin_mime_ext( 0 );
	index = 1;
	do {
	
		p2 = XX_httplib_builtin_mime_ext( index );

		if ( p1 == NULL  || p2 == NULL ) break;

		if ( mg_strcasecmp( p1, p2 ) >= 0 ) {
			
			printf( "Compare ERROR \"%s\" met \"%s\"\n", p1, p2 );
			problems++;
		}

		index++;
		p1 = p2;

	} while ( p1 != NULL  &&  p2 != NULL );


	printf( "Mime type van CSV: \"%s\"\n", mg_get_builtin_mime_type( "fiets.CsV" ) );

	for (a=0; a<index; a++) {

		XX_httplib_snprintf( NULL, NULL, buffer, BUFLEN, "filename%s", XX_httplib_builtin_mime_ext( a ) );
		p1 = XX_httplib_builtin_mime_type( a );
		p2 = mg_get_builtin_mime_type( buffer );

		if ( p1 != p2 ) {

			printf( "Lookup error: %s returned as MIME type for %s\n", p2, buffer );
			problems++;
		}
	}

	if ( problems == 0 ) printf( "MIME type lookup function is working OK\n" );
	else                 printf( "%d errors found in MIME type lookup function.\n", problems );

	return ( problems > 0 );

}  /* main (testmime) */
