<?php
require("phpMQTT.php");
require 'credentials.php';

$credentials = new credentials();
$client_id = "phpMQTT-web-subscriber";
$mqtt = new Bluerhinos\phpMQTT($credentials->server, $credentials->port, $credentials->client_id);
if(!$mqtt->connect(true, NULL, $credentials->username, $credentials->password)) {
	exit(1);
}
$topics['connectedGarageDoor'] = array("qos" => 0, "function" => "procmsg");
$mqtt->subscribe($topics, 0);
while($mqtt->proc()){

}
$mqtt->close();
function procmsg($topic, $msg){
		echo "Msg Recieved: " . date("r") . "\n";
		echo "Topic: {$topic}\n\n";
		echo "\t$msg\n\n";
}
