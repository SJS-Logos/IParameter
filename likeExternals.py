import shutil
import subprocess
import os
from pathlib import Path
import sys

def parseExternalsFile(file):
    externals = []
    with open(file, 'r') as f:
        for line in f:
            line_without_comment = line.split('#')[0] # Remove comments after symbol '#'
            elements = line_without_comment.rstrip().split(' ')
            comment = ""
            if len(line.split('#')) > 1:
                comment = line.split('#')[1]
            elements.append(comment)
            assert (len(elements) == 2 or len(elements) == 3), f'(Can not parse {len(elements)} elements'
            assert ('https://' in elements[0]), '(Unhandled string ' + elements[0]
            externals.append((elements[0], elements[1], elements[2]))
    return externals


def updateSubversion(url, name):
    path = Path(name)
    if not path.exists():
        subprocess.run(['svn', 'co', url, path], check=True)


def updateGit(url, name):
    parts = url.split('/')
    if parts[2] != 'github.com' or parts[3] != 'Logos-Payment-Solution':
        raise Exception("url mismatch!")
        return

    path = Path(parts[4])
    if not path.exists():
        actualUrl = f'git@github.com:Logos-Payment-Solution/{parts[4]}.git'
        subprocess.run(['git', 'clone', actualUrl, name], check=True)

    # Ensure correct tag or branch
    match parts[5]:
        case 'tag':
            subprocess.run(['git', '-C', parts[4], 'checkout', f'tags/{parts[6]}'], check=True)
        case 'branch':
            branchName = parts[6]
            for part in parts[7:]:
                branchName += f'/{part}'
            subprocess.run(['git', '-C', parts[4], 'checkout', branchName], check=True)
        case 'commit':
            commitNumber = parts[6]
            for part in parts[7:]:
                commitNumber += f'/{part}'
            subprocess.run(['git', '-C', parts[4], 'checkout', commitNumber], check=True)
        case other:
            raise Exception('Only supports branch or tag or commit!')


def updateOne(url, name):
    if 'svn.logos.dk' in url or '172.16.1.104' in url:
        updateSubversion(url, name)
    else:
        updateGit(url, name)


if __name__ == "__main__":
    externals = parseExternalsFile('externals.txt')
    for external in externals:
        updateOne(external[0], external[1])
