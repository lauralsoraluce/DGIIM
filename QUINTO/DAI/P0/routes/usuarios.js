import express from 'express';
import bcrypt from 'bcrypt';
import jwt from 'jsonwebtoken';
import Usuarios from '../model/usuarios.js'; // Importa el modelo de usuario
import dotenv from 'dotenv';

dotenv.config(); // Cargar variables de entorno

const router = express.Router();

// Middleware para verificar si el usuario es Admin
const verificarAdmin = (req, res, next) => {
  if (!req.usuario.admin) {
    return res.status(403).send('No tienes permisos para realizar esta acción');
  }
  next();
};

// Middleware para verificar la sesión
const verificarSesion = async (req, res, next) => {
  try {
    const token = req.cookies.access_token;
    if (!token) {
      req.usuario = null; // Si no hay token, no bloqueamos el acceso
      return next(); // Continuamos con la solicitud
    }

    const decoded = jwt.verify(token, process.env.SECRET_KEY); // Aquí puede lanzar un error
    const usuario = await Usuarios.findOne({ username: decoded.usuario });

    if (!usuario) {
      req.usuario = null; // Si el usuario no existe, lo marcamos como no autenticado
      return next(); // Continuamos con la solicitud
    }

    if (!usuario.carrito) {
      usuario.carrito = [];
      await usuario.save(); // Guarda la inicialización del carrito
    }

    req.usuario = usuario; // Establecemos la información del usuario autenticado
    next();
  } catch (error) {
    if (error.name === 'TokenExpiredError') {
      req.usuario = null; // Si el token ha expirado, lo marcamos como no autenticado
      return next(); // Continuamos con la solicitud
    }
    console.error('Error en la autenticación:', error);
    req.usuario = null; // Si hay algún otro error, lo marcamos como no autenticado
    return next(); // Continuamos con la solicitud
  }
};

// Ruta para mostrar el formulario de login
router.get('/login', (req, res) => {
    res.render('login.html');
});

// Ruta POST para procesar el login
router.post('/login', async (req, res) => {
    const { username, password } = req.body;

    try {
        const usuario = await Usuarios.findOne({ username });

        if (!usuario) {
            return res.status(400).send('Usuario no encontrado');
        }

        // Comparar la contraseña proporcionada con la contraseña encriptada en la base de datos
        const match = await usuario.comparePassword(password);

        if (!match) {
            return res.status(400).send('Contraseña incorrecta');
        }

        // Generar el token JWT
        const token = jwt.sign({ usuario: username, admin: usuario.admin }, process.env.SECRET_KEY, { expiresIn: '1y' });

        // Establecer el token en una cookie
        res.cookie('access_token', token, { 
            httpOnly: true, 
            secure: process.env.NODE_ENV === 'production'  // Asegúrate de usar HTTPS en producción
        });

        // Redirigir al usuario a la página de bienvenida
        res.render('bienvenida.html', { usuario: username });
    } catch (error) {
        console.error('Error en el inicio de sesión:', error);
        res.status(500).send('Error en el inicio de sesión');
    }
});

// Ruta para cerrar sesión
router.get('/logout', (req, res) => {
    const usuario = req.username;
    res.clearCookie('access_token').render("despedida.html", { usuario });
});

export default router;
export { verificarSesion, verificarAdmin };
