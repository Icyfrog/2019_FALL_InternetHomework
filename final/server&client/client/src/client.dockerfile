FROM debian:latest
COPY rr /usr/bin
ENV host port tasks poolsize
CMD ["cd /usr/bin/rr","./surl_client $host $port 0 $tasks $poolsize"]