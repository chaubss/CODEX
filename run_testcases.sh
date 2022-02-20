# Run all testcases in testcases directory
# Add your custom testcases to ./testcases/input
# The output will be stored in ./testcases/output

for filename in ./testcases/input/*.cdx; do
    if [ -f ./lexer ]; then
        echo "$x Running testcase $(basename $filename .cdx)"
        ./lexer $filename > ./testcases/output/$(basename $filename .cdx).cdxout
    else
        echo "Lexer not found. Please create the executable first using the make command."
        break
    fi

done