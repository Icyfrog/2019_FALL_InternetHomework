## Apollo: Scalable and Coordinated Scheduling for Cloud-Scale Computing - 2014

### Abstract
Scheduling jobs is important to many things. It is critical for job perfoemance, sysem throughoyr, and resource utilization. Apollo is a scalable and coordinated scheduling framework, which is used to shcedule computations with millions of tasks efficiently. And it works really well. Apollo is robust, can handle many unexpected **system dynamics** (*maybe it means can deal with many situlation?*)  and use other idle syste resources **gracefully** (*an interesting word*) while supplying guaranteed resources when needed.



### 1 Introduction

The paper introduces some useful mechanisms and methods to solve diverse problem and improve performence. Such as advertising cluster information to individual schedulers, *opportunistic scheduling* for driveing high cluster utilization, and so on. Introduction also introduce the other section birefly.



### 2 Scheduling at Production Scale

Introduce tokens to present jobs. A job many have many tasks to complete, one task need a toekn just like a coin. There are many tasks that perform the same computation even on different partitions of the same input. We put them in a stage. The number of tasks in a stage id DOP. And scheduling will face jobs vary much. So it is hard and important.



### 3 The Apollo Framework

##### 3.1 Architectural Overview

In Apollo, we have Job Manager(JM),  Process Node(PN), Resource Monitor(RM). PN manages the local resources on servers and performs local scheduling, RM aggregates load information from PN, and send to JM. RM can do its own job and is not the critical factor of performance.

##### 3.2 PN Queue and Wait-Time Matrix

JM schedules tasks with some informaton to PN, PNs use queue to execute tasks. And PN also provides feedback to the JM to help improve accuracy of runtime and resource usage estimation. Apollo uses a *wait-time matrix* to record the expected wait time for a task that requires a certain amount of CPU and memory. 