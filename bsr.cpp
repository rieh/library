/*
x       0  1  2  3  4  5  6  7  8  9
bsr(x) -1  0  1  1  2  2  2  2  3  3
最上位bit
*/
int bsr(uint x){
	if(x==0) return -1;
	return 31 ^ __builtin_clz(x);
}
int bsr(unsigned long long x){
	if(x==0) return -1;
	return 63 ^ __builtin_clzll(x);
}

/*
x       0  1  2  3  4  5  6  7  8  9
bsl(x) -1  0  1  0  2  0  1  0  3  0
最下位bit
*/
int bsl(uint x){
	if(x==0) return -1;
	return __builtin_ctz(x);
}
int bsl(unsigned long long x){
	if(x==0) return -1;
	return __builtin_ctzll(x);
}

