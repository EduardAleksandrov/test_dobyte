
run:
	g++ -std=c++17 -o build/code ./others/main.cpp && ./build/code

run_omp:
	g++ -std=c++17 -o build/codem ./others/main_omp.cpp -fopenmp && ./build/codem

run_opt:
	g++ -std=c++17 -o build/codet main_opt.cpp -fopenmp && ./build/codet

run_new:
	g++ -std=c++17 -o build/co ./others/mainnew.cpp && ./build/co

run_new_else:
	g++ -std=c++17 -o build/com ./others/main_new_else.cpp && ./build/com

dir:
	mkdir build