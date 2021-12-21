#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <setjmp.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char name;  //имя файла
    char readbuffer[1000];  //строки для имени файла
    int g[2];  //дискрипторы межпроцессного канала
    FILE* fp;  //указатель для файла
    printf("Enter the c-file name (without extension): ");
    scanf("%s", &name);
    pipe(g);  //создание межпроцессного канала
    if ( !fork() ) {  //потомок
        close(g[0]);  //закрытие межпроцессного канала на чтение(ввод)
        printf("sending file name...\n");
        sleep(4);
        write(g[1], &name, strlen(&name));  //посылаем имя файла через выход канала(вывод)
        printf("sent successfully\n");
        sleep(4);
        exit(0);  //успешное завершение программы
    }
    else {  //процесс родитель
        close(g[1]);  //закрытие межпроцессного канала на вывод(запись)
        printf("reading file name...\n");
        sleep(4);
        read(g[0], readbuffer, sizeof(readbuffer));  //чтение строки из межпроцессного канала (ввод)
        printf("read succesfully\n");
        sleep(4);
        printf("creating command file...\n");
        if ( (fp = fopen("laba21.bat","w")) == NULL ) {  //создаем файл и открываем его на запись
            printf("error!\n");
            return 1;
        }
        else {
            fwrite("#!/bin/shell\n", strlen("#!/bin/shell\n"), 1, fp);
            fwrite("gcc -o ", strlen("gcc -o "), 1, fp);
            fwrite(readbuffer, strlen(readbuffer) - 2, 1, fp);
            fwrite(".exe ", strlen(".exe "), 1, fp);
            fwrite(readbuffer, strlen(readbuffer) - 2, 1, fp);
            fwrite(".c\n", strlen(".c\n"), 1, fp);
            fwrite("./", strlen("./"), 1, fp);
            fwrite(readbuffer, strlen(readbuffer) - 2, 1, fp);
            fwrite(".exe", strlen(".exe"), 1, fp);
            fclose(fp);
        }
        sleep(4);
        printf("file laba21.bat created\n");
    }
    return 0;
}


