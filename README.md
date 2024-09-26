# Onegin sorter

### CLI program for sorting big texts (such as "Eugene Onegin" by A. Pushkin) line by line

## Dependencies

- `Windows or Linux`
- `GCC`
- `Make`

## Run program

### Clone the project

```bash
git clone https://github.com/DoneGame/Onegin-Sort.git
cd Onegin-Sort
```

### Compile code

For Windows
```bash
make
```

For Linux 
```bash
make -f Makefile_linux
```


### Finally, run executable file

```bash
./onegin
```

or

```bash
./onegin examples/onegin_example.txt
```

*The name of the file to be read can be specified as the first command line argument*


## Text file format
- The file must not contain empty lines (exept the final one)
- All characters must be contained in the ASCII table (Latin letters, numbers and punctuation marks)
- Example of correct file: [onegin_example.txt](./examples/onegin_example.txt)
- File [onegin_full.txt](./examples/onegin_full.txt) contains full text of Eugene Onegin in english with correct formatting

## Debugging

To get dubugging information in output use
```bash
make debug
./onegin_debug examples/test.txt
```

File [test.txt](./examples/test.txt) contains small test for program

#### Abbreviations in tooltips and code:
<pre>
tmp = temporary
el  = element
str = string
ptr = pointer
cnt = counter
len = length
</pre>
 