//******************************************************************************
//*                                  uBee512                                   *
//*       An emulator for the Microbee Z80 ROM, FDD and HDD based models       *
//*                                                                            *
//*                              getopt module                                 *
//*                                                                            *
//*                       Copyright (C) 2007-2024 uBee                         *
//******************************************************************************
//
// A modified getopt version made from the glibc-2.7/posix source library.
//
// Copyright (C) 1987,88,89,90,91,92,93,94,95,96,98,99,2000,2001,2002,2003,2004
// Free Software Foundation, Inc.
//
//==============================================================================
/*
 *  uBee512 - An emulator for the Microbee Z80 ROM, FDD and HDD based models.
 *  Copyright (C) 2007-2024 uBee   
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
//==============================================================================
// ChangeLog (most recent entries are at top)
//==============================================================================
// v3.1.0 - 6 November 2008, uBee
// - Need to have a version of getopt with no out putting of error messages,
//   instead error messages are returned in a new variable opterr_msg.
// - All getopt() functions have been prepended with 'x'.  The local
//   getopt.h header which also includes getopt_int.h must be used.
// - Added xgetopt_init() for each new set of argv data.
// - Stripped out various parts of the original code that were not relevant.
//   #include config.h, TEST, gettext(msgid), _LIBC specific code.
// - The relavant parts of the getopt1.c have been appened to the end of
//   this file.
// - The getopt_init.c file is not required.
//==============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#ifdef VMS
# include <unixlib.h>
#endif

#ifndef attribute_hidden
# define attribute_hidden
#endif

/* This version of `getopt' appears to the caller like standard Unix `getopt'
   but it behaves differently for the user, since it allows the user
   to intersperse the options with the other arguments.

   As `getopt' works, it permutes the elements of ARGV so that,
   when it is done, all the options precede everything else.  Thus
   all application programs are extended to handle flexible argument order.

   Setting the environment variable POSIXLY_CORRECT disables permutation.
   Then the behavior is completely standard.

   GNU application programs can use a third alternative mode in which
   they can distinguish the relative order of options and other arguments.  */

#include "getopt.h"

/* For communication from `getopt' to the caller.
   When `getopt' finds an option that takes an argument,
   the argument value is returned here.
   Also, when `ordering' is RETURN_IN_ORDER,
   each non-option ARGV-element is returned here.  */

char *optarg;

/* Index in ARGV of the next element to be scanned.
   This is used for communication to and from the caller
   and for communication between successive calls to `getopt'.

   On entry to `getopt', zero means this is the first call; initialize.

   When `getopt' returns -1, this is the index of the first of the
   non-option elements that the caller should itself scan.

   Otherwise, `optind' communicates from one call to the next
   how much of ARGV has been scanned so far.  */

/* 1003.2 says this must be 1 before any call.  */
int optind = 1;

/* Callers store zero here to inhibit the error message
   for unrecognized options.  */

int opterr = 1;

/* Set to an option character which was unrecognized.
   This must be initialized on some systems to avoid linking in the
   system's own getopt implementation.  */

int optopt = '?';

/* My error variable addition, all fprintf() calls replaced with snprintf()
   that sets this variable equal to the error message - uBee 25/10/08 */

char opterr_msg[512];

/* Keep a global copy of all internal members of getopt_data.  */

static struct _getopt_data getopt_data;

#define SWAP_FLAGS(ch1, ch2)

/* Initialise the data for a new argv list - uBee 26/10/08
   This is called before each new line of options are to be processed. */
void xgetopt_init (void)
{
 optarg = NULL;
 optind = 1;
 opterr = 1;
 optopt = '?';
 memset(&getopt_data, 0, sizeof(getopt_data));
}

/* Exchange two adjacent subsequences of ARGV.
   One subsequence is elements [first_nonopt,last_nonopt)
   which contains all the non-options that have been skipped so far.
   The other is elements [last_nonopt,optind), which contains all
   the options processed since those non-options were skipped.

   `first_nonopt' and `last_nonopt' are relocated so that they describe
   the new indices of the non-options in ARGV after they are moved.  */

