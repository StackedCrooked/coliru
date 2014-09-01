//  Middle   Right edge of box              ExternPt
//           |
//  O        |
//           |                              O
//           |
// X0,Y0     X1,Y1                          X2,Y2

// X0, Y0, X2, Y2, X1 are all known, only have to find Y1

// Slope = (y2-y0)/(x2-x0)  [trivially solved]
// Offset = Y0-Slope*X0
// Y1 = Slope*X1+Offset 