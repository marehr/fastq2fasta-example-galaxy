#!/usr/bin/env bash

python -m venv ./planemo-venv
source ./planemo-venv/bin/activate
pip install planemo

planemo test
