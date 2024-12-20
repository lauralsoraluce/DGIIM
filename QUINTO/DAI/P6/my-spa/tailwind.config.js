/** @type {import('tailwindcss').Config} */
export default {
  content: [
    "./index.html", // Incluye el archivo raíz HTML
    "./src/**/*.{js,ts,jsx,tsx}", // Incluye todos los archivos en src con estas extensiones
  ],
  theme: {
    extend: {}, // Aquí puedes extender el tema base de Tailwind si lo necesitas
  },
  plugins: [require('daisyui')],
}
