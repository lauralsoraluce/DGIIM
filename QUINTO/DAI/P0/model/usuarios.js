import mongoose from 'mongoose';
import bcrypt from 'bcrypt';

// Definir el esquema de usuario
const usuarioSchema = new mongoose.Schema({
  username: {
    type: String,
    required: true,
    unique: true,  // El nombre de usuario debe ser único
  },
  password: {
    type: String,
    required: true,
  },
  email: {
    type: String,
    required: true,
    unique: true,  // El correo debe ser único
  },
  nombre: {
    type: String,
    required: true,
  },
}); 

// Método para encriptar la contraseña antes de guardar un usuario
usuarioSchema.pre('save', async function(next) {
  if (!this.isModified('password')) {
    return next();  // Si la contraseña no ha cambiado, sigue el proceso
  }

  try {
    const salt = await bcrypt.genSalt(10);  // Generar el salt
    this.password = await bcrypt.hash(this.password, salt);  // Encriptar la contraseña
    next();
  } catch (error) {
    next(error);  // En caso de error, pasarlo al siguiente middleware
  }
});

// Método para comparar la contraseña proporcionada con la almacenada en la base de datos
usuarioSchema.methods.comparePassword = async function(password) {
  return await bcrypt.compare(password, this.password);
};

// Crear el modelo de usuario a partir del esquema
const Usuarios = mongoose.model('Usuario', usuarioSchema);

export default Usuarios;
