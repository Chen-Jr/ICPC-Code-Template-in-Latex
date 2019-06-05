template.pdf: template.tex main
	./main
	pdflatex template.tex
	pdflatex template.tex

template.tex: main

main: main.cpp
	cc main.cpp -o main

clean:
	rm template.* main
