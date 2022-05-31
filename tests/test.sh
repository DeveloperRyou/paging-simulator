idx=1
while [ $idx -le 1 ]
do
	TEST=test$idx
	echo $TEST
	./project3.exe -page=fifo < "tests/"$TEST > "tests/"$TEST"_fifo"
	./project3.exe -page=stack < "tests/"$TEST > "tests/"$TEST"_stack"
	./project3.exe -page=sample < "tests/"$TEST > "tests/"$TEST"_sample"
	./project3.exe -page=second-chance < "tests/"$TEST > "tests/"$TEST"_second-chance"
	./project3.exe -page=lfu < "tests/"$TEST > "tests/"$TEST"_lfu"
	./project3.exe -page=mfu < "tests/"$TEST > "tests/"$TEST"_mfu"
	./project3.exe -page=optimal < "tests/"$TEST > "tests/"$TEST"_optimal"
	idx=`expr $idx + 1`
done