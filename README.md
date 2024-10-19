# Weight Filling Macros Library

This library provides macros to read trained weights from files and store them in memory using `Numcy::Collective<double>` structures. The current macros `READ_W1` and `READ_W2` are designed to read the respective weights and store them in a new instance of a composite data structure.

## Macros

### `READ_W1(p, w1)`

This macro reads weight values from a file using an instance of the tokenizer and fills the provided `w1` instance of `Collective<double>` with the weight data.

- **Parameters:**
  - `p`: An instance of the tokenizer that reads the weight data file.
  - `w1`: An instance of `Collective<double>` that stores the weights.

- **Functionality:**
  - Resets the tokenizer to read lines and tokens from the weight file.
  - Initializes `w1` with dimensions based on the number of lines and tokens.
  - Fills the weights into `w1` by iterating through lines and tokens of the file.

### `READ_W2(p, w2)`

This macro works similarly to `READ_W1`, but with a different orientation for how the weights are filled into the `w2` instance of `Collective<double>`.

- **Parameters:**
  - `p`: An instance of the tokenizer that reads the weight data file.
  - `w2`: An instance of `Collective<double>` that stores the weights.

- **Functionality:**
  - Resets the tokenizer to read lines and tokens from the weight file.
  - Initializes `w2` with dimensions based on the number of lines and tokens.
  - Fills the weights into `w2` by iterating through lines and tokens of the file, in a column-wise manner.

### `WRITE_W1(w1, f, v)`
Writes the input weights (`w1`) to a file.

- ***Parameters***:
  - `w1`: A container holding the input weights.
  - `f`: The file name where the weights will be written.
  - `v`: The vocabulary instance.

### `WRITE_W2(w2, f, v)`
Writes the output weights (`w2`) to a file.

- ***Parameters***:
  - w2: A container holding the output weights.
  - f: The file name where the weights will be written.
  - v: The vocabulary instance.

## Example Usage

```cpp
#ifdef GRAMMAR_END_OF_TOKEN_MARKER
#undef GRAMMAR_END_OF_TOKEN_MARKER
#endif
#ifdef GRAMMAR_END_OF_LINE_MARKER
#undef GRAMMAR_END_OF_LINE_MARKER
#endif

#define GRAMMAR_END_OF_TOKEN_MARKER ' '
#define GRAMMAR_END_OF_LINE_MARKER '\n'

/*
    Dependencies
    - csv
    - Numcy
    - sundry
    - Skip-gram -OR- CBOW    
 */
#include "../lib/csv/parser.hh"
#include "../lib/Numcy/header.hh"
#include "../lib/sundry/cooked_read_new.hh"
#include "../lib/sundry/cooked_write_new.hh"

#include "../lib/read_write_weights/header.hh"

int main(int argc, char* argv[])
{
    cc_tokenizer::String<char> w1trained = cc_tokenizer::cooked_read<char>(cc_tokenizer::String<char>("w1trained.txt"));
    cc_tokenizer::String<char> w2trained = cc_tokenizer::cooked_read<char>(cc_tokenizer::String<char>("w2trained.txt"));

    Collective<double> W1;
    Collective<double> W2;

    cc_tokenizer::csv_parser<cc_tokenizer::String<char>, char> w1trainedParser(w1trained);  
    cc_tokenizer::csv_parser<cc_tokenizer::String<char>, char> w2trainedParser(w2trained);

    READ_W1(w1trainedParser, W1);
    READ_W2(w2trainedParser, W2);

   
    // Now let's write the weights back to files
    corpus vocab; // Assuming vocab is filled appropriately
    cc_tokenizer::String<char> w1OutputFile("w1output.txt");
    cc_tokenizer::String<char> w2OutputFile("w2output.txt");

    WRITE_W1(W1, w1OutputFile, vocab);
    WRITE_W2(W2, w2OutputFile, vocab);

    return 0;
}
```
