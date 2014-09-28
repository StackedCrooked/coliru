ElementType a0 = a % midBase, b0 = b % midBase;
ElementType a1 = a / midBase, b1 = b / midBase;
ProductType p = { a1*b1, a0*b0 };

ElementType cross;
ElementType tmp = base - b1*a0;
	
if (a1*b0 < tmp) {
    cross = a1*b0 + b1*a0;
} else {
	p.high += midBase;
	cross = a1*b0 - tmp;
}
	
// if base is odd, midBase is one digit too high
p.high += cross / (base/midBase);
p.low += cross % (base/midBase);
	
return p;