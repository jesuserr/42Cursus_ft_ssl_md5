#!/bin/bash

function echo_green {
    echo -e "\033[32m$1\033[0m"
}

function echo_red {
    echo -e "\033[31m$1\033[0m"
}

function echo_yellow {
    echo -e "\033[33m$1\033[0m"
}

make all

# Failing arguments
./ft_ssl 2>/dev/null || echo_green "[OK] no arguments"
./ft_ssl md4 2>/dev/null || echo_green "[OK] invalid command \"md4\""
./ft_ssl "" 2>/dev/null || echo_green "[OK] invalid command \"\""

function check_output {
    local command="$1"
    local expected="$2"
    local result
    result=$(eval "$command" 2>&1)
    if [[ "$(echo "$result" | sort)" == "$(echo "$expected" | sort)" ]]; then
        echo_green "[OK] $command"
    else
        diff --side-by-side --color <(echo "$expected" | sort) <(echo "$result" | sort) | sed -e 's/\x1b\[[0-9;]*m//g' | while IFS= read -r line; do
            if [[ "$line" =~ \| ]]; then
                echo -e "\033[31m$line\033[0m"
            else
                echo "$line"
            fi
        done
    fi
}

function check_valgrind {
    local command="$1"
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 $command &> /dev/null
    if [[ $? -eq 0 ]]; then
        echo_green "[OK] No memory leaks detected in: $command"
    else
        echo_red "[FAIL] Memory leaks detected in: $command"
          echo_yellow "     valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 $command"
    fi
}

check_output 'echo -n '' | ./ft_ssl md5' '(stdin)= d41d8cd98f00b204e9800998ecf8427e'

# Tests with expected output
check_output 'echo -n "42 is nice" | ./ft_ssl md5' "(stdin)= 0029a98ee90fdb85d70924d44d3c9e75"
check_output 'echo "42 is nice" | ./ft_ssl md5' '(stdin)= 35f1d6de0302e2086a4e472266efb3a9'
check_output 'echo "Pity the living." | ./ft_ssl md5 -q -r' 'e20c3b973f63482a778f3fd1869b7f25'


# just a newline
check_output 'echo "" | ./ft_ssl md5' '(stdin)= 68b329da9893e34099c7d8ad5cb9c940'

# # File based tests
echo "And above all," > file
check_output './ft_ssl md5 file' 'MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a'
 check_output './ft_ssl md5 -r file' '53d53ea94217b259c11a5a2d104ec58a file'

 # String input with -s flag
check_output './ft_ssl md5 -s "pity those that aren'\''t following baerista on spotify."' 'MD5 ("pity those that aren'\''t following baerista on spotify.") = a3c990a1964705d9bf0e602f44572f5f'

 # Edge cases
check_output 'echo "be sure to handle edge cases carefully" | ./ft_ssl md5 -p file' '("be sure to handle edge cases carefully")= 3553dc7dc5963b583c056d1b9fa3349c
MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a'

 check_output 'echo "some of this will not make sense at first" | ./ft_ssl md5 file' 'MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a'

 # Combined flags
 check_output 'echo "but eventually you will understand" | ./ft_ssl md5 -p -r file' '("but eventually you will understand")= dcdd84e0f635694d2a943fa8d3905281
53d53ea94217b259c11a5a2d104ec58a file'

 check_output 'echo "GL HF let'\''s go" | ./ft_ssl md5 -p -s "foo" file' '("GL HF let'\''s go")= d1e3cc342b6da09480b27ec57ff243e2
MD5 ("foo") = acbd18db4cc2f85cedef654fccc4a4d8
MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a'

 check_output 'echo "one more thing" | ./ft_ssl md5 -r -p -s "foo" file -s "bar"' '("one more thing")= a0bd1876c6f011dd50fae52827f445f5
acbd18db4cc2f85cedef654fccc4a4d8 "foo"
53d53ea94217b259c11a5a2d104ec58a file
ft_ssl: md5: -s: No such file or directory
ft_ssl: md5: bar: No such file or directory'

 check_output 'echo "just to be extra clear" | ./ft_ssl md5 -r -q -p -s "foo" file' 'just to be extra clear
3ba35f1ea0d170cb3b9a752e3360286c
acbd18db4cc2f85cedef654fccc4a4d8
53d53ea94217b259c11a5a2d104ec58a'

 # Additional edge cases
 echo "another edge case" > edge_case_file
 check_output './ft_ssl md5 edge_case_file' 'MD5 (edge_case_file) = c4f09c0dcac6fb390a9625936cb676d4'
 check_output './ft_ssl md5 -s ""' 'MD5 ("") = d41d8cd98f00b204e9800998ecf8427e'
 check_output 'echo -n "" | ./ft_ssl md5' '(stdin)= d41d8cd98f00b204e9800998ecf8427e'


