#!/bin/bash

RESET="\033[0m"
PINK = "\x1b[35;01m"
BOLDGREEN="\033[1m\033[32m"
BOLDRED="\033[1m\033[31m"
LPURPLE="\033[90m"
LRED="\033[95m"
GREEN="\033[32m"
BLUE="\033[34m"
BOLDCYAN="\033[1m\033[36m"
CYAN="\033[36m"

printf " $BOLDCYAN ___  ___ _____  _   _  _____  _____  _   _  _____  _      _       _____  _____  _____  _____  _____  ______ \n";
printf "  |  \/  ||_   _|| \ | ||_   _|/  ___|| | | ||  ___|| |    | |     |_   _||  ___|/  ___||_   _||  ___|| ___ \\n";
printf "  | .  . |  | |  |  \| |  | |  \ \`--. | |_| || |__  | |    | |       | |  | |__  \ \`--.   | |  | |__  | |_/ /\n";
printf "  | |\/| |  | |  | . \` |  | |   \`--. \|  _  ||  __| | |    | |       | |  |  __|  \`--. \  | |  |  __| |    / \n";
printf "  | |  | | _| |_ | |\  | _| |_ /\__/ /| | | || |___ | |____| |____   | |  | |___ /\__/ /  | |  | |___ | |\ \ \n";
printf "  \_|  |_/ \___/ \_| \_/ \___/ \____/ \_| |_/\____/ \_____/\_____/   \_/  \____/ \____/   \_/  \____/ \_| \_|\n\n\n$RESET";

