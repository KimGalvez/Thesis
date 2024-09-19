<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "parol";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// Fetch data from the table
$sql = "SELECT * FROM sample";
$result = $conn->query($sql);

// Convert the result to JSON
$Layer6 = array();
while($row = $result->fetch_assoc()) {
    $Layer6[] = $row['Layer6'];
}
echo json_encode($Layer6);
$conn->close();
?>
