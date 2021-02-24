#!/bin/bash

TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
SRCDIR=${SRCDIR:-$TOPDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

herbstersD=${herbstersD:-$SRCDIR/herbstersd}
herbstersCLI=${herbstersCLI:-$SRCDIR/herbsters-cli}
herbstersTX=${herbstersTX:-$SRCDIR/herbsters-tx}
herbstersQT=${herbstersQT:-$SRCDIR/qt/herbsters-qt}

[ ! -x $herbstersD ] && echo "$herbstersD not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
HERBSVER=($($herbstersCLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }'))

# Create a footer file with copyright content.
# This gets autodetected fine for herbstersd if --version-string is not set,
# but has different outcomes for herbsters-qt and herbsters-cli.
echo "[COPYRIGHT]" > footer.h2m
$herbstersD --version | sed -n '1!p' >> footer.h2m

for cmd in $herbstersD $herbstersCLI $herbstersTX $herbstersQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${HERBSVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${HERBSVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m