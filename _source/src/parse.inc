<?php

$def_raw = file($ini);
$def = array();
$errors = array();

for($x = 0; $x < count($def_raw); $x++) {
	$l = trim($def_raw[$x]);
	$row = $x+1;

	// is it a empty line or a comment?
	if(!empty($l) && substr($l, 0, 2) != "//" && substr($l, 0, 1) != "#") {
		// check data integrity
		$split = explode("|~|", $l);
		if(!is_array($split) || count($split) !== 3) {
			$errors[] = "Syntax Error on Line " . $row . ": 3 parts seperated by 2 delimiters expected ///###\\\\\\ in (" . $ini . ")";
		}

		//*** validate flag
		if(!in_array(trim($split[1]), $valid_flags)) {
			$errors[] = "Syntax Error on Line " . $row . ": " . trim($split[1]) . " is not a valid flag (valid flags are listed in the ini file)! ///###\\\\\\ in (" . $ini . ")";
		}

		//*** split aliases
		$aliases_split = explode(",", $split[0]);
		foreach ($aliases_split as $a) {
			//*** validate alias
			if(trim($a) == "") {
				$errors[] = "Syntax Error on Line " . $row . ": aliases cannot be empty! ///###\\\\\\ in (" . $ini . ")";
			} else if(preg_match('/[^a-zA-Z0-9_\.+\-]/', trim($a)) > 0) {
				$errors[] = "Syntax Error on Line " . $row . ": aliases can only consist of the character-set a-zA-Z0-9_.+- and be seperated by commas ///###\\\\\\ in (" . $ini . ")";
			} else {
				//*** add row
				$def[trim($a)] = array("flag" => trim($split[1]), "do" => trim($split[2]));
			}
		}
	}
}

//*** parsing errors
if(count($errors) > 0) {
	echo "  ===  ERRORS  ===\n";
	foreach($errors as $error) {
		echo "  " . $error . "\n";
	}
	echo "  === // ERRORS  ===\n\n";
	$wait = true;
	wait(true);
}

?>