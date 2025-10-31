ASSUME DS:DATA, CS:CODE

DATA SEGMENT
    MSG1 DB 0AH,0DH, "ENTER THE FIRST NUMBER:$"
    MSG2 DB 0AH,0DH, "ENTER THE SECOND NUMBER:$"
    MSG3 DB 0AH,0DH, "DIFFERENCE IS :$"
DATA ENDS


CODE SEGMENT
START:
    MOV AX, DATA
    MOV DS, AX

    ; ======= INPUT FIRST NUMBER =======
    LEA DX, MSG1
    MOV AH, 09H
    INT 21H

    MOV AH, 01H        ; input first digit (tens)
    INT 21H
    MOV BH, AL

    MOV AH, 01H        ; input second digit (ones)
    INT 21H
    MOV BL, AL

    ; ======= INPUT SECOND NUMBER =======
    LEA DX, MSG2
    MOV AH, 09H
    INT 21H

    MOV AH, 01H        ; input first digit (tens)
    INT 21H
    MOV CH, AL

    MOV AH, 01H        ; input second digit (ones)
    INT 21H
    MOV CL, AL

    ; ======= SUBTRACTION START =======

    ; Convert ASCII digits to numeric
    SUB BH, 30H
    SUB BL, 30H
    SUB CH, 30H
    SUB CL, 30H

    ; Subtract ones place (BL - CL)
    MOV AL, BL
    MOV AH, 00H
    SUB AL, CL
    AAS                  ; adjust ASCII after subtraction
    ADD AX, 3030H        ; convert to ASCII
    MOV BL, AL           ; store result (ones)
    MOV DL, AH           ; DL may have borrow in ASCII form

    ; Subtract tens place (BH - CH - borrow)
    MOV AL, BH
    MOV AH, 00H
    SBB AL, CH           ; subtract tens + borrow
    AAS
    ADD AX, 3030H
    MOV BH, AL           ; store result (tens)
    MOV CL, AH           ; CL may have additional borrow if any

    ; ======= DISPLAY RESULT =======
    LEA DX, MSG3
    MOV AH, 09H
    INT 21H

    ; Display tens digit
    MOV DL, BH
    MOV AH, 02H
    INT 21H

    ; Display ones digit
    MOV DL, BL
    MOV AH, 02H
    INT 21H

    ; ======= EXIT PROGRAM =======
    MOV AH, 4CH
    INT 21H

CODE ENDS
END START
