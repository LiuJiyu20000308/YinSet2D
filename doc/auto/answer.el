(TeX-add-style-hook
 "answer"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-class-options
                     '(("article" "twoside" "a4paper")))
   (add-to-list 'LaTeX-verbatim-environments-local "lstlisting")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "lstinline")
   (add-to-list 'LaTeX-verbatim-macros-with-delims-local "lstinline")
   (TeX-run-style-hooks
    "latex2e"
    "article"
    "art10"
    "geometry"
    "float"
    "tikz"
    "pgfplots"
    "amsfonts"
    "amsmath"
    "amssymb"
    "amsthm"
    "enumerate"
    "graphicx"
    "multicol"
    "fancyhdr"
    "layout"
    "listings"
    "longtable"
    "multirow"
    "subfigure")
   (TeX-add-symbols
    '("pdfFrac" 2)
    '("difFrac" 2)
    '("avg" 1)
    "dif"
    "OFL"
    "UFL"
    "fl"
    "op"
    "Eabs"
    "Erel")
   (LaTeX-add-labels
    "fig:figure1"))
 :latex)

