; extern "C" void countIntsAsm(int* theInts, int* counts, int nInts);
;   rcx  is the address of theInts
;   rdx  is the address of counts
;	r8d   is the number of ints in theInts


RCX_Home equ 8
RDX_Home equ 16
R8_Home  equ 24
R9_Home  equ 32

	.code
countIntsAsm_ proc

	ret
countIntsAsm_ endp
	end
