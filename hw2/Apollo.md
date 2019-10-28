# Apollo: Scalable and Coordinated Scheduling for Cloud-Scale Computing - 2014

## PART 1:  Reading Paper

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

##### 3.3 Estimation-Based Scheduling

JM decides which server to schedulea task by tht aggregated view by RM and the individual characteristice of the task. There may be some conflicting factors factors and Apollo uses task priorities to decisied how to scehdule efficiently, uses stable matching, put maching tasks and servers in pairs, dispatches in order. If some task is not picked, they will enter the next iteration until all tasks have been assigned or it reaches the maximum number of iterations. And for some situations it introduces in 3.4 and 3.5 sections.

##### 3.4 Correction Mechanisms

Sometimes several JMs mightmake competing decisions at the same time. Or some information can't be updated in time. So this section talks about mechanisms to dynamically adjust scheduling decisions and handling competions.

Apollo dosen't handle the conflicts until after tasks ate dispatched to PN queues. Mostly they are not harmful to the system. Apollo will check the information to keep it right in scheduling.  In some condition, the scheduler will re-evaluate the desion about shceduling. Apollo adds a small random number to each completion time estimation, whichj helps reduce the chances of conflicts. And the aggregated cluster information obtained form the RM has different confidience. When the confidence is too low, the scheduler will try to get new. Apollo compares time tasts use to run to figure out where the straggler is.

##### 3.5 Opportunistic Scheduling

This section explain how Apollo operates efficiently and drives high cluster utilization with fairness. It's hard to guarantee absolute instantaneous fainess. We focus on how to avoiding the worst case, a few jobs consuming all available resource. Apollo uses random allocation and upgraded task.

### 4 Engineer Experiences

This section is about how Apollo develop step by step and some tries to implement and evaluating Apollo.

### 5 Evaluation

This section is mostly about performance comparison between Apollo and some others. I just introduce some test outcomes about Apollo here.

##### 5.1 Apollp at Scale

Highly scalable.

##### 5.2 Scheduling Quality

Excellent job performance.

##### 5.3 Evaluating Estimates

Apollo provides good estimates on task wait time and CPU time.

##### 5.4 Correction Effectiveness

Apollo's correction mechanisms are shown effecitve withsmall overhead.

##### 5.5 Stable Matching Efficiency

Comparing with greedy algorithm with negiligle overhead, Apollo performs much better.

### 6 Related Work

Monolithic schedulers such as Hadoop Fair Scheduler and Quincy.Mesos and YARN, Omega and Sparrow and othes work about scheduling.

### 7 Conclusion

Apollo, a scalable and coordinated scheduling framework for cloud-scale computing, which really works well in scheduling architecture and resources utilizaion. Apollo has been deployed on production clusters at Microsoft showing to achieve high utilization and low latency in many situations.

### Acknowledgements
Be grateful tothe  people who helped you.

## PART 2: After Reading The Paper

### What is Apollo?

Apollo, a scalable and coordinated scheduling framework for cloud-scale computing.

### How does it work?

Apollo forcus on scheduling and resource utilization. In scheduling, Apollo departs jobs into small tasks, and JM sends tasks to server, PN will put tasks in a queue(but can be reordered to fill gap between task with a smaller task). RM aggregates load information (**wait-time matrices**) from PN, and send to JM. RM can do its own job and is not the critical factor of performance for estimation of new tasks before sending them to servers. In resource utilization, Apollo tries to assign a task to the server which is free and fits the task best in a single batch. Althought there are some questions such as scheduling conflicts, straggler and stale information, Apollo has mechanisms to handle these. For example randomization and confidence of matrix.

The achievement is significant, Apollo has been deployed on production clusters at Microsoft showing to achieve high utilization and low latency in many situations. It shows great performence and robustness in gorwing cluster sizes and more complex workloads.

### My Thinking

Inventing a new useful and high-quality framework is nerver a easy work. We need solve many questions from theory to practice to meet the needs of jobs with diverse characterstics and dynamics in diverse workloads and large clusters. Don't forget the efficiency and cost. So we also need a series of kinds to assess the performence of the production, compairing with other competitors.