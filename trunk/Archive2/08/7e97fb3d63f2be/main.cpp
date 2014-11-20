#include <stdio.h>
#include <stdlib.h>

/*
** Translation Table as described in RFC1113
*/
static const char cb64[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/*
** Translation Table to decode (created by author)
*/
static const char cd64[]="|$$$}rstuvwxyz{$$$$$$$>?@ABCDEFGHIJKLMNOPQRSTUVW$$$$$$XYZ[\\]^_`abcdefghijklmnopq";

#define B64_SYNTAX_ERROR        1
#define B64_FILE_ERROR          2
#define B64_FILE_IO_ERROR       3
#define B64_ERROR_OUT_CLOSE     4
#define B64_LINE_SIZE_TO_MIN    5
#define B64_SYNTAX_TOOMANYARGS  6

#define B64_MAX_MESSAGES 7
static char *b64_msgs[ B64_MAX_MESSAGES ] = {
            "b64:000:Invalid Message Code.",
            "b64:001:Syntax Error -- check help (-h) for usage.",
            "b64:002:File Error Opening/Creating Files.",
            "b64:003:File I/O Error -- Note: output file not removed.",
            "b64:004:Error on output file close.",
            "b64:005:linesize set to minimum.",
            "b64:006:Syntax: Too many arguments."
};

#define b64_message( ec ) ((ec > 0 && ec < B64_MAX_MESSAGES ) ? b64_msgs[ ec ] : b64_msgs[ 0 ])

static void encodeblock( unsigned char *in, unsigned char *out, int len )
{
    out[0] = (unsigned char) cb64[ (int)(in[0] >> 2) ];
    out[1] = (unsigned char) cb64[ (int)(((in[0] & 0x03) << 4) | ((in[1] & 0xf0) >> 4)) ];
    out[2] = (unsigned char) (len > 1 ? cb64[ (int)(((in[1] & 0x0f) << 2) | ((in[2] & 0xc0) >> 6)) ] : '=');
    out[3] = (unsigned char) (len > 2 ? cb64[ (int)(in[2] & 0x3f) ] : '=');
}

static int encode( FILE *infile, FILE *outfile, int linesize )
{
    int retcode = 0;

    unsigned char in[3];
    unsigned char out[4];
    int i, len, blocksout = 0;

    *in = (unsigned char) 0;
    *out = (unsigned char) 0;
    while( feof( infile ) == 0 ) {
        len = 0;
        for( i = 0; i < 3; i++ ) {
            in[i] = (unsigned char) getc( infile );
            if( feof( infile ) == 0 ) {
                len++;
            }
            else {
                in[i] = (unsigned char) 0;
            }
        }
        if( len > 0 ) {
            encodeblock( in, out, len );
            for( i = 0; i < 4; i++ ) {
                if( putc( (int)(out[i]), outfile ) == 0 ) {
                    if( ferror( outfile ) != 0 ) {
                        perror( b64_message( B64_FILE_IO_ERROR ) );
                        retcode = B64_FILE_IO_ERROR;
                    }
                    break;
                }
            }
            blocksout++;
        }
        if( ( blocksout >= (linesize/4) ) || ( feof( infile ) != 0 ) ) {
            if( blocksout > 0 ) {
                fprintf( outfile, "\r\n" );
            }
            blocksout = 0;
        }
    }
    return( retcode );
}

static void decodeblock( unsigned char *in, unsigned char *out )
{   
    out[ 0 ] = (unsigned char ) (in[0] << 2 | in[1] >> 4);
    out[ 1 ] = (unsigned char ) (in[1] << 4 | in[2] >> 2);
    out[ 2 ] = (unsigned char ) (((in[2] << 6) & 0xc0) | in[3]);
}

static int decode( FILE *infile, FILE *outfile )
{
    int retcode = 0;

    unsigned char in[4];
    unsigned char out[3];
    int v, i, len;

    *in = (unsigned char) 0;
    *out = (unsigned char) 0;
    while( feof( infile ) == 0 ) {
        for( len = 0, i = 0; i < 4 && feof( infile ) == 0; i++ ) {
            v = 0;
            while( ( feof( infile ) == 0 ) && ( v == 0 ) ) {
                v = getc( infile );
                if( v != EOF ) {
                    v = ((v < 43 || v > 122) ? 0 : (int) cd64[ v - 43 ]);
                    if( v != 0 ) {
                        v = ((v == (int)'$') ? 0 : v - 61);
                    }
                }
            }
            if( feof( infile ) == 0 ) {
                len++;
                if( v != 0 ) {
                    in[ i ] = (unsigned char) (v - 1);
                }
            }
            else {
                in[i] = (unsigned char) 0;
            }
        }
        if( len > 0 ) {
            decodeblock( in, out );
            for( i = 0; i < len - 1; i++ ) {
                if( putc( (int) out[i], outfile ) == 0 ){
                    if( ferror( outfile ) != 0 )      {
                        perror( b64_message( B64_FILE_IO_ERROR ) );
                        retcode = B64_FILE_IO_ERROR;
                    }
                    break;
                }
            }
        }
    }
    return( retcode );
}

static int b64( char opt, char *infilename, char *outfilename, int linesize )
{
    int retcode = B64_FILE_ERROR;

    FILE *infile;

    if( !infilename ) {
        infile = stdin;
    }
    else {
        infile = fopen( infilename, "rb" );
    }
    if( !infile ) {
        perror( infilename );
    }
    else {
        FILE *outfile;
        if( !outfilename ) {
            outfile = stdout;
        }
        else {
            outfile = fopen( outfilename, "wb" );
        }
        if( !outfile ) {
            perror( outfilename );
        }
        else {
            if( opt == 'e' ) {
                retcode = encode( infile, outfile, linesize );
            }
            else {
                retcode = decode( infile, outfile );
            }
            if( retcode == 0 ) {
                if (ferror( infile ) != 0 || ferror( outfile ) != 0) {
                    perror( b64_message( B64_FILE_IO_ERROR ) );
                    retcode = B64_FILE_IO_ERROR;
                }
            }
            if( outfile != stdout ) {
                if( fclose( outfile ) != 0 ) {
                    perror( b64_message( B64_ERROR_OUT_CLOSE ) );
                    retcode = B64_FILE_IO_ERROR;
                }
            }
        }
        if( infile != stdin ) {
            if( fclose( infile ) != 0 ) {
                perror( b64_message( B64_ERROR_OUT_CLOSE ) );
                retcode = B64_FILE_IO_ERROR;
            }
        }
    }

    return( retcode );
}

static void showuse( int morehelp )
{
    {
        printf( "\n" );
        printf( "  b64      (Base64 Encode/Decode RFC1113)\n" );
        printf( "  Usage:   b64 -option [-l<num>] [<FileIn> [<FileOut>]]\n" );
        printf( "  Options: -e  encode to Base64\n" );
        printf( "           -d  decode from Base64 -?\n" );
        printf( "           -l  use to change line size (from 72 characters)\n" );
        printf( "           -h  This help text.\n" );
        printf( "           -?  This help text.\n" );
        printf( "  Returns: 0 = success, 1 = Bad Syntax, 2 = File Open, 3 = File I/O\n" );
        printf( "  Example: b64 -e binfile b64file     <- Encode to b64\n" );
        printf( "           b64 -d b64file binfile     <- Decode from b64\n" );
        printf( "           b64 -e -l40 infile outfile <- Line Length of 40\n" );
        printf( "  Note:    Will act as a filter, but this should only be\n" );
        printf( "           used on text files due to translations made by\n" );
        printf( "           operating systems.\n" );
        printf( "  Source:  Source code and latest releases can be found at:\n" );
        printf( "           http://base64.sourceforge.net\n" );
    }
}

#define B64_DEF_LINE_SIZE   72
#define B64_MIN_LINE_SIZE    4

#define THIS_OPT(ac, av) ((char)(ac > 1 ? av[1][0] == '-' ? av[1][1] : 0 : 0))

int main( int argc, char **argv )
{
    char opt = (char) 0;
    int retcode = 0;
    int linesize = B64_DEF_LINE_SIZE;
    char *infilename = NULL, *outfilename = NULL;

    while( THIS_OPT( argc, argv ) != (char) 0 ) {
        switch( THIS_OPT(argc, argv) ) {
            case 'l':
                    linesize = atoi( &(argv[1][2]) );
                    if( linesize < B64_MIN_LINE_SIZE ) {
                        linesize = B64_MIN_LINE_SIZE;
                        printf( "%s\n", b64_message( B64_LINE_SIZE_TO_MIN ) );
                    }
                    break;
            case '?':
            case 'h':
                    opt = 'h';
                    break;
            case 'e':
            case 'd':
                    opt = THIS_OPT(argc, argv);
                    break;
             default:
                    opt = (char) 0;
                    break;
        }
        argv++;
        argc--;
    }
    if( argc > 3 ) {
        printf( "%s\n", b64_message( B64_SYNTAX_TOOMANYARGS ) );
        opt = (char) 0;
    }
    switch( opt ) {
        case 'e':
        case 'd':
            infilename = argc > 1 ? argv[1] : NULL;
            outfilename = argc > 2 ? argv[2] : NULL;
            retcode = b64( opt, infilename, outfilename, linesize );
            break;
        case 0:
            if( argv[1] == NULL ) {
                showuse( 0 );
            }
            else {
                retcode = B64_SYNTAX_ERROR;
            }
            break;
        case 'h':
            showuse( (int) opt );
            break;

    }
    if( retcode != 0 ) {
        printf( "%s\n", b64_message( retcode ) );
    }

    return( retcode );
}
