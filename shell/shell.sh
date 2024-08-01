


test -f data.bin && rm -f data.bin
for idx in $(seq 0 255); do
	printf "00 %02X" $idx | xxd -r > .data.bin~
	test -f data.bin && cat data.bin .data.bin~ > .data.bin
	test -f data.bin || cat .data.bin~ > .data.bin
	cp .data.bin data.bin
done
rm -f .data.bin .data.bin~
xxd -u data.bin