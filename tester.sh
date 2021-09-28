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

PROMPT==^..^=;
i=1;
compare_shells ()
{
	echo -n "test $i "; let "i=i+1";
	printf "$CYAN \"$@\" $RESET\n"
	MINI=$(echo "$@
exit" | ./minishell 2>&-| grep -v $PROMPT)
	EXIT_MINI=$?
	BASH=$(echo "$@
	exit" | /bin/bash 2>&-)
	EXIT_BASH=$?
if [ "$MINI" == "$BASH" ]; then
    printf "shell: $BOLDGREEN%s$RESET\n" "     ✔ "
else
    printf "shell: $BOLDRED%s$RESET\n" "    ✘ "
	printf " $LRED MINI: %s\n$RESET $LPURPLE BASH: %s\n$RESET" "$MINI" "$BASH"
fi
if [ "$EXIT_MINI" == "$EXIT_BASH" ]; then
    printf "exitstatus: $BOLDGREEN%s$RESET\n\n" "✔ "
else
    printf "exitstatus: $BOLDRED%s$RESET\n" "✘ "
	printf " $LRED MINI: %s\n$RESET $LPURPLE BASH: %s\n\n$RESET" "$EXIT_MINI" "$EXIT_BASH"
fi
printf "****************************************************\n"
}

compare_shells 'echo Hello World!'
compare_shells 'echo Hello World! > test'
compare_shells 'echo Hello again! >> test'
compare_shells '< Makefile cat | sort | grep a'
compare_shells 'echo this amazing sentence | cat > out
cat out'
compare_shells '< Makefile | ls > out
cat out'
compare_shells 'echo "$USER""Users/$USER/file""'$USER'"'$USER''
compare_shells 'echo '$USER'"$USER"'$USER''
compare_shells 'export 6test=testing'
compare_shells 'echo $USER'$PATH'$USER'
compare_shells echo
compare_shells echo echo
compare_shells eChO
compare_shells ECHO
compare_shells echo stop barking
compare_shells echo "testing"
compare_shells echo testing
compare_shells echo 'testing'
compare_shells 'echo -n testing'
compare_shells 'echo -nn testing'
compare_shells echo -n -n -n testing
compare_shells echo -n -n -n testing
compare_shells echo "-n" testing
compare_shells echo -n"-n" testing
compare_shells echo "-nnnn" testing
compare_shells echo "-n -n -n"-n testing
compare_shells echo "-n '-n'" testing
compare_shells echo ~
compare_shells echo "~"
compare_shells echo '~'
compare_shells echo ~123
compare_shells echo 123~
compare_shells echo ~/123
compare_shells echo ~/123/456
compare_shells echo $USER
compare_shells echo "$USER"
compare_shells echo "'$USER'"
compare_shells echo " '$USER' "
compare_shells echo text"$USER"
compare_shells echo text"'$USER'" ' $USER '
compare_shells echo "text"   "$USER"    "$USER"
compare_shells echo '              $USER          '
compare_shells echo               text "$USER"            "$USER"text
compare_shells echo ''''''''''$USER''''''''''
compare_shells echo """"""""$USER""""""""
compare_shells echo $USER'$USER'text oui oui     oui  oui $USER oui      $USER ''
compare_shells echo $USER '' $USER $USER '' $USER '' $USER -n $USER
compare_shells echo ' \' ' \'
compare_shells echo '\" ' " \"\""
compare_shells echo \\\" \\\" \\\" \\\"\\\"\\\" \\\'\\\'\\\'
compare_shells echo "$USER""$USER""$USER"
compare_shells echo text"$USER"test
compare_shells echo '$USER' "$USER" "text \' text"
compare_shells echo '$USER'
compare_shells echo $USER " "
compare_shells echo "$USER""Users/$USER/file""'$USER'"'$USER'
compare_shells echo "$USER$USER$USER"
compare_shells echo '$USER'"$USER"'$USER'
compare_shells echo '"$USER"''$USER'"""$USER"
compare_shells echo " $USER  "'$PWD'
compare_shells echo " $USER  \$ "'$PWD'
compare_shells echo $USER=4
compare_shells echo $USER=thallard
compare_shells echo $USER
compare_shells echo $?
compare_shells echo $USER213
compare_shells echo $USER $123456789USER $USER123456789
compare_shells echo $USER $9999USER $8888USER $7777USER
compare_shells echo $USER $USER9999 $USER8888 $USER7777
compare_shells echo $USER $USER9999 $USER8888 $USER7777 "$USER"
compare_shells echo "$USER=12$USER"
compare_shells echo "$9USER" "'$USER=12$SOMETHING'"
compare_shells echo $PWD/file
compare_shells echo "$PWD/file"
compare_shells echo "text" "text$USER" ... "$USER"
compare_shells echo $PWD
compare_shells echo "$?TEST"
compare_shells cd 
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
compare_shells cd "$PWD/file_tests" 
compare_shells cd "doesntexist" 
compare_shells cd "doesntexist" 2>/dev/null 
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
compare_shells cd $PWD/file_tests 
compare_shells cd $OLDPWD/something 

# check if old file content is removed and not overwritten. O_TRUNC flag
# force execve error with fake command (like cat or echo +x)
# check if file permissions are the same as the terminals output files
