ASSUME CS:CODE, DS:DATA

DATA SEGMENT
    MSG1 DB 0AH,0DH, 'ENTER THE FIRST 2-DIGIT NUMBER:$'
    MSG2 DB 0AH,0DH, 'ENTER THE SECOND 2-DIGIT NUMBER:$'
    MSG3 DB 0AH,0DH, 'CHOOSE OPERATION (+, -, *, /):$'
    MSG_ADD DB 0AH,0DH, 'SUM IS :$'
    MSG_SUB DB 0AH,0DH, 'DIFFERENCE IS :$'
    MSG_MUL DB 0AH,0DH, 'PRODUCT IS :$'
    MSG_DIV DB 0AH,0DH, 'QUOTIENT IS :$'
    MSG_ERR DB 0AH,0DH, 'DIVISION BY ZERO ERROR!$'
DATA ENDS

CODE SEGMENT
START:
    MOV AX, DATA
    MOV DS, AX

    ; ===== INPUT FIRST NUMBER =====
    LEA DX, MSG1
    MOV AH, 09H
    INT 21H

    MOV AH, 01H      ; first digit
    INT 21H
    SUB AL, 30H
    MOV BL, AL

    MOV AH, 01H      ; second digit
    INT 21H
    SUB AL, 30H
    MOV BH, AL

    MOV AL, BL
    MOV CL, 0AH
    MUL CL           ; AL = BL * 10
    ADD AL, BH       ; AL = tens*10 + ones
    MOV BL, AL       ; BL = first number (0–99)

    ; ===== INPUT SECOND NUMBER =====
    LEA DX, MSG2
    MOV AH, 09H
    INT 21H

    MOV AH, 01H
    INT 21H
    SUB AL, 30H
    MOV DL, AL

    MOV AH, 01H
    INT 21H
    SUB AL, 30H
    MOV DH, AL

    MOV AL, DL
    MOV CL, 0AH
    MUL CL
    ADD AL, DH
    MOV BH, AL       ; BH = second number (0–99)

    ; ===== CHOOSE OPERATION =====
    LEA DX, MSG3
    MOV AH, 09H
    INT 21H

    MOV AH, 01H
    INT 21H
    MOV CH, AL        ; store operator in CH

    CMP CH, '+'
    JE ADDITION
    CMP CH, '-'
    JE SUBTRACTION
    CMP CH, '*'
    JE MULTIPLICATION
    CMP CH, '/'
    JE DIVISION

    JMP EXIT          ; invalid input (exit)

; ===== ADDITION =====
ADDITION:
    MOV AL, BL
    ADD AL, BH
    MOV CL, 0AH
    MOV AH, 00H
    DIV CL
    MOV DL, AL        ; quotient = tens
    MOV DH, AH        ; remainder = ones

    LEA DX, MSG_ADD
    MOV AH, 09H
    INT 21H

    ADD DL, 30H
    MOV AH, 02H
    INT 21H

    ADD DH, 30H
    MOV AH, 02H
    INT 21H
    JMP EXIT

; ===== SUBTRACTION =====
SUBTRACTION:
    CMP BL, BH
    JAE SUB_OK
    ; If 2nd > 1st, show negative sign
    LEA DX, MSG_SUB
    MOV AH, 09H
    INT 21H
    MOV DL, '-'
    MOV AH, 02H
    INT 21H
    XCHG BL, BH
SUB_OK:
    MOV AL, BL
    SUB AL, BH
    MOV CL, 0AH
    MOV AH, 00H
    DIV CL
    MOV DL, AL
    MOV DH, AH

    LEA DX, MSG_SUB
    MOV AH, 09H
    INT 21H

    ADD DL, 30H
    MOV AH, 02H
    INT 21H

    ADD DH, 30H
    MOV AH, 02H
    INT 21H
    JMP EXIT

; ===== MULTIPLICATION =====
MULTIPLICATION:
    MOV AL, BL
    MUL BH            ; AX = BL * BH (result)
    MOV CX, 0AH
    MOV DX, 0000H
    DIV CX             ; AX / 10 → quotient in AL, remainder in AH
    MOV DL, AL         ; tens
    MOV DH, AH         ; ones

    LEA DX, MSG_MUL
    MOV AH, 09H
    INT 21H

    ADD DL, 30H
    MOV AH, 02H
    INT 21H

    ADD DH, 30H
    MOV AH, 02H
    INT 21H
    JMP EXIT

; ===== DIVISION =====
DIVISION:
    CMP BH, 00H
    JE DIV_ZERO
    MOV AL, BL
    MOV AH, 00H
    DIV BH             ; AL = quotient, AH = remainder

    LEA DX, MSG_DIV
    MOV AH, 09H
    INT 21H

    ADD AL, 30H
    MOV DL, AL
    MOV AH, 02H
    INT 21H

    JMP EXIT

DIV_ZERO:
    LEA DX, MSG_ERR
    MOV AH, 09H
    INT 21H
    JMP EXIT

; ===== EXIT =====
EXIT:
    MOV AH, 4CH
    INT 21H

CODE ENDS
END START
