// routes/router_tienda.js
import express from "express";
import Productos from "../model/productos.js";
import session from 'express-session';
const router = express.Router();

// Ruta base para redirigir a la portada para que sea lo que se ve de primeras
router.get('/', (req, res) => {
    res.redirect('/portada');  // Redirige a /portada cuando acceden a /
});

// Ruta para la portada
router.get('/portada', async (req, res) => {
  try {
    const productos = await Productos.find({}); // Obtener todos los productos
    res.render('home.html', { productos });  // Pasa todos los productos de la BD a home.html
  } catch (err) {
    res.status(500).send({ err });
  }
});

// Buscar productos en la base de datos que coincidan con el término de búsqueda
router.post('/buscar', async (req, res) => {
  const { search } = req.body;  // Término de búsqueda enviado por el formulario

  try {
    const productos = await Productos.find({  // Va comprobando producto por producto
      $or: [
        { title: { $regex: search, $options: 'i' } },  // Busca en el título (insensible a mayúsculas)
        { description: { $regex: search, $options: 'i' } }  // Busca en la descripción (insensible a mayúsculas)
      ]
    });

    res.render('home.html', { productos });  // Pasa todos los productos de la BD a home.html
  } catch (err) {
    res.status(500).send({ err });
  }
});

// Guardar el producto en la sesión del usuario
router.post('/carrito/agregar', (req, res) => {
  const productoId = req.body.productoId;

  if (!req.session.carrito) {
    req.session.carrito = [];  // Si aún no se ha creado el carrito, se crea
  }

  req.session.carrito.push(productoId);  // Añade el producto al carrito

  res.redirect('/carrito');  // Redirige al usuario a la página del carrito 
});

// Mostrar los productos del carrito
router.get('/carrito', async (req, res) => {
  if (!req.session.carrito || req.session.carrito.length === 0) {
    return res.render('carrito_vacio.html');  // Si está vacío, redirige a carrito_vacio.html
  }

  try {
    const productosEnCarrito = await Productos.find({_id: { $in: req.session.carrito } });  // Busca los productos por su id
    res.render('carrito.html', { productos: productosEnCarrito });  
  } catch (err) {
    res.status(500).send({ err });
  }
});

// Para deshabilitar el icono del carrito en la interfaz
router.get('/api/estado_carrito', (req, res) => {
    const carritoVacio = !req.session.carrito || req.session.carrito.length === 0;
    res.json({ carritoVacio });  // Devuelve un JSON con el estado del carrito
});

// Ruta para ver el detalle de un producto
router.get('/producto/:id', async (req, res) => {
  const productoId = req.params.id;

  try {
    const producto = await Productos.findById(productoId);  // Busca el producto por su ID
    if (!producto) {
      return res.status(404).send('Producto no encontrado');
    }
    res.render('detalle_producto.html', { producto });  // Renderiza la vista detalle con el producto encontrado
  } catch (err) {
    res.status(500).send({ err });
  }
});


export default router;
