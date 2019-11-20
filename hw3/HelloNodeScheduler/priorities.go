package main

import (
	"log"
	"math/rand"

	schedulerapi "k8s.io/kubernetes/pkg/scheduler/api"
)

// 由于我们要找的是叫做hello的pod 所以给名为hello的pod更高的优先级
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
