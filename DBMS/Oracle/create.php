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

$sql= "CREATE TABLE employee(id INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
firstname VARCHAR(30) NOT NULL,
lastname VARCHAR(30) NOT NULL,  
adress VARCHAR(30)
 )";

if($conn->query($sql)===TRUE)
{
 echo " created";
}
else{
  echo "ERROR".$conn->error;
}

$conn->close();


?>
