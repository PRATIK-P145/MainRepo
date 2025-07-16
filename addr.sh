echo -e "\nEnter name of File : "
read file

while true; do

echo -e "\n1.Create File\n2.Insert Data\n3.Display data\n4.Search\n5.Delete\n6.Modify\n0.Exit"

echo -e "\nEnter your choice : "
read ch


case $ch in
	
	1) touch $file.txt
	   echo -e "File Created successfully"
	   
	   ;;
	
	2) echo -e "Enter data to Insert :"
	   read id name branch
	    
	   echo -e "$id\t$name\t$branch" >> $file.txt
	   ;;
	   
	3)echo -e "id\tname\tbranch" 
	  cat $file.txt
	   ;;
	  
	4) echo -e "Enter data to Search :"
	   read pattern
	   if grep $pattern $file.txt
	   then
	   echo -e "Record Found"
	   else
	   echo -e "Record Not found"
	   fi
	   ;;
	   
	 5)echo -e "Enter index to Delete :"
	   read id
	   if sed -i "/$id/d" $file.txt
	   then
	   echo -e "Record Deleted"
	   else
	   echo -e "Record Not found"
	   fi
	   ;;
	   
	  6)echo -e "Enter Old Data :"
	   read old
	   echo -e "Enter new data to replace:"
	   read new
	   
	   sed -i "s/$old/$new/" $file.txt
	   ;;


esac
done
