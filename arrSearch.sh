#arr=(2 3 14 54 82 23)
#n=6 
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

echo -e  Enter VAlue to be searched : 
read num

for (( i=0 ; i<n ; i++ ))
do

 if(( $num==${arr[$i]} ))
 then
  #echo -e Number Found at index $i
  flag=1
  break
 fi
 
done



if (( $flag==1 ))
then
echo -e Number Found at index $i
else
echo -e Number Not Found !

fi

