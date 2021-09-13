#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <math.h>
#include <time.h>

#define QT_THREAD 4
#define TERMOS 100

typedef struct
{
  int idx, length;
} thread_arg, *ptr_thread_arg;

pthread_t threads[QT_THREAD];
thread_arg arguments[QT_THREAD];

sem_t semaforo;

double resultado;

void *thread_funcao(void *arg)
{
  ptr_thread_arg argument = (ptr_thread_arg)arg;
  double somaLocal = 0;
  int endidx;
  endidx = argument->idx + argument->length;
  for (int i = argument->idx; i < endidx; i++)
  {
    somaLocal += ((pow(-1, i)) / (2 * i + 1));
  }
  printf("Soma local: %lf\n", somaLocal);
  sem_wait(&semaforo);
  resultado += somaLocal;
  sem_post(&semaforo);
}

int main(int argc, char **argv)
{
  clock_t tInicio, tFim, t;
  sem_init(&semaforo, 0, 1);
  resultado = 0;
  int length = TERMOS / QT_THREAD;
  int remainder = TERMOS % QT_THREAD;
  tInicio = clock();

  for (int i = 0; i < QT_THREAD; i++)
  {
    arguments[i].idx = i * length;
    arguments[i].length = length;
    if (i == (QT_THREAD - 1))
    {
      arguments[i].length += remainder;
    }
    pthread_create(&threads[i], NULL, thread_funcao, &arguments[i]);
  }

  for (int i = 0; i < QT_THREAD; i++)
  {
    pthread_join(threads[i], NULL);
  }
  sem_destroy(&semaforo);
  tFim = clock();
  t = tFim - tInicio;
  printf("A aproximacao para pi/4 eh igual a: %lf\n", resultado);
  printf("\nOu seja, a aproximacao para pi eh igual a: %lf \n", resultado * 4);
  printf("Ticks gastos: %d. Tempo gasto: %Lf s\n", (int)t, (long double)(t / CLOCKS_PER_SEC));
}
