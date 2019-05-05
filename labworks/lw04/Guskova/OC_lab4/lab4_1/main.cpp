#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
using namespace std;
//������������ ������ �4.1
//������������� �������������� ����� ����� pipe
//��������� ��������� ��.�����-22 �������� �.�.
int main()
{
    printf("������������ ������ �4.1\n");
    printf("������������� �������������� ����� ����� pipe\n");
    printf("��������� ��������� ��.�����-22 �������� �.�.\n");
    printf("�������: ������������� ������ ��� ����� ����� ����� ���� ����������� ���������, ����������� ������ ���������.\n");
	int fd[2], result;//fd - ��������� �� ������ �� ���� ����� ����������
	size_t size;//
	char string[] = "Some text";//������ ��� ������
	char resstring[14];//������ ��� ������
	int channel=pipe(fd);// ������ ����� � ����� ��������� ������������� - ������ ����� � ������
    if (channel == 0)         //������ -1 ,0 ��� ���������� ����������
    {                  //fd[0]-����� ������� �������� ����������, �����. �������� ������ ������ ������
                        //� ����������� ��������� ������ �������� ������
                       //fd[1] - ����� ������� �������� ����������, ���������������
                     //��������� ������ ������ � ����������� ��������� ������ �������� ������
        result = fork(); // ���������� �������� �������
        if (result > 0)
        { //�������� ������������ �������
            printf("������ ����� ������������ �������\n");// �������� ���������� ������ � �����
            close(fd[0]);//��������� ������� ����� ������
            printf("������ ������ ������...\n");
            size = write(fd[1],string, 14); //������ ���� ������ ������ � ��������� ����� ������ � �����
            printf("�������� ������...\n");
            close(fd[1]); // ��������� �������� ����� ������
            //���� ���� ��������, � ������� ���� pipe ������ ��� ������, �� ��������� ����� read ����������� �
            //���� ��������� ����������
            printf("������� �������� �����! \n");
        }
        else
         {//�������� �������� �������
            printf("������ ����� �������� �������\n");// ������� ������ ������ �� ������ ����� ������� �����
            close(fd[1]); //��������� �������� ����� ������
            printf("������ ������ ������...\n");
            size = read(fd[0], resstring, 14); // ���� �������� �� ������� ������, �� ������� �����������
                                                //(write,read - ����������� ��������� ������)
            printf("��������� ������...\n");
            printf("����������� ������: \n");
            printf("%s\n", resstring);// �������� ����������� ������
            close(fd[0]); //��������� ������� ����� ������
            printf("������� ������� �����! \n");
         }
	}
	else
        printf("������ �������� ������...\n");
    return 0;
}