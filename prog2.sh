echo -e "Enter a Number : "
read num
# x=`expr $num % 2`
# if[ $x -eq 0 ]
if (( num % 2 == 0 ))
then 
echo $num is Even
else
echo $num is Odd
fi 
