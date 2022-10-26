#!/usr/bin/python
from setuptools import setup, find_packages
from glob import glob
from pybind11.setup_helpers import Pybind11Extension
from os import environ, path
import sys
#Install phonetisaurus 

if sys.platform == 'win32':
    ext_modules = [
        Pybind11Extension(
            "phonetisaurus",
            ['src/lib/util.cc', 'src/phonetisaurus.cpp'],
            cxx_std=17,
            extra_compile_args=[
                '/wd4018', 
                '/wd4244',
                '/wd4267', 
                '/wd4291', 
                '/wd4305',
                '/wd4819'
                ],
            define_macros=[
                # ('_HAS_STD_BYTE', '0'),
                ('WIN32_LEAN_AND_MEAN', None),
                ('NOMINMAX', None),
                ('_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS', None),
                ('_USE_MATH_DEFINES', None),
                ],
            include_dirs = [
                'src',
                'src/3rdparty/utfcpp',
                ],
            libraries= [ 'fst' ]
        )
    ]
else:
    ext_modules = [
        Pybind11Extension(
            "phonetisaurus",
            ['src/lib/util.cc', 'src/phonetisaurus.cpp'],
            cxx_std=17,
            include_dirs = [
                'src',
                'src/3rdparty/utfcpp',
                ],
            libraries= [ 'fst' ]
        )
    ]

__version__ = '0.3'

setup (
    name         = 'phonetisaurus-py',
    version      = '0.3',
    description  = 'Pybind11 bound Phonetisaurus G2P python package',
    url          = 'http://github.com/cvrunmin/phonetisaurus-py',
    author       = 'Josef Novak',
    author_email = 'josef.robert.novak@gmail.com',
    maintainer   = 'cvrunmin',
    maintainer_email= 'cvrunmin@outlook.com',
    license      = 'BSD',
    packages     = find_packages(),
    install_requires = ["pybind11"],
    ext_modules  = ext_modules,
    zip_safe     = False
)
