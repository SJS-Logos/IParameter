import subprocess
from pathlib import Path

import likeExternals

def verifyGit(url, name, comment):
    path = Path(name)

    parts = url.split('/')

    if parts[2] != 'github.com' or parts[3] != 'Logos-Payment-Solution':
        print("ERROR!")
        return

    match parts[5]:
        case 'tag':
            expected = parts[6]
            actual_tags = subprocess.run(['git', '-C', parts[4], 'tag', '--points-at', 'HEAD'],
                                    capture_output=True, text=True, check=True).stdout.strip("\n")
            matched_tag = False
            for tag in actual_tags.strip().split('\n'):
              if tag == expected:
                  matched_tag = True
            if not matched_tag:
              print(f'{name} is not correct!')
        case 'branch':
            expected = parts[6]
            for part in parts[7:]:
                expected += f'/{part}'
            actual = subprocess.run(['git', '-C', parts[4], 'rev-parse', '--abbrev-ref', 'HEAD'], capture_output=True, text=True, check=True).stdout.strip("\n")
            if actual != expected:
                raise Exception(f'{name} is not correct!')
        case 'commit':
            expected = parts[6]
            for part in parts[7:]:
                expected += f'/{part}'
            actual = subprocess.run(['git', '-C', parts[4], 'rev-parse', 'HEAD'], capture_output=True, text=True, check=True).stdout.strip("\n")
            if actual != expected:
                raise Exception(f'{name} is not correct! actual=' + str(actual) + ", expected=" + str(expected))

        case other:
            raise Exception(f'{parts[5]} is not supported!')

    # Detect if current branch is behind branch 'main'
    num_commits_behind = subprocess.run(['git', '-C', parts[4], 'rev-list', '--count', '..main'],
                                        capture_output=True, text=True).stdout.strip("\n")
    if int(num_commits_behind) > 0:
        # Get last commit date for tag that is currently in use
        last_included_commit_date = subprocess.run(['git', '-C', parts[4], 'log', '-1', '--date=format:%Y-%m-%d', '--format=%ad'],
                                            capture_output=True, text=True).stdout.strip("\n")
        if len(comment) > 0:
            comment = " (" + comment.strip() + ")"
        print(parts[4] + " (includes commits up to " + str(last_included_commit_date) + ") is behind 'main' with " + num_commits_behind + " commits" + " " + comment)

    # Notify if git files belonging to another git repo have been modified locally
    git_diff = subprocess.run(['git', 'diff', '--name-only'], capture_output=True, text=True, cwd=name, check=True).stdout.strip("\n")
    if git_diff:
        print("File(s) in external GIT repo '", name, "' modified locally!\n", git_diff, "\n\n", sep='')



def verifySubversion(url, name):
    path = Path(name)
    parts = url.split('/')

    fromIndex = 4
    if parts[fromIndex] == 'svn':
        fromIndex += 1

    expected = '^'
    for part in parts[fromIndex:]:
        expected += f'/{part}'

    actual = subprocess.run(['svn', 'info', '--show-item=relative-url', f'{name}'], capture_output=True, text=True, check=True).stdout.strip("\n")
    if actual != expected:
        raise Exception(f'{name} is not correct!')

    # Notify if svn files belonging to another svn repo have been modified locally
    svn_diff = subprocess.run(['svn', 'diff', f'{name}'], capture_output=True, text=True, check=True).stdout.strip("\n") 
    if svn_diff:
        print("File(s) in external SVN repo '", name, "' modified locally!\n", svn_diff, "\n\n", sep='')


def verifyOne(url, name, comment):
    if 'svn.logos.dk' in url:
        verifySubversion(url, name)
    else:
        verifyGit(url, name, comment)

if __name__ == "__main__":
    externals = likeExternals.parseExternalsFile('externals.txt')
    for external in externals:
        verifyOne(external[0], external[1], external[2])
