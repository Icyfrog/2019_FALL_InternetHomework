## Hello Node Scheduler
这是一个专门针对于hello-node应用的schduler，用go语言编写。参考资料为[creating a custom scheduler](https://developer.ibm.com/articles/creating-a-custom-kube-scheduler/)。
#### 集群的搭建
我搭建集群的过程用了kind(Kubernetes IN Docker)，是在本地搭建的一个单node的集群。这个集群里创建3个pod，其中两个跑的是hello-node的镜像：
```cmd
kubectl create deployment hello-node --image=gcr.io/hello-minikube-zero-install/hello-node
``` 
#### Filter
Filter只让名字开头为hello的pod通过检测，其余的全部拦截。
里面用到的逻辑函数主要是这个：
```go
func testIsHello(pod *v1.Pod, node v1.Node) (bool, []string, error) {
	isHello := pod.Name[0:4] == "hello"
	if isHelle {
		log.Printf("hello node!\n")
		return true, nil, nil
	}
	log.Printf("not hello node!\n")
	return false, []string{"not hello node\n"}, nil
}
```
#### Priority
Priority的过程是把名为hello的pod赋予更高的分数。
```go
// 由于我们要找的是叫做hello node的pod 所以给名为hello的pod更高的优先级
func prioritize(args schedulerapi.ExtenderArgs) *schedulerapi.HostPriorityList {
	pod := args.Pod
	nodes := args.Nodes.Items

	hostPriorityList := make(schedulerapi.HostPriorityList, len(nodes))
	for i, node := range nodes {
		score := 0
		if node.Name[0:4] == "hello"
			score := 10
		log.Printf("pod [%v].%v got score %v", pod.Namespace, pod.Name ,score)
		hostPriorityList[i] = schedulerapi.HostPriority{
			Host:  node.Name,
			Score: score,
		}
	}

	return &hostPriorityList
}

```