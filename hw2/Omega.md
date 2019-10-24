# Reading Notes "Omega: flexible, scalable schedulers for large compute clusters"

## 简介

**为什么有调度的问题？**

在集群中，让多个工作负载（任务）运行在同一个设备上，可以提高资源利用率和效率。更合适的调度策略和架构可以更好地利用资源，同时保证性能。

**这篇论文主要涉及到三种调度器的架构：**

+ Monolithtic schedulers
+ Two-level schedulers
+ Shared state schedulers
  
**集群的调度器的目标：**

+ 高资源利用率
+ 用户要求的位置约束
+ 快速决策
+ 不同程度的“公平性”
+ 高可用

**工作负载不均匀**

不同的工作负载可以大致分为两类：long-running service jobs, batch jobs

这两种任务运行的时长、task的数量、占用的CPU和内存等资源比例都不太一样。例如，batch job运行时间比较短，而service jobs占用资源比例更大。

下面是论文中给出的batch jobs和service jobs对比的图表
![pic](Files_pic/o_batch_service.jpg)
![pic](Files_pic/o_cdf.jpg)

调度应该考虑不同的工作负载，考虑实际情况下不同负载的比例

对于batch jobs，快速的、轻量级的处理方法更合适，因为执行时间短，花很多时间在调度上面是不划算的。

对于service jobs， 因为会运行很长时间，所以应该比较谨慎的进行调度，来保证可用性和性能。
