#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    printf ("Лабораторная работа № 4.3\
            \nБатюшкиной А.Ю. ИСТбд-21\n");
	int fd[2], result;
	size_t size;
	pipe(fd);//Создаем pipe
	result = fork();//Порождаем новый процесс
	if (result > 0)//Проверка на успешность операции
	{//Работает родительский процесс
		int buf = 0;
		close(fd[0]);//Закрываем поток чтения
		while (1)
		{ // Родитель в бесконечном цикле записывает по 1 байту в поток
			buf++;
			size = write(fd[1],"", 1);
			printf("%d байт \n ", buf); //размер канала в используемой операционной системе
		}
		close(fd[1]);//Закрываем поток записи
	}
	else//Работает дочерний процесс
	{
		close(fd[1]);//Закрываем поток записи
		while (1); // Потомок ничего не читает из потока
		close(fd[0]);//Закрываем поток чтения
	}
	return 0;
}
