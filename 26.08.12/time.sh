start=$(date +%s%N)
./a.out
end=$(date +%s%N)
cost=$(( (end - start)/1000000 ))
echo "$cost 毫秒"