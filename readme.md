# Get next line

This project is about write `get_next_line()` function that read text file one line at a time

## Futures

- Repeated calls to get_next_line() (such as within a loop) will read a text file line by line. The function accepts a file descriptor as input, pointing to the file you want to read.
- The function returns the next line from the file each time it is called.
- If there are no more lines to read or if an error occurs, the function will return `NULL`.

## Usage

```c
int fd = open("example.txt", O_RDONLY);
char *line;

while ((line = get_next_line(fd)) != NULL) {
    printf("%s\n", line);
    free(line);
}

close(fd);
```

## Resources
- [Subject](./static/Get_Next_Line.pdf)
- [Static Variable](https://www.geeksforgeeks.org/static-variables-in-c/)