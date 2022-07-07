#include "matrix.h"

struct Matrix *mat_new(int rows, int cols) {
    struct Matrix *mat = (struct Matrix *) malloc(sizeof(struct Matrix));
    mat->rows = rows;
    mat->cols = cols;
    mat->data = (float**) malloc(cols * sizeof(float *));
    for (int i=0; i<rows; i++) {
        mat->data[i] = (float*) calloc(cols, sizeof(float));
    }
    return mat;
}

void mat_out(struct Matrix *mat) {
    for (int i=0; i<mat->rows; i++) {
        for (int j=0; j<mat->cols; j++) {
            printf("%f ", mat->data[i][j]);
        }
        printf("\n");
    }
    printf("rows: %i, columns: %i\n", mat->rows, mat->cols);
}

void mat_delete(struct Matrix *mat) {
    for (int i=0; i<mat->rows; i++) {
        free(mat->data[i]);
    }
    free(mat->data);
    free(mat);
}

void mat_scl(struct Matrix *mat, char op, float val) {
    switch (op) {
        case '+': {
            for (int i=0; i<mat->rows; i++) {
                for (int j=0; j<mat->cols; j++) {
                    mat->data[i][j] += val;
                }
            }
            break;
        }
        case '-': {
            for (int i=0; i<mat->rows; i++) {
                for (int j=0; j<mat->cols; j++) {
                    mat->data[i][j] -= val;
                }
            }
            break;
        }
        case '*': {
            for (int i=0; i<mat->rows; i++) {
                for (int j=0; j<mat->cols; j++) {
                    mat->data[i][j] *= val;
                }
            }
            break;
        }
        case '/': {
            if (0.0f == val)
                break;
            for (int i=0; i<mat->rows; i++) {
                for (int j=0; j<mat->cols; j++) {
                    mat->data[i][j] /= val;
                }
            }
            break;
        }
        default: {
            break;
        }
    }
}

void mat_ew(struct Matrix *chmat, char op, struct Matrix *omat) {
    if (chmat->rows != omat->rows || chmat->cols != omat->cols) {
        printf("\nPANIC: element-wise operation, matrices have different dimensions\n");
        return;
    }
    switch (op) {
        case '+': {
            for (int i=0; i<chmat->rows; i++) {
                for (int j=0; j<chmat->cols; j++) {
                    chmat->data[i][j] += omat->data[i][j];
                }
            }
            break;
        }
        case '-': {
            for (int i=0; i<chmat->rows; i++) {
                for (int j=0; j<chmat->cols; j++) {
                    chmat->data[i][j] -= omat->data[i][j];
                }
            }
            break;
        }
        case '*': {
            for (int i=0; i<chmat->rows; i++) {
                for (int j=0; j<chmat->cols; j++) {
                    chmat->data[i][j] *= omat->data[i][j];
                }
            }
            break;
        }
        case '/': {
            for (int i=0; i<chmat->rows; i++) {
                for (int j=0; j<chmat->cols; j++) {
                    if (0.0f == omat->data[i][j])
                        continue;
                    chmat->data[i][j] /= omat->data[i][j];
                }
            }
            break;
        }
        default: {
            break;
        }
    }
}

void mat_dot(struct Matrix *chmat, struct Matrix *omat) {
    if (chmat->cols != omat->rows) {
        printf("\nPANIC: matrices cant be dotted\n");
        return;
    }
    for (int i=0; i<chmat->rows; i++) {
        for (int j=0; j<omat->cols; j++) {
            float sum = 0.0;
            for (int k=0; k<chmat->cols; k++) {
                sum += chmat->data[i][k] * omat->data[k][j];
            }
            chmat->data[i][j] = sum;
        }
    }
}

struct Matrix *mat_identity(int nSIZE) {
    struct Matrix *mat = mat_new(nSIZE, nSIZE);
    for (int i=0; i<nSIZE; i++) {
        mat->data[i][i] = 1.0f;
    }
    return mat;
}

struct Matrix *mat_translation(float fx, float fy, float fz) {
    struct Matrix *mat = mat_identity(4);
    mat->data[0][3] = fx;
    mat->data[1][3] = fy;
    mat->data[2][3] = fz;
    return mat;
}

struct Matrix *mat_scaling(float fx, float fy, float fz) {
    struct Matrix *mat = mat_identity(4);
    mat->data[0][0] = fx;
    mat->data[1][1] = fy;
    mat->data[2][2] = fz;
    return mat;
}

struct Matrix *mat_shearing(float fxy, float fxz, float fyx, float fyz, float fzx, float fzy) {
    struct Matrix *mat = mat_identity(4);
    mat->data[0][1] = fxy;
    mat->data[0][2] = fxz;
    mat->data[1][0] = fyx;
    mat->data[1][2] = fyz;
    mat->data[2][0] = fzx;
    mat->data[2][1] = fzy;
    return mat;
}

struct Matrix *mat_rx(float r) {
    struct Matrix *mat = mat_identity(4);
    float cosine = cosf(r), sine = sinf(r);
    mat->data[1][1] = cosine;
    mat->data[1][2] =  -sine;
    mat->data[2][1] =   sine;
    mat->data[2][2] = cosine;
    return mat;
}

struct Matrix *mat_ry(float r) {
    struct Matrix *mat = mat_identity(4);
    float cosine = cosf(r), sine = sinf(r);
    mat->data[0][0] = cosine;
    mat->data[0][2] =   sine;
    mat->data[2][0] =  -sine;
    mat->data[2][2] = cosine;
    return mat;
}

struct Matrix *mat_rz(float r) {
    struct Matrix *mat = mat_identity(4);
    float cosine = cosf(r), sine = sinf(r);
    mat->data[0][0] = cosine;
    mat->data[0][1] =  -sine;
    mat->data[1][0] =   sine;
    mat->data[1][1] = cosine;
    return mat;
}