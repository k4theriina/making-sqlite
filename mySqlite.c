/*
Sqlite
*/

typedef struct {
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
}  InputBuffer;

InputBuffer* new_input_buffer() {
    InputBuffer* input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;

    return input_buffer;
}

void print_prompt() { printf("db > "); }

void read_input(InputBuffer* input_buffer) {
    // returns bytes read from input and puts it into the buffer. 
    ssize_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

    if(bytes_read <= 0) {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }

    // discard newline
    input_buffer->input_length = bytes_read - 1;
    input_buffer->buffer[bytes_read - 1] = 0;
}

void close_input_buffer(InputBuffer* input_buffer) {
    free(input_buffer->buffer);
    free(input_buffer);
}

int main (int argc, char* argv[]) {
    // ask print loop
    InputBuffer* inputBuffer = new_input_buffer();


    while(1){
        // print the response n read input
        print_prompt();
        read_input(inputBuffer);

        // process exit and catch command errors
        if (strcmp(input_buffer->buffer, ".exit") == 0) {
        close_input_buffer(input_buffer);
        exit(EXIT_SUCCESS);
        } 
        else {
        printf("Unrecognized command '%s'.\n", input_buffer->buffer);
        }
    }
}
