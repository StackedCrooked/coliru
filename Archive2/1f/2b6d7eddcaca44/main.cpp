def MAXSUBARRAY(A):
    maxsum = cursum = 0
    maxseq = curseq = []
    for i in A:
        cursum += i
        curseq.append(i)
        if cursum <= 0: # cut
            cursum = 0
            curseq = []  
        if cursum > maxsum: # we have a better subarray
            maxsum = cursum
            maxseq = list(curseq)
    return (maxsum, maxseq)
    
A = [1, 4, -9, 8, 1, 3, 3, 1, -1, -4, -6, 2, 8, 19, -10, -11]
print MAXSUBARRAY(A)