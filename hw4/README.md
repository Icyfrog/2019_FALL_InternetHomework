以c语言编写client和server(虽然跑偏了)

运用socket，数据库采用redis

在aws服务器上选取一个部署redis，再配置了一个双node的集群，针对server和client分别设置节点，尝试实现负载均衡

配置文件见yaml
