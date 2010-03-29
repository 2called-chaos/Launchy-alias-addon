<?php

//*** constants
define("VERSION", "1.0");
define("BUILD", "5168");
ini_set("auto_detect_line_endings", true);

//*** init variables
$cmd_delimiter = "%";											// char(s) to call commands
$wait = false;													// wait at the end
$execute = false;												// execute request
$wd = dirname($argv[0]);										// working directory
$request = (!empty($argv[1])) ? trim($argv[1]) : null;			// request
$windir = trim(`ECHO %windir%`);								// windows directory
$ini = $wd . '\\aliases.ini';									// ini file
$valid_flags = array(
						"d", "dir",
						"dt", "dirtree",
						"dn", "dirnewwin",
						"dtn", "dirtreenewwin",
						"c", "cmd",
						"url", "link",
					);
echo "\n";

//*** load functions
/**
  * loads a function to read runtime inputs from console
  * string readcmd()
  */
require_once("readcmd.inc");

/**
  * loads a function to handle the debug halt
  * string wait(bool $exit, string $custom)
  */
require_once("wait.inc");


//*** create ini file if it not exists
if(!file_exists($ini) || strlen(file_get_contents($ini)) == 0) {
	echo "  aliases.ini was not found and was created in \"" . $wd . "\"\n\n";
	$wait = true;
	$h = fopen($ini, "w");
	fwrite($h, file_get_contents("aliases.ini"));
	@fclose($h);
}

//*** load & parse ini file
require_once("parse.inc");

//*** parse request
if(substr(0, strlen($cmd_delimiter), $request) == $cmd_delimiter) {
	$request = substr(0, strlen($cmd_delimiter), $request);
	$execute = true;
} else {
	$pipes = array();
	$pipe_split = explode("|", $request);
	if(is_array($pipe_split) && count($pipe_split) != 1) {
		$request = $pipe_split[0];
		$pipes = array_slice($pipe_split, 1);
	}
}

//*** command handling
if($execute === true){
	echo "  Executing \"" . $request . "\"...\n";
	`$request`;
	echo "  DONE! ";
}

//*** pipe handling
require("pipe_handling.inc");

//*** backup ini file
require("backup.inc");


//*** checking request
if(empty($request)) {
	echo "\n  No parameter given, doing nothing...\n";
	$wait = true;
	wait(true);
}

if(!isset($def[$request])) {
	//*** try to complete the alias automatically
	$reg_keys = array_keys($def);
	$results = array();
	foreach($reg_keys as $key) {
		if(substr($key, 0, strlen($request)) == $request) {
			$results[] = $key;
		}
	}
	switch(count($results)) {
		case 0:
				//*** we failed or the alias doesn't exists
				echo "  Alias \"" . $request . "\" was NOT found and could not be autocompleted...\n";
				$wait = true;
				wait(true);
			break;
		case 1:
				//*** we're successful :)
				echo "  Your request \"" . $request . "\" was autocompleted to \"" . $results[0] . "\"...\n\n";
				sleep(2);
				$request = $results[0];
			break;
		default:
				//*** we're found to much
				echo "  Alias \"" . $request . "\" was exactly not found but matches several other aliases:\n";
				foreach($results as $key => $result) {
					$cmd_o = (strlen($def[$result]['do']) > 50) ? substr(0, 47, $def[$result]['do']) . "..." : $def[$result]['do'];
					echo "     $key) [" . $def[$result]['flag'] . "] " . $result . " => " . $cmd_o . " \n";
				}
				echo "\n  Enter the number to choose the alias or press enter to quit: ";

				$choice = readcmd();
				if(is_numeric($choice)) {
					if(isset($results[$choice])) {
						$request = $results[$choice];
						echo "\n";
					} else {
						echo "  Invalid input!\n";
						$wait = true;
						wait(true);
					}
				} else {
					echo "  Invalid input!\n";
					sleep(2);
					exit();
				}
			break;
	}
}


//*** handle request
require("handle_request.inc");

wait();

?>