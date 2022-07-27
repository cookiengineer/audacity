#!/bin/sh

((${BASH_VERSION%%.*} >= 4)) || { echo >&2 "$0: Error: Please upgrade Bash."; exit 1; }

set -uo pipefail

max_retry=12
counter=0
num_secs_await_retry=20

echo "Trying: /usr/bin/hdiutil $*"

until /usr/bin/hdiutil "$@"; do
   sleep $num_secs_await_retry
   if [[ $counter -eq $max_retry ]]; then
        echo "CPack failed despite retry attempts!"
        exit 1
   else
        echo "Attempting to umount before retry..."
        modified_args=("$@")
        modified_args[0]="umount"
        /usr/bin/hdiutil "${modified_args[@]}"
        echo "Trying hdiutil call again. Retry attempt #$counter"
        ((counter++))
   fi
done
