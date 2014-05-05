/ / Cada objeto do tipo sse_t serão alinhados para 16 bytes limite 
struct alignas ( 16 ) sse_t
 { 
  flutuador sse_data [ 4 ] ; 
} ;
 
/ / Para o array "cacheline" será alinhado com 128 bytes de fronteira 
alignas ( 128 )  caractere cacheline [ 128 ] ;