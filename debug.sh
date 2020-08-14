#!/bin/bash
# debug.sh
# Created on: Fri 14 Aug 2020 06:33:45 AM CEST
#
#  ____   __  ____  __
# (  _ \ /. |(  _ \/  )
#  )___/(_  _))___/ )(
# (__)    (_)(__)  (__)
#
# Description:

valgrind -s --track-origins=yes --leak-check=full ./trap

