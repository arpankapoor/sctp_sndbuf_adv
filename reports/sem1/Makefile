logs=*.aux *.bbl *.bcf *.blg *.lof *.log *.out *.run.xml *.toc *-gnuplottex-*

all: report.tex
	pdflatex -shell-escape $^
	biber report
	pdflatex -shell-escape $^
	pdflatex -shell-escape $^

clean:
	$(RM) $(logs)

.PHONY: all clean
