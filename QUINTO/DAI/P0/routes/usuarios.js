import express from 'express';
import bcrypt from 'bcrypt';
import jwt from 'jsonwebtoken';
import Usuarios from '../model/usuarios.js';  // Importa el modelo de usuario
import dotenv from 'dotenv';
dotenv.config();  // Cargar variables de entorno

const router = express.Router();

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
      const token = jwt.sign({ usuario: username }, process.env.SECRET_KEY, { expiresIn: '1h' });

      // Establecer el token en una cookie
      res.cookie('access_token', token, { httpOnly: true, secure: false });
      
      // Redirigir al usuario a la página de bienvenida
      res.render('bienvenida.html', {usuario: username});
      
    } catch (error) {
      console.error('Error en el inicio de sesión:', error);
      res.status(500).send('Error en el inicio de sesión');
    }
  });

router.get('/logout', (req, res) => {
  const usuario = req.username 
  res.clearCookie('access_token').render("despedida.html", {usuario})
})

export default router;