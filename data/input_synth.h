//#define S 2048
#define S 512
#define M 100
#define K 3

// VISUALIZATION
void print_matrix(float**, int, int);
void print_kernels(float**, int);

// WRITE
float random_float();
void persist_input_matrix();
void persist_input_kernels();


//READ
void read_persisted_matrix(float **im_out);
void read_persisted_kernels(float **kernels_out);
void kernel_matrix_from_line(float *kernel_line, float **kernel_matrix);
