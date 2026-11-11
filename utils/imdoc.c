#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <libgen.h>
#include <sys/stat.h>
#include <unistd.h>
#include <m17n.h>

void
invalid_file (char *filename)
{
  fprintf (stderr, "Invalid input method file: %s\n", filename);
  exit (1);
}

int mt_looking_at (MText *mt, int pos, char *str)
{
  for (int i = 0; ; i++)
    {
      if (str[i] == '\0')
	return pos + i;
      if (mtext_ref_char (mt, pos + i) != str[i])
	break;
    }
  return -1;
}

int mt_insert (MText *mt, int pos, char *str)
{
  int len = strlen (str);
  MText *inserted = mtext_from_data (str, len, MTEXT_FORMAT_UTF_8);
  mtext_ins (mt, pos, inserted);
  pos += mtext_len (inserted);
  m17n_object_unref (inserted);
  return pos;
}

#define INHIBIT_TITLE

int
main (int argc, char **argv)
{
  char *file, *base, *dot;
  char *iconbase = NULL;
  MText *title = NULL;
  MPlist *plist;
  MSymbol language, name, extra = Mnil;
  MText *mt;
  FILE *fp;
  char buf[1024];
  MText *head_comment = NULL;
  MSymbol Minput_method, Mutf8;

  setlocale (LC_ALL, "");
  M17N_INIT ();
  Minput_method = msymbol ("input-method");
  Mutf8 = msymbol ("utf-8");

  if (argc < 2)
    {
      fprintf (stderr, "Usage: imdoc FILE\n");
      exit (1);
    }
  fp = fopen (argv[1], "r");
  if (! fp)
    {
      fprintf (stderr, "Usage: imdoc FILE\n");
      exit (1);
    }

  MConverter *decoder = mconv_buffer_converter (Mcoding_utf_8, buf + 4,
						sizeof (buf) - 4);
  while (fgets (buf, sizeof (buf), fp)
	 && buf[0] != '(')
    {
      if (buf[0] == ';' && buf[1] == ';' && buf[2] == ';'
	  && (buf[3] == ' ' || buf[3] == '\n' || buf[3] == '\0'))
	{
	  if (! head_comment)
	    head_comment = mtext ();
	  if (buf[3] == ' ')
	    {
	      mconv_rebind_buffer (decoder, buf + 4, strlen (buf) - 4);
	      mconv_decode (decoder, head_comment);
	    }
	  else
	    mtext_ins_char (head_comment, mtext_len (head_comment), '\n', 1);
	}
    }
  mconv_free_converter (decoder);
  if (! buf[0])
    invalid_file (argv[1]);
  mt = mtext_from_data (buf, strlen (buf), MTEXT_FORMAT_US_ASCII);
  plist = mplist_deserialize (mt);
  m17n_object_unref (mt);
  if (! plist)
    invalid_file (argv[1]);
  plist = mplist_value (plist);
  if (mplist_value (plist) != Minput_method)
    invalid_file (argv[1]);
  plist = mplist_next (plist);
  language = mplist_value (plist);
  plist = mplist_next (plist);
  name = mplist_value (plist);
  plist = mplist_next (plist);
  if (mplist_key (plist) == Msymbol)
    extra = mplist_value (plist);
  m17n_object_unref (plist);

  file = basename (strdup (argv[1]));
  base = strdup (file);
  dot = strrchr (base, '.');
  if (dot != NULL)
    *dot = '\0';
  fprintf (stderr, "im: %s\n", base);

  if (name != Mnil)
    {
      MPlist *plist;
      plist = minput_get_title_icon (language, name);
      if (plist)
	{
#ifndef INHIBIT_TITLE
	  /* PLIST = ("title text" [ "icon filename" ]) */
	  title = mplist_value (plist);
	  mconv_encode_stream (Mutf8, title, stdout);
#endif
	  plist = mplist_next (plist);
	  if (mplist_key (plist) != Mnil)
	    {
	      MText *icon;
	      char *iconfile;
	      int result;

	      icon = mplist_value (plist);
	      iconfile = mtext_data (icon, MTEXT_FORMAT_US_ASCII,
				     NULL, NULL, NULL);
	      iconbase = basename (strdup (iconfile));
	      dot = strrchr (iconbase, '.');
	      *dot = '\0';
	      /* sprintf (buf, "magick %s -resize x24 icons/%s.png", */
	      /* 	       iconfile, iconbase); */
	      /* result = system (buf); */
	      /* if (result != 0) */
	      /* 	{ */
	      /* 	  fprintf (stderr, "Command fail: %s", buf); */
	      /* 	  iconbase = NULL; */
	      /* 	} */
	    }
	}
      /* Generate a section from base, file, language, name, title, iconbase */
      printf ("@if FOR_HTML\n@subsection %s", base);
      if (iconbase != NULL)
	printf (" <img src=\"icons/%s.png\" style=\"border:1px; height:1.5em; vertical-align:middle;\">&nbsp; %s", iconbase, file);
      printf ("\n@elseif FOR_LATEX\n");
      printf ("@latexonly\n\\subsection{");
      if (iconbase != NULL)
	printf ("\\texorpdfstring{\\img{icons/%s.png}\\:%s}{%s}", iconbase, file, file);
      else
	printf ("%s", file);
      printf ("}@endlatexonly\n@endif\n");
      printf ("@verbatim\n");
      if (language != Mt)
	{
	  MSymbol langname = mlanguage_name (language);
	  printf ("language:%s", msymbol_name (language));
	  if (langname != Mnil)
	    printf (" (%s)",msymbol_name (langname));
	}
      else
	printf ("language: generic");
      printf (" name:%s",msymbol_name (name));
#ifndef INHIBIT_TITLE
      if (title != null)
	{
	  printf (" title:\"");
	  mconv_encode_stream (Mutf8, title, stdout);
	  printf ("\"");
	}
#endif
      printf ("\n@endverbatim\n");
    }
  else if (extra != Mnil)
    {
      printf ("@subsection %s %s\nextra-name:%s, only for inclusion\n",
	      base, file, msymbol_name (extra));
      language = extra;
    }
  else
    {
      fprintf (stderr, "invalid input method: %s", argv[1]);
      exit (1);
    }

  mt = head_comment;
  if (! mt)
    mt = minput_get_description (language, name);
  if (! mt)
    {
      printf ("Not yet officially released.\n");
      exit (0);
    }
  else
    {
      MText *copy = mtext_dup (mt);
      int len = mtext_len (mt), i, c, pos;
      int beg;
      MConverter *encoder = mconv_stream_converter (Mutf8, stdout);
      char *magick = "magick -background white -fill black -font \"Noto Sans\" -pointsize 32 pango:";
      char *unichars_dir = "unichars/";
      struct stat st;

      if (stat (unichars_dir, &st) != 0
	  && mkdir (unichars_dir, 0755) != 0)
	{
	  fprintf (stderr, "Making of directory %s failed\n", unichars_dir);
	  M17N_FINI ();
	  exit (1);
	}

      if (mtext_ref_char (mt, len - 1) != '\n')
	{
	  mtext_ins_char (mt, len, '\n', 1);
	  len++;
	}
      printf ("@if FOR_HTML\n<pre>");
      for (i = 0; (c = mtext_ref_char (mt, i)) >= 0; i++)
	{
	  if (c == '#')
	    {
	      mtext_ins_char (mt, i, '@', 1);
	      i++;
	    }
	  else if (c == '/' && mtext_ref_char (mt, i + 1) == '*')
	    {
	      i++;
	      i = mt_insert (mt, i, "​") - 1;
	    }
	  else if (c == '@'
		   && (i == 0 || mtext_ref_char (mt, i - 1) == '\n')
		   && mt_looking_at (mt, i, "@image") > i)
	    {
	      i = mt_insert (mt, i, "</pre>");
	      while ((c = mtext_ref_char (mt, i)) >= 0 && c != '\n') i++;
	      i = mt_insert (mt, i, "\n<pre>") - 1;
	    }
	}
      mconv_encode (encoder, mt);
      printf ("</pre>@endif\n");
      mt = copy;
      mconv_reset_converter (encoder);
      printf ("@if FOR_LATEX\n@latexonly\n\\begin{alltt}\n");
      i = beg = 0;
      while ((c = mtext_ref_char (mt, i)) >= 0)
	{
	  if (c == '`' || c == '^' || c == '\\' || c == '{' || c == '}')
	    {
	      mtext_del (mt, i, i + 1);
	      sprintf (buf, "\\char\"%02X\\/", c);
	      i = mt_insert (mt, i, buf);
	    }
	  else if ((i == 0 || mtext_ref_char (mt, i - 1) == '\n')
		   && (pos = mt_looking_at (mt, i, "@image ")) > i)
	    {
	      if ((pos = mt_looking_at (mt, pos, "html")) > i)
		{
		  /* The line "@image html ..." should be just skipped. */
		  for (; pos < len; pos++)
		    {
		      if ((c = mtext_ref_char (mt, pos)) == '\n')
			{
			  pos++;
			  break;
			}
		      else if (c < 0)
			break;
		    }
		  mtext_del (mt, i, pos);
		}
	      else
		{
		  /* The line "@image latex ..." should be treated outside of
		     alltt environment. */
		  i = mt_insert (mt, i, "\\end{alltt}@endlatexonly\n");
		  /* skip to the next line (it is assured that \n is found) */
		  i = mtext_character (mt, i, mtext_len (mt), '\n') + 1;
		  i = mt_insert (mt, i, "@latexonly\\begin{alltt}\n");
		}
	    }
	  else if (c >= 0x100 || c == 0xA8) // '¨'
	    {
	      /* Generate an image file for the sequence of characters (>=
		 U+0100). */
	      int beg = i;
	      char *cmd, *fname;
	      int nchars, nbytes;
	      char *utf8beg, *utf8end;
	      int result;

	      utf8beg = (char *) mtext_data (mt, NULL, NULL, &i, NULL);
	      for (i++; mtext_ref_char (mt, i) >= 0x100; i++);
	      utf8end = (char *) mtext_data (mt, NULL, NULL, &i, NULL);
	      nchars = i - beg;

	      /* fname = "unichars/XXX[-XXX]*.png" (max length of X.. is 6 */
	      /* cmd = magick + UTF8BYTES + ' ' + fname */
	      int before_fname = strlen (magick) + (utf8end - utf8beg) + 1;
	      cmd = malloc (before_fname
			    + strlen (unichars_dir) + (nchars * 7 - 1) + 4 + 1);
	      sprintf (cmd, "%s", magick);
	      memcpy (cmd + strlen (magick), utf8beg, utf8end - utf8beg);
	      cmd[before_fname - 1] = ' ';
	      fname = cmd + before_fname;
	      nbytes = sprintf (fname, "%s%X", unichars_dir, c);
	      for (int j = beg + 1; j < i; j++)
		{
		  c = mtext_ref_char (mt, j);
		  nbytes += sprintf (fname + nbytes, "+%X", c);
		}
	      sprintf (fname + nbytes, ".png");
	      if (stat (fname, &st) != 0)
		{
		  result = system (cmd);
		  if (result != 0 || stat (fname, &st) != 0)
		    {
		      fprintf (stderr, "command failure: %s\n", cmd);
		      exit (1);
		    }
		}
	      fname[nbytes] = '\0'; /* truncate ".png" part */
	      fname += strlen (unichars_dir); /* skip the first "unichars/" */
	      sprintf (buf, "\\uni{%s}", fname);
	      mtext_del (mt, beg, i);
	      i = mt_insert (mt, beg, buf);
	      free (cmd);
	    }
	  else
	    i++;
	}
      mconv_encode (encoder, mt);
      printf ("\\end{alltt}@endlatexonly\n");
      printf ("@endif\n");
      mconv_free_converter (encoder);
    }

  M17N_FINI ();
  exit (0);
}
