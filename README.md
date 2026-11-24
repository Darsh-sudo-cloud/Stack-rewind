# Rewind

A small bytecode virtual machine in C with a browser-based time-travel debugger. Run a program, record every step, then move backward and forward through its history to find where a value went wrong.

**[Try the live debugger](https://darsh-sudo-cloud.github.io/Stack-rewind/)**. Load `docs/sample-trace.json` from this repository.  

## Features

| Feature | Status |
|---|---|
| Stack-based VM (`PUSH`, `LOAD`, `STORE`, `ADD`, `PRINT`, `HALT`) | ✅ Done |
| Execution trace to `trace.json` | ✅ Done |
| Step forward/back, timeline slider | ✅ Done |
| Find when a variable last changed | ✅ Done |
| Breakpoints | 📋 Planned |
| Source-language compiler | 📋 Planned |
| Custom allocator and mark-and-sweep GC | 📋 Planned |

## Architecture

```
Bytecode → C VM (src/vm.c) → trace.json → Web debugger (docs/)
```

The VM writes the stack and variables after every instruction. The browser loads that file and replays it, so going back is just moving an index.

## Project structure

```
rewind/
├── src/
│   ├── vm.h          # opcodes, instruction and VM structs
│   ├── vm.c          # interpreter loop and trace writer
│   └── main.c        # sample program
├── web/
│   ├── index.html    # debugger layout
│   ├── style.css     # panel styling
│   └── app.js        # loads the trace, handles steps and search
├── tests/
│   └── test_vm.c     # VM test program
├── .gitignore
└── README.md
```

## Getting started

**Build and run the VM (Windows PowerShell)**

```powershell
gcc -Wall -Wextra -o rewind.exe src/*.c
.\rewind.exe
```

**Open the debugger:** open `web/index.html`, click **Choose File**, select `trace.json`, then use the buttons or arrow keys.

**Run the tests**

```powershell
gcc -Wall -Wextra -o test_vm.exe tests/test_vm.c src/vm.c
.\test_vm.exe
```

## Design choices

- **Full snapshot per step:** simple and always correct, but memory grows with program length.
- **JSON between C and JavaScript:** each half can be built and tested on its own.

## Limitations

- The sample program is hard-coded.
- Tests only check that the program runs.

## Author

Darsh · [GitHub](https://github.com/Darsh-sudo-cloud)