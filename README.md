# calc

My take on writing a calculator that implements [Reverse Polish notation][0], I
think, I'm not sure if it's well implemented, I like to read about something
and take the ideas that I like best.

[0]: https://en.wikipedia.org/wiki/Reverse_Polish_notation

Use it like this, type the following and hit enter:

```
3 2 +
```

In the next line should display:

```
[ 5 ]
```

Clear the array by writing `=` and hitting enter, should print an empty array:

```
[ ]
```

Also you can enter numbers only and operate later, for example type the
following, pressing enter in each line:

```
1
2
3
```

Each time you press enter, it should print the current numbers in the array, by
the end you should have:

```
[ 1 2 3 ]
```

Then write `+` and hit enter, the program should print:

```
[ 1 5 ]
```

It adds the last 2 numbers from right to left, so `3 + 2`. Supported operations
are `+`, `-`, `*`, `/`.
