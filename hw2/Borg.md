## Borg
#### Main idea
Goolgle's Borg system is a cluter manager which runs hunderds of thousands of jobs of Google on many clusters, each consisting of tens of thousands of machines.
> We present a summary of the Borg system architecture and features, important design decisions, a quantitative analysis of some of its policy decisions, and a qualitative examination of lessons learned from a decade of operational experience with it.
#### Some keywords
- <b>prod</b> higher-priority Brod jobs 
- <b>non-prod</b> lower-priority ones
- <b>cell</b> tens of thousands of machines in a datacenter building 
- <b>cluster</b> a cluster is made up of a few cells 
- <b>task</b> a set of Linux processes
- <b>job</b> a set of tasks
- <b>aloc</b> a reserved set of resources on a machine in which one or more tasks can be run
- <b>quota</b> describes the resource a job needs, used to decide which jobs to admit for scheduling
- <b>BNS</b> Borg Name Service, used to find a task
- <b>Chubby</b> used by RPC to find task end point
- <b>Sigma</b> provides a UI to users that help them monitor their tasks
#### Cell-level management: Centralized archietecture
A Borg cell-level management is made up of a centralized controller called Borgmaster and an agent process called Borglet for each machine.
###### Borgmaster
Borgmaster consists of main Borgmaster process and a seperate scheduler. The main Borgmaster process communicates with each Borglet and provides information to users. 
###### Crash consistency for Borgmaster
To achieve crash consistency, the Brogmaster has 5 replicas. Besides, Borgmaster keeps a checkpoint periodically, which helps it to restore states.
###### Debug in Borgmaster
Fauxmaster is a Borgmaster simutalor, which can act exactly like a Borgmaster. It can be used to debug, simulate Borgmater changes.
###### Scheduler
When a job is submitted to pending queue by Borgmaster, scheduler decides if there is sufficient resources to conduct the job.
###### Feasibility checking of scheduler
Scheduler checks if machine has enough resource. It is noticable that jobs of lower priority can be evicted to gain more resrouces.
###### Scoring of scheduler
The current scoring model is a hybrid one that tries to reduce the amount of stranded resources. It provides about 3–5% better packing efficiency than best fit for the workloads. It is noticable that since the installation can cause a great deal of latency, so scheduler prefers to assign jobs to machines that have necessary packages installed.
###### Borglet
A machine-level management process, controlled by Borgmaster. Borgmaster is logically center of all Borglets in a Cell, it keeps states of Borglets. Borgmaster polls Borglets' states periodically. If the poll fails a few times in a row, the master will reorganize jobs.
###### Deal with scalability
To deal with large scale, the paper came up with following ideas:
1. Split the scheduler into a seperate process. Also use a replica on a chached copy of cell state.
2. Add seperate threads to talk to Borglets and respond to read-only RPCs to improve response time.
3. Split Borgmaster functions among its five replcas.
4. Since scoring a machine is expensice, Borg caches scores until properties of the machine or task changes.
5. Since tasks in a Borg job usually have same requirements, Borg only does feasibility and scoring for one task per equivalence class – a group of tasks with identical requirements. 
6. Examine machines in a random order until it has found “enough” feasible machines to score, and then selects the best within that set.
###### Keep availability
To keep availability, already-running jobs will continue to run even if the Borgmaster or Borglet of a machine goes down.
#### Utilization: make efficient use of Google’s fleet of machines
The driver to improve utilization is that increasing utilization by a few percentage points can save millions of dollars for Google.
###### Cell Sharing
They found that segregating prod and non-prod jobs would result in using 20-30% more machines because prod jobs often don't make full use of resources. Packing unrelated jobs (even from unrelated users) help to increace utilization.
###### Large Cells
Google tests to use large cell or multiple small cells for the same workload, and finds that using a large cell consumes far fewer machines.
###### Finer-grained CPU-level request
Experiments have shown that finer level of CPU request can reduce resource cost.
###### Resource Reclaimation
Because an overestimated allocation of resource can be a lot of waste, the Borgmaster conducts a computation of the real needs of jobs every few seconds. 
#### Isolation: keeping security and performance on shared cell/machines
###### Security
A Linux chroot jail is used as primary security isolation between tasks on the same machine. Instead of a ssh key, Borg now provides users with a borgssh command, which provides an ssh connection through Borg. (with access constraints more tightly) VM and security sandboxing techniques are also used.
###### Performance
All Borg tasks run inside a Linux cgroup-based resource container and the Borglet manipulates the container settings. 
To help with overload and overcommitement, Borg also does following adjustments:
1. Make a distinction between latency-sensitive(LS) jobs and the others. LS jobs are granted with higher-priority.
2. Make a distinction between compressible jobs (whose resources can be reduced after resource reclaimation )and non-comprissible jobs. Comprissible jobs can help to increace utilization without killing jobs, which non-compressible jobs can't.
3. To reduce scheduling delays, their version of CFS(their CPU scheduler) uses extended per-cgroup load history, allows preemption of batch tasks by LS tasks, and reduces the scheduling quantum when multiple LS asks are runnable on a CPU.
4. Tasks are allowed to go beyond their resource limit for compressible resources.
#### Their conclusion
> Virtually all of Google’s cluster workloads have switched to use Borg over the past decade. We continue to evolve it, and have applied the lessons we learned from it to Kubernetes.
#### What I think 
Indeed, Google has done a great job in creating a huge computer sets that can work together, with good performance, outstanding fault tolerance and data consistency. Google applied a lot of techniques, among them some are hardly noticable without trying. Some of the ideas can never be drawn without practice and experiments. In system research, it is more important to try than to just think. For example, you would never think of to change the grains of CPU-level request. This does not seem important at all.