check_output 'echo "crazy edge case 1" | ./ft_ssl md5 -p -q -r file -s "test string"' 'crazy edge case 1
f507a568c27ebf71fb6eea0aeb7ed4ad
53d53ea94217b259c11a5a2d104ec58a
ft_ssl: md5: -s: No such file or directory
ft_ssl: md5: test string: No such file or directory'

check_output 'echo -n "crazy edge case 2" | ./ft_ssl md5 -p -q -r -s "test string" file' 'crazy edge case 2
39cb7603517969f2020514c661438aa0
6f8db599de986fab7a21625b7916589c
53d53ea94217b259c11a5a2d104ec58a'

# check_output 'cat .gitignore | ./ft_ssl md5 -q ' '3703fa5ed0438b06c8e7230afbe3e564'
# check_output './ft_ssl md5 -q .gitignore .gitignore .gitignore' '3703fa5ed0438b06c8e7230afbe3e564
# 3703fa5ed0438b06c8e7230afbe3e564
# 3703fa5ed0438b06c8e7230afbe3e564'



dd if=/dev/random of=random_file bs=1M count=5 > /dev/null 2>&1
md5=$(md5sum random_file | cut -d ' ' -f 1)
mv random_file $md5
check_output "./ft_ssl md5 $md5" "MD5 ($md5) = $md5"


####################################################

SHA256=$(echo -n "42 is the answer" | shasum -a 256 | cut -d ' ' -f 1)
check_output "./ft_ssl sha256 -q -s '42 is the answer'" "$SHA256"
check_output 'echo -n "42 is the answer" | ./ft_ssl sha256' "(stdin)= $SHA256"

check_output 'echo test | ./ft_ssl sha256' '(stdin)= f2ca1bb6c7e907d06dafe4687e579fce76b37e4e93b7605022da52e6ccc26fd2'
check_output 'echo test | ./ft_ssl sha256 -q' 'f2ca1bb6c7e907d06dafe4687e579fce76b37e4e93b7605022da52e6ccc26fd2'

dd if=/dev/random of=/tmp/random_file bs=1M count=5 > /dev/null 2>&1
SHA256=$(sha256sum /tmp/random_file | cut -d' ' -f1)
mv /tmp/random_file /tmp/$SHA256
check_output "./ft_ssl sha256 /tmp/$SHA256" "SHA256 (/tmp/${SHA256}) = $SHA256"
# check_output "cat .gitignore | ./ft_ssl sha256" "(stdin)= af6d8d9ae298642865cdc7abff561bdc605507b391dcbcc9248f23288b7130da"
# check_output "./ft_ssl sha256 -q .gitignore .gitignore .gitignore" "af6d8d9ae298642865cdc7abff561bdc605507b391dcbcc9248f23288b7130da
# af6d8d9ae298642865cdc7abff561bdc605507b391dcbcc9248f23288b7130da
# af6d8d9ae298642865cdc7abff561bdc605507b391dcbcc9248f23288b7130da"

# extensive sha256 tests with flags
check_output "echo -n '' | ./ft_ssl sha256 -q" "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"
check_output "echo -e '' | ./ft_ssl sha256 -q" "01ba4719c80b6fe911b091a7c05124b64eeece964e09c058ef8f9805daca546b"
check_output "echo -n sha256 | ./ft_ssl sha256 -q" "5d5b09f6dcb2d53a5fffc60c4ac0d55fabdf556069d6631545f42aa6e3500f2e"


if [ "$1" == "--valgrind" ]; then
  echo_yellow "Running valgrind tests..."
  check_valgrind "./ft_ssl md5 -s ''"
  check_valgrind "./ft_ssl md5 file"
  check_valgrind "./ft_ssl md5 -s 'test'"
  check_valgrind "./ft_ssl md5 -s '' -s bad -s wrong file1 file2 file3"
  check_valgrind "./ft_ssl md5 edge_case_file"
  echo test | check_valgrind "./ft_ssl md5"
  check_valgrind "echo -n '' | ./ft_ssl md5 -r -q file -s test"

  check_valgrind "./ft_ssl sha256 -s ''"
  check_valgrind "./ft_ssl sha256 file"
  check_valgrind "./ft_ssl sha256 -s 'test'"
  check_valgrind "./ft_ssl sha256 -s '' -s bad -s wrong file1 file2 file3"
  check_valgrind "./ft_ssl sha256 edge_case_file"
  echo test | check_valgrind "./ft_ssl sha256"
fi

rm -f $md5
rm -f file edge_case_file $SHA256