# Storage
### Vendors
- <b>Dell EMC</b>, products include silon NAS([Network Attached Storage](https://zh.wikipedia.org/zh/%E7%B6%B2%E8%B7%AF%E9%99%84%E5%8A%A0%E5%84%B2%E5%AD%98)) storage, EMC Unity hybrid-flash storage arrays for block and file storage, SC series arrays and the enduring VMAX family of products.
- <b>HPE(Hewlett Packard Enterprise) and its Chinese joint venture, the New H3C Group</b>. Notable product lines include [HPE 3PAR StoreServ midrange arrays](https://www.kelsercorp.com/blog/what-is-hpe-3par-storeserv-storage), entry-level HPE StoreEasy Storage NAS systems and flash-enabled MSA Storage.
- <b>NetApp</b>. They have added latency-busting NVMe-over-Fabrics (FC-NVMe) support to its all-flash arrays and offering hybrid cloud data tiering support in its [ONTAP storage software](https://en.wikipedia.org/wiki/ONTAP).
- <b>IBM</b>. IBM is working on [NVMe](https://www.enterprisestorageforum.com/storage-technology/ibm-storage-banks-on-nvme.html).
- <b>Hitachi VantaraM</b>. HDS(Hitachi Data Systems) storage systems live on in the form of the company's Hitachi NAS Platform and G Series arrays.
- <b>Huawei</b>. Its expanding product portfolio includes [all-flash OceanStor Dorado V3 arrays with NVMe support](https://e.huawei.com/en/products/cloud-computing-dc/storage/unified-storage/dorado-v3) and OceanStor 18000 V5 hybrid-flash storage systems.
- <b>etc.</b>
### Types
When I was introducing the above companies, I have already listed a bunch of storage device types, including local and network. And here is a more detailed list of various decice types.
- <b>Floppy Diskette</b>. The floppy diskette was first created in 1967 by IBM as an alternative to buying hard drives, which were extremely expensive at the time. Capable of storing approximately 1MB.
- <b>Tape Drive</b>. 
- <b>Zip Disk</b>. The Zip drive is a removable floppy disk storage system that was introduced by Iomega in late 1994. Stores like 100 MB.
- <b>CD</b>. 在我小时候我也刻录过...多的能有1个G，小的一般就700MB。
- <b>DVD</b>. Capacity depends on its layers, from 4GB to 17GB.
- <b>Blu-ray disc</b>. 25GB~128GB.
- <b>Flash jump drive</b>. Removable and durable. Small.
- <b>Memory Card</b>. Speed from 2MB/s to 30MB/s.
- <b>Hard Drive</b>. Hard Disk is <b>mainly largest data storage device</b> which is used for External Memory and a permanent Storage,in computer HD need for  operating system, software titles, and most other files are stored in the hard disk drive. Can store up to 10 TB.
- <b>SSD</b>. Faster than normal HDD.
- <b>NAS Storage</b>. NAS is any storage device that is connected to a network and provides a network with additional storage. A key benefit is that data in the cloud can be <b>accessed at any time from any place</b>.
- <b>Cloud Storage</b>. A company’s data is stored in and accessible from multiple distributed and connected resources that comprise a cloud. Cloud storage can provide the benefits of <b>greater accessibility ,reliability, rapid deployment and strong protection for data backup, archival and disaster recovery purposes; and lower overall storage costs as a result of not having to purchase, manage and maintain expensive hardware</b>. However, cloud storage does have the potential for <font color="red">security and compliance concerns that are not associated with traditional storage systems. </font>
- <b>Flash Memory device</b>. Many companies are working on it. It is economical, more functional and dependable.
### Key Indicators (Storage performance matrics)
Disk <b>throughput, latency and seek time</b> are the key indicators of disk. Disk throughput is often expressed as megabytes per second. It is often indicated directly by manufacturers, which you <b>cannot believe 100%</b>, since latency and seek time really matters.
So in order to measure disk performance in a way which adapts to real systems, many storage benchmarks are designed with certain assumptions about these systems. 
> The grandfather of all storage performance metrics is a simple statement of the number of input/output operations per second (IOPS) that a subsystem can sustain.

> Because theoretical performance metrics often don't hold up when it comes to real-world systems, many people rely on application workloads for benchmarking. Since applications and expectations change frequently, and it's useful to compare the performance of systems separated by years or decades. This has led to the creation of synthetic application benchmarks, with the Standard Performance Evaluation Corporation (SPEC) leading the way.

SPEC often contains a mixture of read and write operations, which adapts to real-time systems.
Furthermore, <b>RAID level</b> is also a key indicator.  Each RAID level generally has strengths and weaknesses when it comes to either protecting data or performance. One of the critical aspects of RAID levels when thinking about performance is the write penalty that each RAID level incurs. 
|RAID Level | Write Penalty |
|---        | --------- |
|0|1|
|1|2|
|5|4|
|6|6|
|10|2|
### My own comment
Within the last 50 years, our storage divice has improved a lot. It is now bigger, faster and stronger. Nowadays many manufacturers are working on storage devices that are not like anything we used to think. Some of them are trying to turn flash disk into real disk. Some of them has come up with the idea of binding storage with network. With network and storage bacome stronger and stronger, we may not need a disk of our own anymore in the future. 
When it comes to disk performance, we cannot trust the throughput given by manufactures 100%. If we need to know the real performance of the disk, we nned to consider IOPS, using SPEC.
### Reference
1. [20 Top Enterprise Data Storage Vendors](https://www.enterprisestorageforum.com/products/20-top-enterprise-data-storage-vendors.html)
2. [Different Types of Storage Devices
](https://www.ahirlabs.com/2019/02/01/different-types-of-storage-devices/)
3. [Storage Devices](https://teachcomputerscience.com/storage-devices/)
4. [Understanding storage performance metrics
](https://searchstorage.techtarget.com/tip/Understanding-storage-performance-metrics)
5. [Important storage performance metrics](https://www.vembu.com/blog/important-storage-performance-metrics/)