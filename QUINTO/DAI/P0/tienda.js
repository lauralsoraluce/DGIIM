import express from "express";
import nunjucks from "nunjucks";
import connectDB from "./model/db.js";
import dotenv from "dotenv";
import session from 'express-session';
import cookieParser from "cookie-parser";
import jwt from "jsonwebtoken";

dotenv.config(); // Cargar variables de entorno desde .env

const app = express();
const IN = process.env.IN || 'development';

// Conectar a la base de datos
connectDB();

// Configuración de Nunjucks
nunjucks.configure('views', {
  autoescape: true,
  noCache: IN === 'development',
  watch: IN === 'development',
  express: app
});

// Middleware globales
app.set('view engine', 'html');
app.use(express.static('public')); // Archivos estáticos
app.use(cookieParser());

app.use(express.urlencoded({ extended: true })); // Procesar formularios POST

app.use(session({
  secret: 'secret',  
  resave: false,  // No volver a guardar la sesión si no se modifica
  saveUninitialized: true,  // Guardar una sesión nueva aunque no esté inicializada
  cookie: { secure: false }  // Asegúrate de usar true si estás en HTTPS
}));

// Middleware de autenticación
const autentificación = (req, res, next) => {
  const token = req.cookies.access_token;

  if (!token) {
      req.username = null;  // Usuario no autenticado
      return next();  // Permite continuar sin bloquear
  }

  try {
      const data = jwt.verify(token, process.env.SECRET_KEY);
      req.username = data.usuario;  // Nombre de usuario en la solicitud
      next();
  } catch (error) {
      console.error('Error al verificar el token:', error.message);
      res.status(403).send('Token inválido o caducado');
  }
};
app.use(autentificación);

// Ruta base para redirigir a la portada
app.get('/', (req, res) => {
  res.redirect('/portada');  // Redirige a /portada cuando acceden a /
});

// Rutas
import TiendaRouter from "./routes/router_tienda.js";
import UsuariosRouter from "./routes/usuarios.js";

app.use("/", TiendaRouter);
app.use("/", UsuariosRouter);

// Puerto del servidor
const PORT = process.env.PORT || 8000;
app.listen(PORT, () => {
  console.log(`Servidor ejecutándose en http://localhost:${PORT}`);
});
