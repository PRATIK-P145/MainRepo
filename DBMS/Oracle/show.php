

<?php
$servername = "localhost:3307";
$username = "root";
$password = "";
$dbname = "PRAT";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$sql = "SELECT id,firstname,lastname,adress FROM employee where adress='PUNE'";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
    // output data of each row
    while($row = $result->fetch_assoc()) {
        echo "<br>| id: ". $row["id"]. " | Name: ". $row["firstname"]." | Last-Name: ". $row["lastname"]." | Address: ". $row["adress"] . "<br>";
    }
} else {
    echo "0 results";
}

$conn->close();
?>
