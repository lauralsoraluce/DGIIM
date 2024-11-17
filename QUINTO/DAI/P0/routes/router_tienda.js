import express from "express";
import Productos from "../model/productos.js";
import { verificarSesion } from './usuarios.js'; // Asegúrate de importar el middleware

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

// Mostrar productos del carrito
router.get('/carrito', verificarSesion, async (req, res) => {
  try {
    const usuario = req.usuario;

    // Poblar el carrito para obtener los detalles de los productos
    await usuario.populate('carrito');  // Esto cargará los detalles de los productos

    // Verificar si el carrito está vacío
    if (usuario.carrito.length === 0) {
      return res.render('carrito_vacio.html');
    }

    res.render('carrito.html', { productos: usuario.carrito });  // Renderizar los productos en el carrito
  } catch (error) {
    console.error('Error al obtener el carrito:', error);
    res.status(500).send('Error al obtener el carrito');
  }
});

// Ruta protegida para agregar productos al carrito
router.post('/carrito/agregar', verificarSesion, async (req, res) => {
  const { productoId } = req.body;

  try {
    const producto = await Productos.findById(productoId);
    if (!producto) {
      return res.status(404).send('Producto no encontrado');
    }

    const usuario = req.usuario;

    if (!usuario.carrito.includes(producto._id)) {
      usuario.carrito.push(producto._id);
      await usuario.save();
    }

    res.redirect('/carrito'); // Redirige al carrito actualizado
  } catch (error) {
    console.error('Error al añadir producto al carrito:', error);
    res.status(500).send('Error interno al añadir producto al carrito');
  }
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
