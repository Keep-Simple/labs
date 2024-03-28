#!/bin/sh

# first arg is lab number

asciidoctor -r asciidoctor-pdf -b pdf $1/README.adoc -a pdf-theme=default-sans
