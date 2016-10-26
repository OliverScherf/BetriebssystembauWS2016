
;******************************************************************************
;* Betriebssysteme                                                            *
;*----------------------------------------------------------------------------*
;*                                                                            *
;*                             S E T U P  A P                                 *
;*                                                                            *
;*----------------------------------------------------------------------------*
;* Der Setup-Code liegt an 0x00004000. Er wird nach einem Startup-IPI noch im *
;* 'Real-Mode' gestartet, so dass zu Beginn auch noch BIOS-Aufrufe erlaubt    *
;* sind. Dann werden jedoch alle Interrupts verboten, die Adressleitung A20   *
;* aktiviert und die Umschaltung in den 'Protected-Mode' vorgenommen. Alles   *
;* weitere uebernimmt der Startup-Code des Systems.                           *
;******************************************************************************
SETUP_AP_MAGIC	equ 0xdead

[GLOBAL setup_ap_start]
[GLOBAL setup_ap]
[GLOBAL setup_ap_end]

[EXTERN system_gdt_descr]
[EXTERN system_gdt_start]
[EXTERN system_gdt_end]
[EXTERN system_idt_descr]
[EXTERN system_idt_start]
[EXTERN system_idt_end]
[EXTERN system_code_start]
[EXTERN bootinfo_pointer]
[EXTERN guardian]
[EXTERN ap_stack]
[EXTERN main_ap]
[EXTERN startup_ap]

[SECTION .text]

USE16
;
; Segmentregister initialisieren
;
setup_ap_start:
	dw SETUP_AP_MAGIC
setup_ap:
	mov	ax,cs		; Daten- und Codesegment sollen
	mov	ds,ax		; hierher zeigen. Stack brauchen wir hier nicht.
;
; So, jetzt werden die Interrupts abgeschaltet
;
	cli			; Maskierbare Interrupts verbieten
	mov	al,0x80		; NMI verbieten
	out	0x70,al
;
; IDT und GDT setzen
;
	lidt	[idt_48 - setup_ap]
	lgdt	[gdt_48 - setup_ap]
;
; Umschalten in den Protected Mode
;
	mov	ax,1
	lmsw	ax
	jmp flush_instr

flush_instr:
	;jmp	dword 0x08:0x30000
	jmp	dword 0x08:startup_ap
	hlt

gdt:
	dw	0,0,0,0		; NULL Deskriptor

	dw	0xFFFF		; 4Gb - (0x100000*0x1000 = 4Gb)
	dw	0x0000		; base address=0
	dw	0x9A00		; code read/exec
	dw	0x00CF		; granularity=4096, 386 (+5th nibble of limit)

	dw	0xFFFF		; 4Gb - (0x100000*0x1000 = 4Gb)
	dw	0x0000		; base address=0
	dw	0x9200		; data read/write
	dw	0x00CF		; granularity=4096, 386 (+5th nibble of limit)

idt_48:
	dw	0		; idt limit=0
	dw	0,0		; idt base=0L
	
gdt_48:
	dw	0x18		; GDT Limit=24, 3 GDT Eintraege
	dd	0x40000 + gdt - setup_ap; Physikalische Adresse der GDT

setup_ap_end:
	dw SETUP_AP_MAGIC
