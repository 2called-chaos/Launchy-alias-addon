<?php

function wait($exit = false, $custom = "") {
	global $wait;
	if($wait === true) {
		echo "\n  DEBUG HALT!\n";
		echo "  Press enter, ctrl+c or click the X in the upper right..." . $custom;
		$x = readcmd();
	}

	if($exit === true) {
		exit;
	}

	return $x;
}

?>