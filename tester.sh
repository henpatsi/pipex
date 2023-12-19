#!/bin/bash

PIPEX=./pipex

TEST_DIR=./test_files/

VALID_INFILE=${TEST_DIR}valid_infile
INVALID_INFILE=${TEST_DIR}invalid_infile

VALID_OUTFILE=${TEST_DIR}valid_outfile
INVALID_OUTFILE=${TEST_DIR}invalid_outfile
VALID_OUTFILE_BASH=${TEST_DIR}valid_outfile_bash

# ERROR_LOG=${TEST_DIR}error_log
# ERROR_LOG_BASH=${TEST_DIR}error_log_bash

NC='\033[0m'
GREEN='\033[0;32m'
LGREEN='\033[1;32m'
RED='\033[0;31m'
CYAN='\033[0;36m'
LCYAN='\033[1;36m'

HEADER_COLOR=${LCYAN}
SUBHEADER_COLOR=${CYAN}

check_output()
{
	cmp ${OUTFILE_BASH} ${OUTFILE} && 
		echo -e ${GREEN}"Outfile content: [OK]"${NC} || 
		echo -e ${RED}"Outfile content: [KO]"${NC}
	rm ${OUTFILE_BASH}
	rm ${OUTFILE}
}

# check_stderr()
# {
# 	cmp ${ERROR_LOG_BASH} ${ERROR_LOG} && 
# 		echo -e ${GREEN}"stderr ouput: [OK]"${NC} || echo -e ${RED}"stderr ouput: [KO]"${NC}
# }

check_exit_code()
{
	if [ ${EXIT_CODE_BASH} -eq ${EXIT_CODE} ]
	then
		echo -e ${GREEN}"Exit code: [OK]"${NC}
	else
		echo -e ${RED}"Exit code: [KO]"
		echo -e "bash was: ${EXIT_CODE_BASH}"
		echo -e "pipex was: ${EXIT_CODE}"${NC}
	fi
	echo ""
}

run_two_commands()
{
	echo "$COMMAND1 | $COMMAND2"
	< ${INFILE} $COMMAND1 | $COMMAND2 > ${OUTFILE_BASH}
	EXIT_CODE_BASH=$?
#	cat ${VALID_OUTFILE_BASH}
	${PIPEX} ${INFILE} "$COMMAND1" "$COMMAND2" ${OUTFILE}
	EXIT_CODE=$?
#	cat ${VALID_OUTFILE}
}

run_three_commands()
{
	echo "$COMMAND1 | $COMMAND2 | $COMMAND3"
	< ${INFILE} $COMMAND1 | $COMMAND2 | $COMMAND3 > ${OUTFILE_BASH}
	EXIT_CODE_BASH=$?
#	cat ${VALID_OUTFILE_BASH}
	${PIPEX} ${INFILE} "$COMMAND1" "$COMMAND2" "$COMMAND3" ${OUTFILE}
	EXIT_CODE=$?
#	cat ${VALID_OUTFILE}
}

run_five_commands()
{
	echo "$COMMAND1 | $COMMAND2 | $COMMAND3 | $COMMAND4 | $COMMAND5"
	< ${INFILE} $COMMAND1 | $COMMAND2 | $COMMAND3 | $COMMAND4 | $COMMAND5 > ${OUTFILE_BASH}
	EXIT_CODE_BASH=$?
#	cat ${VALID_OUTFILE_BASH}
	${PIPEX} ${INFILE} "$COMMAND1" "$COMMAND2" "$COMMAND3" "$COMMAND4" "$COMMAND5" ${OUTFILE}
	EXIT_CODE=$?
#	cat ${VALID_OUTFILE}
}

run_heredoc_commands()
{
	${PIPEX} ${INFILE} "" "$COMMAND1" "$COMMAND2" ${OUTFILE}
}

printf ${HEADER_COLOR}"\n\n----- VALID ALL -----\n"${NC}

INFILE=${VALID_INFILE}
OUTFILE=${VALID_OUTFILE}
OUTFILE_BASH=${VALID_OUTFILE_BASH}

printf ${SUBHEADER_COLOR}"\n- Single call -\n\n"${NC}

COMMAND1="wc"
COMMAND2="grep 3"
run_two_commands
check_output
check_exit_code

COMMAND1="grep 3"
COMMAND2="wc"
run_two_commands
check_output
check_exit_code

COMMAND1="ls -la"
COMMAND2="grep pipex"
run_two_commands
check_output
check_exit_code

printf ${SUBHEADER_COLOR}"- Two calls -\n\n"${NC}

COMMAND1="ls -la"
COMMAND2="grep x"
run_two_commands
COMMAND1="wc"
COMMAND2="wc"
run_two_commands
check_output
check_exit_code



printf ${HEADER_COLOR}"\n----- NOT ENOUGH ARGS -----\n\n"${NC}

echo "${PIPEX} ${VALID_INFILE} "cat" ${VALID_OUTFILE}"
${PIPEX} ${VALID_INFILE} "cat" ${VALID_OUTFILE}



printf ${HEADER_COLOR}"\n\n----- INVALID COMMAND -----\n"${NC}

