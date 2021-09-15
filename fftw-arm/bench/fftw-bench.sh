#!/bin/sh
for TYPE in 'c' 'r'; do
  for PLACE in 'i' 'o'; do
    echo "$TYPE $PLACE 1-D powers of two"
    for SIZE in '2' '4' '8' '16' '32' '64' '128' '256' '512' '1024' '2048' '4096' \
                '8192' '16384' '32768' '65536' '131072' '262144' '524288' '1048576' '2097152'; do
      ./bench $OPTS ${PLACE}${TYPE}${SIZE}
    done
  done
  for PLACE in 'i' 'o'; do
    echo "$TYPE $PLACE 1-D non-powers of two"
    for SIZE in '6' '9' '12' '15' '18' '24' '36' '80' '108' '210' '504' '1000' '1960' \
                '4725' '10368' '27000' '75600' '165375' '362880' '1562500'; do
      ./bench $OPTS ${PLACE}${TYPE}${SIZE}
    done
  done
  for PLACE in 'i' 'o'; do
    echo "$TYPE $PLACE 2-D powers of two"
    for SIZE in '4x4' '8x4' '4x8' '8x8' '16x16' '32x32' '64x64' '16x512' '128x64' '128x128' \
                '256x128' '512x64' '64x1024' '256x256' '512x512' '1024x1024' '2048x2048'; do
      ./bench $OPTS ${PLACE}${TYPE}${SIZE}
    done
  done
  for PLACE in 'i' 'o'; do
    echo "$TYPE $PLACE 2-D non-powers of two"
    for SIZE in '5x5' '6x6' '7x7' '9x9' '10x10' '11x11' '12x12' '13x13' '14x14' '15x15' '25x24' \
                '48x48' '49x49' '60x60' '72x56' '75x75' '80x80' '84x84' '96x96' '100x100' '105x105' \
                '112x112' '120x120' '144x144' '180x180' '240x240' '360x360' '1000x1000' '1050x1050' \
                '1458x1458' '1960x1960'; do
      ./bench $OPTS ${PLACE}${TYPE}${SIZE}
    done
  done
  for PLACE in 'i' 'o'; do
    echo "$TYPE $PLACE 3-D powers of two"
    for SIZE in '4x4x4' '8x8x8' '4x8x16' '16x16x16' '32x32x32' '64x64x64' '256x64x32' '16x1024x64' '128x128x128'; do
      ./bench $OPTS ${PLACE}${TYPE}${SIZE}
    done
  done
  for PLACE in 'i' 'o'; do
    echo "$TYPE $PLACE 3-D non-powers of two"
    for SIZE in '5x5x5' '6x6x6' '7x7x7' '9x9x9' '10x10x10' '11x11x11' '12x12x12' '13x13x13' '14x14x14' '15x15x15' \
                '24x25x28' '48x48x48' '49x49x49' '60x60x60' '72x60x56' '75x75x75' '80x80x80' '84x84x84' \
                '96x96x96' '100x100x100' '105x105x105' '112x112x112' '120x120x120'; do
      ./bench $OPTS ${PLACE}${TYPE}${SIZE}
    done
  done
done
