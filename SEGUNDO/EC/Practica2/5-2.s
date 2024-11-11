.section .data
#ifndef TEST
#define TEST 9
#endif
	.macro linea
#if TEST==1
	.int 1, 1, 1, 1
#elif TEST==2
	.int 0x0fffffff, 0x0fffffff, 0x0fffffff, 0x0fffffff
#elif TEST==3
	.int 0x10000000, 0x10000000, 0x10000000, 0x10000000
#elif TEST==4
	.int 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff
#elif TEST==5
	.int -1, -1, -1, -1
#elif TEST==6
	.int 200000000, 200000000, 200000000, 200000000
#elif TEST==7
	.int 300000000, 300000000, 300000000, 300000000
#elif TEST==8
	.int 5000000000, 5000000000, 5000000000, 5000000000
#else
	.error "Definir TEST entre 1 y 8"
#endif
	.endm
	
	lista: 	.irpc i,1234
			linea
			.endr
	longlista: 	.int (.-lista)/4 
	resultado: 	.quad 0
	formato: 	.ascii "resultado \t = %18lu (uns)\n"
			.ascii "\t\t = 0x%18lx (hex)\n"
			.asciz "\t\t = 0x %08x %08x \n"	

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
	adc $0, %edx		# suma el contenido del registro que cuenta los acarreos más el acarreo de la suma anterior
	inc %rdi		# incrementamos el contador de sumas: i++
	jmp bucle		# volvemos a empezar el bucle
	
#En este ejercicio, no hace falta una función no_acarreo, ya que si no hay acarreo, simplemente se mantendrá el valor de %edx intacto. 

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
