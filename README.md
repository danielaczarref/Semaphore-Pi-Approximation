# Real Time Systems - Semaphore

This is an exercise proposed for the subject of Real Time Systems of the Computer Engineering major.

## Objective

To develop a program that calculates an approximation for pi from a given series. Use 100 terms in the series and 4 threads to perform the calculations. Use semaphores to protect the critical region of the program.

##TO-DO
- Timing the program's runtime

## Running

- Make sure you have all essentials installed

```
sudo apt-get install build-essential
```

You can run my program just by typing ./semaforo in your terminal, but, in case in want to generate the executable version of the program all by yourself, you need to run:

```
gcc programDescription.c -o outputExectableDescription -lpthread -lrt -lm

```

After you run it, you can run your own executable (with the description of your preference):

```
./outputExectableDescription
```
