#!/bin/sh

echo "Enter lab number: "
read n
poetry run python -m "l${n}.l${n}"
