\NeedsTeXFormat{LaTeX2e}[1994/06/01]
\ProvidesClass{homework}[2021 Shao Jie Hu Chen]
\LoadClass[11pt, a4paper]{article}

\RequirePackage[spanish]{babel}
\RequirePackage[utf8]{inputenc} % comment when using lualatex
\RequirePackage{fullpage}
\RequirePackage{graphicx}
\RequirePackage[hidelinks]{hyperref,xcolor}
\RequirePackage{charter} % Use the Charter font

\RequirePackage{setspace}

\RequirePackage{parskip}

\RequirePackage{amsmath}
\RequirePackage{amsfonts}
\RequirePackage{amssymb}
\RequirePackage{hyperref}

\newcommand{\course}{Asignatura}

\newcommand{\HRule}{\rule{\linewidth}{0.3mm}} % Defines a new command for horizontal lines, change thickness here

\renewcommand{\maketitle}{
	
\begin{titlepage}
	
	\vspace*{0.25cm}
	
	\center % Centre everything on the page
	%------------------------------------------------
	%	Headings
	%------------------------------------------------
	
	\includegraphics[scale=0.15]{logo-ugr.jpeg}
	
	\vspace*{1cm}
	
	% \textsc{\LARGE Universidad de Granada}\\[1cm]
	
	\textsc{\Large Doble Grado en Ingeniería Informática y Matemáticas}\\[0.8cm]
	
	\textsc{\Large \course}\\[0.8cm]
	
	%------------------------------------------------
	%	Title
	%------------------------------------------------
	
	\HRule\\[0.5cm]
	
	\doublespacing
	
	{\huge\bfseries \@title}\\[0.0mm]
	
	\singlespacing
	
	\HRule\\[1.5cm]
	
	%------------------------------------------------
	%	Author(s)
	%------------------------------------------------
	\begin{minipage}{0.4\textwidth}
		\begin{flushleft}
			\large
			\@author % Your name
		\end{flushleft}
	\end{minipage}
	~
	\begin{minipage}{0.4\textwidth}
		\begin{flushright}
			\large
			\textit{Grupo}
			Rojo
		\end{flushright}
	\end{minipage}

	%------------------------------------------------
	%	Date
	%------------------------------------------------
	
	\vspace{2cm}
	{\large\@date} % Date, change the \today to a set date if you want to be precise
	\vfill\vfill\vfill
	
\end{titlepage}
}