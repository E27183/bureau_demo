.PHONY: gendata

gendata:
	gcc c/generate_data.c -o c/compiled_c -lm
	c/compiled_c