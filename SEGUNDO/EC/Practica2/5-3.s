.section .data
#ifndef TEST
#endif
	.macro linea
#if TEST==1
	.int -1 ,-1 ,-1, -1
#elif TEST==2
	.int 0x04000000, 0x04000000, 0x04000000, 0x04000000
#elif TEST==3
	.int 0x08000000, 0x08000000, 0x08000000, 0x08000000
#elif TEST==4
	.int 0x10000000, 0x10000000, 0x10000000, 0x10000000
#elif TEST==5
	.int 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff
#elif TEST==6
	.int 0x80000000, 0x80000000, 0x80000000, 0x80000000
#elif TEST==7
	.int 0xF0000000, 0xF0000000, 0xF0000000, 0xF0000000
#elif TEST==8
	.int 0xF8000000, 0xF8000000, 0xF8000000, 0xF8000000
#elif TEST==9
	.int 0xF7FFFFFF, 0xF7FFFFFF, 0xF7FFFFFF, 0xF7FFFFFF
#elif TEST==10
	.int 100000000, 100000000, 100000000, 100000000
#elif TEST==11
	.int 200000000, 200000000, 200000000, 200000000
#elif TEST==12
	.int 300000000, 300000000, 300000000, 300000000
#elif TEST==13
	.int 2000000000, 2000000000, 2000000000, 2000000000
#elif TEST==14
	.int 3000000000, 3000000000, 3000000000, 3000000000
#elif TEST==15
	.int -100000000, -100000000, -100000000, -100000000
#elif TEST==16
	.int -200000000, -200000000, -200000000, -200000000
#elif TEST==17
	.int -300000000, -200000000, -200000000, -200000000
#elif TEST==18
	.int -2000000000, -2000000000, -2000000000, -2000000000
#elif TEST==19
	.int -3000000000, -3000000000, -3000000000, -3000000000
#else
	.error "Definir TEST valido"
#endif
	.endm
		
	lista: 	.irpc i,1234
			linea
			.endr
	longlista: 	.int (.-lista)/4 
	resultado: 	.quad 0
	formato: 	.ascii "resultado \t = %18ld (sgn)\n"
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
	xor %r8d, %r8d		# poner a 0 los registros auxiliares
	xor %r9d, %r9d
	xor %edi, %edi		# poner a 0 el contador de sumas (índice)
	xor %eax, %eax		# poner a 0 acumulador
	xor %edx, %edx		# poner a 0 contador de acarreos
	
bucle:
	cmp %rdi, %rcx 	# comprobamos si el núm de sumas hechas es igual a de sumas total
	jz .Lterminar		# si son iguales, se han hecho todas las sumas y no hay que seguir haciendo más
	mov (%rbx, %rdi, 4), %eax # copiamos el i-ésimo elemento si quedan sumas por hacer
	cltd 			# extendemos eax a edx:eax con el bit más significativo de eax
	add %eax, %r8d 	# hacemos la suma (acumulador) en el registro auxiliar %r8d
	adc %edx, %r9d		# suma el contenido del registro que cuenta los acarreos más el acarreo de la suma anterior y lo añade al contador de acarreos (registro auxiliar %r9d). Se hace en el auxiliar ya que el valor de %edx cambia en cada iteración del bucle, dependiendo de cual sea el bit más significativo del i-ésimo elemento de la lista 
	inc %rdi		# incrementamos el contador de sumas: i++
	jmp bucle		# volvemos a empezar el bucle
	
#En este ejercicio, no hace falta una función no_acarreo, ya que si no hay acarreo, simplemente se mantendrá el valor de %edx intacto. 

.Lterminar:
	mov %r8d, %eax 	# Copiamos el valor de la suma total en el registro eax ya que no se va a modificar más
	mov %r9d, %edx		# Copiamos el valor del contador de acarreos en edx ya que no se va a modificar más
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
