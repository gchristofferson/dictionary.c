# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

This is one of the longest words in the English dictionary.  It literally refers to a lung disease caused by silica dust.

## According to its man page, what does `getrusage` do?

getrusage() returns resource usage measures for who, which can be one of the following:

RUSAGE_SELF
      Return resource usage statistics for the calling process, which is the sum of resources used by all threads in the process.

RUSAGE_CHILDREN
      Return  resource  usage statistics for all children of the calling process that have terminated and been waited for.  These statistics will include the resources used by grandchildren, and further removed
      descendants, if all of the intervening descendants waited on their terminated children.

RUSAGE_THREAD (since Linux 2.6.26)
      Return resource usage statistics for the calling thread.

## Per that same man page, how many members are in a variable of type `struct rusage`?

There are 16 membors in the variable of type 'struct usage'.

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

If passed by value, the functions won't have access to each others memory spaces and will only get copies of what is passed in. If passed by reference, we are going to access the actual values of the functions variables.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

Main's for loop first argument assigns fgetc(file) to int c. 'fgetc' will return the next character in the opened file.  The main will continue reading the file, character by character, as long as c does
not equal 'EOF' or end of file. If it doesn't equal 'EOF', the for loop executes the code in the for loop, then assigns c to fgetc(file), which will be the next character in the file.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

We might run into a segmentation fault because we don't know how long each word is within the file.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

Const means the variable cannot be changed.  Since the compiler knows they won't change it can optimize the code that uses them.  For example, the dictionary
parameter passed by value doesn't need to be copied since the value never changes and the word array is only copied if it was written to in the function.
# dictionary.c
