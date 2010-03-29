<?php

if(isset($def[$request])) {
	echo "  Alias \"" . $request . "\" found...\n";
	echo "  Executing... ";
	$run = $def[$request]["do"];
	$command = "";
	switch($def[$request]["flag"]) {
		case "dir":
		case "d":
				$command = 'explorer.exe "' . $run . '"';
			break;
		case "dirtree":
		case "dt":
				$command = 'explorer.exe /e, "' . $run . '"';
			break;
		case "dirnewwin":
		case "dn":
				$command = 'explorer.exe /n, "' . $run . '"';
			break;
		case "dirtreenewwin":
		case "dtn":
				$command = 'explorer.exe /n, /e, "' . $run . '"';
			break;
		case "c":
		case "cmd":
				$command = $run;
			break;
		case "url":
		case "link":
				$tmpfile = $request;
				$handle = fopen($wd . "\\" . $tmpfile . ".tmp.url", "w");
$tpl = <<<EOT
[InternetShortcut]
URL=$run
IDList=
[{000214A0-0000-0000-C000-000000000046}]
Prop3=19,2
EOT;
				fwrite($handle, $tpl);
				@fclose($handle);
				$command = '"' . $wd . "\\" . $tmpfile . ".tmp.url" . '"';
				$destruct = 'unlink("' . $wd . '\\' . $tmpfile . '.tmp.url");';
			break;
	}
	if(empty($command)) {
		`explorer.exe "$run"`;
	} else {
		`$command`;
		if(isset($destruct)) {
			eval($destruct);
		}
	}
	echo "DONE!\n";
}

?>