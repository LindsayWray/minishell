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

printf " $BOLDCYAN ___  ___ _____  _   _  _____  _____  _   _  _____  _      _       _____  _____  _____  _____  _____  ______ \n";
printf "  |  \/  ||_   _|| \ | ||_   _|/  ___|| | | ||  ___|| |    | |     |_   _||  ___|/  ___||_   _||  ___|| ___ \\n";
printf "  | .  . |  | |  |  \| |  | |  \ \`--. | |_| || |__  | |    | |       | |  | |__  \ \`--.   | |  | |__  | |_/ /\n";
printf "  | |\/| |  | |  | . \` |  | |   \`--. \|  _  ||  __| | |    | |       | |  |  __|  \`--. \  | |  |  __| |    / \n";
printf "  | |  | | _| |_ | |\  | _| |_ /\__/ /| | | || |___ | |____| |____   | |  | |___ /\__/ /  | |  | |___ | |\ \ \n";
printf "  \_|  |_/ \___/ \_| \_/ \___/ \____/ \_| |_/\____/ \_____/\_____/   \_/  \____/ \____/   \_/  \____/ \_| \_|\n\n\n$RESET";


i=1;
compare_shells ()
{
	echo -n "test $i "; let "i=i+1";
	MINI=$(echo "$@
exit" | ./minishell)
	BASH=$(echo "$@
	exit" | /bin/bash)
if [ "$MINI" == "$BASH" ]; then
    printf " $BOLDGREEN%s$RESET\n" "✔ "
else
    printf " $BOLDRED%s$RESET\n" "✘ "
	printf " $LRED MINI: %s\n$RESET $LPURPLE BASH: %s\n$RESET" "$MINI" "$BASH"
# 
fi
}

compare_shells 'echo Hello World!'
compare_shells 'echo Hello World! > test'
compare_shells 'echo Hello again! >> test'
compare_shells '< Makefile cat | sort | grep a'
compare_shells 'echo this amazing sentence | cat > out
cat out'
# compare_shells '< Makefile | ls > out
#                 cat out'

compare_shells 'export 6test=testing'
compare_shells echo $USER'$PATH'$USER

# check if old file content is removed and not overwritten. O_TRUNC flag
# force execve error with fake command (like cat or echo +x)
# check if file permissions are the same as the terminals output files

#echo "$USER""Users/$USER/file""'$USER'"'$USER'
#echo '$USER'"$USER"'$USER'

