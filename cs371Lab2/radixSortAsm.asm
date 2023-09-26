; extern "C" radixSortAsm_(int* thingToSort, int* scratch, int* counts, int nElementsToSort);
; rcx is the address of thingToSort
; rdx is the address of the scratch register
; r8 is the address of counts
; r9d is the number of elements to sort

RCX_Home equ 8
RDX_Home equ 16
R8_Home equ 24
R9_Home equ 32

.code
radixSortAsm_ proc

	ret

radixSortAsm_ endp
	end