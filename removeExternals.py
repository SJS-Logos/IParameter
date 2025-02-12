import os
import shutil
import subprocess
from pathlib import Path
import stat

import likeExternals

def rmtree(top):
    for root, dirs, files in os.walk(top, topdown=False):
        for name in files:
            filename = os.path.join(root, name)
            os.chmod(filename, stat.S_IWUSR)
            os.remove(filename)
        for name in dirs:
            if os.path.isdir(os.path.join(root, name)):
                os.rmdir(os.path.join(root, name))
    if os.path.isdir(top):
        os.rmdir(top)


if __name__ == "__main__":
    # Delete all external files
    externals = likeExternals.parseExternalsFile('externals.txt')
    for external in externals:
        rmtree(external[1])

