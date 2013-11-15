/*

    VAG-Depack, hacked by bITmASTER@bigfoot.com
    V0.1
*/




#ifdef _mam
extern "C"
{
#endif /* _mam */

#include <stdio.h>
#include <string.h>

double f[5][2] = { { 0.0, 0.0 },
                    {  60.0 / 64.0,  0.0 },
                    {  115.0 / 64.0, -52.0 / 64.0 },
                    {  98.0 / 64.0, -55.0 / 64.0 },
                    {  122.0 / 64.0, -60.0 / 64.0 } };

double samples[28];

int main( int argc, char *argv[] )
{
    FILE *vag, *pcm;
    char fname[128];
    char *p;
    int predict_nr, shift_factor, flags;
    int i;
    int d, s;
    static double s_1 = 0.0;
    static double s_2 = 0.0;
        
    if ( argc != 2 ) {
        printf( "usage: depack *.vag\n" );
        return( -1 );
    }
    
    vag = fopen( argv[1], "rb" );
    fseek( vag, 64, SEEK_SET );

    strcpy( fname, argv[1] );
    p = strrchr( fname, '.' );
    p++;
    strcpy( p, "PCM" );
    pcm = fopen( fname, "wb" );
    if ( vag == NULL ) {
        printf( "canï½´t write output file\n" );
        return( -8 );
    }




    while( 1 ) {
        predict_nr = fgetc( vag );
        shift_factor = predict_nr & 0xf;
        predict_nr >>= 4;
        flags = fgetc( vag );                          // flags
        if ( flags == 7 )
            break;              
        for ( i = 0; i < 28; i += 2 ) {
            d = fgetc( vag );
            s = ( d & 0xf ) << 12;
            if ( s & 0x8000 )
                s |= 0xffff0000;
            samples[i] = (double) ( s >> shift_factor  );
            s = ( d & 0xf0 ) << 8;
            if ( s & 0x8000 )
                s |= 0xffff0000;
            samples[i+1] = (double) ( s >> shift_factor  );
        }
    
        for ( i = 0; i < 28; i++ ) {
            samples[i] = samples[i] + s_1 * f[predict_nr][0] + s_2 * f[predict_nr][1];
            s_2 = s_1;
            s_1 = samples[i];
            d = (int) ( samples[i] + 0.5 );
            fputc( d & 0xff, pcm );
            fputc( d >> 8, pcm );
        }
    }
    
    fclose( pcm );
    fclose( vag );
    return( 0 );
}