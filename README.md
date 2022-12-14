# Oak Programming Language
## About
Oak programming language is a simple, fast, interpreter programming language for writing variouse applications.
## Features
- No immutable variables
- Easy to learn and use
- Free and open source
- Fast interpreter
## Goals
- Lexer
- Parser
- Evaluator
- Add runtime libraries
## Screenshots
### First Hello, World ever writted in Oak
![First Hello, World!](Screenshots/first_hello_world.png)
## Build & Usage
To build oak compiler you need to write down this commands:
```bash
git clone https://github.com/solindekdev/oak
cd oak
node build.js && ./Build/oak --version
```
More about commands in compiler in command `./Build/oak --help`
You can use Makefile too
```bash
git clone https://github.com/solindekdev/oak
cd oak
make && ./Build/oak --version
```
## Grammar and TODO
### Hello, World! Program
```
fn main [
    push: "Hello, World!";
    call: println;
]
```
### Stack
#### Pushing to stack
On stack you can push every type
```
fn main [
    push: "Roben";
    push: 18;
]
```
#### Poping to stack
You can pop from stack and save it in variable
```
fn get_name_and_age [
    push: "Roben";
    push: 18;
]

fn main [
    call: get_name_and_age; # Calling to function

    # Creating important variables
    let: text_to_print | string;
    let: name | string;
    let: age | int;

    # Pop from stack name and age
    # they was push to stack in
    # get_name_and_age function
    pop: name;
    pop: age;

    # Add to string
    text_to_print<>add: "Your name is ";
    text_to_print<>add: name;
    text_to_print<>add: " and you are ";
    text_to_print<>add: age;
    text_to_print<>add: " years old.";

    # Push this string to stack
    # and after it print it out
    push: text_to_print;
    call: println;
]
```
### Variables declaration & usage
```
fn main [
    # let: (HERE_NAME_OF_VAR) | (HERE_TYPE_OF_VAR);
    # for example
    let: is_oak_terrible_syntax | bool;
    set: is_oak_terrible_syntax | true;
]
```
### Function declaration & calling functions
```
fn function_to_call [
    push: "Function has been called";
    call: println;
]

fn main [
    push: "Before calling function";
    call: println;
    call: function_to_call;
    push: "After calling function";
    call: println;
]
```
### Importing files
**main.oak**
```
@import "./function.oak"

fn main [
    call: function_from_import;
]
```
**function.oak**
```
fn function_from_import [
    push: "Hello";
    call: println;
]
```
### If & else
### While loops
### For loops
### Array
### Classes & class methods
### Object
### Namespaces
