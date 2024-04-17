#!/bin/bash

gource \
    -s 2.5 \
    -1280x920 \
    --auto-skip-seconds .01 \
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
    --output-framerate 60 \
    | ffmpeg -y -r 60 -f image2pipe -vcodec ppm -i - -vcodec libx264 -preset medium -pix_fmt yuv420p -crf 1 -threads 0 -bf 0 movie.x264.avi

#-b 65536K movie.mp4
