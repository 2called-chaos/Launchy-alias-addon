<?php

foreach($pipes as $pipe) {
	$pipe = trim(strtolower($pipe));
	switch($pipe) {
		case "w":
		case "wait":
		case "halt":
				$wait = true;
			break;
		case "v":
		case "ver":
		case "version":
				echo "  =================================\n";
				echo "  === Version: " . VERSION . " (BUILD " . BUILD . ") ===\n";
				echo "  =================================\n\n";
				$wait = true;
			break;
		case "a":
		case "alias":
		case "aliases":
					echo "  Editing " . $ini . "...\n\n";
					echo "  You can close this window, if it does not do this by itself...\n\n";
					`"$ini"`;
					$exit = true;
			break;
		case "h":
		case "help":
		case "?":
					echo file_get_contents("help.inc");
					$wait = true;
					$exit = true;
			break;
		case "i":
		case "info":
					echo '  This tool is programmed by 2called-chaos in the language PHP' . "\n";
					echo '  URL: www.project-production.de/goto/projects/lap' . "\n";
					echo '  ' . "\n";
					echo '  Questions, suggestions, critic? Write it to chaos@project-production.de' . "\n";
					echo '  Supported languages: German, English' . "\n\n";
					$wait = true;
					$exit = true;
			break;
		case "p":
		case "pdir":
		case "pwd":
				echo '  Program directory is "' . $wd . '"' . "\n";
				echo '  Press enter to do nothing, type "o" or "open" '
					.'(and press enter) to open this directory in the explorer...' . "\n  ";
				$input = readcmd();
				if($input == "o" || $input == "open") {
					`explorer.exe $wd`;
				}
				echo "\n";
			break;
		case "":
				
			break;
		default:
				echo "  The pipe command \"" . $pipe . "\" is invalid!\n"
					."  Pipe help (file.exe |help) to get more support\n\n";
					$wait = true;
			break;
	}
}
if($exit === true) {
	wait(true);
}

?>