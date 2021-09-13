#!/bin/bash

RESET="\033[0m"
BOLDGREEN="\033[1m\033[32m"
BOLDRED="\033[1m\033[31m"
RED="\033[31m"
GREEN="\033[32m"
BLUE="\033[34m"
BOLDYELLOW="\033[1m\033[33m"
BOLDCYAN="\033[1m\033[36m"

printf " $BOLDCYAN ___  ___ _____  _   _  _____  _____  _   _  _____  _      _       _____  _____  _____  _____  _____  ______ \n";
printf "  |  \/  ||_   _|| \ | ||_   _|/  ___|| | | ||  ___|| |    | |     |_   _||  ___|/  ___||_   _||  ___|| ___ \\n";
printf "  | .  . |  | |  |  \| |  | |  \ \`--. | |_| || |__  | |    | |       | |  | |__  \ \`--.   | |  | |__  | |_/ /\n";
printf "  | |\/| |  | |  | . \` |  | |   \`--. \|  _  ||  __| | |    | |       | |  |  __|  \`--. \  | |  |  __| |    / \n";
printf "  | |  | | _| |_ | |\  | _| |_ /\__/ /| | | || |___ | |____| |____   | |  | |___ /\__/ /  | |  | |___ | |\ \ \n";
printf "  \_|  |_/ \___/ \_| \_/ \___/ \____/ \_| |_/\____/ \_____/\_____/   \_/  \____/ \____/   \_/  \____/ \_| \_|\n\n\n$RESET";

$i = 0;
compare_shells ()
{
	MINI=$(echo "$@
exit" | ./minishell)
	BASH=$(echo "$@
	exit" | /bin/bash)
if [ "$MINI" == "$BASH" ]; then
    printf " $BOLDGREEN%s$RESET\n" "✔ "
else
    printf " $BOLDRED%s$RESET $RED\n MINI: %s\n$BLUE BASH: %s\n$RESET" "✗ " "$MINI" "$BASH"
i=$((i-1))
((i=i-1))
let "i=i-1"
fi
}

echo "test $i " compare_shells 'echo Hello World!'
echo "test $i " compare_shells 'echo Hello World! > test'
echo "test $i " compare_shells 'echo Hello again! >> test'
echo "test $i " compare_shells '< Makefile cat | sort | grep a'
echo "test $i " compare_shells 'echo this amazing sentence | cat > out
                cat out'
# compare_shells '< Makefile | ls > out
#                 cat out'

# check if old file content is removed and not overwritten. O_TRUNC flag
# force execve error with fake command (like cat or echo +x)
# check if file permissions are the same as the terminals output files