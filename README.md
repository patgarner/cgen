# cgen - Your Basic C Project Boilerplate Generator

Hey there! I create a lot of small C projects and I couldn't find a super simple tool to automate the process of creating the basic boilerplate: a directory, a Makefile, and a simple main.c.

CGEN is a utility for quickly setting up new C projects. It generates a new directory with a base C source file and a Makefile. It eliminates the need to manually write the boilerplate code for a new C program.

## Features

- Automates the creation of a new C program with a new directory, a `main.c` file, and a Makefile.
- For the special case of creating the CGEN program itself, it embeds the source code and Makefile in the generated `main.c` for easy modifications in the future.

## Prerequisites

Before you begin, ensure you have met the following requirements:

- You have installed gcc or a compatible C compiler.
- You have basic knowledge of C programming.

## Installing CGEN

To install CGEN, follow these steps:

(Linux and macOS)

1. Clone the repository
2. Change into the directory containing the project
3. Run make
4. (Optional) Install to a directory in your PATH

## Using CGEN

To use CGEN, follow these steps:

`cgen <program_name>`

This will create a directory named `<program_name>`, and in it a Makefile and `main.c` that prints "Hello World".

`cgen cgen`

This will create a directory named `cgen`, and in it a Makefile and `main.c` that, when compiled and run, will reproduce the `cgen` program. Note that only in this case is the Makefile and source code embedded in `main.c`.

## Contributing to CGEN

To contribute to CGEN, follow these steps:

1. Fork this repository.
2. Create a branch.
3. Make your changes and commit them.
4. Push to the original branch.
5. Create the pull request.

## Contact

If you want to contact me, you can reach me at patgarner@gmail.com

## License & Disclaimer

This project is licensed under the MIT License

Please note that CGEN is provided "as is" without warranty of any kind, either expressed or implied, including, but not limited to, the implied warranties of merchantability and fitness for a particular purpose. Use it at your own risk!

