; extern "C" void countCharsAsm(char* chars, int* counts, int nChars);
;   rcx  is the address of char array
;   rdx  is the address of counts
;	r8d   is the number of characters in chars

	.code
countCharsAsm_ proc

	ret
countCharsAsm_ endp
	end
