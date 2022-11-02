.586P
.MODEL FLAT, STDCALL

DATA SEGMENT
	Num1       DD 17, 3, -51, 242, -113	;  Оголошення масиву чисел, кожне з яких займає подвійне слово
	N          DD 5			;  Кількість елементів в масиві Num1
	Sum        DD 0			;  Сума елементів масиву Num1
DATA ENDS
CODE SEGMENT
	ASSUME CS:CODE,DS:DATA
START:
	lea EBX, Num1		;  Завантажуємо в BX адресу першого елемента масиву Num1
	mov ECX, N			;  Завантажуємо в CX кількість елементів в масиві Num1
	mov EAX, 0			;  В AX буде сума елементів масиву Num1
M1:
	add EAX, [EBX]		;  Додаємо до AX поточний елемент масиву Num1
	add EBX, 4			;  Формуємо адресу наступного елемента масиву Num1
	loop M1			;  Декрементує CX і якщо CX не дорівнює нулю, то на М1
	mov Sum, EAX		;  Цикл завершений. Зберігаємо обчислену суму в змінній Sum
CODE ENDS
END START
