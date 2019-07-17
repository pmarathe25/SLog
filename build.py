#!/usr/bin/env python3
import sbuildr
import glob
import os
project = sbuildr.Project()

libslog = project.library("slog", sources=glob.glob("src/*.cpp"))
project.install(libslog, "/usr/local/lib")
project.install("SLog.hpp", "/usr/local/include/Stealth")

# Add tests
for source in glob.iglob("tests/*.cpp"):
    project.test(source.split('.')[0], sources=[source], libs=["stdc++", "stest", libslog])

sbuildr.cli(project, default_profiles=["debug"])
