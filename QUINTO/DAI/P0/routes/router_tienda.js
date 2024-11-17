import express from "express";
import Productos from "../model/productos.js";
import { verificarSesion } from './usuarios.js'; // Asegúrate de importar el middleware
import { verificarAdmin } from './usuarios.js';

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
router.get('/producto/:id', verificarSesion, async (req, res) => {
  const productoId = req.params.id;
  try {
    const producto = await Productos.findById(productoId);
    if (!producto) return res.status(404).send('Producto no encontrado');

    // Si el usuario está autenticado, obtenemos su información
    const usuario = req.usuario ? req.usuario.username : null;
    const admin = req.usuario ? req.usuario.admin : false;

    // Renderizar el detalle del producto, con la información de usuario y admin si está autenticado
    res.render('detalle_producto.html', { 
      producto, 
      usuario, 
      admin
    });
  } catch (err) {
    res.status(500).send({ err });
  }
});

// Ruta para editar producto
router.post('/producto/editar/:id', verificarSesion, verificarAdmin, async (req, res) => {
  const { id } = req.params;
  let { title, price } = req.body;

  try {
    price = parseFloat(price); // Convertir el precio a un número flotante

    if (isNaN(price)) {
      return res.status(400).send('El precio debe ser un número válido.');
    }
    
    const producto = await Productos.findByIdAndUpdate(
      id,
      { title, price },
      { new: true, runValidators: true } // Ejecutar validaciones
    );

    if (!producto) {
      return res.status(404).send('Producto no encontrado');
    }

    res.status(200).send(`Producto actualizado: ${producto.title}, $${producto.price}`);
  } catch (error) {
    console.error('Error al actualizar el producto:', error);
    res.status(500).send('Error al actualizar el producto');
  }
});

export default router;