static void
exchange (char **argv, struct _getopt_data *d)
{
  int bottom = d->__first_nonopt;
  int middle = d->__last_nonopt;
  int top = d->optind;
  char *tem;

  /* Exchange the shorter segment with the far end of the longer segment.
     That puts the shorter segment into the right place.
     It leaves the longer segment in the right place overall,
     but it consists of two parts that need to be swapped next.  */

  while (top > middle && middle > bottom)
    {
      if (top - middle > middle - bottom)
        {
          /* Bottom segment is the short one.  */
          int len = middle - bottom;
          register int i;

          /* Swap it with the top part of the top segment.  */
          for (i = 0; i < len; i++)
            {
              tem = argv[bottom + i];
              argv[bottom + i] = argv[top - (middle - bottom) + i];
              argv[top - (middle - bottom) + i] = tem;
              SWAP_FLAGS (bottom + i, top - (middle - bottom) + i);
            }
          /* Exclude the moved bottom segment from further swapping.  */
          top -= len;
        }
      else
        {
          /* Top segment is the short one.  */
          int len = top - middle;
          register int i;

          /* Swap it with the bottom part of the bottom segment.  */
          for (i = 0; i < len; i++)
            {
              tem = argv[bottom + i];
              argv[bottom + i] = argv[middle + i];
              argv[middle + i] = tem;
              SWAP_FLAGS (bottom + i, middle + i);
            }
          /* Exclude the moved top segment from further swapping.  */
          bottom += len;
        }
    }

  /* Update records for the slots the non-options now occupy.  */

  d->__first_nonopt += (d->optind - d->__last_nonopt);
  d->__last_nonopt = d->optind;
}

/* Initialize the internal data when the first call is made.  */

static const char *
_getopt_initialize (int argc, char *const *argv, const char *optstring,
                    struct _getopt_data *d)
{
  /* Start processing options with ARGV-element 1 (since ARGV-element 0
     is the program name); the sequence of previously skipped
     non-option ARGV-elements is empty.  */

  d->__first_nonopt = d->__last_nonopt = d->optind;

  d->__nextchar = NULL;

  d->__posixly_correct = !!getenv ("POSIXLY_CORRECT");

  /* Determine how to handle the ordering of options and nonoptions.  */

  if (optstring[0] == '-')
    {
      d->__ordering = RETURN_IN_ORDER;
      ++optstring;
    }
  else if (optstring[0] == '+')
    {
      d->__ordering = REQUIRE_ORDER;
      ++optstring;
    }
  else if (d->__posixly_correct)
    d->__ordering = REQUIRE_ORDER;
  else
    d->__ordering = PERMUTE;

  return optstring;
}
/* Scan elements of ARGV (whose length is ARGC) for option characters
   given in OPTSTRING.

   If an element of ARGV starts with '-', and is not exactly "-" or "--",
   then it is an option element.  The characters of this element
   (aside from the initial '-') are option characters.  If `getopt'
   is called repeatedly, it returns successively each of the option characters
   from each of the option elements.

   If `getopt' finds another option character, it returns that character,
   updating `optind' and `nextchar' so that the next call to `getopt' can
   resume the scan with the following option character or ARGV-element.

   If there are no more option characters, `getopt' returns -1.
   Then `optind' is the index in ARGV of the first ARGV-element
   that is not an option.  (The ARGV-elements have been permuted
   so that those that are not options now come last.)

   OPTSTRING is a string containing the legitimate option characters.
   If an option character is seen that is not listed in OPTSTRING,
   return '?' after printing an error message.  If you set `opterr' to
   zero, the error message is suppressed but we still return '?'.

   If a char in OPTSTRING is followed by a colon, that means it wants an arg,
   so the following text in the same ARGV-element, or the text of the following
   ARGV-element, is returned in `optarg'.  Two colons mean an option that
   wants an optional arg; if there is text in the current ARGV-element,
   it is returned in `optarg', otherwise `optarg' is set to zero.

   If OPTSTRING starts with `-' or `+', it requests different methods of
   handling the non-option ARGV-elements.
   See the comments about RETURN_IN_ORDER and REQUIRE_ORDER, above.

   Long-named options begin with `--' instead of `-'.
   Their names may be abbreviated as long as the abbreviation is unique
   or is an exact match for some defined option.  If they have an
   argument, it follows the option name in the same ARGV-element, separated
   from the option name by a `=', or else the in next ARGV-element.
   When `getopt' finds a long-named option, it returns 0 if that option's
   `flag' field is nonzero, the value of the option's `val' field
   if the `flag' field is zero.

   The elements of ARGV aren't really const, because we permute them.
   But we pretend they're const in the prototype to be compatible
   with other systems.

   LONGOPTS is a vector of `struct option' terminated by an
   element containing a name which is zero.

   LONGIND returns the index in LONGOPT of the long-named option found.
   It is only valid when a long-named option has been found by the most
   recent call.

   If LONG_ONLY is nonzero, '-' as well as '--' can introduce
   long-named options.  */

