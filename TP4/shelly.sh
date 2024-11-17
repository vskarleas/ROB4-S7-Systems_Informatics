#!/bin/bash

GREEN='\033[0;32m'
BLUE='\033[0;36m'
PURPLE='\033[1;35m'
YELLOW='\033[0;33m'
NORMAL='\033[0m'  # Define NORMAL as reset (in ASNI) 

clear

# Print a message to the user
echo -e "${BLUE}Welcome to Shelly, your customised shell, developed by Vasileios Filippos Skarleas. Once you are ready to start exploring the capabilities of the software simply press ENTER"
echo -e "${GREEN}Bienvenue dans le Shelly, votre shell perosnalisé, créé par Vasileios Filippos Skarleas. Une fois que vous êtes prêt à commencer de decouvrir le logiciel, appuyez simplement sur ENTER"

# Read a line of input from the use
read input

# If the user presses Enter, run the specified commands
if [[ -n "$input" ]]; then
  echo -e "${PURPLE}You did not press ENTER and the Shelly installer will terminate"
else
  # Run the initial commands
  clear
  echo -e "${PURPLE}Initialising environment..."
  sleep 2
  make clean
  make
  clear
  echo -e "${NORMAL}This software allows you to have a customised shell environment according to your needs.\n"
  echo -e "Simply, you can clone its repository and modify its code to perfom the tasks that you wish. It's easy even to integrate commands that do not exist by default in your OS since Shelly is built exclusively on C. The repository of Shelly is available at https://github.com/vskarleas/ROB3-S7-Shelly\n"
  echo -e "++++++++++++++++++++++++++++++++++++++++++++++++++++++++"

  # Infinite loop with user options
  while true; do
    echo -e "\n- start: Runs the Shelly software."
    echo -e "- close: Exits Shelly."
    echo -e "${GREEN}========================================================\n${NORMAL}Enter a command (start, close):"
    read command

    case "$command" in
      start)
        clear
        ./shell
        ;;
      test)
        clear
        ./test
        ;;
      close | exit)
        break  # Exit the loop
        ;;
      *)
        echo -e "${YELLOW}\nInvalid command. Please try again!${NORMAL}"
        ;;
    esac
  done

  # Commands to execute after exiting the loop
  make clean
  clear
  echo -e "${GREEN}Shelly has been successfully terminated\n"
  echo -e "${NORMAL}Thank you! | ${BLUE}Copyright © 2024 - $(date +%Y) ${NORMAL} Vasileios Filippos Skarleas - All rights reserved"
fi
