.PHONY: gendata csvconversion todatapoints runmodel all makedatafolder

makedatafolder:
	test -d data || mkdir data

gendata:
	gcc c/generate_data.c -o c/compiled_c -lm
	c/compiled_c

csvconversion:
	gfortran -o fortran/compiled fortran/convert_to_csv.f95
	fortran/compiled

todatapoints:
	gcc -o cpp/compiled_cpp cpp/refine_datapoints.cpp -lstdc++
	cpp/compiled_cpp

runmodel:
	python3 python3/apply_model.py

all: makedatafolder gendata csvconversion todatapoints runmodel