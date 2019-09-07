#!/usr/bin/env python3
import sbuildr
import sbuildr.dependencies.builders as builders
import sbuildr.dependencies.fetchers as fetchers

import glob
import os

stdlib = sbuildr.Library("stdc++")
project = sbuildr.Project()

project.interfaces(["SLog.hpp"])

# Add tests
stest = sbuildr.dependencies.Dependency(fetchers.GitFetcher("https://github.com/pmarathe25/STest", tag="v0.3.1"), builders.SBuildrBuilder())
for source in glob.iglob("tests/*.cpp"):
    project.test(os.path.basename(source).split('.')[0], sources=[source], libs=[stdlib, stest.library("stest")])

project.export()
