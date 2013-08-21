int neighbour_in_plane ( elem_t l[LATTICE_SIZE][LATTICE_SIZE], int j, int k )
{
    return 
     (V != l[(j-1) & (LATTICE_SIZE-1)][k  ].t) +
     (V != l[j                       ][k-1].t) + 
     (V != l[j                       ][k+1].t) +
     (V != l[(j+1) & (LATTICE_SIZE-1)][k  ].t);
}