# Real-Time Operating Systems
Implemented the internals of a real-time operating system. Real time operating systems have a number of subsystems, but their most important functions are task scheduling, resource allocation and memory protection (a form of fault isolation). 

We implemented the basic infrastructure, context switching, task management, concurrency control through mutexes and interface layers with admission control and the priority inheritance locking discipline.


Scheduler:
The scheduler is a part of the kernel that is in charge of deciding the order in which tasks run and the length of each run. The scheduling policy that a scheduler follows is the theoretical frame- work that the scheduler employs in making its allocation decisions. Note that there is no mention of context switching or architecture specific implementation details. In this lab, you will be implement- ing sections of a scheduler, and in particular the predicates needed to implement the rate monotonic scheduling policy.

Dispatcher:
The dispatcher deals with enforcing the scheduler’s policy. The context switch and task switch routines are under the purview of the dispatcher.

Run queue:
The run queue or run list is a list of tasks that are currently runnable that satisfy some criteria. On simple round-robin scheduling systems, there is one system run list where runnable tasks are served in a first come first served (FCFS) manner (hence the name run queue). Systems that have multiple task priorities do not have a universal run queue. Gravelv2 has a ‘run list’ for every priority level on the system, but since there are as many priorities as tasks on Gravelv2, the scheduler enforces that no more than one task can be in a run queue at once. Hence, we end up not using the FCFS nature of the queue, working instead on a purely priority based scheduling policy.

Task state:
During the life-time of a task, it can be in a number of states. All tasks start out as runnable. The scheduler can only schedule runnable tasks to run. When a runnable task is scheduled to run, it is now in the running state. A running task can block on a lock or an event. When it does this, the task moves to the blocked state. A task that is blocked cannot be scheduled to run. It can be made runnable upon the signaling of an appropriate event. In traditional operating systems, a task that is exiting will move from the running state to the undead or zombie state at which point it will be reaped and have its resources returned to the system in an appropriate manner. In Gravelv2, no tasks exit and all tasks are assumed to be periodic forever. Please remember that the scheduler will not (and is not supposed to) schedule any task that is not runnable.
