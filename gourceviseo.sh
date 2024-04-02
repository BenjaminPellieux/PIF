#!/bin/bash

gource \
    -s 2.5 \
    -1080x920 \
    --auto-skip-seconds .1 \
    --multi-sampling \
    --stop-at-end \
    --highlight-users \
    --date-format "%d/%m/%y" \
    --hide mouse \
    --file-idle-time 0 \
    --max-files 0  \
    --background-colour 000000 \
    --font-size 25 \
    --font-colour FFFFFF \
    --output-ppm-stream - \
    --output-framerate 30 \
    | ffmpeg -y -r 30 -f image2pipe -vcodec ppm -i - -b 65536K movie.mp4
