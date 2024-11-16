import express from "express";
import Productos from "../model/productos.js";

const router = express.Router();

// Redirigir a la portada principal
router.get('/', (req, res) => {
  res.redirect('/portada');
});

// Mostrar la portada con todos los productos
router.get('/portada', async (req, res) => {
  try {
    const productos = await Productos.find({});
    res.render('home.html', { productos, usuario: req.username });
  } catch (err) {
    res.status(500).send({ err });
  }
});

// Buscar productos
router.post('/buscar', async (req, res) => {
  const { search } = req.body;
  try {
    const productos = await Productos.find({
      $or: [
        { title: { $regex: search, $options: 'i' } },
        { description: { $regex: search, $options: 'i' } }
      ]
    });
    res.render('home.html', { productos, usuario: req.username });
  } catch (err) {
    res.status(500).send({ err });
  }
});

// Agregar productos al carrito
router.post('/carrito/agregar', (req, res) => {
  const productoId = req.body.productoId;
  if (!req.session.carrito) req.session.carrito = [];
  req.session.carrito.push(productoId);
  res.redirect('/carrito');
});

// Mostrar productos del carrito
router.get('/carrito', async (req, res) => {
  if (!req.session.carrito || req.session.carrito.length === 0) {
    return res.render('carrito_vacio.html');
  }
  try {
    const productosEnCarrito = await Productos.find({ _id: { $in: req.session.carrito } });
    res.render('carrito.html', { productos: productosEnCarrito, usuario: req.username });
  } catch (err) {
    res.status(500).send({ err });
  }
});

// API para verificar estado del carrito
router.get('/api/estado_carrito', (req, res) => {
  const carritoVacio = !req.session.carrito || req.session.carrito.length === 0;
  res.json({ carritoVacio });
});

// Ver detalle de un producto
router.get('/producto/:id', async (req, res) => {
  const productoId = req.params.id;
  try {
    const producto = await Productos.findById(productoId);
    if (!producto) return res.status(404).send('Producto no encontrado');
    res.render('detalle_producto.html', { producto, usuario: req.username });
  } catch (err) {
    res.status(500).send({ err });
  }
});

export default router;
