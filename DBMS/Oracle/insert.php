<?php
$servername="localhost:3307";
$username="root";
$password="";
$dbname="PRAT";

$conn= new mysqli($servername,$username,$password, $dbname);
if($conn->connect_error)
{
die("Connection failure".$conn->connect_error);
}

$sql= "INSERT INTO employee VALUES (101,'PRATIK','PATIL','PUNE')
 ";

if($conn->query($sql)===TRUE)
{
 echo " created";
}
else{
  echo "ERROR".$conn->error;
}

$conn->close();


?>
