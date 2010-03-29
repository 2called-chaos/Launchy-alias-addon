<?php

function readcmd() {
	if(!defined('STDIN')) {
		define("STDIN", fopen('php://stdin','r'));
	}
	return trim(fread(STDIN, 1024));
}

?>