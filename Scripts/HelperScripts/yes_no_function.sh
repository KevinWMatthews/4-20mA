#!/bin/bash

### Use Guidlines ###
#To use this function in a script, include the following at the top of your script:
# function yes_no ()
# {
#   source ./yes_no_function.sh "$1" $2
# }


### Documentation ###
#Exit code 0 for Yes
#Exit code 1 for No
#Will not exit otherwise

message=$1

while true; do
  if [ "$2" == "Y" ]; then
    prompt="Y/n"
    default=Y
  elif [ "$2" == "N" ]; then
    prompt="y/N"
    default=N
  else
    prompt="y/n"
    defualt=
  fi

  read -p "$message [$prompt] " response
  if [ -z "$response" ]; then
    response=$default
  fi

  case $response in
    [yY])
      return 0
      ;;
    [nN])
      return 1
      ;;
    *)
      echo "Invalid input!"
      ;;
  esac
done
