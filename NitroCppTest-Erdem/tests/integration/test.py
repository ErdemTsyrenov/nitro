import platform
import subprocess
import os

if __name__ == '__main__':
    executable = ''
    if platform.system() == 'Windows':
        executable = os.path.join('..','..','build','Debug','main.exe')
    else:
        executable = os.path.join('..','..','build','main')

    run = subprocess.run([executable, 'test.json'], capture_output=True, text=True)
    assert run.returncode == 0
    with open('expected.txt', 'r') as f:
        expected = f.read()
        assert run.stdout.strip() == expected.strip()
    print('Success!')