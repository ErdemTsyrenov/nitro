import platform
import subprocess

if __name__ == '__main__':
    executable = '../../build/main'
    if platform.system() == 'Windows':
        executable += '.exe'
    run = subprocess.run([executable, 'test.json'], capture_output=True, text=True)
    assert run.returncode == 0
    with open('expected.txt', 'r') as f:
        expected = f.read()
        assert run.stdout.strip() == expected.strip()
    print('Success!')