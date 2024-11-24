// model/productos.js
import mongoose from "mongoose";

const ProductosSchema = new mongoose.Schema({
  id: {
    type: Number,
    unique: true,
  },
  title: {
    type: String,
    required: true,
    validate: {
      validator: function(v) {
        return /^[A-Z]/.test(v); // Comienza con una mayúscula
      },
      message: props => `${props.value} debe comenzar con una mayúscula.`
    }
  },
  price: {
    type: Number,
    required: true,
    min: 0 // El precio debe ser positivo
  },
  description: { type: String },
  category: { type: String },
  image: { type: String },
  rating: {
    rate: { type: Number, default: null },
    count: { type: Number, default: 0 }
  }
});

const Productos = mongoose.model("productos", ProductosSchema);
export default Productos;

