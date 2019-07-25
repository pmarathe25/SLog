#!/usr/bin/env python3
import sbuildr
import glob
import os
project = sbuildr.Project()

project.install("SLog.hpp", "/usr/local/include/Stealth")

# Add tests
for source in glob.iglob("tests/*.cpp"):
    project.test(source.split('.')[0], sources=[source], libs=["stdc++", "stest"])

sbuildr.cli(project, default_profiles=["debug"])
