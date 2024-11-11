.section .data
	lista: 	.int 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
	longlista: 	.int (.-lista)/4 
	resultado: 	.quad 0
	formato: 	.string "suma = %llu = 0x%016llx\n" 	

.section .text 		# PROGRAMA PRINCIPAL
_start: .global _start 	# se puede abreviar de esta forma

	call trabajar 		# subrutina de usuario
	call imprim_C 		# printf() de libC
 	call acabar_C 		# exit() de libC
	ret

trabajar:
	mov $lista, %rbx 	# dirección del array lista
	mov longlista, %ecx 	# número de elementos a sumar
	call suma 		# llamar suma(&lista, longlista);
	mov %eax, resultado 	# salvar resultado
	mov %edx, resultado + 4  # guardamos el núm de acarreos en la siguiente pos de resultado
	ret
	

suma:
	xor %edi, %edi		# poner a 0 el contador de sumas (índice)
	xor %eax, %eax		# poner a 0 acumulador
	xor %edx, %edx		# poner a 0 contador de acarreos
	
bucle:
	cmp %rdi, %rcx 	# comprobamos si el núm de sumas hechas es igual a de sumas total
	jz .Lterminar		# si son iguales, se han hecho todas las sumas y no hay que seguir haciendo más
	add (%rbx, %rdi, 4), %eax # acumular i-ésimo elemento si quedan sumas por hacer
	jno .Lno_acarreo	
	inc %edx 		# incrementar el contador de acarreos si lo hay en la suma anterior
.Lno_acarreo:
	inc %rdi 		# incrementamos el contador de sumas: i++
	jmp bucle 		# seguimos acumulando
.Lterminar:
	ret
	
imprim_C:
 	mov $formato, %rdi 	# traduce resultado a decimal/hex
 	mov resultado, %rsi 	# versión libC de syscall __NR_write
 	mov resultado, %rdx 	# ventaja: printf() con fmt "%u" / "%x"
 	xor %eax, %eax		# varargin sin xmm
 	call printf 		# == printf(formato,resultado,resultado)
  	ret

acabar_C: 			# void exit(int status);
 	mov resultado, %edi 	# status: código a retornar (la suma)
 	call _exit 		# == exit(resultado)
 	ret 
