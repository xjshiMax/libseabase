#!/bin/bash
#filename:multithreading.sh
#多线程压力测试
starttime=$(date +%s)
for ((i=0;i<800;i++));do
        {
                sleep 3;echo result|nc 0.0.0.0 6000;
                echo $i;
        }&
done

echo "waiting"
wait

