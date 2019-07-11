#!/usr/bin/env python3
import sbuildr
import os
project = sbuildr.Project()

project.test("logging", sources=["main.cpp", "containers.cpp", "overloadedStreamOps.cpp", "logging.cpp"], libs=["stdc++", "stest"])
sbuildr.cli(project, default_profiles=["debug"])
