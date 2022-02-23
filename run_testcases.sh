# Run all testcases in testcases directory
# Add your custom testcases to ./testcases/input
# The output will be stored in ./testcases/output

for filename in ./testcases/input/*.cdx; do
    if [ -f ./lexer ]; then
        echo "$x Running testcase \033[1;36m$(basename $filename .cdx).cdx\033[0m"
        ./lexer $filename > ./testcases/output/$(basename $filename .cdx).cdxout
        sleep 0.1
    else
        echo "\033[1;31mError: Lexer not found. Please create the executable first using the make command.\033[0m"
        exit
    fi
done

echo "\n\n\033[1;32mFinished running all testcases. Check the output in ./testcases/output\033[0m"