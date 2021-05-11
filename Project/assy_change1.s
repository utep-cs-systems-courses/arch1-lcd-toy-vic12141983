	.arch msp430g2553
	

	.p2align 1,0





	.data

state:
	.byte 0
	.text


jt:

	
	.word case0
	.word case1
	.word case2
	.word case3
	.word default		;not needed
	.global assy_change



assy_change:
	cmp #4, &state 		; state -4
        jc default    		; jump if not borrowed.

	mov &state, r12       	; move state into r12
	add r12, r12		; add r12 to itself. indexing of jt; doubleing of the of state.

	mov jt(r12),r0		;move address from branch into r0(program conter); reference of *(jt+r12)
        
                    
case0:

	call #shape1   		;method call to shape

	add #1, &state		;add one to state

	jmp out			;break



case1:

	call #shape2 		; method call to shape2

	add #1, &state		; add one to state

	jmp out			; break



case2:

	call #shape3		;method call to shape3

	add #1, &state		;add one to state

	jmp out			;break



case3:

	call #shape4		;method call to shape4

	add #1, &state		;add one to state

	jmp out			;break



default:

	mov #0, &state		;default. move r0 to state



out:

	pop r0			;pop into R0. From the stack to r0.
