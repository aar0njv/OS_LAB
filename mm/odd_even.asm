DATA SEGMENT
    MSG1 DB 0AH,0DH, "ENTER A NUMBER (0-9): $"
    EVEN_MSG DB 0AH,0DH, "THE NUMBER IS EVEN.$"
    ODD_MSG DB 0AH,0DH, "THE NUMBER IS ODD.$"
DATA ENDS

CODE SEGMENT
ASSUME CS:CODE, DS:DATA

START:
    MOV AX, DATA
    MOV DS, AX

    ; Display message to enter number
    LEA DX, MSG1
    MOV AH, 09H
    INT 21H

    ; Input a single digit
    MOV AH, 01H
    INT 21H          ; AL = ASCII of entered number

    SUB AL, 30H      ; Convert ASCII to actual number

    MOV BL, AL       ; Copy number to BL
    AND BL, 01H      ; Mask LSB

    JZ EVEN          ; If zero -> even
    JMP ODD

EVEN:
    LEA DX, EVEN_MSG
    MOV AH, 09H
    INT 21H
    JMP EXIT

ODD:
    LEA DX, ODD_MSG
    MOV AH, 09H
    INT 21H

EXIT:
    MOV AH, 4CH
    INT 21H

CODE ENDS
END START
