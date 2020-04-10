	.text
	.intel_syntax noprefix
	.file	"1.hello.c"
	.globl	main                    # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
.Lmain$local:
	.cfi_startproc
# %bb.0:                                # %entry
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	sub	rsp, 32
	mov	dword ptr [rbp - 4], 0
	mov	dword ptr [rbp - 8], edi
	mov	qword ptr [rbp - 16], rsi
	movabs	rdi, offset .L.str
	mov	al, 0
	call	printf
	xor	ecx, ecx
	mov	dword ptr [rbp - 20], eax # 4-byte Spill
	mov	eax, ecx
	add	rsp, 32
	pop	rbp
	.cfi_def_cfa rsp, 8
	ret
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"Hello world!!!\n"
	.size	.L.str, 16

	.ident	"clang version 11.0.0 (https://github.com/llvm/llvm-project.git e08464fb450456881733c885267b32dc7339cf11)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym printf
