/*
 * PSMM [G4011449] Labs
 * Last update: 05/02/2017
 * Issue date:  01/05/2016
 * 
 * Author: Pablo Quesada Barriuso
 *
 * This work is licensed under a Creative Commons
 * Attribution-NonCommercial-ShareAlike 4.0 International.
 * http:// https://creativecommons.org/licenses/by-nc-sa/4.0/
 * 
 * THE AUTHOR MAKES NO REPRESENTATION ABOUT THE SUITABILITY OF THIS SOURCE
 * CODE FOR ANY PURPOSE.  IT IS PROVIDED "AS IS" WITHOUT EXPRESS OR
 * IMPLIED WARRANTY OF ANY KIND.  THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOURCE CODE, INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
 * OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
 * OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE
 * OR PERFORMANCE OF THIS SOURCE CODE.
 */

/*
 * Function:  importDOUBLE
 * -----------------------
 * read data from a txt file into a matrix x of size rows x cols as double 
 *
 *  i_file: input file name
 *  rows: number of rows
 *  cols: number of cols
 *
 *  returns: a matrix of rows x cols elements of type double
 */
double* importDOUBLE(const char* i_file, int cols, int rows)
{
    FILE* fp;
    int i, j;

    fp = fopen (i_file, "rb");

    double* x = NULL;
    x = (double *) malloc( sizeof(double) * cols * rows);

    // read data from file
    for (i = 0; i< cols*rows; ++i) { fscanf(fp,"%lf",&x[i]); }

    fclose(fp);

    return x;
}

/*
 * Function:  importPGM
 * -----------------------
 * read data from a png image file into a matrix h_data of size wxh as unsigned char
 *
 *  i_file: input file name
 *
 *  w: width of the image (number of cols)
 *  h: height of the image (number of rows)
 *
 *  returns: a matrix of wxh elements of type unsigned char
 */
unsigned char* importPGM(const char* i_file, int& w, int& h)
{
    FILE* fp;
    int i;
    // warning: ignoring return value of ‘int fscanf(FILE*, const char*, ...)’, declared with attribute warn_unused_result
    int f = 0;
    // read buffers
    unsigned char c; char buffer[100];

    fp = fopen (i_file, "rb");

    if( fp == NULL ) { fprintf(stderr,"ERROR: Failed to load file: %s\n",i_file); return NULL; }

    // clean header of file
    f = fscanf(fp,"%s", buffer); c=fgetc(fp); c=fgetc(fp); if(c!='#')ungetc(c,fp);
    while((c=='#')) { while (c != '\n') { c = fgetc(fp); } }
    // read data from file
    f = fscanf(fp,"%s",buffer); w=atoi(buffer); f = fscanf(fp,"%s",buffer); h=atoi(buffer);

    unsigned char* h_data = NULL;
    h_data = (unsigned char *) malloc( sizeof(unsigned char) * w * h);

    f = fscanf(fp,"%s",buffer); c = fgetc(fp); ;

    // read data from file
    for (i = 0; i< w*h; ++i) { c=fgetc(fp); h_data[i] = c; }

    fclose(fp);

    return h_data;
}
