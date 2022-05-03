# Run all testcases in testcases directory
# Add your custom testcases to ./testcases_parser/input
# The output will be stored in ./testcases_parser/output

for filename in ./testcases_parser/input/*.cdx; do
    if [ -f ./parser ]; then
        echo "$x Running testcase \033[1;36m$(basename $filename .cdx).cdx\033[0m"
        ./parser $filename > ./testcases_parser/output/$(basename $filename .cdx).cdxout
        sleep 0.1
    else
        echo "\033[1;31mError: Parser not found. Please create the executable first using the make command.\033[0m"
        exit
    fi
done

echo "\n\n\033[1;32mFinished running all testcases. Check the output in ./testcases_parser/output\033[0m"