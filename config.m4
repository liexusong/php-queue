dnl $Id$
dnl config.m4 for extension queue

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(queue, for queue support,
dnl Make sure that the comment is aligned:
dnl [  --with-queue             Include queue support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(queue, whether to enable queue support,
dnl Make sure that the comment is aligned:
dnl [  --enable-queue           Enable queue support])

if test "$PHP_QUEUE" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-queue -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/queue.h"  # you most likely want to change this
  dnl if test -r $PHP_QUEUE/$SEARCH_FOR; then # path given as parameter
  dnl   QUEUE_DIR=$PHP_QUEUE
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for queue files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       QUEUE_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$QUEUE_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the queue distribution])
  dnl fi

  dnl # --with-queue -> add include path
  dnl PHP_ADD_INCLUDE($QUEUE_DIR/include)

  dnl # --with-queue -> check for lib and symbol presence
  dnl LIBNAME=queue # you may want to change this
  dnl LIBSYMBOL=queue # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $QUEUE_DIR/$PHP_LIBDIR, QUEUE_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_QUEUELIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong queue lib version or lib not found])
  dnl ],[
  dnl   -L$QUEUE_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(QUEUE_SHARED_LIBADD)

  PHP_NEW_EXTENSION(queue, queue.c, $ext_shared)
fi
