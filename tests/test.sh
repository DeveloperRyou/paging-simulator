idx=1
while [ $idx -le 1 ]
do
	TEST=test$idx
	echo $TEST
	./project3 -page=fifo < "tests/"$TEST > "tests/"$TEST"_fifo"
	./project3 -page=stack < "tests/"$TEST > "tests/"$TEST"_stack"
	./project3 -page=sampled < "tests/"$TEST > "tests/"$TEST"_sampled"
	./project3 -page=second-chance < "tests/"$TEST > "tests/"$TEST"_second-chance"
	./project3 -page=lfu < "tests/"$TEST > "tests/"$TEST"_lfu"
	./project3 -page=mfu < "tests/"$TEST > "tests/"$TEST"_mfu"
	./project3 -page=optimal < "tests/"$TEST > "tests/"$TEST"_optimal"
	idx=`expr $idx + 1`
done