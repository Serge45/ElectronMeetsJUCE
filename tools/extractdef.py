import os

if __name__ == '__main__':
    with open('../bin/Electron/node_.def', 'r') as f:
        lines = f.readlines()
        out_lines = []

        for line in lines:
            out_lines.append(line.split(' ')[-1])

        with open('../bin/Electron/node.def', 'w') as out:
            for line in out_lines:
                out.write(line)
