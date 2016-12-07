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
    mov eax, [esp+4]
    mov ebx, [eax + ebx_offset]           ; [regs.ebx]          -> ebx
    mov esi, [eax + esi_offset]           ; [regs.esi]          -> esi
    mov edi, [eax + edi_offset]           ; [regs.edi]          -> edi
    mov ebp, [eax + ebp_offset]           ; [regs.ebp]          -> ebp
    mov esp, [eax + esp_offset]           ; [regs.esp]          -> esp
    ret

; Hier muesst ihr selbst Code vervollstaendigen

; TOC_SWITCH : Prozessumschaltung. Der aktuelle Registersatz wird
;              gesichert und der Registersatz des neuen "thread of control"
;              wird in den Prozessor eingelesen.
;
; C Prototyp: void toc_switch (struct toc* regs_now,
;                              struct toc* reg_then);

toc_switch:
    mov eax,                  [esp+4]       ; *regs_now           -> eax
    mov [eax + ebx_offset],   ebx         ; current ebx         -> [regs_now.ebx]
    mov [eax + esi_offset],   esi         ; current esi         -> [regs_now.esi]
    mov [eax + edi_offset],   edi         ; current edi         -> [regs_now.edi]
    mov [eax + ebp_offset],   ebp         ; current ebp         -> [regs_now.ebp]
    mov [eax + esp_offset],   esp         ; current esp         -> [regs_now.esp]

    mov eax, [esp+8]                      ; *regs_then          -> eax
    mov ebx, [eax + ebx_offset]           ; [regs_now.ebx]      -> ebx
    mov esi, [eax + esi_offset]           ; [regs_now.esi]      -> esi
    mov edi, [eax + edi_offset]           ; [regs_now.edi]      -> edi
    mov ebp, [eax + ebp_offset]           ; [regs_now.ebp]      -> ebp
    mov esp, [eax + esp_offset]           ; [regs_now.esp]      -> esp
    ret
; Hier muesst ihr selbst Code vervollstaendigen
