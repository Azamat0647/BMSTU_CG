

results_path="./results"
json_file="./func_tests/tests.json"

cli_path=$1

if [ ! $cli_path ] || [ ! -f $cli_path ]; then
    echo "cli not found"
    exit 1
fi

if [ ! $json_file ] || [ ! -f $json_file ]; then
    echo "$json_file not fount"
    exit 1
fi

if ! [ -d $results_path ]; then
    mkdir $results_path
else
    rm -f $results_path/*
fi

echo -e "tests start\n"
tests=$(jq -r '. | keys | join(" ")' $json_file)

for i in $tests
do
    name=$(jq -r ".[$i].name" $json_file)
    desc=$(jq -r ".[$i].desc" $json_file)
    args=$(jq -j --argjson i $i '.[$i] | "--alg "+.algorithm+" ",([.commands[] | (.command,(.input | .. | join(" ")?))] | join(" "))' $json_file)

    filepath="$results_path/$name.jpeg"

    echo "test_name: $name"
    echo "desc: $desc"

    echo $desc > $results_path/$name-desc.txt
    
    if ! $cli_path -o $filepath $args; then
        exit 1
    fi

    echo -e "saved to $filepath\n"
done

echo "Done"
