logs=*.aux *.bbl *.bcf *.blg *.lof *.log *.nav *.out *.run.xml *.snm *.toc

all: presentation.tex
	pdflatex $^
	biber presentation
	pdflatex $^
	pdflatex $^

clean:
	$(RM) $(logs)

.PHONY: all clean
