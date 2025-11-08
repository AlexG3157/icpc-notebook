notebook.pdf: notebook.tex
	pdflatex notebook.tex
	pdflatex notebook.tex

notebook.tex:
	python GenerateNotebook.py

clean:
	rm *.aux *.fdb_latexmk *.fls *.log *.out *.gz *.toc notebook.tex template.pdf