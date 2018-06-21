<?php
require("phpMQTT.php");
require ("credentials.php");

$credentials = new credentials();
$client_id = "phpMQTT-web-publisher";
$mqtt = new Bluerhinos\phpMQTT($credentials->server, $credentials->port, $credentials->client_id);
if ($mqtt->connect(true, NULL, $credentials->username, $credentials->password)) {
	$mqtt->publish("connectedGarageDoor/$client_id/action", "activate", 0);
	$mqtt->close();
} else {
    echo "Time out!\n";
}
