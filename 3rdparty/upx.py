#!/usr/bin/env python
import os
import sys

def which(program):
    import os
    def is_exe(fpath):
        return os.path.isfile(fpath) and os.access(fpath, os.X_OK)

    fpath, fname = os.path.split(program)
    if fpath:
        if is_exe(program):
            return program
    else:
        for path in os.environ["PATH"].split(os.pathsep):
            path = path.strip('"')
            exe_file = os.path.join(path, program)
            if is_exe(exe_file):
                return exe_file

    return None

def red(text):
    return "\x1b[1;31m" + text + "\x1b[0m"

def green(text):
    return "\x1b[1;32m" + text + "\x1b[0m"

def yellow(text):
    return "\x1b[1;33m" + text + "\x1b[0m"

if which("upx"):
    print("-- " + green("UPX found"))
    var = os.popen("upx --ultra-brute -q {}".format(sys.argv[1])).read().split("\n")[6].split()
    print("-- " + yellow("UPX reduced size of {} to {} from {}kb to {}kb".format(var[5], var[3], var[0], var[2])))
else:
    print("-- " + red("UPX not found"))
