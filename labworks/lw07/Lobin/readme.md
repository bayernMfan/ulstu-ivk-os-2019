#Лабораторная работа №7 Лобина Михаила
##Первое задание
Две части, 1.c и 2.c. Просто переписано (творчески) из методички, по заданию. Первый ждет семафора на один, второй посылает этот семафор.
##Второе задание
Две части, 2_1.с и 2_2.с. Измененная версия первого задания, теперь первый ждет семафора на пять, а второй посылает семафор по единичке.
##Третье задание
Одна часть, взаимодействие pipe по семафорам. Родитель посылает сообщение, потомок ждет. Когда потомок получает сообщение, посылает семафор родителю, и тот начинает ждать сообщения. Потомок посылает сообщение.

На этот раз lab.sh рядом нет, потому что не гарантируется одновременность.