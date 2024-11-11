// tienda.js
import express from "express";
import nunjucks from "nunjucks";
import connectDB from "./model/db.js";
import dotenv from "dotenv";
import session from 'express-session';

dotenv.config(); // Cargar las variables de entorno desde .env

connectDB(); // Conectar con la BD MongoDB usando Mongoose

const app = express();
const IN = process.env.IN || 'development';

nunjucks.configure('views', {
  autoescape: true,
  noCache: IN === 'development',
  watch: IN === 'development',
  express: app
});

app.set('view engine', 'html'); 
app.use(express.static('public')); // Archivos estáticos como imágenes desde la carpeta public

app.use(session({
  secret: 'secret',  
  resave: false,  // No volver a guardar la sesión si no se modifica
  saveUninitialized: true,  // Guardar una sesión nueva aunque no esté inicializada
  cookie: { secure: false }  // Asegúrate de usar true si estás en HTTPS
}));

app.use(express.urlencoded({ extended: true }));  // Para procesar formularios POST

// Rutas de la tienda
import TiendaRouter from "./routes/router_tienda.js";
app.use("/", TiendaRouter);

// El servidor escucha en un puerto definido en .env o en el 8000 por defecto
const PORT = process.env.PORT || 8000;
app.listen(PORT, () => {
  console.log(`Servidor ejecutándose en http://localhost:${PORT}`);
});
