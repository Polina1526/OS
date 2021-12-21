#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <setjmp.h>
#include <string.h>
#include <stdlib.h>

sigjmp_buf obl;  //область памяти для запоминания состояния процесса
int p = 0;  //счетчик прерываний

void prer();  //функция обработки прерывания

int main()
{
    printf("  !! Testing of interuption: !!\n");
    while(1){
        sleep(2);  //пауза
        sigsetjmp(obl, 1);  //запоминает текущее состояние процесса для “прыжка”
        signal(SIGINT,prer);  //в случае поступления прерывания управление передается функции prer
        printf(" Make an interuption! (press CTRL+C)\n");
    }
    return 0;
}


void prer(){  //обработка прерываний
    p++;  //счетчик прерываний
    signal(SIGINT, prer);  // при получении сигнала, поданного с клавиатуры (Ctrl+C),
                           // выполнить соответствующую функцию
    if (p == 2) {
        printf(" Interruption # %d\n", p);
        printf(" Restart the programm\n");
        siglongjmp(obl, 1);
    }
    if ((p != 2) && (p != 3)) {
        printf(" Interruption # %d\n", p);
    }
    if (p == 3) {
        printf(" Interruption #3 is the last interruption.\n");
        printf(" Making an exit!");
        exit(1);
    }
}



