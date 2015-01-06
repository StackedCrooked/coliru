
    for ( int i=0; i<3; i++) 
        for (int j=0; j<3; j++) {
            for (k=0; k<3; k++) {
                if (k==1)
                    goto l1;
                if (k==2)
                    goto l2;
            }
        }
    l1:
    }
l2:
}