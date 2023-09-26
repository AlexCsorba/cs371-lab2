; extern "C" void zeroAsm(int* arrayToZero, int nElements);
;   rcx  is the address of int array
;	edx   is the number of chars in the array

	.code
zeroAsm_ proc
	ret
zeroAsm_ endp
	end