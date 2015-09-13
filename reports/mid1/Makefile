logs=*.aux *.bbl *.bcf *.blg *.lof *.log *.out *.run.xml *.toc

all: report.tex
	pdflatex $^
	biber report
	pdflatex $^
	pdflatex $^

clean:
	$(RM) $(logs)

.PHONY: all clean
