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
- Codegen
- Add runtime libraries 
## Build & Usage
To build oak compiler you need to write down this commands:
```bash
git clone https://github.com/solindekdev/oak
cd oak
node build.js && ./Build/oak --version
```
More about commands in compiler in command `./Build/oak --help`
## Grammar and TODO
### Types
**Types in Oak:**
- **Integers**
  - *int16*
  - *int32*
  - *int64* (`defualt`)
  - *int* (`alias of int64`)
- **Float numbers**
  - *float* (`alias of float32`)
  - *float32* (`default`)
  - *float64*
- **String**
  - *string*
  - *char* (`only one character`)
- **Boolean**
  - *bool*
- **Arrays**
  - [More about arrays in array part](#array)

**Examples:**
```javascript
3.14159 // float (float32)
100 // int (int64)
'a' // char
"ABC" // string
true // bool
[1, 2, 3, 4, 5] // array of int (int64)
```
**TODO:**
- [ ] Implement type detection

### Variables declaration & usage
To declare variable in Oak you need to use this grammar:
```javascript
let [NAME_OF_VAR]: [TYPE_OF_VAR] = [VALUE_OF_VAR]
```
- `NAME_OF_VAR` For example **age_of_woman**, in oak to name a variable you need to use snake_case in lower case.
- `TYPE_OF_VAR` More about [types here!](#types), for example **int**
- `VALUE_OF_VAR` Value can be an:
  - Math expression for example **2 + 2** or **2 * (5 + 6)**
  - Only an value for example **100**
  - Return of function, for example you create a [function](#function-calls--parameters) with return type **int** an you are returning a value **69**. That will be in variable.

**Examples:**
```javascript
let age: int = 18
let name: string = "Bruno" 
let pi: float = 3.14159
let dynamic_var: dyn = "Dynamic changes" // String
```
### Function declaration & calls and parameters
To declare function in Oak you need to use this grammar:
```rs 
fn [NAME_OF_FUNC]([ARGS_OF_FUNC]) => [RETURN_TYPE_OF_FUNC] {
  [BODY_OF_FUNC]
}
```
- `NAME_OF_FUNC` For example **get_age_of_alex**, in oak to name a function you need to use snake_case in lower case.
- `ARGS_OF_FUNC` In arguments first you need to write down type of argument next the name of argument like this **int age** or if you want more arguments then write for example **int age, string name**
- `RETURN_TYPE_OF_FUNC` Return type is an optional feature not every function need to reutrn something but if you want to return something in your function you need to write something like this after arguments **=> int** or any other [type](#types)
- `BODY_OF_FUNC` Just an normal body of function

**Examples:**
```rs
fn get_age_of_alex() => int {
  return 19
}

fn main() {
  println("{}", get_age_of_alex())
}
```
### Built in functions
### If & else 
### While loops
### For loops
### Array
### Classes & class methods
### Object
### Namespaces
