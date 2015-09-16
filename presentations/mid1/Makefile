logs=*.aux *.bbl *.bcf *.blg *.lof *.log *.nav *.out *.run.xml *.snm *.toc

all: main.tex
	pdflatex $^
	biber main
	pdflatex $^
	pdflatex $^

clean:
	$(RM) $(logs)

.PHONY: all clean
