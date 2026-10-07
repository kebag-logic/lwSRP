#!/bin/bash
# SPDX-License-Identifier: Apache-2.0
# Get the path of the script
SCRIPTPATH="$(cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P)"

# The virtual env, zephyr uses python3
VENV_SHISH_LAN=${SCRIPTPATH}/build/.venv-shish-lan

# export the ZEPHYR_BASE that will be used as a basis for the
# building with west
export ZEPHYR_BASE=${SCRIPTPATH}/build/


# First creatre the virtual environment if it does not exists already
if [ ! -d ${VENV_SHISH_LAN} ]; then
	python3 -m venv ${VENV_SHISH_LAN}
fi

# Insaslllal the 
