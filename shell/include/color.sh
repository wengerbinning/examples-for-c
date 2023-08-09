

for value in {0..30..1}; do
    attr="\e[${value}m"
    echo -e ${attr}color $value'\e[0m'
done
