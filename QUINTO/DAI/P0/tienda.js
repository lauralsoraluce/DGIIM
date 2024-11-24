import express from "express";
import nunjucks from "nunjucks";
import connectDB from "./model/db.js";
import dotenv from "dotenv";
import session from "express-session";
import cookieParser from "cookie-parser";
import jwt from "jsonwebtoken";
import logger from "./utils/logger.js";

// Cargar variables de entorno
dotenv.config();

const app = express();
const IN = process.env.NODE_ENV || "development";

// Conectar a la base de datos
connectDB();

// Configuración de Nunjucks
nunjucks.configure("views", {
  autoescape: true,
  noCache: IN === "development",
  watch: IN === "development",
  express: app,
});

// Middleware globales
app.set("view engine", "html");
app.use(express.static("public")); // Archivos estáticos
app.use(cookieParser());
app.use(express.urlencoded({ extended: true })); // Procesar formularios POST
app.use(express.json()); // Procesar solicitudes con cuerpo JSON (IMPORTANTE para PUT y POST)

app.use(
  session({
    secret: process.env.SESSION_SECRET || "default_secret", // Mejora: usa una variable de entorno para el secreto
    resave: false,
    saveUninitialized: true,
    cookie: { secure: IN === "production" }, // Seguro en producción con HTTPS
  })
);

// Middleware para logs de cada solicitud
app.use((req, res, next) => {
  logger.info(`${req.method} ${req.url}`);
  next();
});

// Middleware de autenticación
const autentificación = (req, res, next) => {
  const token = req.cookies.access_token;

  if (!token) {
    req.username = null;
    return next(); // Permitir continuar sin autenticación
  }

  try {
    const data = jwt.verify(token, process.env.SECRET_KEY);
    req.username = data.usuario; // Adjuntar el nombre de usuario
    next();
  } catch (error) {
    if (error.name === "TokenExpiredError") {
      logger.warn("El token ha expirado.");
      res.clearCookie("access_token"); // Limpiar el token expirado
      return res.status(403).send("El token ha expirado. Por favor, inicia sesión de nuevo.");
    }
    logger.error(`Error al verificar el token: ${error.message}`);
    res.status(403).send("Token inválido o no autorizado");
  }
};

app.use(autentificación);

// Ruta base para redirigir a la portada
app.get("/", (req, res) => {
  res.redirect("/portada"); // Redirige a /portada
});

// Importar y usar rutas
import TiendaRouter from "./routes/router_tienda.js";
import UsuariosRouter from "./routes/usuarios.js";
import RatingsRouter from "./routes/ratings.js";

app.use("/", TiendaRouter);
app.use("/", UsuariosRouter);
app.use("/api/ratings", RatingsRouter);

// Puerto del servidor
const PORT = process.env.PORT || 8000;

app.listen(PORT, () => {
  logger.info(`Servidor ejecutándose en http://localhost:${PORT}`);
}).on("error", (err) => {
  if (err.code === "EADDRINUSE") {
    logger.error(`El puerto ${PORT} ya está en uso. Intenta con otro puerto.`);
    process.exit(1);
  } else {
    logger.error(`Error al iniciar el servidor: ${err.message}`);
  }
});


