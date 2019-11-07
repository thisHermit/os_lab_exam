/*
 * Author: thisHermit
 * Execute the program with g++ sleepingBarber.cpp  -lpthread -lrt
 * Stay frosty!
*/

#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h>
#include <mutex>
#include <iostream>

using namespace std;

sem_t Customers; 
sem_t Barber; 
sem_t Seats; 
int FreeSeats = 4; 
  
void* barberF(void* arg) { 
      while(true) { 
            /* waits for a customer (sleeps). */
	    cout << "Barber: Waiting for customers. Going to sleep zzz..." << endl;
            sem_wait(&Customers);
	    cout << "Barber: Woah, I have a customer." << endl;
  
            /* mutex to protect the number of available seats.*/
            cout << "Barber: Checking if seat is free..." << endl;
	    sem_wait(&Seats); 
	    cout << "Barber: Its free now." << endl;
  
            /* a chair gets free.*/
	    cout << "Barber: Freeing seat for new customers" << endl;
            FreeSeats++; 
             
            /* bring customer for haircut.*/
	    cout << "Barber: Gotta be busy now." << endl;
            sem_post(&Barber); 
             
            /* release the mutex on the chair.*/
	    cout << "Barber: Prepping the chair." << endl;
            sem_post(&Seats); 
	    cout << "Barber: Cutting hair is sick dude!" << endl;
            /* barber is cutting hair.*/
	    cout << endl;
	    sleep(2);
      } 
} 
  
void* customer(void* arg) { 
      int count = 0;
      while(count < 10) { 
            if (FreeSeats > 0) { 
                  cout << "Customer enters the shop." << endl; 
                  /* sitting sem_wait.*/
                  FreeSeats--; 
                   
                  /* notify the barber. */
                  cout << "Customer: I am here Barber! Wake up!" << endl; 
                  sem_post(&Customers); 
                   
                  /* release the lock */
                  cout << "Customer: I am sitting now." << endl; 
                  sem_post(&Seats); 
                   
                  /* wait in the waiting room if barber is busy. */
                  cout << "Customer: Looks like you are busy. Gotta wait." << endl; 
                  sem_wait(&Barber); 
		  cout << "Customer: Getting my hair done feels cool." << endl;
                  // customer is having hair cut 
            } else { 
                  /* release the lock */
                  sem_post(&Seats); 
		  cout << "Damn! The shop is full. Gotta leave!" << endl;
                  // customer leaves 
            }
      count++;
      } 
}

int main() {
	sem_init(&Customers, 0, 1); 
	sem_init(&Seats, 0, 1); 
	sem_init(&Barber, 0, 1); 

	// creating threads
	pthread_t t1,t2; 
	pthread_create(&t1,NULL,barberF,NULL); 
	sleep(2); 
	pthread_create(&t2,NULL,customer,NULL); 

	pthread_join(t1,NULL); 
	pthread_join(t2,NULL); 

	sem_destroy(&Customers); 
	sem_destroy(&Seats); 
	sem_destroy(&Barber); 

	return 0;
}