total_ok=0
total_ko=0
i=1;
compare_shells ()
{
	ok=1
	echo -n "test $i "; let "i=i+1";
	printf "$CYAN \"$@\" $RESET\n"
	MINI=$(echo "$@
	exit" | ./minishell 2>mini_error)
	EXIT_MINI=$?
	BASH=$(echo "$@
	exit" | /bin/bash 2>bash_error)
	EXIT_BASH=$?
if [ "$MINI" == "$BASH" ]; then
    printf "shell: $BOLDGREEN%s$RESET\n" "     ✔ "
else
    printf "shell: $BOLDRED%s$RESET\n" "    ✘ "
	printf " $LRED MINI: %s\n$RESET $LPURPLE BASH: %s\n$RESET" "$MINI" "$BASH"
	ok=0
fi
if [ "$EXIT_MINI" == "$EXIT_BASH" ]; then
    printf "exitstatus: $BOLDGREEN%s$RESET\n" "✔ "
else
    printf "exitstatus: $BOLDRED%s$RESET\n" "✘ "
	printf " $LRED MINI: %s\n$RESET $LPURPLE BASH: %s\n\n$RESET" "$EXIT_MINI" "$EXIT_BASH"
	ok=0
fi
cat bash_error | sed -e "s|/bin/bash: line 1: ||" > bash_error2
if cmp -s "mini_error" "bash_error2"; then
    printf "stderr: $BOLDGREEN%s$RESET\n\n" "    ✔ "
else
    printf "stderr: $BOLDRED%s$RESET\n" "    ✘ "
	printf " $LRED MINI: %s\n$RESET $LPURPLE BASH: %s\n\n$RESET" "$(cat mini_error)" "$(cat bash_error2)"
fi
if [ "$ok" == "1" ]; then
	let "total_ok=total_ok+1"
else
	let "total_ko=total_ko+1"
fi
printf "****************************************************\n"
}

compare_shells 'echo Hello World!'
compare_shells 'echo Hello World! > test'
compare_shells 'echo Hello again! >> test'
compare_shells '< Makefile cat | sort | grep x'
compare_shells 'echo this amazing sentence | cat > outfile
cat outfile'
compare_shells '< Makefile | ls > outfile
cat outfile'
compare_shells "echo "\$USER""Users/\$USER/file""'$USER'"'\$USER'"
compare_shells "echo '\$USER'"\$USER"'\$USER'"
compare_shells 'echo $USER'\$PATH'$USER'
compare_shells echo
compare_shells echo echo
compare_shells eChO
compare_shells ECHO
compare_shells echo teste tester
compare_shells 'echo "testing"'
compare_shells echo testing
compare_shells "echo 'testing'"
compare_shells 'echo -n testing'
compare_shells 'echo -nn testing'
compare_shells echo -n -n -n testing
compare_shells echo -n -n -n testing
compare_shells 'echo "-n" testing'
compare_shells 'echo -n"-n" testing'
compare_shells 'echo "-nnnn" testing'
compare_shells 'echo "-n -n -n"-n testing'
compare_shells 'echo "-n '-n'" testing'
compare_shells echo \$USER
compare_shells 'echo "$USER"'
compare_shells "echo \"'\$USER'\""
compare_shells 'echo " '\$USER' "'
compare_shells 'echo text"$USER"'
compare_shells "echo text\"'\$USER'\" ' \$USER '"
compare_shells "echo \"text\"   \"\$USER\"    \"\$USER\""
compare_shells "echo '              \$USER          '"
compare_shells 'echo               text "$USER"            "$USER"text'
compare_shells "echo ''''''''''\$USER''''''''''"
compare_shells 'echo """"""""$USER""""""""'
compare_shells echo \$USER'$USER'text oui oui     oui  oui \$USER oui      \$USER ''
compare_shells echo \$USER '' \$PATH \$USER '' \$USER '' \$USER -n \$USER
compare_shells echo "\$USER""\$USER""\$USER"
compare_shells echo text"\$USER"test
compare_shells echo '$USER'
compare_shells echo \$USER " "
compare_shells echo "\$USER""Users/\$USER/file""'\$USER'"'$USER'
compare_shells echo "\$USER\$USER\$USER"
compare_shells echo '$USER'"\$USER"'$USER'
compare_shells echo '"$USER"''$PATH'"""\$USER"
compare_shells echo "-n \$USER\$USER2222\$USER333\$USER44\$USER2222\$USER"
compare_shells echo " \$USER  "'$PWD'
compare_shells echo " \$USER  \$ "'$PWD'
compare_shells echo \$USER=4
compare_shells echo \$USER=lwray!
compare_shells echo \$USER
compare_shells echo \$?
compare_shells echo \$PATH213
compare_shells echo "\$USER=12\$USER"
compare_shells echo \$PWD/file
compare_shells echo "\$PWD/file"
compare_shells echo "text" "text\$USER" ... "\$USER"
compare_shells echo \$PWD
compare_shells echo "\$?TEST"
compare_shells 'cd
pwd' 
compare_shells cd .. 
compare_shells cd . 
compare_shells cd /Users 
compare_shells cd // 
compare_shells cd '//' 
compare_shells cd ////// 
compare_shells cd ./././ 
compare_shells cd /
compare_shells cd '/////' 2>/dev/null 
compare_shells cd '/etc' 
compare_shells cd '/var' 
compare_shells cd "\$PWD/file_tests" 
compare_shells 'cd "doesntexist"
pwd'
compare_shells cd ../../..
compare_shells cd "wtf" 2>/dev/null 
compare_shells cd .. 
compare_shells cd ..
compare_shells cd ?
compare_shells cd +
compare_shells cd _
compare_shells cd fake
compare_shells cd more fake
compare_shells cd '/' 
compare_shells 'export | grep " PWD"'
compare_shells 'export $? '
compare_shells 'export TEST
export TEST='
compare_shells 'export TEST=123
export TEST='
compare_shells 'export ___TEST=123'
compare_shells '	'
compare_shells 'export ""=""'
compare_shells "export ''=''"
compare_shells 'export "="="="'
compare_shells "export '='='='"
compare_shells 'export TE-ST=100'
compare_shells 'export TEST-=100'
compare_shells 'export _TEST=100'
compare_shells 'export TEST'
compare_shells 'export =========='
compare_shells 'export 1TEST='
compare_shells 'export TEST'
compare_shells 'export ""=""'
compare_shells 'export TES=T=""'
compare_shells 'export TE+S=T=""'
compare_shells 'export TES.T=123'
compare_shells 'export TES.T=123'
compare_shells 'export TES+T=123'
compare_shells 'export TES=T=123'
compare_shells 'export TES}T=123'
compare_shells 'export TES{T=123'
compare_shells 'export TES-T=123'
compare_shells 'export _TEST=123'
compare_shells 'export TES_T=123'
compare_shells 'export TEST_=123'
compare_shells 'export TE*ST=123'
compare_shells 'export TES#T=123'
compare_shells 'export TES@T=123'
compare_shells 'export TES!T=123'
compare_shells 'export TES$?T=123'
compare_shells 'export =============123'
compare_shells 'export ________=123'
compare_shells 'export export'
compare_shells 'export echo'
compare_shells 'export pwd'
compare_shells 'export cd'
compare_shells 'export export'
compare_shells 'export unset'
compare_shells 'export sudo'
compare_shells 'export TES^T=123'
compare_shells 'export TES!T=123'
compare_shells 'export TEST+=100'
compare_shells 'unset'
compare_shells 'export TEST=100'
compare_shells 'unset doesntexist'
compare_shells 'unset PWD'
compare_shells 'unset PWD '
compare_shells 'unset OLDPWD '
compare_shells 'unset PATH '
compare_shells 'unset PATH '
compare_shells 'unset PATH '
compare_shells 'unset TES.T'
compare_shells 'unset TES+T'
compare_shells 'unset TES=T'
compare_shells 'unset TES}T'
compare_shells 'unset TES{T'
compare_shells 'unset TES-T'
compare_shells 'unset _TEST'
compare_shells 'unset TES_T'
compare_shells 'unset TEST_'
compare_shells 'unset TE*ST'
compare_shells 'unset TES#T'
compare_shells 'unset TES@T'
compare_shells 'unset TES!T'
compare_shells 'unset TES$?T'
compare_shells 'unset ============'
compare_shells 'unset +++++++'
compare_shells 'unset ________'
compare_shells 'unset export'
compare_shells 'unset echo'
compare_shells 'unset pwd'
compare_shells 'unset cd'
compare_shells 'unset unset'
compare_shells 'unset sudo'
compare_shells 'unset TES^T'
compare_shells 'unset TES!T'
compare_shells 'unset TES\~T'
compare_shells 'env | grep "SHLVL"'
compare_shells 'echo oui | cat -e'
compare_shells 'echo oui | echo non | echo something | grep oui'
compare_shells 'echo oui | echo non | echo something | grep non'
compare_shells 'echo oui | echo non | echo something | grep something'
compare_shells 'cd .. | echo "something"'
compare_shells 'cd .. | echo "something"'
compare_shells 'cd / | echo "something"'
compare_shells 'cd .. | pwd'
compare_shells 'ifconfig | grep ":"'
compare_shells 'ifconfig | grep nothing'
compare_shells 'whoami | grep $USER'

mkdir tmp

compare_shells 'whoami | grep $USER > tmp/file'
compare_shells 'whoami | cat -e | cat -e > tmp/file '
compare_shells 'cat Makefile | grep "FLAGS"'
compare_shells 'cat Makefile | cat -e | cat -e'
compare_shells 'cat Makefile | grep "FLAGS" | grep "FLAGS" | cat -e'
compare_shells 'export TEST=123 | cat -e | cat -e'
compare_shells 'unset TEST | cat -e'
compare_shells 'echo test | cat -e | cat -e | cat -e'
compare_shells 'whereis ls | cat -e | cat -e > test'
compare_shells 'echo test | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e'
compare_shells 'ls -la | grep "."'
compare_shells 'whereis grep > tmp/file '
compare_shells 'whereis grep > tmp/file'
compare_shells 'ls -la > tmp/file'
compare_shells 'ls -la > tmp/file '
compare_shells 'test'
compare_shells '| test'
compare_shells 'echo > <'
compare_shells 'echo | |'
compare_shells '<'
compare_shells '|'
compare_shells '| | |'
compare_shells 'hello world'
compare_shells '            '
compare_shells 'cat wouaf wouaf'
compare_shells '>'
compare_shells '<<'
compare_shells '/Users'
compare_shells ' '
compare_shells '..'
compare_shells '/'
compare_shells 'EechoE'
compare_shells '.echo.'
compare_shells 'echo'
compare_shells 'echo something'
compare_shells 'rm -f something'
compare_shells 'cat something'
compare_shells 'echo hhhhhhh > out
echo ii > out
cat out
ls -l out'

compare_shells 'env | grep "SHLVL"'
compare_shells 'echo oui | cat -e'
compare_shells 'echo oui | echo non | echo something | grep oui'
compare_shells 'echo oui | echo non | echo something | grep non'
compare_shells 'echo oui | echo non | echo something | grep something'
compare_shells 'cd .. | echo "something"'
compare_shells 'cd / | echo "something"'
compare_shells 'ifconfig | grep ":"'
compare_shells 'ifconfig | grep nothing'
compare_shells 'whoami | grep $USER'
compare_shells 'whoami | grep $USER > tmp/file' 	 	
compare_shells 'whoami | cat -e | cat -e > tmp/file '
compare_shells 'cat Makefile | grep "FLAGS"'
compare_shells 'cat Makefile | cat -e | cat -e'
compare_shells 'cat Makefile | grep "FLAGS" | grep "FLAGS" | cat -e'
compare_shells 'export TEST=123 | cat -e | cat -e'
compare_shells 'unset TEST | cat -e'
compare_shells 'ls -la | grep "."'
compare_shells 'whereis grep > tmp/file '
compare_shells 'whereis grep > tmp/file'
compare_shells 'ls -la > tmp/file'
compare_shells 'ls -la > tmp/file '
compare_shells 'export TEST="ls -a -l"
$TEST
$TEST -r'
compare_shells 'export TEST2="echo hello world"
$TEST2
$TEST2 and hello universe'

printf "Total OK: $BOLDGREEN%s$RESET\n" "$total_ok"
printf "Total KO: $BOLDRED%s$RESET\n" "$total_ko"


# check if old file content is removed and not overwritten. O_TRUNC flag
# force execve error with fake command (like cat or echo +x)
# check if file permissions are the same as the terminals output files
