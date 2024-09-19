#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "image.h"

ImagePPM *readPPM(char *filename) {
    ImagePPM *pImagePPM=malloc(sizeof(ImagePPM));

    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        return NULL;
    }
    fscanf(fp, "%s %d %d %d", pImagePPM->magic, &pImagePPM->width, &pImagePPM->height, &pImagePPM->max_value);

    pImagePPM->pixels = malloc(pImagePPM->height * sizeof(Pixel *));
    for (int r = 0; r < pImagePPM->height; r++) {
        pImagePPM->pixels[r] = malloc(pImagePPM->width * sizeof(Pixel));
    }

    for (int r = 0; r < pImagePPM->height; r++) {
        for (int c = 0; c < pImagePPM->width; c++) {
            fscanf(fp, "%d %d %d", &pImagePPM->pixels[r][c].red, &pImagePPM->pixels[r][c].green, &pImagePPM->pixels[r][c].blue);
        }
    }

    fclose(fp);
    return pImagePPM;
}

int writePPM(ImagePPM *pImagePPM, char *filename) {
    FILE *fp2;
    fp2 = fopen(filename, "w");
    if (fp2 == NULL) {
        return 0;
    }
    fprintf(fp2, "%s\n%d  %d  %d\n", pImagePPM->magic, pImagePPM->width, pImagePPM->height, pImagePPM->max_value);

    for (int r = 0; r < pImagePPM->height; r++) {
        for (int c = 0; c < pImagePPM->width; c++) {
            fprintf(fp2, "%d %d %d  ", pImagePPM->pixels[r][c].red, pImagePPM->pixels[r][c].green, pImagePPM->pixels[r][c].blue);
        }
        fprintf(fp2, "\n");
    }
    fclose(fp2);
    return 1;
}

ImagePPM *rotatePPM(ImagePPM *pImagePPM) {
    ImagePPM *p2=malloc(sizeof(ImagePPM));
    strcpy(p2->magic, pImagePPM->magic);
    p2->width = pImagePPM->height;
    p2->height = pImagePPM->width;
    p2->max_value = pImagePPM->max_value;

    p2->pixels = malloc(p2->height * sizeof(Pixel *));
    for (int r = 0; r < p2->height; r++) {
        p2->pixels[r] = malloc(p2->width * sizeof(Pixel));
    }

    for (int r = 0; r < pImagePPM->height; r++) {
        for (int c = 0; c < pImagePPM->width; c++) {
            p2->pixels[c][pImagePPM->height - r - 1] = pImagePPM->pixels[r][c];
        }
    }
    return p2;
}

ImagePPM *flipPPM(ImagePPM *pImagePPM) {
    ImagePPM *p2=malloc(sizeof(ImagePPM));
    Pixel temp;
    strcpy(p2->magic, pImagePPM->magic);
    p2->width = pImagePPM->width;
    p2->height = pImagePPM->height;
    p2->max_value = pImagePPM->max_value;

    p2->pixels = malloc(p2->height * sizeof(Pixel *));
    for (int r = 0; r < p2->height; r++) {
        p2->pixels[r] = malloc(p2->width * sizeof(Pixel));
    }
    
    for (int r = 0; r < p2->height; r++) {
        for (int left = 0, right = p2->width - 1; left < ((p2->width) / 2); left++, right--) {
            temp = pImagePPM->pixels[r][left];
            p2->pixels[r][left] = pImagePPM->pixels[r][right];
            p2->pixels[r][right] = temp;
        }
    }
    return p2;
}

ImagePPM *enlargePPM(ImagePPM *pImagePPM) {
    ImagePPM *p2=malloc(sizeof(ImagePPM));
    strcpy(p2->magic, pImagePPM->magic);
    p2->width = (pImagePPM->width * 2);
    p2->height = (pImagePPM->height * 2);
    p2->max_value = pImagePPM->max_value;

    p2->pixels = malloc(p2->height * sizeof(Pixel *));
    for (int r = 0; r < p2->height; r++) {
        p2->pixels[r] = malloc(p2->width * sizeof(Pixel));
    }

    for (int r = 0; r < pImagePPM->height; r++) {
        for (int c = 0; c < pImagePPM->width; c++) {
            p2->pixels[r * 2][c * 2] = pImagePPM->pixels[r][c];
            p2->pixels[(r * 2) + 1][c * 2] = pImagePPM->pixels[r][c];
            p2->pixels[r * 2][(c * 2) + 1] = pImagePPM->pixels[r][c];
            p2->pixels[(r * 2) + 1][(c * 2) + 1] = pImagePPM->pixels[r][c];
        }
    }
    return p2;
}

