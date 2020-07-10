from sys import argv, exit

INSTRUCTION_SET = [
    "nop", "hlt", "psh", "pop", "dpl",
    "swp", "cyc", "add", "cmp", "out",
    "inp", "cbr", "ubr", "crt", "urt"
]

CHARSET = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ.<>!?'-+/* "

def lookupchar(char):
    if char not in CHARSET and char not in ["\\0", "\\n"]:
        print("unrecognised character", char)
        exit(1)
    if char == "\\0":
        return len(CHARSET)+1
    elif char == "\\n":
        return len(CHARSET)
    return CHARSET.index(char)

def lookupop(opcode):
    if opcode not in INSTRUCTION_SET:
        print("unrecognised opcode")
        exit(1)
    return INSTRUCTION_SET.index(opcode)

def parsearg(arg):
    if len(arg) > 2 and arg[0] == "'" and arg[-1] == "'":
        char = arg[1:-1]
        return lookupchar(char)
    elif arg.isdigit:
        return arg
    elif arg[:2] == "..":
        return arg
    else:
        print("invalid argument")
        exit(1)

def parse(assembly):
    tree: {str: []} = {}
    inside: str = None
    labels: [str] = []
    bytecode = []
    labeladdr: {str: int} = {}
    
    for _line in assembly:
        line = _line.rstrip().lstrip()
        if not line or line[:2] == ";;":
            continue
        
        if line[:2] == "..":
            inside = line[2:-1]
            labels.append(inside)
        elif line.lower() == ":using smasm:":
            pass
        else:
            if not inside:
                print("Unlabelled instruction!\t'"+line)
                return None

            if not inside in tree.keys():
                tree[inside] = []
            tree[inside].append(lookupop(line[:3]))

            argument = line[3:].lstrip()
            if argument and argument[:2] != ";;":
                tree[inside].append(parsearg(argument))

    for label in labels:
        labeladdr[label] = len(bytecode)
        for cell in tree[label]:
            bytecode.append(cell)

    for i, cell in enumerate(bytecode):
        if isinstance(cell, str):
            if cell[:2] == "..":
                bytecode[i] = labeladdr[cell[2:]]
            
    return bytecode

if __name__ == "__main__":
    if len(argv) < 2:
        print("Please provide filename\tusage: smasm <file> <optional:outfile>")
        exit(1)

    if len(argv) > 2:
        infile, outfile = argv[1:3]
    else:
        infile, outfile = argv[1], "out.vm"

    try:
        with open(argv[1], "r") as f:
            assembly = f.readlines()
    except FileNotFoundError:
        print("File not found")
        exit(1)

    bytecode = parse(assembly)

    if bytecode is None:
        print("Something went wrong")
        exit(1)

    with open(outfile, "w") as f:
        f.write("|".join([str(b) for b in bytecode]))
        
