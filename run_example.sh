#! /bin/zsh

if [[ ! -n "$1" ]]; then

echo "A valid filename must be provided"
exit 1

fi

cd $(dirname "$0")

g++ -O3 -o "main" "examples/$1.cpp"
./main
