logs = *.aux *.bbl *.bcf *.blg *.lof *.log *.out *.run.xml *.toc

all: report.tex
	pdflatex $^
	pdflatex $^

clean:
	$(RM) $(logs)
