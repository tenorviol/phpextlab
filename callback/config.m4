dnl config.m4 for extension callback

PHP_ARG_ENABLE(callback, whether to enable callback support,
[  --enable-callback           Enable callback support])

if test "$PHP_CALLBACK" != "no"; then
  PHP_NEW_EXTENSION(callback, callback.c, $ext_shared)
fi
