for i in ./$1/*.in;
do
#	echo $i ${i%.in}.out
	./a.out < $i > ${i%.in}.myout 2>/dev/null
	if ! cmp ${i%.in}.myout ${i%.in}.ans >/dev/null 2>&1
	then
		echo "WA"
		exit
	fi
	echo "OK on " $i
done

echo "AC"
