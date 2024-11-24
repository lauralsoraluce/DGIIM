import express from "express";
import Productos from "../model/productos.js";
import { verificarSesion } from './usuarios.js'; // Asegúrate de importar el middleware
import { verificarAdmin } from './usuarios.js';
import logger from '../utils/logger.js';

const router = express.Router();

// Redirigir a la portada principal
router.get('/', (req, res) => {
  res.redirect('/portada');
});

// Mostrar la portada con todos los productos
router.get('/portada', async (req, res) => {
  try {
    logger.info('GET /portada - Solicitud recibida');
    const productos = await Productos.find({});
    res.render('home.html', { productos, usuario: req.username });
  } catch (err) {
    logger.error(`Error al obtener portada: ${err.message}`);
    res.status(500).send({ err });
  }
});

// Buscar productos
router.post('/buscar', async (req, res) => {
  const { search } = req.body;
  try {
    logger.info(`POST /buscar - Búsqueda con término: ${search}`);
    const productos = await Productos.find({
      $or: [
        { title: { $regex: search, $options: 'i' } },
        { description: { $regex: search, $options: 'i' } }
      ]
    });
    res.render('home.html', { productos, usuario: req.username });
  } catch (err) {
    logger.error(`Error en búsqueda: ${err.message}`);
    res.status(500).send({ err });
  }
});

// Mostrar productos del carrito
router.get('/carrito', verificarSesion, async (req, res) => {
  try {
    logger.info(`GET /carrito - Usuario: ${req.usuario?.username || "Desconocido"}`);
    const usuario = req.usuario;

    await usuario.populate('carrito'); // Poblar detalles de productos

    if (usuario.carrito.length === 0) {
      logger.warn('Carrito vacío para el usuario');
      return res.render('carrito_vacio.html');
    }

    res.render('carrito.html', { productos: usuario.carrito });
  } catch (error) {
    logger.error(`Error al obtener el carrito: ${error.message}`);
    res.status(500).send('Error al obtener el carrito');
  }
});

// Ruta protegida para agregar productos al carrito
router.post('/carrito/agregar', verificarSesion, async (req, res) => {
  const { productoId } = req.body;

  try {
    logger.info(`POST /carrito/agregar - Agregando producto: ${productoId}`);
    const producto = await Productos.findById(productoId);
    if (!producto) {
      logger.warn(`Producto no encontrado: ${productoId}`);
      return res.status(404).send('Producto no encontrado');
    }

    const usuario = req.usuario;

    if (!usuario.carrito.includes(producto._id)) {
      usuario.carrito.push(producto._id);
      await usuario.save();
    }

    res.redirect('/carrito');
  } catch (error) {
    logger.error(`Error al añadir producto al carrito: ${error.message}`);
    res.status(500).send('Error interno al añadir producto al carrito');
  }
});

// Ver detalle de un producto
router.get('/producto/:id', verificarSesion, async (req, res) => {
  const productoId = req.params.id;
  try {
    logger.info(`GET /producto/${productoId} - Solicitud de detalle de producto`);
    const producto = await Productos.findById(productoId);
    if (!producto) {
      logger.warn(`Producto no encontrado: ${productoId}`);
      return res.status(404).send('Producto no encontrado');
    }

    const usuario = req.usuario ? req.usuario.username : null;
    const admin = req.usuario ? req.usuario.admin : false;

    res.render('detalle_producto.html', { producto, usuario, admin });
  } catch (err) {
    logger.error(`Error al obtener detalle del producto: ${err.message}`);
    res.status(500).send({ err });
  }
});

// Ruta para editar producto
router.post('/producto/editar/:id', verificarSesion, verificarAdmin, async (req, res) => {
  const { id } = req.params;
  let { title, price } = req.body;

  try {
    logger.info(`POST /producto/editar/${id} - Edición del producto`);
    price = parseFloat(price);

    if (isNaN(price)) {
      logger.warn(`Precio inválido proporcionado: ${price}`);
      return res.status(400).send('El precio debe ser un número válido.');
    }

    const producto = await Productos.findByIdAndUpdate(
      id,
      { title, price },
      { new: true, runValidators: true }
    );

    if (!producto) {
      logger.warn(`Producto no encontrado: ${id}`);
      return res.status(404).send('Producto no encontrado');
    }

    res.status(200).send(`Producto actualizado: ${producto.title}, $${producto.price}`);
  } catch (error) {
    logger.error(`Error al actualizar el producto: ${error.message}`);
    res.status(500).send('Error al actualizar el producto');
  }
});

export default router;
