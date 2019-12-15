all: clean
	# @sudo apt install libboost-dev
	@clang++ -std=c++11 -stdlib=libc++ -Weverything *.cpp -o main.out
	@echo success!
	
clean:
	@rm -f main.out outputs/* logs/*