printf ${SUBHEADER_COLOR}"\n- First Command -\n\n"${NC}

COMMAND1="nocommand"
COMMAND2="wc"
run_two_commands
check_output
check_exit_code

COMMAND1="nocommand"
COMMAND2="ls"
run_two_commands
check_output
check_exit_code

printf ${SUBHEADER_COLOR}"- Second Command -\n\n"${NC}

COMMAND1="wc"
COMMAND2="nocommand"
run_two_commands
check_output
check_exit_code

printf ${SUBHEADER_COLOR}"- Both Commands -\n\n"${NC}

COMMAND1="nocommand1"
COMMAND2="nocommand2"
run_two_commands
check_output
check_exit_code

printf ${SUBHEADER_COLOR}"- Invalid Command Args -\n\n"${NC}

COMMAND1="wc"
COMMAND2="wc --noargs"
run_two_commands
check_output
check_exit_code

COMMAND1="wc --noargs"
COMMAND2="wc"
run_two_commands
check_output
check_exit_code

COMMAND1="wc --noargs"
COMMAND2="wc --noargs"
run_two_commands
check_output
check_exit_code



printf ${HEADER_COLOR}"\n----- INVALID FILES -----\n"${NC}

printf ${SUBHEADER_COLOR}"\n- Input Read Restricted -\n\n"${NC}

INFILE=${INVALID_INFILE}

COMMAND1="cat"
COMMAND2="wc -l"
run_two_commands
check_output
check_exit_code

printf ${SUBHEADER_COLOR}"- Input Does Not Exist -\n\n"${NC}

INFILE=doesnotexist

COMMAND1="cat"
COMMAND2="wc -l"
run_two_commands
check_output
check_exit_code

printf ${SUBHEADER_COLOR}"- Output Write Restricted -\n\n"${NC}

INFILE=${VALID_INFILE}
OUTFILE=${INVALID_OUTFILE}
OUTFILE_BASH=${INVALID_OUTFILE}

COMMAND1="cat"
COMMAND2="wc -l"
run_two_commands
check_output
check_exit_code

printf ${SUBHEADER_COLOR}"- Input Output Restricted -\n\n"${NC}

INFILE=${INVALID_INFILE}
OUTFILE=${INVALID_OUTFILE}
OUTFILE_BASH=${INVALID_OUTFILE}

COMMAND1="cat"
COMMAND2="wc -l"
run_two_commands
check_output
check_exit_code



printf ${HEADER_COLOR}"\n----- BONUS N COMMANDS -----\n"${NC}

INFILE=${VALID_INFILE}
OUTFILE=${VALID_OUTFILE}
OUTFILE_BASH=${VALID_OUTFILE_BASH}

printf ${SUBHEADER_COLOR}"\n- Single call -\n\n"${NC}

COMMAND1="wc"
COMMAND2="tr -d 123"
COMMAND3="wc"
run_three_commands
check_output
check_exit_code

COMMAND1="ls -la"
COMMAND2="grep pipex"
COMMAND3="wc"
COMMAND4="tr -d 123"
COMMAND5="wc"
run_five_commands
check_output
check_exit_code

printf ${SUBHEADER_COLOR}"- Multiple calls -\n\n"${NC}

COMMAND1="ls -la"
COMMAND2="grep pipex"
run_two_commands
COMMAND1="wc"
COMMAND2="tr -d 123"
COMMAND3="wc"
run_three_commands
COMMAND1="ls -la"
COMMAND2="grep pipex"
COMMAND3="wc"
COMMAND4="tr -d 123"
COMMAND5="wc"
run_five_commands
check_output
check_exit_code

printf ${SUBHEADER_COLOR}"- Fails -\n\n"${NC}

COMMAND1="nocommand"
COMMAND2="cat"
COMMAND3="wc"
run_three_commands
check_output
check_exit_code

COMMAND1="wc"
COMMAND2="cat"
COMMAND3="nocommand"
run_three_commands
check_output
check_exit_code

COMMAND1="wc"
COMMAND2="nocommand"
COMMAND3="cat"
run_three_commands
check_output
check_exit_code

COMMAND1="nocommand"
COMMAND2="nocommand"
COMMAND3="cat"
run_three_commands
check_output
check_exit_code

COMMAND1="cat"
COMMAND2="nocommand"
COMMAND3="nocommand"
run_three_commands
check_output
check_exit_code

COMMAND1="nocommand"
COMMAND2="cat"
COMMAND3="nocommand"
run_three_commands
check_output
check_exit_code

COMMAND1="nocommand"
COMMAND2="nocommand"
COMMAND3="nocommand"
run_three_commands
check_output
check_exit_code

COMMAND1="wc"
COMMAND2="wc -l"
COMMAND3="wc --notrealarg"
run_three_commands
check_output
check_exit_code

printf ${HEADER_COLOR}"\n----- BONUS HERE_DOC -----\n\n"${NC}

INFILE="here_doc"
OUTFILE=${VALID_OUTFILE}
OUTFILE_BASH=${VALID_OUTFILE_BASH}

COMMAND1="cat"
COMMAND2="tr -d 1234567890"
run_heredoc_commands
