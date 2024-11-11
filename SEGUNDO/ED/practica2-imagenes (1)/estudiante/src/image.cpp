/**
 * @file image.cpp
 * @brief Fichero con definiciones para los métodos primitivos de la clase Image
 *
 */

#include <cstring>
#include <cassert>
#include <iostream>

#include <image.h>
#include <imageIO.h>

using namespace std;

/********************************
      FUNCIONES PRIVADAS
********************************/
void Image::Allocate(int nrows, int ncols, byte * buffer){
    rows = nrows;
    cols = ncols;

    img = new byte * [rows];

    if (buffer != 0)
        img[0] = buffer;
    else
        img[0] = new byte [rows * cols];

    for (int i=1; i < rows; i++)
        img[i] = img[i-1] + cols;
}

// Función auxiliar para inicializar imágenes con valores por defecto o a partir de un buffer de datos
void Image::Initialize (int nrows, int ncols, byte * buffer){
    if ((nrows == 0) || (ncols == 0)){
        rows = cols = 0;
        img = 0;
    }
    else Allocate(nrows, ncols, buffer);
}

// Función auxiliar para copiar objetos Imagen

void Image::Copy(const Image & orig){
    Initialize(orig.rows,orig.cols);
    for (int k=0; k<rows*cols;k++)
        set_pixel(k,orig.get_pixel(k));
}

// Función auxiliar para destruir objetos Imagen
bool Image::Empty() const{
    return (rows == 0) || (cols == 0);
}

void Image::Destroy(){
    if (!Empty()){
        delete [] img[0];
        delete [] img;
    }
}

LoadResult Image::LoadFromPGM(const char * file_path){
    if (ReadImageKind(file_path) != IMG_PGM)
        return LoadResult::NOT_PGM;

    byte * buffer = ReadPGMImage(file_path, rows, cols);
    if (!buffer)
        return LoadResult::READING_ERROR;

    Initialize(rows, cols, buffer);
    return LoadResult::SUCCESS;
}

/********************************
       FUNCIONES PÚBLICAS
********************************/

// Constructor por defecto

Image::Image(){
    Initialize();
}

// Constructores con parámetros
Image::Image (int nrows, int ncols, byte value){
    Initialize(nrows, ncols);
    for (int k=0; k<rows*cols; k++) set_pixel(k,value);
}

bool Image::Load (const char * file_path) {
    Destroy();
    return LoadFromPGM(file_path) == LoadResult::SUCCESS;
}

// Constructor de copias

Image::Image (const Image & orig){
    assert (this != &orig);
    Copy(orig);
}

// Destructor

Image::~Image(){
    Destroy();
}

// Operador de Asignación

Image & Image::operator= (const Image & orig){
    if (this != &orig){
        Destroy();
        Copy(orig);
    }
    return *this;
}

// Métodos de acceso a los campos de la clase

int Image::get_rows() const {
    return rows;
}

int Image::get_cols() const {
    return cols;
}

int Image::size() const{
    return get_rows()*get_cols();
}

// Métodos básicos de edición de imágenes
void Image::set_pixel (int i, int j, byte value) {
    img[i][j] = value;
}
byte Image::get_pixel (int i, int j) const {
    return img[i][j];
}

// This doesn't work if representation changes
void Image::set_pixel (int k, byte value) {
    // TODO this makes assumptions about the internal representation
    // TODO Can you reuse set_pixel(i,j,value)?
    img[0][k] = value;
}

// This doesn't work if representation changes
byte Image::get_pixel (int k) const {
    // TODO this makes assumptions about the internal representation
    // TODO Can you reuse get_pixel(i,j)?
    return img[0][k];
}

// Métodos para almacenar y cargar imagenes en disco
bool Image::Save (const char * file_path) const {
    // TODO this makes assumptions about the internal representation
    byte * p = img[0];
    return WritePGMImage(file_path, p, rows, cols);
}

void Image::Invert() {
    if (get_rows()>0 && get_cols()>0) {
        byte pixel_inv;
        for (int i = 0; i < get_rows(); i++) {
            for (int j = 0; j < get_cols(); j++) {
                pixel_inv = 255 - get_pixel(i, j);
                set_pixel(i, j, pixel_inv);
            }
        }
    }
}

/*void Image::AdjustContrast(byte in1, byte in2, byte out1, byte out2) {

}*/

double Image::Mean(int i, int j, int height, int width) const {
    double suma = 0;
    for (int rows=i; rows<height; rows++) {
        for (int cols=j; cols<width; cols++) {
            suma += get_pixel(rows,cols);
        }
    }
    double mean = suma/((height-i)*(width-j));
    return mean;
}

Image Image::Subsample(int factor) const {
    double suma=0;
    int numrows = get_rows()/factor;
    int numcols = get_cols()/factor;
    // The number of columns and rows is that of the original image, divided by the factor (the integer part)
    Image subImagen(numrows, numcols, 0);
    // We create the new image, with its number of columns and rows, and all the pixels set to 0

    for (int i=0; i<(numrows*factor); i+=factor){
        for (int j=0; j<(numcols*factor); j+=factor) {
            for (int k1=i; k1<i+factor; k1++) {
                for (int k2=j; k2<j+factor; k2++) {
                    suma+= get_pixel(k1,k2);
                    // It stores the sum of the factorxfactor pixels
                }
            }
            subImagen.set_pixel((i/factor), (j/factor), (suma/factor));
        }
    }
    return subImagen;
}

Image Image::Crop(int nrow, int ncol, int height, int width) const {
    Image nuevaImg(height, width, 0);
    // If  it isn't possible to crop the image, we return a completely black image of the given proportions

    if (((nrow+height)<=get_rows()) && ((ncol+width)<=get_cols())) {
        for (int i=0; i<height; i++){
            for (int j=0; j<width; j++){
                nuevaImg.set_pixel(i,j, get_pixel((i+height),(j+width)));
            }
        }
    }

    return nuevaImg;
}

/*Image Image::Zoom2X() const {
    Image nuevaImg((get_rows()*2), (get_cols()*2), 0);

    for (int i=0; i<get_rows(); i++){
        for (int j=0; j<get_cols(); j++){
            for (int k)
        }
    }

    return nuevaImg;
}*/

void Image::ShuffleRows() {
    const int p=9973;
    Image temp(rows, cols);
    int newr;

    for (int r=0; r<rows; r++){
        newr = r*p;
        for (int c=0; c<cols; c++)
            temp.set_pixel(newr,c,get_pixel(r,c));
    }

    Copy(temp);
}