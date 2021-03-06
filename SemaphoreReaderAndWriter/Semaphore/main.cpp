
#include <thread>
#include <string>
#include <chrono>
#include <iostream>
#include <mutex>

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

//number of readers
int nr = 0;

//lock for access to the database
int rw = 1;

//lock for reader access to nr
std::mutex mutexR;

void Writer()
{
	while (true)
	{
		//variable to hold data sent by the message
		std::string data = "Pizza";

		//wait until empty > 0
		P(empty);

		P(rw);

		//assign data to the buffer at the rear of the queue of buffered messages
		buf[rear] = data;

		// Add +1 to rear as rear should hold the position in buffer after the last message
		rear = (rear + 1) % BUFFER_SIZE;// Rear loops back around to the beginning of the buffer if rear is same as buffer size

		V(rw);

		// signal that data has been added to buffer
		V(full);

	}
}

void Reader()
{
	while (true)
	{
		// variable to hold data received from the buffer
		std::string result;

		//wait until full > 0
		P(full);

		mutexR.lock();
		//increase number of readers
		nr = nr + 1;
		if (nr == 1)
		{
			P(rw);
		}
		mutexR.unlock();


		//get data from the buffer at the front of the queue of buffered messages
		result = buf[front];

		// Add +1 to front to move the next item to the front of the queue
		front = (front + 1) % BUFFER_SIZE; // Front loops back around to the beginning of the buffer if front is same as buffer size


		mutexR.lock();
		//decrease number of readers
		nr = nr - 1;
		if (nr == 0)
		{
			V(rw);
		}
		mutexR.unlock();


		// signal that data has been read from the buffer
		V(empty);
	}
}



int main()
{
	std::thread w1(Writer);
	std::thread r1(Reader);

	while (true)
	{

	}
}

