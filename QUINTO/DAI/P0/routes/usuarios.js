import express from 'express';
import jwt from 'jsonwebtoken';
import Usuarios from '../model/usuarios.js'; // Importa el modelo de usuario
import dotenv from 'dotenv';
import logger from '../utils/logger.js';


dotenv.config(); // Cargar variables de entorno

const router = express.Router();

// Middleware para verificar si el usuario es Admin
const verificarAdmin = (req, res, next) => {
  if (!req.usuario.admin) {
    logger.warn(`Acceso denegado a admin para usuario: ${req.usuario?.username || "Desconocido"}`);
    return res.status(403).send('No tienes permisos para realizar esta acción');
  }
  next();
};

// Middleware para verificar la sesión
const verificarSesion = async (req, res, next) => {
  try {
    const token = req.cookies.access_token;
    if (!token) {
        req.usuario = null; // No hay sesión
        return next();
    }

    const decoded = jwt.verify(token, process.env.SECRET_KEY);
    const usuario = await Usuarios.findOne({ username: decoded.usuario });

    if (!usuario) {
        req.usuario = null; // Usuario no encontrado
        return next();
    }

    req.usuario = usuario; // Usuario autenticado disponible
    next();
  } catch (error) {
    req.usuario = null;
    next(); // Continuar aunque no haya sesión válida
  }
};

// Ruta para mostrar el formulario de login
router.get('/login', (req, res) => {
  logger.info('GET /login - Mostrar formulario de login');
  res.render('login.html');
});

router.post('/login', async (req, res) => {
  const { username, password } = req.body;
  try {
    const usuario = await Usuarios.findOne({ username });
    if (!usuario) return res.status(400).send('Usuario no encontrado');
    
    const match = await usuario.comparePassword(password);
    if (!match) return res.status(400).send('Contraseña incorrecta');

    const token = jwt.sign({ usuario: username }, process.env.SECRET_KEY, { expiresIn: '1h' });
    res.cookie('access_token', token, { httpOnly: true, secure: false });
    res.redirect('/bienvenida');
  } catch (error) {
    logger.error(`Error en el inicio de sesión: ${error.message}`);
    res.status(500).send('Error en el inicio de sesión');
  }
});

// Ruta para cerrar sesión
router.get('/logout', (req, res) => {
    const usuario = req.username;
    res.clearCookie('access_token');
    logger.info(`Usuario ${usuario} ha cerrado sesión.`);
    res.render("despedida.html", { usuario });
});

router.get('/bienvenida', verificarSesion, (req, res) => {
  const usuario = req.usuario ? req.usuario.username : "Invitado";
  res.render('bienvenida.html', { usuario });
});

export default router;
export { verificarSesion, verificarAdmin };
