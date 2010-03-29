<?php

if(!file_exists($wd . "\\backups")) {
	mkdir($wd . "\\backups");
}

//*** copy file
if(file_exists($wd . "\\backups\\~current.tmp") && is_readable($wd . "\\backups\\~current.tmp")) {
	$last = file_get_contents($wd . "\\backups\\~current.tmp");
} else {
	$last = md5("");
}

$ms = explode(" ", microtime());
$current = md5(serialize(file($ini)));
if($current != $last) {
	copy($ini, $wd . "\\backups\\~aliases.ini___" . date("d.m.Y_H-i-s", time()) . "___" . $ms[1] . ".bck");
	$h = fopen($wd . "\\backups\\~current.tmp", "w");
	fwrite($h, $current);
	@fclose($h);
}

?>