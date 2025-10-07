flag=0
echo -e Enter No. of elements :
read n

echo -e Enter $n Values :

for (( i=0 ; i<n ; i++ ))
do 
 read temp
 arr[$i]=$temp
done

echo -e "Array is : ${arr[@]} \n"

for (( j=0; j< n-1; j++ ))
do
for (( i=0; i<n-1; i++ ))
do
 if(( ${arr[$i]}>${arr[$i+1]} ))
 then
  temp=${arr[$i+1]}
  arr[$i+1]=${arr[$i]}
  arr[$i]=$temp
 fi
done
done

echo -e "Sorted Array is : ${arr[@]} \n"
