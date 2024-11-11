.section .data

#ifndef TEST
#define TEST 20
#endif
	.macro linea
#if TEST==1
	.int 1 ,2 ,1, 2
#elif TEST==2
	.int -1, -2, -1, -2
#elif TEST==3
	.int 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff
#elif TEST==4
	.int 0x80000000, 0x80000000, 0x80000000, 0x80000000
#elif TEST==5
	.int 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff
#elif TEST==6
	.int 2000000000, 2000000000, 2000000000, 2000000000
#elif TEST==7
	.int 3000000000, 3000000000, 3000000000, 3000000000
#elif TEST==8
	.int -2000000000, -2000000000, -2000000000, -2000000000
#elif TEST==9
	.int -3000000000, -3000000000, -3000000000, -3000000000
#elif TEST==10
	.int 0, 2, 1, 1
#elif TEST==11
	.int 1, 2, 1, 1
#elif TEST==12
	.int 8, 2, 1, 1
#elif TEST==13
	.int 15, 2, 1, 1
#elif TEST==14
	.int 16, 2, 1, 1
#elif TEST==15
	.int 0, -2, -1, -1
#elif TEST==16
	.int -1, -2, -1, -1
#elif TEST==17
	.int -8, -2, -1, -1
#elif TEST==18
	.int -15, -2, -1, -1
#elif TEST==19
	.int -16, -2, -1, -1
#else
	.error "Definir TEST valido"
#endif
	.endm
	
	.macro linea0 # Media / Resto - Comentario
 #if TEST>=1 && TEST<=9
	linea # casi siempre 4 lineas iguales
#elif TEST==10 // 1 / 0 - equiv toda lista 1
	.int 0, 2, 1, 1
#elif TEST==11
	.int 1, 2, 1, 1
#elif TEST==12
	.int 8, 2, 1, 1
#elif TEST==13
	.int 15, 2, 1, 1
#elif TEST==14
	.int 16, 2, 1, 1
#elif TEST==15 // -1 / 0 - equiv TEST05
	.int 0,-2,-1,-1
#elif TEST==16
	.int -1, -2, -1, -1
#elif TEST==17
	.int -8, -2, -1, -1
#elif TEST==18
	.int -15, -2, -1, -1
#elif TEST==19 // ? / ?
	.int -16,-2,-1,-1
#else
	.error "Definir TEST entre 1..19"
#endif
	.endm
			
	lista:  linea0
		.irpc i,123
		linea
		.endr
	longlista: 	.int (.-lista)/4 
	media: 	.int 0
	resto: 	.int 0
	formato: 	.ascii "media \t = %11d \t resto \t = %11d \n"
			.asciz "\t = 0x %08x \t \t = 0x %08x\n"

.section .text 		# PROGRAMA PRINCIPAL
_start: .global _start 	# se puede abreviar de esta forma

	call trabajar 		# subrutina de usuario
	call imprim_C 		# printf() de libC
 	call acabar_C 		# exit() de libC
	ret

trabajar:
	mov $lista, %rbx 	# dirección del array lista
	mov longlista, %ecx 	# número de elementos a sumar
	call .media		
	mov %eax, media	# Establecemos el valor de la media
	
	mov $lista, %rbx	# dirección del array lista
	mov longlista, %ecx 	# número de elementos a sumar
	call .resto
	mov %edx, resto

	ret
	

suma:
	xor %edi, %edi		# poner a 0 el contador de sumas (índice)
	xor %eax, %eax		# poner a 0 acumulador
	xor %edx, %edx		# poner a 0 contador de acarreos
	
bucle:
	cmp %rdi, %rcx 	# comprobamos si el núm de sumas hechas es igual a de sumas total
	jz .Lterminar		# si son iguales, se han hecho todas las sumas y no hay que seguir haciendo más
	mov (%rbx, %rdi, 4), %r8d # copiamos el i-ésimo elemento si quedan sumas por hacer
	mov %r8d, %r9d # cltd     
	sar $31, %r9d  # cltd     # extendemos r8d a r9d:r8d con el bit más significativo de r8d
	add %r8d, %eax 	# hacemos la suma (acumulador) en el registro eax
	adc %r9d, %edx		# suma el contenido del registro que cuenta los acarreos más el acarreo de la suma anterior y lo añade al contador de acarreos. 
	inc %rdi		# incrementamos el contador de sumas: i++
	jmp bucle		# volvemos a empezar el bucle
	
#En este ejercicio, no hace falta una función no_acarreo, ya que si no hay acarreo, simplemente se mantendrá el valor de %edx intacto. 

.Lterminar:
	ret
	
.media: 
	call suma		
	idiv %ecx		# Dividimos el valor de edx:eax entre %ecx (núm sumas totales). En %eax se guarda el cociente de la división.
	ret

.resto:
	call suma
	idiv %ecx		# Dividimos el valor de edx:eax entre %ecx (núm sumas totales). En %edx se guarda el resto de la división.
#	mov %edx, %eax		# Copiamos el valor del resto en %eax
	ret

imprim_C:
 	mov $formato, %rdi 	# traduce resultado a decimal/hex
 	mov media, %rsi 	# versión libC de syscall __NR_write
 	mov media, %rdx
 	mov resto, %rcx
 	mov resto, %r8d
 	xor %eax, %eax		# varargin sin xmm
 	call printf 		# == printf(formato,resultado,resultado)
  	ret

acabar_C: 			# void exit(int status);
 	mov media, %edi 	# status: código a retornar (la suma)
 	call _exit 		# == exit(resultado)
 	ret 
