#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Esta función crea una matriz dinámica con m filas y n columnas
int **crearMatriz(int m, int n) {
    int **mat;
    int i;

    // Reservamos memoria para las filas
    mat = (int **)malloc(m * sizeof(int *));
    if (mat == NULL) {
        printf("Error al asignar memoria para las filas\n");
        exit(1);
    }

    // Reservamos memoria para las columnas de cada fila
    for (i = 0; i < m; i++) {
        mat[i] = (int *)malloc(n * sizeof(int));
        if (mat[i] == NULL) {
            printf("Error al asignar memoria para las columnas\n");
            exit(1);
        }
    }

    return mat;
}

// Esta función llena la matriz con números aleatorios distintos de cero
void llenarMatriz(int **mat, int m, int n) {
    int i, j;
    int num;

    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            // Generamos hasta que el número no sea cero
            do {
                num = rand();
            } while (num == 0);

            mat[i][j] = num;
        }
    }
}

// Esta función imprime la matriz
void imprimirMatriz(int **mat, int m, int n) {
    int i, j;

    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            printf("%d\t", mat[i][j]); // Se usa tabulador para que se vea ordenado
        }
        printf("\n");
    }
}

// Esta función cambia el tamaño de la matriz y conserva los valores originales si caben
int **redimensionarMatriz(int **mat, int m1, int n1, int m2, int n2) {
    int **nueva;
    int i, j;
    int num;

    // Creamos una nueva matriz del nuevo tamaño
    nueva = crearMatriz(m2, n2);

    // Copiamos los valores de la matriz anterior
    for (i = 0; i < m2; i++) {
        for (j = 0; j < n2; j++) {
            if (i < m1 && j < n1) {
                nueva[i][j] = mat[i][j];
            } else {
                // Si estamos fuera del rango viejo, ponemos un valor aleatorio ≠ 0
                do {
                    num = rand();
                } while (num == 0);

                nueva[i][j] = num;
            }
        }
    }

    // Liberamos la memoria de la matriz vieja
    for (i = 0; i < m1; i++) {
        free(mat[i]);
    }
    free(mat);

    return nueva;
}

// Esta función libera la memoria de cualquier matriz
void liberarMatriz(int **mat, int m) {
    int i;
    for (i = 0; i < m; i++) {
        free(mat[i]);
    }
    free(mat);
}

// Función principal
int main() {
    int m, n, m2, n2;
    int **matriz;

    srand(time(NULL)); // Inicializamos la semilla para que los números sean distintos

    // Le pedimos al usuario el tamaño de la matriz
    printf("Digite el número de filas y columnas (separados por espacio): ");
    scanf("%d %d", &m, &n);

    // Creamos la matriz original
    matriz = crearMatriz(m, n);
    llenarMatriz(matriz, m, n);

    // Mostramos la matriz original
    printf("\nMatriz original:\n");
    imprimirMatriz(matriz, m, n);

    // Pedimos el nuevo tamaño
    printf("\nDigite el nuevo número de filas y columnas: ");
    scanf("%d %d", &m2, &n2);

    // Redimensionamos la matriz
    matriz = redimensionarMatriz(matriz, m, n, m2, n2);

    // Mostramos la nueva matriz
    printf("\nMatriz redimensionada:\n");
    imprimirMatriz(matriz, m2, n2);

    // Liberamos la memoria
    liberarMatriz(matriz, m2);

    return 0;
}