ImagePPM *shrinkPPM(ImagePPM *pImagePPM) {
    ImagePPM *p2=malloc(sizeof(ImagePPM));
    strcpy(p2->magic, pImagePPM->magic);
    p2->width = (pImagePPM->width / 2);
    p2->height = (pImagePPM->height / 2);
    p2->max_value = pImagePPM->max_value;

    p2->pixels = malloc(p2->height * sizeof(Pixel *));
    for (int r = 0; r < p2->height; r++) {
        p2->pixels[r] = malloc(p2->width * sizeof(Pixel));
    }
    double avgRed = 0;
    double avgGreen = 0;
    double avgBlue = 0;

    for (int r = 0; r < p2->height; r++) {
        for (int c = 0; c < p2->width; c++) {
            avgRed += pImagePPM->pixels[r * 2][c * 2].red;
            avgGreen += pImagePPM->pixels[r * 2][c * 2].green;
            avgBlue += pImagePPM->pixels[r * 2][c * 2].blue;
            avgRed += pImagePPM->pixels[(r * 2) + 1][c * 2].red;
            avgGreen += pImagePPM->pixels[(r * 2) + 1][c * 2].green;
            avgBlue += pImagePPM->pixels[(r * 2) + 1][c * 2].blue;
            avgRed += pImagePPM->pixels[r * 2][(c * 2) + 1].red;
            avgGreen += pImagePPM->pixels[r * 2][(c * 2) + 1].green;
            avgBlue += pImagePPM->pixels[r * 2][(c * 2) + 1].blue;
            avgRed += pImagePPM->pixels[(r * 2) + 1][(c * 2) + 1].red;
            avgGreen += pImagePPM->pixels[(r * 2) + 1][(c * 2) + 1].green;
            avgBlue += pImagePPM->pixels[(r * 2) + 1][(c * 2) + 1].blue;

            avgRed = round(avgRed / 4);
            avgGreen = round(avgGreen / 4);
            avgBlue = round(avgBlue / 4);

            p2->pixels[r][c].red = avgRed;
            p2->pixels[r][c].green = avgGreen;
            p2->pixels[r][c].blue = avgBlue;

            avgRed = 0;
            avgGreen = 0;
            avgBlue = 0;
        }
    }
    return p2;
}

ImagePPM *invertPPM(ImagePPM *pImagePPM) {
    ImagePPM *p2=malloc(sizeof(ImagePPM));
    strcpy(p2->magic, pImagePPM->magic);
    p2->width = pImagePPM->width;
    p2->height = pImagePPM->height;
    p2->max_value = pImagePPM->max_value;

    p2->pixels = malloc(p2->height * sizeof(Pixel *));
    for (int r = 0; r < p2->height; r++) {
        p2->pixels[r] = malloc(p2->width * sizeof(Pixel));
    }

    for (int r = 0; r < pImagePPM->height; r++) {
        for (int c = 0; c < pImagePPM->width; c++) {
            p2->pixels[r][c].red = abs(pImagePPM->pixels[r][c].red - pImagePPM->max_value);
            p2->pixels[r][c].green = abs(pImagePPM->pixels[r][c].green - pImagePPM->max_value);
            p2->pixels[r][c].blue = abs(pImagePPM->pixels[r][c].blue - pImagePPM->max_value);
        }
    }
    return p2;
}

ImagePPM *cropPPM(ImagePPM *pImagePPM, int r1, int c1, int r2, int c2) {
    // r1 value should always be less than r2 value, so the results are always positive
    if (r1 > r2) {
        int temp;
        temp = r1;
        r1 = r2;
        r2 = temp;
    }
    
    // Same thing here
    if (c1 > c2) {
        int temp;
        temp = c1;
        c1 = c2;
        c2 = temp;
    }

    ImagePPM *p2=malloc(sizeof(ImagePPM));
    strcpy(p2->magic, pImagePPM->magic);
    p2->width = c2 - c1 + 1;
    p2->height = r2 - r1 + 1;
    p2->max_value = pImagePPM->max_value;

    p2->pixels = malloc(p2->height * sizeof(Pixel *));

    for (int r = 0; r < p2->height; r++) {
        p2->pixels[r] = malloc(p2->width * sizeof(Pixel));
    }
    
    for (int r = r1; r <= r2; r++) {
        for (int c = c1; c <= c2; c++) {
            p2->pixels[r - r1][c - c1] = pImagePPM->pixels[r][c];

        }
    }

    return p2;
}

void freeSpacePPM(ImagePPM *pImagePPM) {
    for (int i = 0; i < pImagePPM->height; i++) {
        free(pImagePPM->pixels[i]);
    }
    free(pImagePPM->pixels);
    free(pImagePPM);

}