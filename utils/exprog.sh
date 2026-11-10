#!/bin/sh

cat <<EOF
/* -*- coding: utf-8; -*- */
/***en @page m17nExProg Sample Programs

This section describes these example programs.  They are to demonstrate
the usage of the m17n library, not for practical use.

<ul>
EOF

cat $* | grep '@enpage' | sed -e 's/@enpage \([^ ]*\)/<li> @ref \1 "\1" --/'

cat <<EOF
</ul>
*/
EOF

cat <<EOF
/***ja @page m17nExProg サンプルプログラム

ここでは以下のサンプルプログラムを説明する。これらのプログラムは m17n
ライブラリの使い方を説明するものであり、実際の使用を意図したものではない。

<ul>
EOF

cat $* | grep '@japage' | sed -e 's/@japage \([^ ]*\)/<li> @ref \1 "\1" --/'

cat <<EOF
</ul>
*/
EOF

cat $* | \
sed -n -e '/\/\*\*\*/,/\*\// p' | \
sed -e 's/^ *//' \
    -e 's/@section/@subsection/' \
    -e 's/@..page \([^ ]*\)/@section \1 \1 --/'

# Local Variables:
# coding: utf-8
# End:
