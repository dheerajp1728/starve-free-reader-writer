# starve-free-reader-writer
**by dheeraj p**

**19114028**


**Introduction**

Reader-Writer problem is one of the classical problems of concurrency. It relates to a situation,
when a file system or any data is being read and written to by multiple concurrent threads. It is
necessary for the program to be able to prevent the reading of the data when there is an overwrite
going and to prevent the reading from interrupting the invalid data under modification. As such, it is
also important that 2 writers don’t enter the data structure or database to start rewriting it. We need
to make sure that readers and writers execute different code before and after critical section to be
able to satisfy the following constraints:
1. Any number of readers can be in the critical section simultaneously.
2. Writers must have exclusive access to the critical section: no writer can enter when there is
another thread in CS, and while writer is there, no other thread can enter critical section.

**Solution Description**

At the very beginning, it is important to initialize the variables that will be responsible for
implementation. I set up a semaphore with the counter variable being initialized to the current
number of Readers in the critical section. That semaphore sem_t mutex is there to prevent other
threads from modifying the counter variable. The second semaphore sem_t wrt will prevent the
other writers from entering the execution while anybody is in there. The third semaphore sem_t wIn
is used as a turnslite. Once writer thread enter, it calls sem_wait on the wIn, so when the reader
arrives after, it puts itself to sleep, which allows the writer to not get overcome by readers and
prevents starvation.

When the writer exits it knows that there is no thread entering the execution as it was the only one in
it to begin with. The code for readers involves keeping reader count, incrementing and decrementing
it, as the readers enter and leave the room. The first one to enter and the first to exit have to call
sem_wait and sem_post for wrt so that the writer knows when to enter the room. When the reader
proceeds to enter the execution, it prevents the writer from entering the execution. If the reader
arrives when the room is busy with writer, it will wait, just as the 2nd writer would and there is a
queue formed.

The third semaphore is there to serve as a turnslite. It is added for the readers and allows writers to
lock it and unlock it once they are done, so that the queued readers can then proceed to execute. If a
writer arrives with readers in execution, it will first lock the turnslite, then will put itself to sleep
since the room is not empty. Next reader that arrives will be put to sleep immediately purely because
that turnslite is already locked, giving the priority for the writer to enter the room first. Once all
readers leave the execution, the writer will immediately enter, since turnslite was closed after the
writer and no readers can now enter it. Upon execution, the writer does sem_post on wIn and
unblocks the next thread which is either a reader or a writer. Now, however, it presents a possibility
for any thread (writer or reader) to enter the execution.

**Semaphore**
Designing a Semaphore with FIRST-IN-FIRST-OUT(FIFO) queue to maintain the list of blocked processes

// The code for a FIFO semaphore.
struct Semaphore{
  int value = 1;
  FIFO_Queue* Q = new FIFO_Queue();
}
    
void wait(Semaphore *S,int* process_id){
  S->value--;
  if(S->value < 0){
  S->Q->push(process_id);
  block(); //this function will block the process by using system call and will transfer it to the waiting queue
           //the process will remain in the waiting queue till it is waken up by the wakeup() system calls
           //this is a type of non busy waiting
  }
}
    
void signal(Semaphore *S){
  S->value++;
  if(S->value <= 0){
  int* PID = S->Q->pop();
  wakeup(PID); //this function will wakeup the process with the given pid using system calls
  }
}


//The code for the queue which will allow us to make a FIFO semaphore.
struct FIFO_Queue{
    ProcessBlock* front, rear;
    int* pop(){
        if(front == NULL){
            return -1;            // Error : underflow.
        }
        else{
            int* val = front->value;
            front = front->next;
            if(front == NULL)
            {
                rear = NULL;
            }
            return val;
        }
    }
    void* push(int* val){
        ProcessBlock* blk = new ProcessBlock();
        blk->value = val;
        if(rear == NULL){
            front = rear = n;
            
        }
        else{
            rear->next = blk;
            rear = blk;
        }
    }
    
}

// A Process Block.
struct ProcessBlock{
    ProcessBlock* next;
    int* process_block;
}

**Pseudocode**

The pseudocode for the problem can be defined by the following.

reader {

acquire_read();

//execute the code in Critical Section (in our case it is the reading_writing() function)

release_read();

} 

writer {

acquire_write();

//execute the code in Critical Section (in our case it is the reading_writing() function)

release_write();

}

Detailed pseudocode for the reader and writer helper functions.

RW Semaphore Initialization:

Wrt = Semaphore(1);

Mutex = Semaphore(1);

wIn = Semaphore(1);

int counter = 0;

Acquire_read():

Wait(wIn);

Wait(mutex);

counter++;

if counter == 1

Wait(wrt)

Post(mutex)

Post(wIn)


Release_read():

Wait(mutex)

Counter--

if counter == 0

Post(wrt)

Post(mutex)

 The requirements of the lock are the following:

Any number of readers can be in the critical section simultaneously.
Writers must have exclusive access to critical section: no 2 writers at the same time, no writers and readers together.
To Run the Program: Compile with:

make rwmain
or alternatively:

gcc -pthread main.c
Execute with:

./rwmain 
or if compiled using alternative way:

./a.out
Clean up by invoking:

make clean
If you are adding your own scenario, make sure to hit enter when you are finished typing. E.G. for 6 scenarios, there should be 7 lines. Otherwise, the last scenario will get ignored as there is no '\n' character.

Scenario 1: Shows that no more than one writer can be in the execution at the same time.

Scenario 2: Shows that writers cannot enter the execution when readers are present.

Scenario 3: Trying to starve the writer, by having many readers scheduled right after the first writer.

Scenario 4, 5, 6: Testing starvation and the presence of only 1 writer in the room.

Scenario 7: No writer to enter while readers are in execution.

Scenario 8, 9: Testing starvation.
Acquire_write():

Wait(wIn)

Wait(wrt)

Release_write():

Post(wrt);

Post(wIn);
