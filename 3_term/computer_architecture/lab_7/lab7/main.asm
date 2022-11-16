	;       П 7, П 1, П 4, П 5, П 6, П 2, П 3
	INCLUDE Irvine32.inc
	.686
	.model  flat, c
	.stack

	.data

	Info    byte "  yasnogorodskyi   nikita       victorivich    02.12.2003       kyiv     kyivska        pz22  ", 00
	InfoLen EQU $-Info

	Subjects    byte 0Dh, 0Ah, "OP - 99, OOP - 99", 00
	SubjectsLen EQU $-Subjects

	Surname         byte     22 DUP(?)
	FirstName       byte     22 DUP(?)
	MiddleName      byte     22 DUP(?)
	Birth           byte     22 DUP(?)
	Town            byte     22 DUP(?)
	Region          byte     22 DUP(?)
	UniversityGroup byte     22 DUP(?)

	SurnameL    byte     0
	NameL       byte     0
	MiddleNameL byte     0
	BirthL      byte     0
	TownL       byte     0
	RegionL     byte     0
	GroupL      byte     0

	Info2    byte  30+InfoLen DUP(?), 0Dh, 0Ah, 00
	Info2Len EQU $-Info2

	Info3    byte  InfoLen DUP(?)
	Info3Len EQU $-Info3

	AllSpaces byte 0

	CountFirstSym byte 0

	fileHandle DWORD ?

	.code

START:

	mov EDI, OFFSET Info; EDI - pointer to Info
	mov ECX, InfoLen; ECX - length of Info
	cld ; direction flag - forward

surnameField:
	;    count spaces
	call CountingSpaces
	add  AllSpaces, DL

	;    count Field Length
	call FieldLenght
	mov  SurnameL, DL

	;    copy from Info to Field variable
	mov  EAX, OFFSET Surname
	call CopyInfoToVariable

firstNameField:
	call CountingSpaces
	add  AllSpaces, DL

	call FieldLenght
	mov  NameL, DL

	mov  EAX, OFFSET FirstName
	call CopyInfoToVariable

middleNameField:
	call CountingSpaces
	add  AllSpaces, DL

	call FieldLenght
	mov  MiddleNameL, DL

	mov  EAX, OFFSET MiddleName
	call CopyInfoToVariable

birthField:
	call CountingSpaces
	add  AllSpaces, DL

	call FieldLenght
	mov  BirthL, DL

	mov  EAX, OFFSET Birth
	call CopyInfoToVariable

townField:
	call CountingSpaces
	add  AllSpaces, DL

	call FieldLenght
	mov  TownL, DL

	mov  EAX, OFFSET Town
	call CopyInfoToVariable

regionField:
	call CountingSpaces
	add  AllSpaces, DL

	call FieldLenght
	mov  RegionL, DL

	mov  EAX, OFFSET Region
	call CopyInfoToVariable

groupField:
	call CountingSpaces
	add  AllSpaces, DL

	call FieldLenght
	mov  GroupL, DL

	mov  EAX, OFFSET UniversityGroup
	call CopyInfoToVariable

	call CountingSpaces
	add  AllSpaces, DL

startCopyToInfo2:
	mov AL, ' '
	mov EDI, OFFSET Info2
	cld

copyGroupToInfo2:
	mov ECX, 7; number of spaces to write
	rep stosb
	mov CL, GroupL; CL is part of ECX
	mov ESI, OFFSET UniversityGroup
	rep movsb

copySurnameToInfo2:
	mov ECX, 1
	rep stosb
	mov CL, SurnameL
	mov ESI, OFFSET Surname
	rep movsb

copyBirthToInfo2:
	mov ECX, 4
	rep stosb
	mov CL, BirthL
	mov ESI, OFFSET Birth
	rep movsb

copyTownToInfo2:
	mov ECX, 5
	rep stosb
	mov CL, TownL
	mov ESI, OFFSET Town
	rep movsb

copyRegionToInfo2:
	mov ECX, 6
	rep stosb
	mov CL, RegionL
	mov ESI, OFFSET Region
	rep movsb

copyNameToInfo2:
	mov ECX, 2
	rep stosb
	mov CL, NameL
	mov ESI, OFFSET FirstName
	rep movsb

copyMiddleNameToInfo2:
	mov ECX, 3
	rep stosb
	mov CL, MiddleNameL
	mov ESI, OFFSET MiddleName
	rep movsb; copy MiddleName to Info2 (ESI -> EDI)

writeToInfoFile:
	;      display Info2 before writting
	mov    EDX, OFFSET Info2
	call   Writestring
	;      create file and write Info2, Info to it
	INVOKE CreateFile, ADDR Surname, GENERIC_WRITE, DO_NOT_SHARE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0
	mov    fileHandle, EAX

	.IF eax != INVALID_HANDLE_VALUE

	INVOKE WriteFile, fileHandle, ADDR Info2, Info2Len, 0, 0
	INVOKE WriteFile, fileHandle, ADDR Info, InfoLen, 0, 0

	INVOKE CloseHandle, fileHandle

	.ENDIF

readFromFileAndWriteToInfo3:
	;      open file, read Info2 from it and write to Info3
	INVOKE CreateFile, ADDR Surname, GENERIC_READ or GENERIC_WRITE, DO_NOT_SHARE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0
	mov    fileHandle, EAX

	INVOKE SetFilePointer, fileHandle, Info2Len, 0, FILE_BEGIN

	INVOKE ReadFile, fileHandle, ADDR Info3, Info3Len, 0, 0

	;    Count first symbol occurences in Info3
	mov  EDI, OFFSET Info3
	mov  ECX, Info3Len
	call CountingSpaces
	mov  AL, [EDI]; search for value in AL
	mov  CountFirstSym, 0

	;----------------
	; Procedures
	;----------------

CountSym:
	repne scasb
	inc   CountFirstSym
	inc   ECX

	loop CountSym
	dec  CountFirstSym

	INVOKE WriteFile, fileHandle, ADDR Subjects, SubjectsLen, 0, 0
	INVOKE CloseHandle, fileHandle

	RET

CopyInfoToVariable:
	;   EAX  - Field variable offset
	mov EBX, ECX; EBX - length of Info after Fragment
	mov CL, DL; ECX = CL - length of Fragment
	sub EDI, ECX; EDI - pointer to Fragment
	mov ESI, EDI; ESI - pointer to Fragment in Info
	mov EDI, EAX; EDI - pointer to Fragment in Fragment variable

	rep movsb; copy Fragment from Info to Fragment variable (ESI -> EDI)

	mov EDI, ESI
	mov ECX, EBX
	ret

CountingSpaces:
	mov  EDX, ECX; save current idx
	mov  AL, ' '
	repe scasb; repeat while equal to ' '

	dec EDI
	inc ECX

	sub EDX, ECX; diff starting and ending idx to find length
	ret

FieldLenght:
	mov   EDX, ECX; save current idx
	mov   AL, ' '
	repne scasb; find first space

	dec EDI
	inc ECX

	sub EDX, ECX; diff starting and ending idx to find length
	ret

	END START
