<?php

function OpenConn(){
$conn = mysqli_connect("localhost","root","","parol") or die("Unable to connect");

return $conn;
}

function CloseConn(){
$conn = mysqli_connect("localhost","root","","parol") or die("Unable to connect");

$conn -> close();

}

?>