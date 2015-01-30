def MAXSUBARRAY(A):
    cursum = 0
    curseq = []
    maxsum = 0
    maxseq = []
    for i in A:
        if cursum + i > 0:
            cursum += i
            curseq.append(i)
        else:
            cursum = 0
            curseq = []  
        if cursum > maxsum:
            maxsum = cursum
            maxseq = list(curseq)
    return (maxsum, maxseq)
    
A = [1, 4, -9, 8, 1, 3, 3, 1, -1, -4, -6, 2, 8, 19, -10, -11]
print MAXSUBARRAY(A)