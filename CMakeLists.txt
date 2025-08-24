# Norb's Fractallizer by... well, NorbCodes
# Copyright (C) 2025 norbcodes (a.k.a Norb, norb3695)
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 4.0.0 FATAL_ERROR)

project(
    "Norb's Fractallizer"
    LANGUAGES CXX
    DESCRIPTION "Renderer for the Mandelbrot Set."
)

set(EXE_NAME nfractallizer)

set(
    NF_SOURCES
    ${CMAKE_SOURCE_DIR}/src/main.cpp
)

add_executable(${EXE_NAME} ${NF_SOURCES})
target_compile_features(${EXE_NAME} PRIVATE cxx_std_17)

# Norb's Fractallizer by... well, NorbCodes
# Copyright (C) 2025 norbcodes (a.k.a Norb, norb3695)
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.