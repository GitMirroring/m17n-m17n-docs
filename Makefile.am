# Makefile.am -- Makefile for the m17n library documentation.
# Copyright (C) 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010
#   National Institute of Advanced Industrial Science and Technology (AIST)
#   Registration Number H15PRO112

# This file is part of the m17n library documentation, a sub-part of
# the m17n library.

# The m17n library is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation; either version 2, or (at
# your option) any later version.

# The m17n library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with the m17n library; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
# Boston, MA 02111-1307, USA.

## Process this file with Automake to create Makefile.in

SUBDIRS = utils

pkgdata_DATA = \
	usr/html/index.html \
	usr/latex/m17n-lib.pdf \
	man/man1/m17n-config.1 \
	man/man3/m17nIntro.3m17n \
	man/man5/mdbGeneral.5

pkgdatadir = $(datadir)/m17n/docs

EXTRA_DIST = usr/html ja/html \
	usr/latex ja/latex \
	man/man1 man/man3 man/man5

install-pkgdataDATA: $(pkgdata_DATA)
	$(mkinstalldirs) $(pkgdatadir)/html
	$(mkinstalldirs) $(mandir)/man1 $(mandir)/man3 $(mandir)/man5
	$(INSTALL_DATA) usr/latex/m17n-lib.pdf $(pkgdatadir)/m17n-lib.pdf
	cd usr/html; \
	  for f in *.html *.png; do \
	    $(INSTALL_DATA) $$f $(pkgdatadir)/html/$$f; \
	  done
	cd man/man1; \
	  for f in *.1; do $(INSTALL_DATA) $$f $(mandir)/man1/$$f; done
	cd man/man3; \
	  for f in *.3m17n; do $(INSTALL_DATA) $$f $(mandir)/man3/$$f; done
	cd man/man5; \
	  for f in *.5; do $(INSTALL_DATA) $$f $(mandir)/man5/$$f; done

#
# The followings are for maintainers only.
#
if MAINTAINER_MODE

PROJECT_NAME_EN = "The m17n Library"
PROJECT_NAME_JA = "m17n ライブラリ"
PROJECT_VERSION = @PACKAGE_VERSION@

DOXYGEN = doxygen

EXAMPLE_PROGS = \
	@M17NLIB@/example/mconv.c \
	@M17NLIB@/example/mview.c \
	@M17NLIB@/example/mdate.c \
	@M17NLIB@/example/mdump.c \
	@M17NLIB@/example/medit.c \
	@M17NLIB@/example/mimx-anthy.c \
	@M17NLIB@/example/mimx-ispell.c

DBFORMAT = \
	@M17NDB@/FORMATS

MAN1 =	data/m17n-config.txt data/m17n-db.txt ${EXAMPLE_PROGS}

MAN3 =	@M17NLIB@/src/m17n-core.h \
	@M17NLIB@/src/m17n.h \
	@M17NLIB@/src/m17n-flt.h \
	@M17NLIB@/src/m17n-gui.h \
	@M17NLIB@/src/m17n-X.h \
	@M17NLIB@/src/m17n-misc.h \
	@M17NLIB@/src

MAN5 = ${DBFORMAT}

SRCALL = \
	mainpage.txt \
	${MAN3} \
	data/m17n-config.txt data/m17n-db.txt data/exprog.txt \
	data/dbformat.txt data/dbdata.txt data/dbtutorial.txt fdl.txt

