; extern "C" int64_t _sg2_gc_offset()
; extern "C" int64_t _sg2_gc_delta()
; extern "C" int64_t _sg2_gc_count()
;
; Description:  get metadata of the binary file geometric.data
;
; extern "C" void _sg2_gc_sinL(unsigned l)
; extern "C" void _sg2_gc_cosL(unsigned l)
; extern "C" void _sg2_gc_R(unsigned l)
;
; Description:  get sinL, cosL, R values at l
;
; Requires      SSE2
;
; Name:		sg2_geocentric_data.asm
;
; Build:
;		nasm -f elf64/macho64 -o sg2_geocentric_data.o sg2_geocentric_data.asm

    global _sg2_gc_data, _sg2_gc_data_sz
    global _sg2_gc_offset, _sg2_gc_delta, _sg2_gc_count
    global _sg2_gc_sinL, _sg2_gc_cosL, _sg2_gc_R
    global _sg2_gc_tuple
    default rel

    section .data
    align 8
_sg2_gc_data:
    incbin  "geocentric.data"
DATALEN: \
    equ     $-_sg2_gc_data

    section .text
_sg2_gc_offset:
    push    rbx
    mov     rax, [_sg2_gc_data]
    jmp     done
_sg2_gc_delta:
    push    rbx
    mov     rax, [_sg2_gc_data+8]
    jmp     done
_sg2_gc_count:
    push    rbx
    mov     rax, [_sg2_gc_data+16]
    jmp     done
_sg2_gc_sinL:
    push    rbx
    push    rcx
    lea     rcx, [_sg2_gc_data]
    mov     rax, 24
    mul     rdi
    lea     rax, [rcx + rax*1 + 24]
    movsd   xmm0, [rax]
    pop     rcx
    jmp     done
_sg2_gc_cosL:
    push    rbx
    push    rcx
    lea     rcx, [_sg2_gc_data]
    mov     rax, 24
    mul     rdi
    lea     rax, [rcx + rax*1 + 32]
    movsd   xmm0, [rax]
    pop     rcx
    jmp     done
_sg2_gc_R:
    push    rbx
    push    rcx
    lea     rcx, [_sg2_gc_data]
    mov     rax, 24
    mul     rdi
    lea     rax, [rcx + rax*1 + 40]
    movsd   xmm0, [rax]
    pop     rcx
    jmp     done
_sg2_gc_tuple:
    push    rbx
    push    rcx
    lea     rcx, [_sg2_gc_data]
    mov     rax, 24
    mul     rdi
    lea     rax, [rcx + rax*1 + 24]
    pop     rcx
    jmp     done
_sg2_gc_data_sz:
    push    rbx
    mov     rax, DATALEN
    jmp     done
done:
    pop    rbx
    ret