int
_getopt_internal_r (int argc, char *const *argv, const char *optstring,
                    const struct option *longopts, int *longind,
                    int long_only, struct _getopt_data *d)
{
  int print_errors = d->opterr;

  /* clear the error string - uBee 25/10/08 */
  opterr_msg[0] = 0;

  if (optstring[0] == ':')
    print_errors = 0;

  if (argc < 1)
    return -1;

  d->optarg = NULL;

  if (d->optind == 0 || !d->__initialized)
    {
      if (d->optind == 0)
        d->optind = 1;  /* Don't scan ARGV[0], the program name.  */
      optstring = _getopt_initialize (argc, argv, optstring, d);
      d->__initialized = 1;
    }

  /* Test whether ARGV[optind] points to a non-option argument.
     Either it does not have option syntax, or there is an environment flag
     from the shell indicating it is not an option.  The later information
     is only used when the used in the GNU libc.  */
# define NONOPTION_P (argv[d->optind][0] != '-' || argv[d->optind][1] == '\0')

  if (d->__nextchar == NULL || *d->__nextchar == '\0')
    {
      /* Advance to the next ARGV-element.  */

      /* Give FIRST_NONOPT & LAST_NONOPT rational values if OPTIND has been
         moved back by the user (who may also have changed the arguments).  */
      if (d->__last_nonopt > d->optind)
        d->__last_nonopt = d->optind;
      if (d->__first_nonopt > d->optind)
        d->__first_nonopt = d->optind;

      if (d->__ordering == PERMUTE)
        {
          /* If we have just processed some options following some non-options,
             exchange them so that the options come first.  */

          if (d->__first_nonopt != d->__last_nonopt
              && d->__last_nonopt != d->optind)
            exchange ((char **) argv, d);
          else if (d->__last_nonopt != d->optind)
            d->__first_nonopt = d->optind;

          /* Skip any additional non-options
             and extend the range of non-options previously skipped.  */

          while (d->optind < argc && NONOPTION_P)
            d->optind++;
          d->__last_nonopt = d->optind;
        }

      /* The special ARGV-element `--' means premature end of options.
         Skip it like a null option,
         then exchange with previous non-options as if it were an option,
         then skip everything else like a non-option.  */

      if (d->optind != argc && !strcmp (argv[d->optind], "--"))
        {
          d->optind++;

          if (d->__first_nonopt != d->__last_nonopt
              && d->__last_nonopt != d->optind)
            exchange ((char **) argv, d);
          else if (d->__first_nonopt == d->__last_nonopt)
            d->__first_nonopt = d->optind;
          d->__last_nonopt = argc;

          d->optind = argc;
        }

      /* If we have done all the ARGV-elements, stop the scan
         and back over any non-options that we skipped and permuted.  */

      if (d->optind == argc)
        {
          /* Set the next-arg-index to point at the non-options
             that we previously skipped, so the caller will digest them.  */
          if (d->__first_nonopt != d->__last_nonopt)
            d->optind = d->__first_nonopt;
          return -1;
        }

      /* If we have come to a non-option and did not permute it,
         either stop the scan or describe it to the caller and pass it by.  */

      if (NONOPTION_P)
        {
          if (d->__ordering == REQUIRE_ORDER)
            return -1;
          d->optarg = argv[d->optind++];
          return 1;
        }

      /* We have found another option-ARGV-element.
         Skip the initial punctuation.  */

      d->__nextchar = (argv[d->optind] + 1
                  + (longopts != NULL && argv[d->optind][1] == '-'));
    }

  /* Decode the current option-ARGV-element.  */

  /* Check whether the ARGV-element is a long option.

     If long_only and the ARGV-element has the form "-f", where f is
     a valid short option, don't consider it an abbreviated form of
     a long option that starts with f.  Otherwise there would be no
     way to give the -f short option.

     On the other hand, if there's a long option "fubar" and
     the ARGV-element is "-fu", do consider that an abbreviation of
     the long option, just like "--fu", and not "-f" with arg "u".

     This distinction seems to be the most useful approach.  */

  if (longopts != NULL
      && (argv[d->optind][1] == '-'
          || (long_only && (argv[d->optind][2]
                            || !strchr (optstring, argv[d->optind][1])))))
    {
      char *nameend;
      const struct option *p;
      const struct option *pfound = NULL;
      int exact = 0;
      int ambig = 0;
      int indfound = -1;
      int option_index;

      for (nameend = d->__nextchar; *nameend && *nameend != '='; nameend++)
        /* Do nothing.  */ ;

      /* Test all long options for either exact match
         or abbreviated matches.  */
      for (p = longopts, option_index = 0; p->name; p++, option_index++)
        if (!strncmp (p->name, d->__nextchar, nameend - d->__nextchar))
          {
            if ((unsigned int) (nameend - d->__nextchar)
                == (unsigned int) strlen (p->name))
              {
                /* Exact match found.  */
                pfound = p;
                indfound = option_index;
                exact = 1;
                break;
              }
            else if (pfound == NULL)
              {
                /* First nonexact match found.  */
                pfound = p;
                indfound = option_index;
              }
            else if (long_only
                     || pfound->has_arg != p->has_arg
                     || pfound->flag != p->flag
                     || pfound->val != p->val)
              /* Second or later nonexact match found.  */
              ambig = 1;
          }

      if (ambig && !exact)
        {
          if (print_errors)
            {
              snprintf(opterr_msg, sizeof(opterr_msg), "%s: option `%s' is ambiguous\n",
              argv[0], argv[d->optind]);
            }
          d->__nextchar += strlen (d->__nextchar);
          d->optind++;
          d->optopt = 0;
          return '?';
        }

      if (pfound != NULL)
        {
          option_index = indfound;
          d->optind++;
          if (*nameend)
            {
              /* Don't test has_arg with >, because some C compilers don't
                 allow it to be used on enums.  */
              if (pfound->has_arg)
                d->optarg = nameend + 1;
              else
                {
                  if (print_errors)
                    {
                      if (argv[d->optind - 1][1] == '-')
                        {
                          /* --option */
                          snprintf(opterr_msg, sizeof(opterr_msg), "%s: option `--%s' doesn't allow an argument\n",
                          argv[0], pfound->name);
                        }
                      else
                        {
                          /* +option or -option */
                          snprintf(opterr_msg, sizeof(opterr_msg), "%s: option `%c%s' doesn't allow an argument\n",
                          argv[0], argv[d->optind - 1][0], pfound->name);
                        }
                    }

                  d->__nextchar += strlen (d->__nextchar);

                  d->optopt = pfound->val;
                  return '?';
                }
            }
          else if (pfound->has_arg == 1)
            {
              if (d->optind < argc)
                d->optarg = argv[d->optind++];
              else
                {
                  if (print_errors)
                    {
                      snprintf(opterr_msg, sizeof(opterr_msg), "%s: option `%s' requires an argument\n",
                      argv[0], argv[d->optind - 1]);
                    }
                  d->__nextchar += strlen (d->__nextchar);
                  d->optopt = pfound->val;
                  return optstring[0] == ':' ? ':' : '?';
                }
            }
          d->__nextchar += strlen (d->__nextchar);
          if (longind != NULL)
            *longind = option_index;
          if (pfound->flag)
            {
              *(pfound->flag) = pfound->val;
              return 0;
            }
          return pfound->val;
        }

      /* Can't find it as a long option.  If this is not getopt_long_only,
         or the option starts with '--' or is not a valid short
         option, then it's an error.
         Otherwise interpret it as a short option.  */
      if (!long_only || argv[d->optind][1] == '-'
          || strchr (optstring, *d->__nextchar) == NULL)
        {
          if (print_errors)
            {
              if (argv[d->optind][1] == '-')
                {
                  /* --option */
                  snprintf(opterr_msg, sizeof(opterr_msg), "%s: unrecognized option `--%s'\n",
                  argv[0], d->__nextchar);
                }
              else
                {
                  /* +option or -option */
                  snprintf(opterr_msg, sizeof(opterr_msg), "%s: unrecognized option `%c%s'\n",
                  argv[0], argv[d->optind][0], d->__nextchar);
                }
            }
          d->__nextchar = (char *) "";
          d->optind++;
          d->optopt = 0;
          return '?';
        }
    }

  /* Look at and handle the next short option-character.  */

  {
    char c = *d->__nextchar++;
    char *temp = strchr (optstring, c);

    /* Increment `optind' when we start to process its last character.  */
    if (*d->__nextchar == '\0')
      ++d->optind;

    if (temp == NULL || c == ':')
      {
        if (print_errors)
          {
            if (d->__posixly_correct)
              {
                /* 1003.2 specifies the format of this message.  */
                snprintf(opterr_msg, sizeof(opterr_msg), "%s: illegal option -- %c\n", argv[0], c);
              }
            else
              {
                snprintf(opterr_msg, sizeof(opterr_msg), "%s: invalid option -- %c\n", argv[0], c);
              }
          }
        d->optopt = c;
        return '?';
      }
    /* Convenience. Treat POSIX -W foo same as long option --foo */
    if (temp[0] == 'W' && temp[1] == ';')
      {
        char *nameend;
        const struct option *p;
        const struct option *pfound = NULL;
        int exact = 0;
        int ambig = 0;
        int indfound = 0;
        int option_index;

        /* This is an option that requires an argument.  */
        if (*d->__nextchar != '\0')
          {
            d->optarg = d->__nextchar;
            /* If we end this ARGV-element by taking the rest as an arg,
               we must advance to the next element now.  */
            d->optind++;
          }
        else if (d->optind == argc)
          {
            if (print_errors)
              {
                /* 1003.2 specifies the format of this message.  */
                snprintf(opterr_msg, sizeof(opterr_msg), "%s: option requires an argument -- %c\n",
                argv[0], c);
              }
            d->optopt = c;
            if (optstring[0] == ':')
              c = ':';
            else
              c = '?';
            return c;
          }
        else
          /* We already incremented `d->optind' once;
             increment it again when taking next ARGV-elt as argument.  */
          d->optarg = argv[d->optind++];

        /* optarg is now the argument, see if it's in the
           table of longopts.  */

        for (d->__nextchar = nameend = d->optarg; *nameend && *nameend != '=';
             nameend++)
          /* Do nothing.  */ ;

        /* Test all long options for either exact match
           or abbreviated matches.  */
        for (p = longopts, option_index = 0; p->name; p++, option_index++)
          if (!strncmp (p->name, d->__nextchar, nameend - d->__nextchar))
            {
              if ((unsigned int) (nameend - d->__nextchar) == strlen (p->name))
                {
                  /* Exact match found.  */
                  pfound = p;
                  indfound = option_index;
                  exact = 1;
                  break;
                }
              else if (pfound == NULL)
                {
                  /* First nonexact match found.  */
                  pfound = p;
                  indfound = option_index;
                }
              else
                /* Second or later nonexact match found.  */
                ambig = 1;
            }
        if (ambig && !exact)
          {
            if (print_errors)
              {
                snprintf(opterr_msg, sizeof(opterr_msg), "%s: option `-W %s' is ambiguous\n",
                argv[0], argv[d->optind]);
              }
            d->__nextchar += strlen (d->__nextchar);
            d->optind++;
            return '?';
          }
        if (pfound != NULL)
          {
            option_index = indfound;
            if (*nameend)
              {
                /* Don't test has_arg with >, because some C compilers don't
                   allow it to be used on enums.  */
                if (pfound->has_arg)
                  d->optarg = nameend + 1;
                else
                  {
                    if (print_errors)
                      {
                        snprintf(opterr_msg, sizeof(opterr_msg), "%s: option `-W %s' doesn't allow an argument\n",
                        argv[0], pfound->name);
                      }

                    d->__nextchar += strlen (d->__nextchar);
                    return '?';
                  }
              }
            else if (pfound->has_arg == 1)
              {
                if (d->optind < argc)
                  d->optarg = argv[d->optind++];
                else
                  {
                    if (print_errors)
                      {
                        snprintf(opterr_msg, sizeof(opterr_msg), "%s: option `%s' requires an argument\n",
                        argv[0], argv[d->optind - 1]);
                      }
                    d->__nextchar += strlen (d->__nextchar);
                    return optstring[0] == ':' ? ':' : '?';
                  }
              }
            d->__nextchar += strlen (d->__nextchar);
            if (longind != NULL)
              *longind = option_index;
            if (pfound->flag)
              {
                *(pfound->flag) = pfound->val;
                return 0;
              }
            return pfound->val;
          }
          d->__nextchar = NULL;
          return 'W';   /* Let the application handle it.   */
      }
    if (temp[1] == ':')
      {
        if (temp[2] == ':')
          {
            /* This is an option that accepts an argument optionally.  */
            if (*d->__nextchar != '\0')
              {
                d->optarg = d->__nextchar;
                d->optind++;
              }
            else
              d->optarg = NULL;
            d->__nextchar = NULL;
          }
        else
          {
            /* This is an option that requires an argument.  */
            if (*d->__nextchar != '\0')
              {
                d->optarg = d->__nextchar;
                /* If we end this ARGV-element by taking the rest as an arg,
                   we must advance to the next element now.  */
                d->optind++;
              }
            else if (d->optind == argc)
              {
                if (print_errors)
                  {
                    /* 1003.2 specifies the format of this message.  */
                    snprintf(opterr_msg, sizeof(opterr_msg), "%s: option requires an argument -- %c\n",
                    argv[0], c);
                  }
                d->optopt = c;
                if (optstring[0] == ':')
                  c = ':';
                else
                  c = '?';
              }
            else
              /* We already incremented `optind' once;
                 increment it again when taking next ARGV-elt as argument.  */
              d->optarg = argv[d->optind++];
            d->__nextchar = NULL;
          }
      }
    return c;
  }
}

