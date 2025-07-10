f0=0
f1=1
echo $f0 $f1 

for(( i=3 ; i<=10 ; i++ ))
do 
 f2=`expr $f0 + $f1`
 echo $f2   
 f0=$f1
 f1=$f2
done















