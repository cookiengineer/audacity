#!/usr/bin/env bash

((${BASH_VERSION%%.*} >= 4)) || { echo >&2 "$0: Error: Please upgrade Bash."; exit 1; }

set -uxo pipefail

set +x

max_retry=5
counter=0
num_secs_await_retry=1

echo "Trying: " /usr/bin/hdiutil "$@"

until /usr/bin/hdiutil "$@"; do
   sleep $num_secs_await_retry
   if [[ $counter -eq $max_retry ]]; then
        echo "CPack failed despite retry attempts!"
        exit 1
   else
        echo "Trying CPack hdiutil call again. Retry attempt #$counter"
        ((counter++))
   fi
done
