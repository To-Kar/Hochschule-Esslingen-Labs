#!/bin/bash

function show_help {
    echo "Usage: email_analysis.sh [-h | --help] [-e| --email] [-c| --company] [file]"
    echo ""
    echo "It only outputs after receiving one or both parameters; by default, the option is email."
    echo ""
    echo " -h|--help: Show this help and quits"
    echo " -e|--email: Outputs the number of emails from this E-Mail address"
    echo " -c| --company: Outputs the number of emails and the Company of the sender"
}

# Check if correct the number of command-line arguments is provided
if [ "$#" -lt 1 ]; then
    echo "Error: Insufficient number of arguments."
    show_help
    exit 1
fi

# Variables to store options and arguments
EMAIL_OPTION=false
COMPANY_OPTION=false
FILE=""

# Parse command line options
while [[ "$#" -gt 0 ]]; do
    case $1 in
        -e|--email)
            EMAIL_OPTION=true
            ;;
        -c|--company)
            COMPANY_OPTION=true
            ;;
        -h|--help)
            show_help
            exit 0
            ;;
        *)
            FILE="$1"
            ;;
    esac
    shift
done

# Check if file exists
if [ ! -f "$FILE" ]; then
    echo "File '$FILE' does not exist."
    exit 1
fi

# Analyze Emails
if [ "$EMAIL_OPTION" == true ]; then
    # Number of emails from each email address
    echo "Emails analysis:"
    grep -oP '^From \K\S+' "$FILE" | sort | uniq -c
fi

# Analyze Companies
if [ "$COMPANY_OPTION" == true ]; then
    # Number of emails from each company
    echo "Companies analysis:"
    grep -oP '^From .*@(\K\S+)' "$FILE" | sort | uniq -c
fi