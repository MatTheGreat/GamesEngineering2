
#include <thread>
#include <string>
#include <iostream>

//signal
void V(int & semaphore)
{
	semaphore = semaphore + 1;
};

//wait
void P(int & semaphore)
{
	while (semaphore <= 0) //same as await(s>0)
	{

	}
	semaphore = semaphore - 1;
};

//buffer size
const int BUFFER_SIZE = 5;

//buffer
std::string buf[BUFFER_SIZE];

//the variable that represents the front and back of the queue of buffered messages
int front = 0, rear = 0;

//Semaphores
int empty = BUFFER_SIZE, full = 0;
int mutexD = 1, mutexF = 1;

void Producer()
{
	while (true)
	{
		//variable to hold data sent by the message
		std::string data = "Pizza";

		//wait until empty > 0
		P(empty);

		//wait until no other producer is in the middle of making changes to buffer
		P(mutexD);

		//assign data to the buffer at the rear of the queue of buffered messages
		buf[rear] = data;

		// Add +1 to rear as rear should hold the position in buffer after the last message
		rear = (rear + 1) % BUFFER_SIZE;// Rear loops back around to the beginning of the buffer if rear is same as buffer size

		// signal that the producer is no longer changing data in buffer
		V(mutexD);

		// signal that data has been added to buffer
		V(full);
	}
}

void Consumer()
{
	while (true)
	{
		// variable to hold data received from the buffer
		std::string result;

		//wait until full > 0
		P(full);

		//wait until no other consumer is in the middle of getting data from the buffer
		P(mutexF);

		//get data from the buffer at the front of the queue of buffered messages
		result = buf[front];

		// Add +1 to front to move the next item to the front of the queue
		front = (front + 1) % BUFFER_SIZE; // Front loops back around to the beginning of the buffer if front is same as buffer size

		// signal that the consumer is no longer getting data from the buffer
		V(mutexF);

		// signal that data has been read from the buffer
		V(empty);
	}
}



int main()
{
	std::thread p1(Producer);
	std::thread c1(Consumer);
	std::thread p2(Producer);
	std::thread c2(Consumer);

	while (true)
	{

	}
}

