//*Alexander Leon*//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void invert(char **image, int rows, int cols);
void flip(char **image, int rows, int cols, char direction);
void rotate(char ***image, int *rows, int *cols, int degrees);
void stretch(char ***image, int *rows, int *cols, int factor);
void freeResources(char **image, int rows);
void outputImage(char **image, int rows, int cols);

void invert(char **image, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            image[i][j] = (image[i][j] == '*') ? ' ' : '*';
        }
    }
}

void flip(char **image, int rows, int cols, char direction) {
    if (direction == 'H' || direction == 'h') {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols / 2; j++) {
                char temp = image[i][j];
                image[i][j] = image[i][cols - j - 1];
                image[i][cols - j - 1] = temp;
            }
        }
    } else if (direction == 'V' || direction == 'v') {
        for (int i = 0; i < rows / 2; i++) {
            for (int j = 0; j < cols; j++) {
                char temp = image[i][j];
                image[i][j] = image[rows - i - 1][j];
                image[rows - i - 1][j] = temp;
            }
        }
    }
}

void rotate90DegreesClockwise(char ***image, int *rows, int *cols) {
    char **rotatedImage = (char **)malloc(*cols * sizeof(char *));
    for (int i = 0; i < *cols; i++) {
        rotatedImage[i] = (char *)malloc(*rows * sizeof(char));
        for (int j = 0; j < *rows; j++) {
            rotatedImage[i][j] = (*image)[*rows - j - 1][i];
        }
    }

    // Free the old image memory
    freeResources(*image, *rows);
    // Update the image pointer and its dimensions
    *image = rotatedImage;
    int temp = *rows;
    *rows = *cols;
    *cols = temp;
}

void rotate(char ***image, int *rows, int *cols, int degrees) {
    int numberOfRotations = degrees / 90;
    for (int i = 0; i < numberOfRotations; i++) {
        rotate90DegreesClockwise(image, rows, cols);
    }
}
void stretch(char ***image, int *rows, int *cols, int factor) {
    int newCols = (*cols) * factor;
    char **stretchedImage = (char **)malloc(*rows * sizeof(char *));
    for (int i = 0; i < *rows; i++) {
        stretchedImage[i] = (char *)malloc(newCols * sizeof(char));
        for (int j = 0; j < newCols; j++) {
            stretchedImage[i][j] = (*image)[i][j / factor];
        }
    }

    // Free the old image memory
    for (int i = 0; i < *rows; i++) {
        free((*image)[i]);
    }
    free(*image);
    // Update the image and its dimensions
    *image = stretchedImage;
    *cols = newCols;
}

char** readImage(int *rows, int *cols) {
    if (scanf("%d %d", rows, cols) != 2 || *rows <= 0 || *cols <= 0) {
        exit(1); // Exit if the dimensions are invalid
    }
    while (getchar() != '\n');//Read the newline

    // Allocate memory for the array of row pointers
    char **image = (char**)malloc(*rows * sizeof(char*));
    if (!image) {
        exit(1); // Exit if memory allocation fails
    }
    for (int i = 0; i < *rows; i++) {
        // Allocate memory for each row
        image[i] = (char*)malloc(*cols * sizeof(char));
        if (!image[i]) {
        // Cleanup and exit if memory allocation fails
        freeResources(image, i);
        exit(1);
        }
        // Read each pixel in the row
        for (int j = 0; j < *cols; j++) {
            char pixel = getchar();

            // Validate the pixel and ignore newline characters
            if(pixel != '*' && pixel != ' ') {
                // Cleanup and exit if the input is invalid
                freeResources(image, *rows);
                exit(1);
            }
            image[i][j] = pixel;
        }
        getchar();//Read the newline character at the end of each row
    }
    return image;
}

int main (int argc, char *argv[]){
    int rows, cols;
    char **image = readImage(&rows, &cols);

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "inv") == 0) {
            invert(image, rows, cols);
        } else if (strcmp(argv[i], "flip") == 0 && i + 1 < argc) {
            char direction = argv[++i][0];
            if(direction != 'V' && direction != 'v' && direction != 'H' && direction != 'h'){
                freeResources(image, rows);
                exit(2);
            }
            flip(image, rows, cols, direction);

        } else if (strcmp(argv[i], "rot") == 0 && i + 1 < argc) {
            int degrees = atoi(argv[++i]);
            if (degrees != 90 && degrees != 180 && degrees != 270){
                freeResources(image, rows);
                exit(2);
            }
            rotate(&image, &rows, &cols, degrees);
        } else if (strcmp(argv[i], "stretch") == 0 && i + 1 < argc) {
            int factor = atoi(argv[++i]);
            if (factor <= 0){
                freeResources(image, rows);
                exit(2);
            }
            stretch(&image, &rows, &cols, factor);
        } else {
            freeResources(image, rows);
            exit(2);
        }
    }
    //Print output
    outputImage(image, rows, cols);
    //Free allocated memory
    freeResources(image, rows);

    return 0;
}
void freeResources(char **image, int rows) {
    for (int i = 0; i < rows; i++) {
        free(image[i]);
    }
    free(image);
}
void outputImage(char **image, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            putchar(image[i][j]);
        }
        putchar('\n'); // Move to the next line after printing each row
    }
}
