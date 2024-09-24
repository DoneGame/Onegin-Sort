# Onegin sorter

### CLI program for sorting big texts (such as "Eugene Onegin" by A. Pushkin) line by line

## Dependencies

- `GCC`
- `Make`

## Run program

Clone the project

```bash
git clone https://github.com/DoneGame/Onegin-Sort.git
cd Onegin-Sort
```

Compile code

```bash
make
```

Finally, run executable file

```bash
onegin.exe
```

or

```bash
onegin.exe test.txt
```

*The name of the file to be read can be specified as the first command line argument*


## Text file format
- The file must not contain empty lines (exept the final one)
- All characters must be contained in the ASCII table (Latin letters, numbers and punctuation marks)
- Example of correct file: [onegin_example.txt](./onegin_example.txt)


#### Abbreviations in tooltips and code:
<pre>
tmp = temporary
el  = element
str = string
ptr = pointer
cnt = counter
</pre>
 