int
_getopt_internal (int argc, char *const *argv, const char *optstring,
                  const struct option *longopts, int *longind, int long_only)
{
  int result;

  getopt_data.optind = optind;
  getopt_data.opterr = opterr;

  result = _getopt_internal_r (argc, argv, optstring, longopts,
                               longind, long_only, &getopt_data);

  optind = getopt_data.optind;
  optarg = getopt_data.optarg;
  optopt = getopt_data.optopt;

  return result;
}

int
xgetopt (int argc, char *const *argv, const char *optstring)
{
  return _getopt_internal (argc, argv, optstring,
                           (const struct option *) 0,
                           (int *) 0,
                           0);
}

int
xgetopt_long (int argc, char *const *argv, const char *options,
              const struct option *long_options, int *opt_index)
{
  return _getopt_internal (argc, argv, options, long_options, opt_index, 0);
}

int
_getopt_long_r (int argc, char *const *argv, const char *options,
                const struct option *long_options, int *opt_index,
                struct _getopt_data *d)
{
  return _getopt_internal_r (argc, argv, options, long_options, opt_index,
                             0, d);
}

/* Like getopt_long, but '-' as well as '--' can indicate a long option.
   If an option that starts with '-' (not '--') doesn't match a long option,
   but does match a short option, it is parsed as a short option
   instead.  */

int
xgetopt_long_only (int argc, char *const *argv, const char *options,
                   const struct option *long_options, int *opt_index)
{
  return _getopt_internal (argc, argv, options, long_options, opt_index, 1);
}

int
_getopt_long_only_r (int argc, char *const *argv, const char *options,
                     const struct option *long_options, int *opt_index,
                     struct _getopt_data *d)
{
  return _getopt_internal_r (argc, argv, options, long_options, opt_index,
                             1, d);
}
