This tool is easy to use (if you have Launchy (www.launchy.net) installed)
Simply make a link to the executable in a directory which is monitored by Launchy ("do" in this example).

Then you can type the name of the link in the Launchy box, press tab and than type your alias.
e.g. (typed in Launchy window): do [tab] foobar
You can use several pipe commands. You don't have to pass an alias if you pass a pipe command.
Possible commands (you can combine them but don't use whitespaces):
  |h, |?, |help           --- Show this help
  |w, |wait, |halt        --- Prevent that the window closes after excecution to detect bugs or errors
  |p, |pwd, |pdir         --- Shows you the programs path and let you open it
  |a, |alias, |aliases    --- Opens the aliases.ini in you standard editor
  |v, |ver, |version      --- Shows the program version and build number
  |i, |info               --- Shows some informations about the author, etc.
e.g. (typed in Launchy window): do [tab] |help|ver

The aliases.ini is well documentated so you shouldn't encounter problems.

Questions, suggestions, critic? Write it to chaos@project-production.de
Supported languages: German, English