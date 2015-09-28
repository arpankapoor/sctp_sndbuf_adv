logs=*.aux *.bbl *.bcf *.blg *.lof *.log *.out *.run.xml *.toc *-gnuplottex-*

all: graph.tex
	pdflatex -shell-escape $^
	pdflatex -shell-escape $^

clean:
	$(RM) $(logs)

.PHONY: all clean
