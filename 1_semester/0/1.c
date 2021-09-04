#include <stdio.h>

int main()
{
	char name[15];
	printf("Enter your name: ");
	scanf("%s", name);
	printf("Hello \"\"%s\"\"! You are welcome to C world\r\n", name);
}

// original code
/*int main()
{
	char name[15];
	printf("Enter your name: ");
	scanf("%s", name)
	printf("Hello ""%s""! You are welcome to C world\r\n", name);
	_getch();
}*/

// проблема у подвійних лапках, потрібно заескейпити, щоб вони були звичайними символами