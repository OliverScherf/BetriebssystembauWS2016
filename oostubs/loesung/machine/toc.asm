; $Id: toc.asm 956 2008-10-19 22:24:23Z hsc $

;******************************************************************************
;* Betriebssysteme                                                            *
;*----------------------------------------------------------------------------*
;*                                                                            *
;*                               T O C . A S M                                *
;*                                                                            *
;*----------------------------------------------------------------------------*
;*
;******************************************************************************

%include "machine/toc.inc"

; EXPORTIERTE FUNKTIONEN

[GLOBAL toc_switch]
[GLOBAL toc_go]

; IMPLEMENTIERUNG DER FUNKTIONEN

[SECTION .text]

; TOC_GO : Startet den ersten Prozess ueberhaupt.
;
; C Prototyp: void toc_go (struct toc* regs);

toc_go:
    mov eax, [esp+8]        ; *ebx    -> eax
    mov ebx, [eax]          ; [*ebx]  -> ebx
    mov esi, [eax+4]        ; [*esi]  -> esi
    mov edi, [eax+8]        ; [*edi]  -> edi
    mov ebp, [eax+12]       ; [*ebp]  -> ebp
    mov esp, [eax+16]       ; [*esp]  -> esp



; Hier muesst ihr selbst Code vervollstaendigen

; TOC_SWITCH : Prozessumschaltung. Der aktuelle Registersatz wird
;              gesichert und der Registersatz des neuen "thread of control"
;              wird in den Prozessor eingelesen.
;
; C Prototyp: void toc_switch (struct toc* regs_now,
;                              struct toc* reg_then);

toc_switch:
; Hier muesst ihr selbst Code vervollstaendigen
