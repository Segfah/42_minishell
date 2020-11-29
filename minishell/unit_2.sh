#!/bin/bash

TEST_ARRAY=(
'##################		    BUILTINS			#################' # ${YELLOW}STDOUT STDERR$NC
#### PWD ####
'pwd'
'pwd "useless argument"'
'unset PWD ; pwd'
#### ECHO ####
'echo | cat -e'
'echo hola buenos dias | cat -e'
'echo -n hola que tal bocadillo digital | cat -e'
#### ENV ####
'env | grep USER'
#### EXPORT ####
'export Z=z ; echo $Z'
'export A=a B=b C=c; echo $A$B$C'
'export A=mi-moto B=alpino C=derrapante; echo $A$B$C'
'export zz zzz= zzzz=asd ; echo $zz$zzz$zzzz; export | grep zz'
'export =a ; echo $a'
'export /dont/export/this=hola ; export | grep /dont/export/this'
'export A=a=a=a=a=a; echo $A'
'export A B C; echo $A$B$C'
'export $'
'export ?=42'
#### UNSET ####
'unset'
'export A=a ; unset A ; echo $A'
'export A=a B=b C=c ; unset A asd B asd ; echo $A$B$C'
#### CD ####
'cd ; pwd'
'unset HOME ; cd ; pwd'
'cd .; pwd'
'cd ..; pwd'
#'cd ..; echo $OLDPWD; pwd'
#'unset OLDPWD; cd .. ; echo $OLDPWD; pwd'
"cd ' /'; pwd"
'cd ../../ ; pwd'
'cd ../../../../../../.. ; pwd'
'cd dirwithoutpermissions'
#### EXIT ####
'exit'
'exit 42'
'exit -42'
'exit 512'
'exit 1407'
'exit 21 42'
'################	NO ENVIRONMENT (env -i ./minishell)	#################'
'cd'
'pwd'
'echo $PWD'
'cd .. ; echo $OLDPWD'
'./lscp'
'################		COMMAND EXECUTION	        #################'
'ls'
'/bin/ls'
'./lscp'
'cd dir ; ../lscp'
'cd dir/encoreuneautredir ; ../../lscp'
'df -h | head -2'
'/'
'./'
'/.'
'ls imnotaflag meneither'
'idontexist'
'./meneither'
'./dir'
'touch ucantexecme.e ; chmod 000 ucantexecme.e ; ./ucantexecme.e'
#'################		    PARSING		        #################'
#';'
'################		    QUOTES			#################'
'echo "$HOME"'
"echo '\$HOME'"
"echo ' \"\$HOME\" '"
"echo \"'\$HOME'\""
"echo \" '\$PWD' \\\"\$PWD\\\" '\$PWD' \"" "echo \"\\\$HOME\""
#"echo \"\\\''\'\""
"echo \"'\$'\""
"echo \\\\\n"
"echo \"< no pipe | or semicolon will ; stop me >\""
#'bash -c "I am not a command" "Im the program name"'
'pwd" should not work"'
'echo\" should not work neiter\"'
'################		    PIPES			#################'
'echo 5 + 3 | bc'
'ls | wc | wc -l | bc'
'echo "cat traveler" | cat | cat | cat | cat | cat | cat'
'################	        RIGHT REDIRECTION		#################'
'> a ; ls'
'pwd > a ; cat a'
'ls > a -f ; cat a'
'echo entre el clavel y la rosa > a su majestad es coja; cat a'
'> a echo cucu cantaba la rana; cat a'
'echo "redirection party trick" > a > b > c > d ; ls ; cat d'
'notacommand > a'
'pwd > dir'
'ls > a imnotaflag meneither'
'################	        DOUBLE REDIRECTION		#################'
'>> a; ls'
'pwd >> a; cat a'
'echo double the redirection double the fun >> a ; cat a'
'pwd >> a ; echo apendicitis >> a ; cat a'
'pwd >> a ; ls >> a -f ; cat a'
'echo entre el clavel y la rosa >> a su majestad es coja ; cat a'
'>> a echo cucu cantaba la rana; cat a'
'echo "party trick x2" >> a >> b >> c >> d ; ls ; cat d'
'notacommand >> a'
'pwd >> dir'
'ls >> a imnotaflag meneither'
'################	    LEFT REDIRECTION			#################'
'echo pim pam > pum ; cat < pum'
'touch a b c; echo sorry > d; cat < a < b < c < d'
'echo ayayay > a ; cat < doesnotexist < a'
'cat < doesnotexist'
'cat < dir'
'pwd > a < b ; ls ; cat a'
'pwd < a > b ; ls ; cat b'
)

