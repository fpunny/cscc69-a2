make
> result.txt

ALGOS="rand fifo clock lru opt"
TRACES="simpleloop matmul blocked fib"
SIZES="50 100 150 200"

for t in $TRACES
do
    echo $t >> result.txt
    for a in $ALGOS
    do
        echo $a >> result.txt
        for s in $SIZES
        do
            eval ./sim -f "traceprogs/tr-${t}.ref" -m $s -s 4096 -a $a | tail -n8 >> result.txt
        done
        echo "----" >> result.txt
    done
done
