#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
//Лабораторная работа №4
//Тема:Потоковое межпроцессное взаимодействие.Межпроцессное взаимодействие через канал pipe.
///Задание: измените предыдущий пример, причем для двухсторонней
///связи используйте два канала: один для передачи от родителя ребенку, второй – от ребенка родителю.
//Выполнила  студентка гр. ИСТбд-22 Тулисова А.А.
using namespace std;
//Канал pipe служит для организации однонаправленной или симплекс-
//ной связи. При попытке организовать через pipe двустороннюю связь, когда
//процесс-родитель пишет информацию в pipe, предполагая, что ее получит
//процесс-ребенок, а затем читает информацию из канала pipe, предполагая,
//что ее записал порожденный процесс, то могла бы возникнуть ситуация, в
//которой процесс-родитель прочитал бы собственную информацию, а про-
//цесс-ребенок не получил бы ничего. Для использования одного канала pipe в
//двух направлениях необходимы специальные средства синхронизации процессов.
int main() {
	int fdParent[2], fdChild[2], result;
	size_t size;
	char resForChild[17], resForParent[15];
	pipe(fdParent); //Канал для записи родителем, чтения потомком
	pipe(fdChild); //Канал для записи потомком, чтения родителем
	result = fork();
	if (result > 0)
	{ //Родительский процесc
		close(fdParent[0]);//Закрываем поток чтения родителем
		close(fdChild[1]);//Закрываем поток записи потомком
		printf("Родитель: Начало записи строки...\n");
		size = write(fdParent[1], "Hello, child!", 15);
		printf("Родитель: Конец записи строки\n");
		printf("Родитель: Ожидание получения строки...\n");
		size = read(fdChild[0], resForParent, 17);
		printf("Родитель: Конец чтения полученной строки\n");
		printf("Родитель: Полученное сообщение: %s\n", resForParent);
		close(fdParent[1]);//Закрываем поток записи родителем
		close(fdChild[0]);//Закрываем поток чтения потомком
        printf("Родитель: Закрыл потоки.\n");
	}
	else
	{ //Дочерний процесс
	    close(fdParent[1]);//Закрываем поток записи родителем
		close(fdChild[0]);//Закрываем поток чтения потомком
		printf("Потомок: Начало чтения строки... \n");
		size = read(fdParent[0], resForChild, 15);
		printf("Потомок: Конец чтения полученной строки \n");
		printf("Потомок: Полученное сообщение: %s\n", resForChild);
		printf("Потомок: Начало записи строки...\n");
		size = write(fdChild[1], "Hello, parent!", 17);
		printf("Потомок: Конец записи строки\n");
		close(fdParent[0]);//Закрываем поток чтения родителем
		close(fdChild[1]);//Закрываем поток записи потомком
		printf("Потомок: Закрыл потоки. \n");
	}
	return 0;
}
