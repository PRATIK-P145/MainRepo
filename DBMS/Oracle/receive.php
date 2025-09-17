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

$userid = $_POST['userid'] ?? '';
$username = $_POST['username'] ?? '';
$lastname = $_POST['lastname'] ?? '';
$address = $_POST['address'] ?? '';

$sql= "INSERT INTO employee VALUES (?,?,?,?)
 ";
 
$stmt = $conn->prepare($sql);
$stmt->bind_param("ssss", $userid, $username, $lastname, $address);

if($stmt->execute()===TRUE)
{
 echo " created";
}
else{
  echo "ERROR".$conn->error;
}

$conn->close();


?>
