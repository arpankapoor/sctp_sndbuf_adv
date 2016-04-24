logs=*.aux *.bbl *.bcf *.blg *.lof *.log *.nav *.out *.run.xml *.snm *.toc *-gnuplottex-* *.vrb

all: presentation.tex
	latexmk

clean:
	latexmk -c
	$(RM) $(logs)

.PHONY: all clean
