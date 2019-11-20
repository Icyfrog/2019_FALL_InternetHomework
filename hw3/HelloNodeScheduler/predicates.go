package main
// 引入必须的包 
import (
	"log"
	"math/rand"
	"strings"

	"k8s.io/api/core/v1"
	schedulerapi "k8s.io/kubernetes/pkg/scheduler/api"
)

// filter筛选现有的pod
func filter(args schedulerapi.ExtenderArgs) *schedulerapi.ExtenderFilterResult {
	var filteredNodes []v1.Node
	failedNodes := make(schedulerapi.FailedNodesMap)
	pod := args.Pod

	for _, node := range args.Nodes.Items {
		fits, failReasons, _ := podFitsOnNode(pod, node)
		if fits {
			filteredNodes = append(filteredNodes, node)
		} else {
			failedNodes[node.Name] = strings.Join(failReasons, ",")
		}
	}

	result := schedulerapi.ExtenderFilterResult{
		Nodes: &v1.NodeList{
			Items: filteredNodes,
		},
		FailedNodes: failedNodes,
		Error:       "",
	}

	return &result
}

func podFitsOnNode(pod *v1.Pod, node v1.Node) (bool, []string, error) {
	fits := true
	failReasons := []string{}
	for _, predicateKey := range predicatesSorted {
		fit, failures, err := testIsHello(pod, node)
		if err != nil {
			return false, nil, err
		}
		fits = fits && fit
		failReasons = append(failReasons, failures...)
	}
	return fits, failReasons, nil
}
// 这个函数专门筛选出执行hello-node任务的pod，那些pod被命名为"hello"
func testIsHello(pod *v1.Pod, node v1.Node) (bool, []string, error) {
	isHello := pod.Name[0:4] == "hello"
	if isHelle {
		log.Printf("hello node!\n")
		return true, nil, nil
	}
	log.Printf("not hello node!\n")
	return false, []string{"not hello node\n"}, nil
}
