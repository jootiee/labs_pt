build:
	g++ main.cpp -o main.out

run: build
	./main.out --generate 105000 in.csv
	./main.out --test in.csv out.csv

clean:
	rm *.csv
	rm *.out