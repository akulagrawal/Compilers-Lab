### Installation on Ubuntu

```bash
$sudo apt-get install <software_name>
```
where software_name = {lex/flex/bison/spim}

### Run

- To display the output on terminal
```bash
$make semantics
```
- To store output in "IR.csv"
```bash
$make intermediate
```
- To give custom input code
```bash
$make intermediate INPUT=<PATH>/<FILENAME>
```

### Debug

Use -v flag with bison command:
```bash
$bison -v c_lang.y
```
and analyze c_lang.output file
