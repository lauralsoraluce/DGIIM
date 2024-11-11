.section .data
lista:		.int 0xffffffff, 1
longlista:	.int   (.-lista)/4
resultado:	.quad 0
  formato: 	.string	"suma = %llu = 0x%llx hex\n"

.section .text
_start: .global _start

	call trabajar	# subrutina de usuario
	call imprim_C	# printf()  de libC
	call acabar_C	# exit()    de libC
	ret

trabajar:
	mov     $lista, %rbx
	mov  longlista, %ecx
	call suma		# suma(&lista, longlista);
	mov  %eax, resultado
	mov  %edx, resultado + 4
	ret

# unsigned long long suma(unsigned *lista, unsigned n)
#            edx:eax                  rbx         ecx
suma:
	xor %eax, %eax            # resultado parte baja = 0
	xor %edx, %edx            # resultado parte alta = 0
	xor %edi, %edi            # i = 0
.Lbucle:
	cmp %edi, %ecx            # comparar i < n
	jz .Lfin
	add (%rbx, %rdi, 4), %eax # sumar partes bajas
	adc $0, %edx              # sumar acarreos
	inc %edi                  # ++i
	jmp .Lbucle
.Lfin:	
	ret

imprim_C:			# requiere libC
	mov   $formato, %rdi
	mov   resultado,%rsi
	mov   resultado,%rdx
	mov          $0,%eax	# varargin sin xmm
	call  printf		# == printf(formato, res, res);
	ret

acabar_C:			# requiere libC
	mov  resultado, %edi
	call _exit		# ==  exit(resultado)
	ret
