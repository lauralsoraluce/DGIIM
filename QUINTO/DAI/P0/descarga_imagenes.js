import fetch from 'node-fetch'; 
import fs from 'fs';             
import path from 'path';         

// Creo la carpeta "imagenes"
const carpetaImagenes = './imagenes';

async function descargarImagen(url, nombreArchivo) {
    const response = await fetch(url); // Petición para obtener la imagen
    const buffer = await response.buffer(); // Convertimos la imagen en un buffer de datos
    fs.writeFileSync(path.join(carpetaImagenes, nombreArchivo), buffer); // Guardamos la imagen
    console.log(`Imagen guardada: ${nombreArchivo}`);
}

async function descargarImagenesDeProductos() {
    try {
        // Obtener los productos de la API
        const response = await fetch('https://fakestoreapi.com/products');
        const productos = await response.json(); // Convertimos la respuesta a JSON

        // Iterar sobre los productos para descargar las imágenes
        for (const producto of productos) {
            const urlImagen = producto.image;   // URL de la imagen del producto
            const nombreArchivo = `${producto.id}.jpg`; // El ID del producto será el nombre del archivo
            await descargarImagen(urlImagen, nombreArchivo); // Descargamos y guardamos la imagen
        }

        console.log('Descarga completada');

    } catch (error) {
        console.error('Error al descargar las imágenes:', error);
    }
}

descargarImagenesDeProductos();