DBDATA = $(shell ls @M17NDB@/*.{dir,fst,tbl} @M17NDB@/MIM/*.mim @M17NDB@/FLT/*.flt @M17NDB@/LANGDATA/LANGUAGE.tbl)
DBIMAGE = $(wildcard images/*.png)

IMICONS = $(wildcard @M17NDB@/icons/*.png)

HTML_USR_TARGET = usr/html/index.html usr/html/parrot.png
HTML_JA_TARGET = ja/html/index.html ja/html/parrot.png
HTML_DEV_TARGET = dev/html/index.html dev/html/parrot.png
HTML_TARGET = ${HTML_USR_TARGET} ${HTML_JA_TARGET} ${HTML_DEV_TARGET}

usr-html html-usr: ${HTML_USR_TARGET}
ja-html html-ja: ${HTML_JA_TARGET}
dev-html html-dev: ${HTML_DEV_TARGET}

LATEX_USR_TARGET = usr/latex/m17n-lib.pdf
LATEX_JA_TARGET = ja/latex/m17n-lib.pdf
LATEX_DEV_TARGET = dev/latex/m17n-lib.pdf
LATEX_TARGET = ${LATEX_USR_TARGET} ${LATEX_JA_TARGET} ${LATEX_DEV_TARGET}

usr-latex latex-usr: ${LATEX_USR_TARGET}
ja-latex latex-ja: ${LATEX_JA_TARGET}
dev-latex latex-dev: ${LATEX_DEV_TARGET}

MAN_TARGET = \
	man/man1/m17n-config.1 \
	man/man3/m17nIntro.3m17n \
	man/man5/mdbGeneral.5

usr-man man-usr: ${MAN_TARGET}

TARGET = ${HTML_TARGET} ${LATEX_TARGET} ${MAN_TARGET}

all: usr ja

data:
	[ -d $@ ] || mkdir $@

usr: usr-html usr-latex usr-man
ja: ja-html ja-latex
dev: dev-html dev-latex

html: usr-html ja-html dev-html
latex: usr-latex ja-latex dev-latex
man: usr-man

doxyfile: Makefile
	${DOXYGEN} -g - | \
	  sed -e '/^PROJECT_NAME / s/=.*/= %PROJECT_NAME%/' \
	      -e '/^PROJECT_NUMBER / s/=.*/= %PROJECT_NUMBER%/' \
	      -e '/^OUTPUT_DIRECTORY / s/=.*/= %USR_JA_DEV%/' \
	      -e '/^OUTPUT_LANGUAGE / s/=.*/= %OUTPUT_LANGUAGE%/' \
	      -e '/^FULL_PATH_NAMES / s/=.*/= NO/' \
	      -e '/^OPTIMIZE_OUTPUT_FOR_C / s/=.*/= YES/' \
	      -e '/^MARKDOWN_SUPPORT / s/=.*/= NO/' \
	      -e '/^EXTRACT_ALL / s/=.*/= NO/' \
	      -e '/^SHOW_INCLUDE_FILES / s/=.*/= NO/' \
	      -e '/^SHOW_MEMBER_DOCS / s/=.*/= NO/' \
	      -e '/^ENABLED_SECTIONS / s/=.*/= %ENABLED_SECTIONS%/' \
	      -e '/^SHOW_USED_FILES / s/=.*/= NO/' \
	      -e '/^INPUT / s/=.*/= %INPUT%/' \
	      -e '/^FILE_PATTERNS / s/=.*/= *.c *.txt \\/' \
	      -e '/^EXCLUDE_PATTERNS / s/=.*/= link*.c font-ft.c/' \
	      -e '/^IMAGE_PATH / s/=.*/= images/' \
	      -e '/^INPUT_FILTER / s/=.*/= utils\/%USR_JA_DEV%_filter.sh/' \
	      -e '/^VERBATIM_HEADERS / s/=.*/= NO/' \
	      -e '/^ALPHABETICAL_INDEX / s/=.*/= YES/' \
	      -e '/^IGNORE_PREFIX / s/=.*/= m M/' \
	      -e '/^GENERATE_HTML / s/=.*/= %GENERATE_HTML%/' \
	      -e '/^HTML_FOOTER / s/=.*/= footer.%USR_JA_DEV%.html/' \
	      -e '/^DISABLE_INDEX / s/=.*/= NO/' \
	      -e '/^ENUM_VALUES_PER_LINE / s/=.*/= 1/' \
	      -e '/^GENERATE_LATEX / s/=.*/= %GENERATE_LATEX%/' \
	      -e '/^EXTRA_PACKAGES / s/=.*/= m17n-lib times/' \
	      -e '/^USE_PDFLATEX / s/=.*/= YES/' \
	      -e '/^LATEX_HIDE_INDICES / s/=.*/= YES/' \
	      -e '/^GENERATE_MAN / s/=.*/= %GENERATE_MAN%/' \
	      -e '/^MAN_EXTENSION / s/=.*/= %MAN_EXTENSION%/' \
	      -e '/^PREDEFINED / s/=.*/= FOR_DOXYGEN/' \
	      -e '/^GENERATE_TAGFILE / s/=.*/= m17n.tag/' \
	      -e '/^HIDE_UNDOC_.* / s/=.*/= YES/' \
	      -e '/^TYPEDEF_HIDES_STRUCT / s/=.*/= YES/' \
	      -e '/^DOT_FONTNAME / s/=.*/=/' \
	      -e '/^SORT_MEMBER_DOCS / s/=.*/= NO/' \
	      -e '/^HAVE_DOT / s/=.*/= NO/' \
	      > $@

doxyfile-html: doxyfile ${SRCALL}
	sed -e 's|%PROJECT_NUMBER%|@PACKAGE_VERSION@|' \
	    -e 's|%INPUT%|${SRCALL}|' \
	    -e 's|%GENERATE_HTML%|YES|' \
	    -e 's|%GENERATE_LATEX%|NO|' \
	    -e 's|%GENERATE_MAN%|NO|' \
	    -e 's|%ENABLED_SECTIONS%|FOR_HTML|' \
	  < $< >$@

doxyfile-html.usr: doxyfile-html
	sed -e 's|%PROJECT_NAME%|${PROJECT_NAME_EN}|' \
	    -e 's/%USR_JA_DEV%/usr/g' \
	    -e 's/%OUTPUT_LANGUAGE%/English/' \
	  < $< >$@

doxyfile-html.dev: doxyfile-html
	sed -e 's|%PROJECT_NAME%|${PROJECT_NAME_EN}|' \
	    -e 's/%USR_JA_DEV%/dev/g' \
	    -e 's/%OUTPUT_LANGUAGE%/English/' \
	  < $< >$@

doxyfile-html.ja: doxyfile-html
	sed -e 's|%PROJECT_NAME%|${PROJECT_NAME_JA}|' \
	    -e 's/%USR_JA_DEV%/ja/g' \
	    -e 's/%OUTPUT_LANGUAGE%/Japanese/' \
	  < $< >$@

doxyfile-latex: doxyfile ${SRCALL}
	sed -e 's|%PROJECT_NUMBER%|@PACKAGE_VERSION@|' \
	    -e 's|%INPUT%|${SRCALL}|' \
	    -e 's|%GENERATE_HTML%|NO|' \
	    -e 's|%GENERATE_LATEX%|YES|' \
	    -e 's|%GENERATE_MAN%|NO|' \
	    -e 's|%ENABLED_SECTIONS%|FOR_LATEX|' \
	  < $< >$@

doxyfile-latex.usr: doxyfile-latex
	sed -e 's|%PROJECT_NAME%|${PROJECT_NAME_EN}|' \
	    -e 's/%USR_JA_DEV%/usr/g' \
	    -e 's/%OUTPUT_LANGUAGE%/English/' \
	  < $< >$@

doxyfile-latex.dev: doxyfile-latex
	sed -e 's|%PROJECT_NAME%|${PROJECT_NAME_EN}|' \
	    -e 's/%USR_JA_DEV%/dev/g' \
	    -e 's/%OUTPUT_LANGUAGE%/English/' \
	  < $< >$@

doxyfile-latex.ja: doxyfile-latex
	sed -e 's|%PROJECT_NAME%|${PROJECT_NAME_JA}|' \
	    -e 's/%USR_JA_DEV%/ja/g' \
	    -e 's/%OUTPUT_LANGUAGE%/Japanese/' \
	  < $< >$@

doxyfile-man1tag: doxyfile ${MAN1}
	sed -e 's|%PROJECT_NUMBER%|@PACKAGE_VERSION@|' \
	    -e 's|%INPUT%|${MAN1}|' \
	    -e 's|%GENERATE_HTML%|NO|' \
	    -e 's|%GENERATE_LATEX%|NO|' \
	    -e 's|%GENERATE_MAN%|NO|' \
	    -e 's|%MAN_EXTENSION%|.3m17n|' \
	    -e '/^WARN_IF_DOC_ERROR / s,=.*,= NO,' \
	    -e '/^GENERATE_TAGFILE / s,=.*,= %USR_JA_DEV%/man/man1.tag,' \
	    -e 's|%ENABLED_SECTIONS%|FOR_MAN|' \
	  < $< >$@

doxyfile-man1: doxyfile ${MAN1}
	sed -e 's|%PROJECT_NUMBER%|@PACKAGE_VERSION@|' \
	    -e 's|%INPUT%|${MAN1}|' \
	    -e 's|%GENERATE_HTML%|NO|' \
	    -e 's|%GENERATE_LATEX%|NO|' \
	    -e 's|%GENERATE_MAN%|YES|' \
	    -e 's|%MAN_EXTENSION%|.1|' \
	    -e '/^TAGFILES / s,=.*,= %USR_JA_DEV%/man/man5.tag=../man5,' \
	    -e 's|%ENABLED_SECTIONS%|FOR_MAN|' \
	  < $< >$@

doxyfile-man3tag: doxyfile ${MAN3}
	sed -e 's|%PROJECT_NUMBER%|@PACKAGE_VERSION@|' \
	    -e 's|%INPUT%|${MAN3}|' \
	    -e 's|%GENERATE_HTML%|NO|' \
	    -e 's|%GENERATE_LATEX%|NO|' \
	    -e 's|%GENERATE_MAN%|NO|' \
	    -e 's|%MAN_EXTENSION%|.3m17n|' \
	    -e '/^WARN_IF_DOC_ERROR / s,=.*,= NO,' \
	    -e '/^GENERATE_TAGFILE / s,=.*,= %USR_JA_DEV%/man/man3.tag,' \
	    -e 's|%ENABLED_SECTIONS%|FOR_MAN|' \
	  < $< >$@

doxyfile-man3: doxyfile ${MAN3}
	sed -e 's|%PROJECT_NUMBER%|@PACKAGE_VERSION@|' \
	    -e 's|%INPUT%|${MAN3}|' \
	    -e 's|%GENERATE_HTML%|NO|' \
	    -e 's|%GENERATE_LATEX%|NO|' \
	    -e 's|%GENERATE_MAN%|YES|' \
	    -e 's|%MAN_EXTENSION%|.3m17n|' \
	    -e '/^TAGFILES / s,=.*,= %USR_JA_DEV%/man/man1.tag=../man1 %USR_JA_DEV%/man/man5.tag=../man5,' \
	    -e 's|%ENABLED_SECTIONS%|FOR_MAN|' \
	  < $< >$@

doxyfile-man5tag: doxyfile ${MAN5}
	sed -e 's|%PROJECT_NUMBER%|@PACKAGE_VERSION@|' \
	    -e 's|%INPUT%|${MAN5}|' \
	    -e 's|%GENERATE_HTML%|NO|' \
	    -e 's|%GENERATE_LATEX%|NO|' \
	    -e 's|%GENERATE_MAN%|NO|' \
	    -e 's|%MAN_EXTENSION%|.5|' \
	    -e '/^WARN_IF_DOC_ERROR / s,=.*,= NO,' \
	    -e '/^GENERATE_TAGFILE / s,=.*,= %USR_JA_DEV%/man/man5.tag,' \
	    -e 's|%ENABLED_SECTIONS%|FOR_MAN|' \
	  < $< >$@

doxyfile-man5: doxyfile ${MAN5}
	sed -e 's|%PROJECT_NUMBER%|@PACKAGE_VERSION@|' \
	    -e 's|%INPUT%|${MAN5}|' \
	    -e 's|%GENERATE_HTML%|NO|' \
	    -e 's|%GENERATE_LATEX%|NO|' \
	    -e 's|%GENERATE_MAN%|YES|' \
	    -e 's|%MAN_EXTENSION%|.5|' \
	    -e '/^TAGFILES / s,=.*,= %USR_JA_DEV%/man/man3.tag=../man3,' \
	    -e 's|%ENABLED_SECTIONS%|FOR_MAN|' \
	  < $< >$@

doxyfile-man%.usr: doxyfile-man%
	sed -e 's|%PROJECT_NAME%|${PROJECT_NAME_EN}|' \
	    -e 's/%USR_JA_DEV%/usr/g' \
	    -e 's/%OUTPUT_LANGUAGE%/English/' \
	  < $< >$@

data/exprog.txt: ${EXAMPLE_PROGS} utils/exprog.sh data
	utils/exprog.sh ${EXAMPLE_PROGS} > $@

data/dbdata.txt: ${DBDATA} ${DBIMAGE} @M17NDB@/mdb.dir utils/dbdata.awk utils/dbdata.sh utils/imdoc.c data
	(cd utils; make)
	echo ${prefix}/share/m17n
	 M17NDIR=${prefix}/share/m17n @AWK@ -f utils/dbdata.awk @M17NDB@/mdb.dir > $@

data/dbformat.txt: ${DBFORMAT} utils/dbformat.sh data
	utils/dbformat.sh ${DBFORMAT} > $@

data/dbtutorial.txt: ${DBFORMAT} utils/dbtutorial.sh data
	utils/dbtutorial.sh ${DBFORMAT} > $@

data/m17n-config.txt: @M17NLIB@/m17n-config.in data
	sed -n -e '/\/\*\*\*/,/\*\// p' < $< > $@

data/m17n-db.txt: @M17NDB@/m17n-db.in data
	sed -n -e '/\/\*\*\*/,/\*\// p' < $< > $@

%/html/index.html: doxyfile-html.% header.%.html footer.%.html ${SRCALL} \
		utils/%_filter.sh utils/%_filter.rb m17n-lib.css ${IMICONS}
	rm -f `dirname $@`/*.html
	${DOXYGEN} $<
	[ -d `dirname $@`/icons ] || mkdir `dirname $@`/icons
	cp @M17NDB@/icons/*.png `dirname $@`/icons
	echo 'code { font-weight: bold }' >> `dirname $@`/doxygen.css

%/html/parrot.png: images/parrot.png
	cp $< $@

%/latex/refman.tex: doxyfile-latex.% ${SRCALL} utils/%_filter.rb
#	rm -rf `dirname $@`
	${DOXYGEN} $<

%/latex/m17n-lib.pdf: %/latex/refman.tex styles/m17n-lib.sty utils/latex.sh ${IMICONS}
	[ -d `dirname $@`/icons ] || mkdir `dirname $@`/icons
#	For latex, @image is not used for icons and unichars (image of
#	Unicode characters over U+0100), thus they must be copied here.
	cp -u -r @M17NDB@/icons `dirname $@`
	cp -u -r unichars `dirname $@`
	-utils/latex.sh `dirname $@` @M17NDB@

%/man/man1.tag: doxyfile-man1tag.% ${MAN1} utils/%_filter.rb
	[ -d `dirname $@` ] || mkdir -p `dirname $@`
	${DOXYGEN} $<

%/man/man3.tag: doxyfile-man3tag.% ${MAN3} utils/%_filter.rb
	[ -d `dirname $@` ] || mkdir -p `dirname $@`
	${DOXYGEN} $<

%/man/man5.tag: doxyfile-man5tag.% ${MAN5} utils/%_filter.rb
	[ -d `dirname $@` ] || mkdir -p `dirname $@`
	${DOXYGEN} $<

%/man/man1/m17n-config.1: doxyfile-man1.% ${MAN1} %/man/man5.tag utils/%_filter.rb
	rm -rf `dirname $@`
	cp doxyfile-man1.usr temp
	${DOXYGEN} $<
	cd `dirname $@`; rm -f _*.1 *.c.1 *.txt.1

%/man/man3/m17nIntro.3m17n: doxyfile-man3.% ${MAN3} %/man/man1.tag %/man/man5.tag utils/%_filter.rb
	rm -rf `dirname $@`
	${DOXYGEN} $<

%/man/man5/mdbGeneral.5: doxyfile-man5.% ${MAN5} %/man/man3.tag utils/%_filter.rb
	rm -rf `dirname $@`
	${DOXYGEN} $<

sample/man3/SampleGroup.3: sample.c
	[ -d sample ] || mkdir sample
	[ -d sample/man3 ] || mkdir sample/man3
	-${DOXYGEN} -g doxytemp
	echo "INPUT = sample.c" >> doxytemp
	echo "GENERATE_LATEX = NO" >> doxytemp
	echo "GENERATE_HTML = NO" >> doxytemp
	echo "GENERATE_MAN = YES" >> doxytemp
	echo "MAN_OUTPUT = sample" >> doxytemp
	echo "OPTIMIZE_OUTPUT_FOR_C  = yes" >> doxytemp
	${DOXYGEN} doxytemp
	rm -rf doxytemp

man/man1/%: usr/man/man1/% sample/man3/SampleGroup.3 utils/mkman.rb \
		utils/reform-man.sh
	$(mkinstalldirs) man/man1
	rm -rf doxywork man/man1/*
	LC_ALL=ja_JP.UTF-8 ruby utils/mkman.rb 1 usr/man/man1 man/man1
	utils/reform-man.sh man/man1/*.1

man/man3/%: usr/man/man3/% sample/man3/SampleGroup.3 utils/mkman.rb \
		utils/reform-man.sh
	$(mkinstalldirs) man/man3
	rm -rf doxywork man/man3/*
	LC_ALL=ja_JP.UTF-8 ruby utils/mkman.rb 3m17n usr/man/man3m17n man/man3
	utils/reform-man.sh man/man3/*.3m17n

man/man5/%: usr/man/man5/% sample/man3/SampleGroup.3 utils/mkman.rb \
		utils/reform-man.sh
	$(mkinstalldirs) man/man5
	rm -rf doxywork man/man5/*
	LC_ALL=ja_JP.UTF-8 ruby utils/mkman.rb 5 usr/man/man5 man/man5
	utils/reform-man.sh man/man5/*.5

man/ja/man1/%: ja/man/man1/% sample/man3/SampleGroup.3 utils/mkman.rb 
	$(mkinstalldirs) man/ja/man1
	rm -rf doxywork man/ja/man1/*
	LC_ALL=ja_JP.UTF-8 ruby utils/mkman.rb 1 ja/man/man1 man/ja/man1

man/ja/man3/%: ja/man/man3/% sample/man3/SampleGroup.3 utils/mkman.rb
	$(mkinstalldirs) man/ja/man3
	rm -rf doxywork man/ja/man3/*
	LC_ALL=ja_JP.UTF-8 ruby utils/mkman.rb 3m17n ja/man/man3 man/ja/man3

man/ja/man5/%: ja/man/man5/% sample/man3/SampleGroup.3 utils/mkman.rb 
	$(mkinstalldirs) man/ja/man5
	rm -rf doxywork man/ja/man5/*
	LC_ALL=ja_JP.UTF-8 ruby utils/mkman.rb 5 ja/man/man5 man/ja/man5

CLEANFILES=doxyfile* ${TARGET} data/*.txt *.tar.gz warning *~

clean-local:
	rm -rf unichars usr dev ja man doxywork

dist-tgz: distdir
	for d in usr ja; do \
	  (cd $(distdir)/"$$d"/latex/; \
	   rm -f *8[ch]* *8txt* *.aux *.ttf *.ind *.dvi *.idx *.ilg *.log); \
	done
	tardir=$(distdir) && $(am__tar) | GZIP=$(GZIP_ENV) gzip -c >$(distdir).tar.gz
	$(am__remove_distdir)

WEBDIR = /project/web/extra/m17n-lib

release: dist-tgz
	[ -d ${WEBDIR}/m17n-docs ] || mkdir ${WEBDIR}/m17n-docs
	for f in usr/html/*; do [ -d "$$f" ] || cp "$$f" ${WEBDIR}/m17n-docs; done
	[ -d ${WEBDIR}-ja2/m17n-docs ] || mkdir ${WEBDIR}-ja2/m17n-docs
	for f in ja/html/*; do [ -d "$$f" ] || cp "$$f" ${WEBDIR}-ja2/m17n-docs; done
	[ -d ${WEBDIR}/download ] || mkdir ${WEBDIR}/download
	cp ${distdir}.tar.gz ${WEBDIR}/download


.SECONDARY:

endif

# Local Variables:
# coding: utf-8
# End:
