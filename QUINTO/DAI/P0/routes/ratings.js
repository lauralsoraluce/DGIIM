import express from 'express';
import Productos from '../model/productos.js';

const router = express.Router();

// Lista los ratings de todos los productos con paginación
router.get('/', async (req, res) => {
  const { desde = 0, hasta = 10 } = req.query;
  try {
    const productos = await Productos.find({}, { _id: 1, title: 1, rating: 1 }) // Solo obtener campos necesarios
      .skip(parseInt(desde))
      .limit(parseInt(hasta) - parseInt(desde) + 1);
    res.json(productos.map(p => ({ id: p._id, title: p.title, ...p.rating })));
  } catch (err) {
    res.status(500).json({ error: 'Error al obtener los ratings' });
  }
});

// Obtiene el rating de un producto por ID
router.get('/:id', async (req, res) => {
  try {
    const producto = await Productos.findById(req.params.id, { _id: 1, title: 1, rating: 1 }); // Solo obtener campos necesarios
    if (!producto) return res.status(404).json({ error: 'Producto no encontrado' });
    res.json({ id: producto._id, title: producto.title, ...producto.rating });
  } catch (err) {
    res.status(500).json({ error: 'Error al obtener el rating' });
  }
});

// Modifica el rating de un producto por ID
router.put('/:id', async (req, res) => {
  const { rate } = req.body;

  try {
    if (rate === undefined || rate < 1 || rate > 5) {
      return res.status(400).json({ error: 'Calificación inválida' });
    }

    const producto = await Productos.findById(req.params.id);

    if (!producto) {
      return res.status(404).json({ error: 'Producto no encontrado' });
    }

    // Calcular nuevos valores
    console.log(`Nuevo rating calculado: ${producto.rating.rate}`);
    const totalVotes = producto.rating.count + 1;
    console.log(`Votos totales: ${totalVotes}`);
    const newRate = ((producto.rating.rate * producto.rating.count) + rate) / totalVotes;
    console.log(`Nuevo rating: ${rate}`);
    producto.rating.rate = parseFloat(newRate.toFixed(4));
    producto.rating.count = totalVotes;
    console.log(`Nuevo rating calculado: ${producto.rating.rate}`);

    const productoActualizado = await producto.save();

    res.json({
      id: productoActualizado._id,
      title: productoActualizado.title,
      rating: productoActualizado.rating,
    });
  } catch (err) {
    console.error(err);
    res.status(500).json({ error: 'Error al actualizar el rating' });
  }
});


export default router;


