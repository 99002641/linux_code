// C program to demonstrate working of Semaphores 
#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
#include <sys/ipc.h> 
#include <sys/msg.h>

sem_t mutex; 

struct mesg_buffer { 
	long mesg_type; 
	char mesg_text[100]; 
    char mesg_text2[100]; 
    char mesg_text3[100];
} message;

void* thread(void* arg) 
{ 
	key_t key; 
	int msgid;
	key = ftok("progfile", 65); 
	msgid = msgget(key, 0666 | IPC_CREAT); 
	message.mesg_type = 1; 

	//wait 
	sem_wait(&mutex); 

	printf("Enter the time: "); 
	fgets(message.mesg_text3,100,stdin);
	printf("How many employees entered office: "); 
	fgets(message.mesg_text,100,stdin); 
    printf("How many employees left: "); 
	fgets(message.mesg_text2,100,stdin);
    


	msgsnd(msgid, &message, sizeof(message), 0); 

	
	
	
	sem_post(&mutex); 
} 


int main() 
{ 
	sem_init(&mutex, 0, 1); 
	pthread_t t1,t2,t3,t4,t5; 
	pthread_create(&t1,NULL,thread,NULL); 
	pthread_create(&t2,NULL,thread,NULL);
	pthread_create(&t3,NULL,thread,NULL);
	pthread_create(&t4,NULL,thread,NULL);
	pthread_create(&t5,NULL,thread,NULL); 
	pthread_join(t1,NULL); 
	pthread_join(t2,NULL);
	pthread_join(t3,NULL);
	pthread_join(t4,NULL);
	pthread_join(t5,NULL);
	sem_destroy(&mutex); 
	return 0; 
} 
