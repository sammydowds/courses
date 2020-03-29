# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

It is a lung disease caused by silica.

## According to its man page, what does `getrusage` do?

It returns the resource usage measure for who: RUSAGE_SELF: statistics for the calling process, which is the sum of resources used by all threads in the process.

## Per that same man page, how many members are in a variable of type `struct rusage`?

There are 16

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

Because calculate is a double which stores the pointers of const structs of rusage.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

In the for loop, you begin by checking each character from "file". If the character is not is not the end of file you check if it is numeric. If it is numeric, you then append it to an array - word, and update the index.
If the character is not alphanumeric, but an apostraphe AND the index is not = 0 - then you add this character to the word as well. If the index count is greater than 45, then you iterate through the rest of the file then set index to 0
to prepare for a new word. If the character is a digit, you do the same thing - iterating through the file until reaching EOF, and then setting index = 0.
To end a word, if you know the index is not 0 - but the character is not a digit, alpha, or an apostraphe - then you know you have hit the end of the word, in this case
you add \0 to the word array.You update the word count then, and the you record the time it takes to run the "check" function. During this you record the amount of times a word is misspelled.
Finally, you restore the index to 0.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

You can predict the size of a character, however, you cannot predict the size of a string - as it varies word to word.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

To ensure that the pointer do not accidentally get changed, and you pass in bytes you did not mean to.
