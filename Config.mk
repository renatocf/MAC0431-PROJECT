
############################################################
##     UNCOMMENT ANY TARGET TO OVERWRITE THE DEFAULT!     ##
############################################################

# Project info
# ===============
PROJECT         := Waves
VERSION         := 1.0.0
STD_NAMESPACE   := waves
GIT_REMOTE_PATH := https://github.com/renatocf/MAC0431-PROJECT.git
MAINTEINER_NAME := Erika Midori Akabane \
                   Karina Suemi Awoki \
                   Renato Cordeiro Ferreira \
                   Vinícius Nascimento Silva
MAINTEINER_MAIL := # your_name@mail.com
COPYRIGHT       := MAC0431-PROJECT
SYNOPSIS        := Challenge for the discipline MAC0431
DESCRIPTION     := Simulation of waves in a lake for the discipline \
                   MAC0431 (Introduction to Parallel and Distributed \
                   Programming)

# Program settings
# ==================
# BIN             := # Binaries' names. If a subdir of any
                     # src dir has the same name of this bin
                     # it and all its subdir will be compiled
                     # only for this specific binary
# ARLIB           := # Static/Shared libraries' names. If
# SHRLIB          := # one is a dir, all srcs within will
                     # make the lib

# Dependencies
# ==============
# GIT_DEPENDENCY  := # List of git dependencies in the form: 
#                    # DEP_NAME => dep_path build_cmd        
# WEB_DEPENDENCY  := # Same as above, but for URL downloads  
#                    # with 'curl -o' (default) or 'wget -O' 

# Paths
# =======
# ASLIBS          := # Assembly paths
# CLIBS           := # C paths
# CXXLIBS         := # C++ paths
# LDLIBS          := # Linker paths

# Flags
# =======
CPPFLAGS        := -DNDEBUG
ASFLAGS         := # Assembly Flags
COMMFLAGS       := -Wall -Wextra -pedantic -Wno-deprecated-declarations \
                   -Ofast -msse2 -march=native
CFLAGS          := -ansi $(COMMFLAGS)
FFLAGS          := -ffree-form $(COMMFLAGS)
CXXFLAGS        := -std=c++11 $(COMMFLAGS)
# LDFLAGS         := # Linker flags

# Documentation
# ===============
# LICENSE         := # File with a License (def: LICENSE)
# NOTICE          := # Notice of the License, to be put in 
#                    # the top of any file (def: NOTICE).
# DOXYFILE        := # Dxygen config file (def: Doxyfile)

# Makeball list
# ===============
# 'include conf/makeball.mk' for pre-configured options
# to use the library 'makeball'
include conf/eigen.mk
include conf/openmp.mk
include conf/googletest.mk
include conf/sistmo_prng_engine.mk
