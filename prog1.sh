echo -n 'Enter pattern :'
read pattern
echo -n 'Enter FileName :'
read fName
if grep $pattern $fName
then
echo -n 'Pattern Found'
else
echo -n 'Pattern not Found'
fi