GREEN=$(tput setaf 2)
RED=$(tput setaf 1)
YELLOW=$(tput setaf 3)
ROSITA=$(tput setaf 5)
BLUE=$(tput setaf 4)
VERDEKTSALTAALACARA=$(tput setaf 10)
ROJOKTSALTAALACARA=$(tput setaf 196)
MARRONMIERDA=$(tput setaf 8)
COLORBONITO=$(tput setaf 12)
NC=$(tput sgr0)


make 
cp ./the_big_minishell ./minishell
printf "copying your minishell to the current directory...\n"

rm -rf diff.txt

if  [[ ! -d dir || ! -d dir/encoreuneautredir ]]; then
    mkdir dir dir/encoreuneautredir
    printf "creating directories ${ROSITA}dir$NC, ${ROSITA}dir/encoreuneautredir$NC...\n"
fi
if [[ ! -d dirwithoutpermissions ]]; then
    mkdir -m 0000 dirwithoutpermissions
    printf "creating directory ${ROSITA}dirwithoutpermissions$NC...\n"
fi
cp $(which ls) lscp
printf "%s\n" "copying ${ROSITA}$(which ls)$NC to ${ROSITA}lscp$NC..."

printf "\n\t\t\t    ${YELLOW}[ MINISHELL UNIT TEST ]$NC\n\n\n"


TOTAL=0
PASSED=0
ENV=""
for val in "${TEST_ARRAY[@]}"
do
    if [[ "$val" = *ENVIRONMENT* ]]
    then
	ENV="env -i"
    elif [[ "$val" = *EXECUTION* ]]
    then
	ENV=""
    fi
    if [[ "$val" = *####* ]]; then
	printf "%s" "${NC}$val"
	printf " ${COLORBONITO}STDERR$NC\n"
	continue 
    fi
    $ENV bash -c "$val" minishell > out1 2> err1
    RET1=$?
    rm -rf a b c d
    $ENV ./minishell -c "$val" > out2 2> err2
    RET2=$?
    rm -rf a b c d
    if [[ $(uname) == "Darwin" ]]; then
        sed -i "" 's/line 0: //' err1
    else
        sed -i 's/line 0: //' err1
    fi
    if [[ $(cat out2) == "exit" ]];then
	echo exit >> out1
    fi
    DIFF=$(diff out1 out2) 
    ERRDIFF=$(diff err1 err2)
    if [[ "$DIFF" != "" || $RET1 != $RET2 || $ERRDIFF != ""  ]]
    then
	if [[ $ENV == "" ]]; then
	    printf "%s\n" "${YELLOW}$val$NC" >> diff.txt
	else
	    printf "%s\n" "${YELLOW}$ENV ./minishell: $val$NC" >> diff.txt
	fi
	printf "${ROSITA}< bash       (exited with %d)$NC\n" "$RET1" >> diff.txt
	printf "${ROSITA}> minishell  (exited with %d)\n$NC" "$RET2" >> diff.txt
    fi

    if [[ "$DIFF" == "" && $RET1 == $RET2 ]]
    then
	PASSED=$((PASSED+1))
	printf "%-80s[PASS] [$NC" "${GREEN}$val"
    else
	printf "%-80s[FAIL] [$NC" "${RED}$val"
	if [[ "$DIFF" != "" ]]; then
		printf "%s\n" "${COLORBONITO}----- STDOUT -----$NC" >> diff.txt
		diff out1 out2 >> diff.txt
	fi
    fi

    if [[ "$ERRDIFF" == "" ]]
    then
	printf "    "
    else
	printf "${MARRONMIERDA}FAIL$NC"
	printf "%s\n" "$COLORBONITO----- STDERR -----$NC" >> diff.txt
	diff err1 err2 >> diff.txt
    fi

    if [[ "$DIFF" != "" || $RET1 != $RET2 || $ERRDIFF != ""  ]]
    then
	printf "\n\n" >> diff.txt
    fi

    if [[ "$DIFF" == "" && $RET1 == $RET2 ]]; then
	    printf "${GREEN}]$NC\n"
	else
	    printf "${RED}]$NC\n"
    fi
    TOTAL=$((TOTAL+1))
done

printf "\n\n\t${GREEN}$PASSED$NC tests ${GREEN}passed$NC from a total of $TOTAL tests"
printf "  ||  ${GREEN}$PASSED passed$NC - ${RED}$((TOTAL - PASSED)) failed$NC"

printf "\n\n\t\t\'cat diff.txt | less\'  for detailed information\n\n"

rm -rf minishell out1 out2 err1 err2 a b c d pum lscp
chmod +r dirwithoutpermissions
rm -rf ucantexecme.e dir dir/encoreuneautredir dirwithoutpermissions