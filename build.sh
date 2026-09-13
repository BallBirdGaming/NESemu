mkdir build
clang++ -o2 -s src/*.cpp -o build/NESemu
{
	echo "date of build:"
	date
} > build/date.txt
