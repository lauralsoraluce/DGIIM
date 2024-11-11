/**
 * @file image.cpp
 * @brief Fichero con definiciones para los métodos primitivos de la clase Image
 *
 */

#include <cstring>
#include <cassert>
#include <iostream>
#include <cmath>

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
    set_pixel(k/cols,k%cols,value);

//    img[0][k] = value;
}

// This doesn't work if representation changes
byte Image::get_pixel (int k) const {
    // TODO this makes assumptions about the internal representation
    // TODO Can you reuse get_pixel(i,j)?
    return get_pixel(k/cols, k%cols);

//    return img[0][k];
}

// Métodos para almacenar y cargar imagenes en disco
bool Image::Save (const char * file_path) const {
    // TODO this makes assumptions about the internal representation
/*    byte * p = img[0];
    return WritePGMImage(file_path, p, rows, cols);*/

    byte * p = new byte [rows * cols];

    for (int  i = 0; i < rows*cols; ++i)
            p[i] = this->get_pixel(i);


    return WritePGMImage(file_path, p, rows, cols);
}

void Image::Invert() {
    if (get_rows()>0 && get_cols()>0) {
        byte pixel_inv;
        for (int i = 0; i < size(); i++) {
            set_pixel(i, 255- get_pixel(i));
        }
    }
}

// Modifica el contraste de una Imagen .
void Image::AdjustContrast (byte in1, byte in2, byte out1, byte out2) {
    double contrastado=0;
    byte correcion=0;

    if (in1>=0 && in2>=0 && out1>=0 && out2>=0 && in1<=255 && in2<=255 && out1<=255 && out2<=255 && in1<in2 && out1<out2) {
        for (int i = 0; i < get_rows(); i++) {
            for (int j=0; j< get_cols(); j++) {
                int z=get_pixel(i,j);

                if (z>=0 && z<in1){
                    double coc1= ((double)(out1-0)/(in1-0));
                    contrastado=0 + (coc1*(z-0));
                    correcion = round(contrastado);
                    set_pixel(i,j, (correcion));
                }
                if (z>=in1 && z<=in2){
                    double coc2= ((double)(out2-out1)/(in2-in1));
                    contrastado=out1 + (coc2*(z-in1));
                    correcion = round(contrastado);
                    set_pixel(i,j, (correcion));
                }
                if (z>in2 && z<=255){
                    double coc3= ((double)(255-out2)/(255-in2));
                    contrastado=out2+ (coc3*(z-in2));
                    correcion = round(contrastado);
                    set_pixel(i,j, (correcion));
                }
            }
        }
    }
}


double Image::Mean(int i, int j, int height, int width) const {
    double suma = 0;
    for (int rows=i; rows<(i+height); rows++) {
        for (int cols=j; cols<(j+width); cols++) {
            suma += double(img[rows][cols]);
        }
    }
    double mean = suma/(height*width);
    return mean;
}

Image Image::Subsample(int factor) const {
    int numrows = int(get_rows()/factor);
    int numcols = get_cols()/factor;

    Image subimage(numrows, numcols, 0);
    // If it isn't possible to create an icon, we return a completely black image with the new proportions.

    if (factor>0) {
        for (int i = 0; i < numrows; i++) {
            for (int j = 0; j < numcols; j++) {
                subimage.set_pixel(i, j, round(Mean(i * factor, j * factor, factor, factor)));
            }
        }
    }

    return subimage;
}

Image Image::Crop(int nrow, int ncol, int height, int width) const {
    Image nuevaImg(height, width, 0);
    // If  it isn't possible to crop the image, we return a completely black image with the given proportions

    if ((((nrow+height)<=get_rows()) && ((ncol+width)<=get_cols())) && (height>0 && width>0 && nrow>=0 && ncol>=0)) {
        for (int i=0; i<height; i++){
            for (int j=0; j<width; j++){
                nuevaImg.set_pixel(i,j, get_pixel((i+nrow),(j+ncol)));
            }
        }
    }

    return nuevaImg;
}

Image Image::Zoom2X() const {
    int size = (get_rows()*2)-1;
    Image aux(get_rows(), size, 0);
    Image nueva(size, size, 0);
    int k=0;
    int l=0;

    for (int j=0; j<size; j++) {
        if (j%2==0){
            for (int i=0; i<get_rows(); i++) {
                aux.set_pixel(i,j, get_pixel(i,l));
            }
            l++;
        }
        else {
            for (int i=0; i<get_rows(); i++) {
                aux.set_pixel(i,j, round(Mean(i,k,1,2)));
            }
            k++;
        }
    }
    k=0;
    l=0;
    for (int i=0; i<size; i++) {
        if (i%2==0) {
            for (int j=0; j<size; j++) {
                nueva.set_pixel(i,j,aux.get_pixel(l,j));
            }
            l++;
        }
        else {
            for (int j=0; j<size; j++) {
                if (j%2!=0) {
                    nueva.set_pixel(i, j, round(Mean(k, j / 2, 2, 2)));
                }
                else {
                    nueva.set_pixel(i,j,round(aux.Mean(k,j,2,1)));
                }
            }
            k++;
        }
    }

    return nueva;
}

void Image::ShuffleRows() {
    const int p=9973;
    int newr;

    byte ** k = new byte *[rows];

    for (int i=0; i<rows; i++) {
        k[i] = img[i];
    }
    for (int i=0; i<rows; i++) {
        newr=i*p%rows;
        img[i] = k[newr];
    }

/*    const int p= 9971;
    Image temp(rows, cols);
    int newr;

    for (int r=0; r<rows; r++) {
        newr = r*p%rows;
        for (int c=0; c<cols; c++) {
            temp.set_pixel(r,c,get_pixel(newr,c));
        }
    }

    Copy(temp);*/

}