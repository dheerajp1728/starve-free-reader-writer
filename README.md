# starve-free-reader-writer
The readers-writers problem is a classical one in computer science: we have a resource (e.g., a database) that can be accessed by readers, who do not modify the resource, and writers, who can modify the resource. When a writer is modifying the resource, no-one else (reader or writer) can access it at the same time: another writer could corrupt the resource, and another reader could read a partially modified (thus possibly inconsistent) value.

This problem has been extensively studied since the 60’s, and is often categorized into three variants:

Give readers priority: when there is at least one reader currently accessing the resource, allow new readers to access it as well. This can cause starvation if there are writers waiting to modify the resource and new readers arrive all the time, as the writers will never be granted access as long as there is at least one active reader.
Give writers priority: here, readers may starve.
Give neither priority: all readers and writers will be granted access to the resource in their order of arrival. If a writer arrives while readers are accessing the resource, it will wait until those readers free the resource, and then modify it. New readers arriving in the meantime will have to wait.

#The third readers-writers problem
We will build the solution using C code. We will use semaphores for mutual exclusion (mutex). Those semaphores, being used as locks, are all initialized in the released state (1 available place); those initializations will not appear in code snippets below but will be shown in comments.

First of all, we said earlier that we want fair-queuing between readers and writers in order to prevent starvation. To achieve that, we will use a semaphore named orderMutex that will materialize the order of arrival. This semaphore will be taken by any entity that requests access to the resource, and released as soon as this entity gains access to the resource:

#The third readers-writers problem
We will build the solution using C code. We will use semaphores for mutual exclusion (mutex). Those semaphores, being used as locks, are all initialized in the released state (1 available place); those initializations will not appear in code snippets below but will be shown in comments.

First of all, we said earlier that we want fair-queuing between readers and writers in order to prevent starvation. To achieve that, we will use a semaphore named orderMutex that will materialize the order of arrival. This semaphore will be taken by any entity that requests access to the resource, and released as soon as this entity gains access to the resource:
